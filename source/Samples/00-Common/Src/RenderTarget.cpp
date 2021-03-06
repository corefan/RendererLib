#include "RenderTarget.hpp"

#include "OpaqueRendering.hpp"
#include "TransparentRendering.hpp"

#include <Buffer/StagingBuffer.hpp>
#include <Buffer/UniformBuffer.hpp>
#include <Command/Queue.hpp>
#include <Descriptor/DescriptorSet.hpp>
#include <Descriptor/DescriptorSetLayout.hpp>
#include <Descriptor/DescriptorSetPool.hpp>
#include <Image/Texture.hpp>
#include <Image/TextureView.hpp>
#include <Pipeline/PipelineLayout.hpp>
#include <Pipeline/Pipeline.hpp>
#include <Pipeline/VertexLayout.hpp>
#include <RenderPass/FrameBuffer.hpp>
#include <RenderPass/RenderPass.hpp>
#include <RenderPass/RenderSubpass.hpp>
#include <RenderPass/RenderSubpassState.hpp>
#include <Shader/ShaderProgram.hpp>
#include <Sync/ImageMemoryBarrier.hpp>

#include <Utils/Transform.hpp>

#include <chrono>

namespace common
{
	namespace
	{
		static renderer::PixelFormat const DepthFormat = renderer::PixelFormat::eD24S8;
		static renderer::PixelFormat const ColourFormat = renderer::PixelFormat::eR8G8B8A8;
	}

	RenderTarget::RenderTarget( renderer::Device const & device
		, renderer::UIVec2 const & size
		, Scene && scene
		, ImagePtrArray && images )
		: m_device{ device }
		, m_scene{ std::move( scene ) }
		, m_images{ std::move( images ) }
		, m_size{ size }
	{
		try
		{
			doCreateStagingBuffer();
			std::cout << "Staging buffer created." << std::endl;
			doCreateTextures();
			std::cout << "Textures created." << std::endl;
			doCreateRenderPass();
			std::cout << "Offscreen render pass created." << std::endl;
		}
		catch ( std::exception & )
		{
			doCleanup();
			throw;
		}

	}

	RenderTarget::~RenderTarget()
	{
		doCleanup();
	}

	void RenderTarget::resize( renderer::UIVec2 const & size )
	{
		if ( size != m_size )
		{
			m_size = size;
			doUpdateRenderViews();
			doResize( size );
			m_opaque->update( *this );
			m_transparent->update( *this );
		}
	}

	void RenderTarget::update( std::chrono::microseconds const & duration )
	{
		doUpdate( duration );
	}

	bool RenderTarget::draw( std::chrono::microseconds & gpu )
	{
		std::chrono::nanoseconds opaque;
		std::chrono::nanoseconds transparent;
		auto result = m_opaque->draw( opaque );
		result &= m_transparent->draw( transparent );
		gpu = std::chrono::duration_cast< std::chrono::microseconds >( opaque + transparent );
		return result;
	}

	void RenderTarget::doInitialise()
	{
		m_opaque = doCreateOpaqueRendering( m_device
			, *m_stagingBuffer
			, { *m_depthView, *m_colourView }
			, m_scene
			, m_textureNodes );
		m_transparent = doCreateTransparentRendering( m_device
			, *m_stagingBuffer
			, { *m_depthView, *m_colourView }
			, m_scene
			, m_textureNodes );
	}

	void RenderTarget::doCleanup()
	{
		m_updateCommandBuffer.reset();

		m_stagingBuffer.reset();

		m_transparent.reset();
		m_opaque.reset();
		m_depthView.reset();
		m_depth.reset();
		m_colourView.reset();
		m_colour.reset();

		m_images.clear();
		m_textureNodes.clear();
	}

	void RenderTarget::doCreateStagingBuffer()
	{
		m_updateCommandBuffer = m_device.getGraphicsCommandPool().createCommandBuffer();
		m_stagingBuffer = std::make_unique< renderer::StagingBuffer >( m_device
			, 0u
			, 200u * 1024u * 1024u );
	}

	void RenderTarget::doCreateTextures()
	{
		for ( auto & image : m_images )
		{
			common::TextureNodePtr textureNode = std::make_shared< common::TextureNode >();
			textureNode->image = image;
			textureNode->texture = m_device.createTexture();
			textureNode->texture->setImage( image->format
				, { image->size[0], image->size[1] }
				, 4u
				, renderer::ImageUsageFlag::eTransferSrc | renderer::ImageUsageFlag::eTransferDst | renderer::ImageUsageFlag::eSampled );
			textureNode->view = textureNode->texture->createView( textureNode->texture->getType()
				, textureNode->texture->getFormat()
				, 0u
				, 4u );
			auto view = textureNode->texture->createView( textureNode->texture->getType()
				, textureNode->texture->getFormat() );
			m_stagingBuffer->uploadTextureData( *m_updateCommandBuffer
				, image->data
				, *view );
			textureNode->texture->generateMipmaps();
			m_textureNodes.emplace_back( textureNode );
		}
	}

	void RenderTarget::doCreateRenderPass()
	{
		doUpdateRenderViews();
	}

	void RenderTarget::doUpdateRenderViews()
	{
		m_colourView.reset();
		m_colour = m_device.createTexture();
		m_colour->setImage( ColourFormat
			, m_size
			, renderer::ImageUsageFlag::eColourAttachment | renderer::ImageUsageFlag::eSampled );
		m_colourView = m_colour->createView( m_colour->getType()
			, m_colour->getFormat() );

		m_depthView.reset();
		m_depth = m_device.createTexture();
		m_depth->setImage( DepthFormat
			, m_size
			, renderer::ImageUsageFlag::eDepthStencilAttachment );
		m_depthView = m_depth->createView( m_depth->getType()
			, m_depth->getFormat() );
	}
}
