/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#include "Core/GlDevice.hpp"

#include "Buffer/GlBuffer.hpp"
#include "Buffer/GlBufferView.hpp"
#include "Buffer/GlGeometryBuffers.hpp"
#include "Buffer/GlUniformBuffer.hpp"
#include "Command/GlCommandPool.hpp"
#include "Command/GlQueue.hpp"
#include "Core/GlConnection.hpp"
#include "Core/GlContext.hpp"
#include "Core/GlDummyIndexBuffer.hpp"
#include "Core/GlRenderer.hpp"
#include "Core/GlSwapChain.hpp"
#include "Descriptor/GlDescriptorSetLayout.hpp"
#include "Image/GlSampler.hpp"
#include "Image/GlTexture.hpp"
#include "Image/GlTextureView.hpp"
#include "Miscellaneous/GlQueryPool.hpp"
#include "Pipeline/GlPipelineLayout.hpp"
#include "RenderPass/GlRenderPass.hpp"
#include "RenderPass/GlRenderSubpass.hpp"
#include "Shader/GlShaderModule.hpp"
#include "Sync/GlFence.hpp"
#include "Sync/GlSemaphore.hpp"

#include <iostream>

namespace gl_renderer
{
	namespace
	{
		void doApply( renderer::ColourBlendState const & state )
		{
			if ( state.isLogicOpEnabled() )
			{
				glLogCall( gl::LogicOp, convert( state.getLogicOp() ) );
			}

			auto & blendConstants = state.getBlendConstants();
			glLogCall( gl::BlendColor
				, blendConstants[0]
				, blendConstants[1]
				, blendConstants[2]
				, blendConstants[3] );

			bool blend = false;
			GLuint buf = 0u;

			for ( auto & blendState : state )
			{
				if ( blendState.isBlendEnabled() )
				{
					blend = true;
					glLogCall( gl::BlendEquationSeparatei
						, buf
						, convert( blendState.getColourBlendOp() )
						, convert( blendState.getAlphaBlendOp() ) );
					glLogCall( gl::BlendFuncSeparatei
						, buf
						, convert( blendState.getSrcColourBlendFactor() )
						, convert( blendState.getDstColourBlendFactor() )
						, convert( blendState.getSrcAlphaBlendFactor() )
						, convert( blendState.getDstAlphaBlendFactor() ) );
				}

				++buf;
			}

			if ( blend )
			{
				glLogCall( gl::Enable, GL_BLEND );
			}
			else
			{
				glLogCall( gl::Disable, GL_BLEND );
			}
		}

		void doApply( renderer::RasterisationState const & state )
		{
			if ( state.getCullMode() != renderer::CullModeFlag::eNone )
			{
				glLogCall( gl::Enable, GL_CULL_FACE );
				glLogCall( gl::CullFace, convert( state.getCullMode() ) );
				glLogCall( gl::FrontFace, convert( state.getFrontFace() ) );
			}
			else
			{
				glLogCall( gl::Disable, GL_CULL_FACE );
			}

			glLogCall( gl::PolygonMode
				, GL_CULL_MODE_FRONT_AND_BACK
				, convert( state.getPolygonMode() ) );

			if ( state.isDepthBiasEnabled() )
			{
				switch ( state.getPolygonMode() )
				{
				case renderer::PolygonMode::eFill:
					glLogCall( gl::Enable, GL_POLYGON_OFFSET_FILL );
					break;

				case renderer::PolygonMode::eLine:
					glLogCall( gl::Enable, GL_POLYGON_OFFSET_LINE );
					break;

				case renderer::PolygonMode::ePoint:
					glLogCall( gl::Enable, GL_POLYGON_OFFSET_POINT );
					break;
				}

				glLogCall( gl::PolygonOffsetClampEXT, state.getDepthBiasConstantFactor()
					, state.getDepthBiasSlopeFactor()
					, state.getDepthBiasClamp() );
			}
			else
			{
				switch ( state.getPolygonMode() )
				{
				case renderer::PolygonMode::eFill:
					glLogCall( gl::Disable, GL_POLYGON_OFFSET_FILL );
					break;

				case renderer::PolygonMode::eLine:
					glLogCall( gl::Disable, GL_POLYGON_OFFSET_LINE );
					break;

				case renderer::PolygonMode::ePoint:
					glLogCall( gl::Disable, GL_POLYGON_OFFSET_POINT );
					break;
				}
			}

			if ( state.isDepthClampEnabled() )
			{
				glLogCall( gl::Enable, GL_DEPTH_CLAMP );
			}
			else
			{
				glLogCall( gl::Disable, GL_DEPTH_CLAMP );
			}

			if ( state.isRasteriserDiscardEnabled() )
			{
				glLogCall( gl::Enable, GL_RASTERIZER_DISCARD );
			}
			else
			{
				glLogCall( gl::Disable, GL_RASTERIZER_DISCARD );
			}

			glLogCall( gl::LineWidth, state.getLineWidth() );
		}

		void doApply( renderer::MultisampleState const & state )
		{
			if ( state.getRasterisationSamples() != renderer::SampleCountFlag::e1 )
			{
				glLogCall( gl::Enable, GL_MULTISAMPLE );

				if ( state.isAlphaToCoverageEnabled() )
				{
					glLogCall( gl::Enable, GL_SAMPLE_ALPHA_TO_COVERAGE );
				}
				else
				{
					glLogCall( gl::Disable, GL_SAMPLE_ALPHA_TO_COVERAGE );
				}

				if ( state.isAlphaToOneEnabled() )
				{
					glLogCall( gl::Enable, GL_SAMPLE_ALPHA_TO_ONE );
				}
				else
				{
					glLogCall( gl::Disable, GL_SAMPLE_ALPHA_TO_ONE );
				}
			}
			else
			{
				glLogCall( gl::Disable, GL_MULTISAMPLE );
			}
		}

		void doApply( renderer::DepthStencilState const & state )
		{
			if ( state.isDepthWriteEnabled() )
			{
				glLogCall( gl::DepthMask, GL_TRUE );
			}
			else
			{
				glLogCall( gl::DepthMask, GL_FALSE );
			}

			if ( state.isDepthTestEnabled() )
			{
				glLogCall( gl::Enable, GL_DEPTH_TEST );
				glLogCall( gl::DepthFunc, convert( state.getDepthCompareOp() ) );
			}
			else
			{
				glLogCall( gl::Disable, GL_DEPTH_TEST );
			}

			if ( state.isStencilTestEnabled() )
			{
				glLogCall( gl::Enable, GL_STENCIL_TEST );

				glLogCall( gl::StencilMaskSeparate
					, GL_CULL_MODE_BACK
					, state.getBackStencilOp().getWriteMask() );
				glLogCall( gl::StencilFuncSeparate
					, GL_CULL_MODE_BACK
					, convert( state.getBackStencilOp().getCompareOp() )
					, state.getBackStencilOp().getReference()
					, state.getBackStencilOp().getCompareMask() );
				glLogCall( gl::StencilOpSeparate
					, GL_CULL_MODE_BACK
					, convert( state.getBackStencilOp().getFailOp() )
					, convert( state.getBackStencilOp().getDepthFailOp() )
					, convert( state.getBackStencilOp().getPassOp() ) );
				glLogCall( gl::StencilMaskSeparate
					, GL_CULL_MODE_FRONT
					, state.getFrontStencilOp().getWriteMask() );
				glLogCall( gl::StencilFuncSeparate
					, GL_CULL_MODE_FRONT
					, convert( state.getFrontStencilOp().getCompareOp() )
					, state.getFrontStencilOp().getReference()
					, state.getFrontStencilOp().getCompareMask() );
				glLogCall( gl::StencilOpSeparate
					, GL_CULL_MODE_FRONT
					, convert( state.getFrontStencilOp().getFailOp() )
					, convert( state.getFrontStencilOp().getDepthFailOp() )
					, convert( state.getFrontStencilOp().getPassOp() ) );
			}
			else
			{
				glLogCall( gl::Disable, GL_STENCIL_TEST );
			}

			if ( state.isDepthBoundsTestEnabled() )
			{
				glLogCall( gl::Enable, GL_DEPTH_CLAMP );
				glLogCall( gl::DepthRange, state.getMinDepthBounds(), state.getMaxDepthBounds() );
			}
			else
			{
				glLogCall( gl::Disable, GL_DEPTH_CLAMP );
			}
		}

		void doApply( renderer::TessellationState const & state )
		{
			if ( state.getControlPoints() )
			{
				glLogCall( gl::PatchParameteri, GL_PATCH_VERTICES, int( state.getControlPoints() ) );
			}
		}

		void doApply( renderer::InputAssemblyState const & state )
		{
			if ( state.getTopology() == renderer::PrimitiveTopology::ePointList )
			{
				glLogCall( gl::Enable, GL_PROGRAM_POINT_SIZE );
			}
			else
			{
				glLogCall( gl::Disable, GL_PROGRAM_POINT_SIZE );
			}

			if ( state.isPrimitiveRestartEnabled() )
			{
				glLogCall( gl::Enable, GL_PRIMITIVE_RESTART );
			}
			else
			{
				glLogCall( gl::Disable, GL_PRIMITIVE_RESTART );
			}
		}
	}

	Device::Device( renderer::Renderer const & renderer
		, PhysicalDevice const & gpu
		, renderer::ConnectionPtr && connection )
		: renderer::Device{ renderer, gpu, *connection }
		, m_context{ Context::create( gpu, std::move( connection ) ) }
		, m_rsState{ 1.0f }
	{
		enable();
		glLogCall( gl::ClipControl, GL_UPPER_LEFT, GL_ZERO_TO_ONE );
		initialiseDebugFunctions();
		disable();

		m_timestampPeriod = 1;
		m_presentQueue = std::make_unique< Queue >();
		m_computeQueue = std::make_unique< Queue >();
		m_graphicsQueue = std::make_unique< Queue >();
		m_presentCommandPool = std::make_unique< CommandPool >( *this, 0u );
		m_computeCommandPool = std::make_unique< CommandPool >( *this, 0u );
		m_graphicsCommandPool = std::make_unique< CommandPool >( *this, 0u );

		enable();
		doApply( m_cbState );
		doApply( m_dsState );
		doApply( m_msState );
		doApply( m_rsState );
		doApply( m_tsState );
		doApply( m_iaState );
		m_dummyIndexed.indexBuffer = renderer::makeBuffer< uint32_t >( *this
			, sizeof( dummyIndex ) / sizeof( dummyIndex[0] )
			, renderer::BufferTarget::eIndexBuffer
			, renderer::MemoryPropertyFlag::eHostVisible | renderer::MemoryPropertyFlag::eHostCoherent );

		if ( auto * buffer = m_dummyIndexed.indexBuffer->lock( 0u
			, sizeof( dummyIndex ) / sizeof( dummyIndex[0] )
			, renderer::MemoryMapFlag::eWrite ) )
		{
			std::memcpy( buffer, dummyIndex, sizeof( dummyIndex ) );
			m_dummyIndexed.indexBuffer->unlock();
		}

		auto & indexBuffer = static_cast< Buffer const & >( m_dummyIndexed.indexBuffer->getBuffer() );
		m_dummyIndexed.geometryBuffers = std::make_unique< GeometryBuffers >( VboBindings{}
			, BufferObjectBinding{ indexBuffer.getBuffer(), 0u, &indexBuffer }
			, renderer::VertexInputState{}
			, renderer::IndexType::eUInt32 );
		m_dummyIndexed.geometryBuffers->initialise();

		gl::GenFramebuffers( 2, m_blitFbos );
		disable();
	}

	Device::~Device()
	{
		enable();
		gl::DeleteFramebuffers( 2, m_blitFbos );
		m_dummyIndexed.geometryBuffers.reset();
		m_dummyIndexed.indexBuffer.reset();
		disable();
	}

	renderer::RenderPassPtr Device::createRenderPass( renderer::RenderPassAttachmentArray const & attaches
		, renderer::RenderSubpassPtrArray && subpasses
		, renderer::RenderSubpassState const & initialState
		, renderer::RenderSubpassState const & finalState )const
	{
		return std::make_unique< RenderPass >( *this
			, attaches
			, std::move( subpasses )
			, initialState
			, finalState );
	}

	renderer::RenderSubpassPtr Device::createRenderSubpass( renderer::PipelineBindPoint pipelineBindPoint
		, renderer::RenderSubpassState const & state
		, renderer::RenderSubpassAttachmentArray const & inputAttaches
		, renderer::RenderSubpassAttachmentArray const & colourAttaches
		, renderer::RenderSubpassAttachmentArray const & resolveAttaches
		, renderer::RenderSubpassAttachment const * depthAttach
		, renderer::UInt32Array const & preserveAttaches )const
	{
		return std::make_unique< RenderSubpass >( *this
			, pipelineBindPoint
			, state
			, inputAttaches
			, colourAttaches
			, resolveAttaches
			, depthAttach
			, preserveAttaches );
	}

	renderer::PipelineLayoutPtr Device::createPipelineLayout( renderer::DescriptorSetLayoutCRefArray const & setLayouts
		, renderer::PushConstantRangeCRefArray const & pushConstantRanges )const
	{
		return std::make_unique< PipelineLayout >( *this
			, setLayouts
			, pushConstantRanges );
	}

	renderer::DescriptorSetLayoutPtr Device::createDescriptorSetLayout( renderer::DescriptorSetLayoutBindingArray && bindings )const
	{
		return std::make_unique< DescriptorSetLayout >( *this, std::move( bindings ) );
	}

	renderer::TexturePtr Device::createTexture( renderer::ImageLayout initialLayout )const
	{
		return std::make_shared< Texture >( *this );
	}

	renderer::SamplerPtr Device::createSampler( renderer::WrapMode wrapS
		, renderer::WrapMode wrapT
		, renderer::WrapMode wrapR
		, renderer::Filter minFilter
		, renderer::Filter magFilter
		, renderer::MipmapMode mipFilter
		, float minLod
		, float maxLod
		, float lodBias
		, renderer::BorderColour borderColour
		, float maxAnisotropy
		, renderer::CompareOp compareOp )const
	{
		return std::make_unique< Sampler >( *this
			, wrapS
			, wrapT
			, wrapR
			, minFilter
			, magFilter
			, mipFilter
			, minLod
			, maxLod
			, lodBias
			, borderColour
			, maxAnisotropy
			, compareOp );
	}

	renderer::BufferBasePtr Device::createBuffer( uint32_t size
		, renderer::BufferTargets target
		, renderer::MemoryPropertyFlags memoryFlags )const
	{
		return std::make_unique< Buffer >( *this
			, size
			, target
			, memoryFlags );
	}

	renderer::BufferViewPtr Device::createBufferView( renderer::BufferBase const & buffer
		, renderer::PixelFormat format
		, uint32_t offset
		, uint32_t range )const
	{
		return std::make_unique< BufferView >( *this
			, static_cast< Buffer const & >( buffer )
			, format
			, offset
			, range );
	}

	renderer::UniformBufferBasePtr Device::createUniformBuffer( uint32_t count
		, uint32_t size
		, renderer::BufferTargets target
		, renderer::MemoryPropertyFlags memoryFlags )const
	{
		return std::make_unique< UniformBuffer >( *this
			, count
			, size
			, target
			, memoryFlags );
	}

	renderer::SwapChainPtr Device::createSwapChain( renderer::UIVec2 const & size )const
	{
		renderer::SwapChainPtr result;

		try
		{
			result = std::make_unique< SwapChain >( *this, size );
		}
		catch ( std::exception & exc )
		{
			std::cerr << "Could not create the swap chain:\n" << exc.what() << std::endl;
		}
		catch ( ... )
		{
			std::cerr << "Could not create the swap chain:\nUnknown error" << std::endl;
		}

		return result;
	}

	renderer::SemaphorePtr Device::createSemaphore()const
	{
		return std::make_unique< Semaphore >( *this );
	}

	renderer::FencePtr Device::createFence( renderer::FenceCreateFlags flags )const
	{
		return std::make_unique< Fence >( *this, flags );
	}

	renderer::CommandPoolPtr Device::createCommandPool( uint32_t queueFamilyIndex
		, renderer::CommandPoolCreateFlags const & flags )const
	{
		return std::make_unique< CommandPool >( *this
			, queueFamilyIndex
			, flags );
	}

	renderer::ShaderModulePtr Device::createShaderModule( renderer::ShaderStageFlag stage )const
	{
		return std::make_unique< ShaderModule >( *this, stage );
	}

	renderer::QueryPoolPtr Device::createQueryPool( renderer::QueryType type
		, uint32_t count
		, renderer::QueryPipelineStatisticFlags pipelineStatistics )const
	{
		return std::make_unique< QueryPool >( *this
			, type
			, count
			, pipelineStatistics );
	}

	void Device::waitIdle()const
	{
		glLogCall( gl::Finish );
	}

	renderer::Mat4 Device::frustum( float left
		, float right
		, float bottom
		, float top
		, float zNear
		, float zFar )const
	{
		renderer::Mat4 result( float( 0 ) );
		result[0][0] = ( float( 2 ) * zNear ) / ( right - left );
		result[1][1] = ( float( 2 ) * zNear ) / ( top - bottom );
		result[2][0] = ( right + left ) / ( right - left );
		result[2][1] = ( top + bottom ) / ( top - bottom );
		result[2][3] = float( -1 );
		result[2][2] = zFar / ( zNear - zFar );
		result[3][2] = -( zFar * zNear ) / ( zFar - zNear );

		return result;
	}

	renderer::Mat4 Device::perspective( renderer::Angle fovy
		, float aspect
		, float zNear
		, float zFar )const
	{
		float const tanHalfFovy = tan( float( fovy ) / float( 2 ) );

		renderer::Mat4 result( float( 0 ) );
		result[0][0] = float( 1 ) / ( aspect * tanHalfFovy );
		result[1][1] = float( 1 ) / ( tanHalfFovy );
		result[2][3] = -float( 1 );
		result[2][2] = zFar / ( zNear - zFar );
		result[3][2] = -( zFar * zNear ) / ( zFar - zNear );

		return result;
	}

	renderer::Mat4 Device::ortho( float left
		, float right
		, float bottom
		, float top
		, float zNear
		, float zFar )const
	{
		renderer::Mat4 result{ 1 };
		result[0][0] = float( 2 ) / ( right - left );
		result[1][1] = float( 2 ) / ( top - bottom );
		result[3][0] = -( right + left ) / ( right - left );
		result[3][1] = -( top + bottom ) / ( top - bottom );
		result[2][2] = -float( 1 ) / ( zFar - zNear );
		result[3][2] = -zNear / ( zFar - zNear );

		return result;
	}

	void Device::swapBuffers()const
	{
		m_context->swapBuffers();
	}

	void Device::doEnable()const
	{
		m_context->setCurrent();
	}

	void Device::doDisable()const
	{
		m_context->endCurrent();
	}
}
