#include "RenderTarget.hpp"

#include "NodesRenderer.hpp"

#include <FileUtils.hpp>
#include <OpaqueRendering.hpp>
#include <TransparentRendering.hpp>

#include <Buffer/StagingBuffer.hpp>
#include <Buffer/UniformBuffer.hpp>

#include <Utils/Transform.hpp>

namespace vkapp
{
	RenderTarget::RenderTarget( renderer::Device const & device
		, renderer::UIVec2 const & size
		, common::Scene && scene
		, common::ImagePtrArray && images )
		: common::RenderTarget{ device, size, std::move( scene ), std::move( images ) }
		, m_sceneUbo{ renderer::makeUniformBuffer< common::SceneData >( device
			, 1u
			, renderer::BufferTarget::eTransferDst
			, renderer::MemoryPropertyFlag::eDeviceLocal ) }
		, m_objectUbo{ renderer::makeUniformBuffer< common::ObjectData >( device
			, 1u
			, renderer::BufferTarget::eTransferDst
			, renderer::MemoryPropertyFlag::eDeviceLocal ) }
		, m_lightsUbo{ renderer::makeUniformBuffer< common::LightsData >( device
			, 1u
			, renderer::BufferTarget::eTransferDst
			, renderer::MemoryPropertyFlag::eDeviceLocal ) }
	{
		doInitialise();
		doUpdateMatrixUbo( size );
		doInitialiseLights();
	}

	void RenderTarget::doUpdate( std::chrono::microseconds const & duration )
	{
		static renderer::Mat4 const originalTranslate = []()
		{
			renderer::Mat4 result;
			result = utils::translate( result, { 0, 0, -5 } );
			return result;
		}();
		m_rotate = utils::rotate( m_rotate
			, float( utils::DegreeToRadian ) * ( duration.count() / 20000.0f )
			, { 0, 1, 0 } );
		m_objectUbo->getData( 0 ).mtxModel = originalTranslate * m_rotate;
		m_stagingBuffer->uploadUniformData( *m_updateCommandBuffer
			, m_objectUbo->getDatas()
			, *m_objectUbo
			, renderer::PipelineStageFlag::eVertexShader );
	}

	void RenderTarget::doResize( renderer::UIVec2 const & size )
	{
		doUpdateMatrixUbo( size );
	}

	common::OpaqueRenderingPtr RenderTarget::doCreateOpaqueRendering( renderer::Device const & device
		, renderer::StagingBuffer & stagingBuffer
		, renderer::TextureViewCRefArray const & views
		, common::Scene const & scene
		, common::TextureNodePtrArray const & textureNodes )
	{
		return std::make_unique< common::OpaqueRendering >( std::make_unique< NodesRenderer >( device
				, common::getPath( common::getExecutableDirectory() ) / "share" / AppName / "Shaders" / "offscreen.frag"
				, common::getFormats( views )
				, true
				, true
				, *m_sceneUbo
				, *m_objectUbo
				, *m_lightsUbo )
			, scene
			, stagingBuffer
			, views
			, textureNodes );
	}

	common::TransparentRenderingPtr RenderTarget::doCreateTransparentRendering( renderer::Device const & device
		, renderer::StagingBuffer & stagingBuffer
		, renderer::TextureViewCRefArray const & views
		, common::Scene const & scene
		, common::TextureNodePtrArray const & textureNodes )
	{
		return std::make_unique< common::TransparentRendering >( std::make_unique< NodesRenderer >( device
				, common::getPath( common::getExecutableDirectory() ) / "share" / AppName / "Shaders" / "offscreen.frag"
				, common::getFormats( views )
				, false
				, false
				, *m_sceneUbo
				, *m_objectUbo
				, *m_lightsUbo )
			, scene
			, stagingBuffer
			, views
			, textureNodes );
	}

	void RenderTarget::doUpdateMatrixUbo( renderer::UIVec2 const & size )
	{
#if 0
		float halfWidth = static_cast< float >( size[0] ) * 0.5f;
		float halfHeight = static_cast< float >( size[1] ) * 0.5f;
		float wRatio = 1.0f;
		float hRatio = 1.0f;

		if ( halfHeight > halfWidth )
		{
			hRatio = halfHeight / halfWidth;
		}
		else
		{
			wRatio = halfWidth / halfHeight;
		}

		m_sceneUbo->getData( 0u ).mtxProjection = m_device->ortho( -2.0f * wRatio
			, 2.0f * wRatio
			, -2.0f * hRatio
			, 2.0f * hRatio
			, 0.0f
			, 10.0f );
#else
		auto width = float( size[0] );
		auto height = float( size[1] );
		m_sceneUbo->getData( 0u ).mtxProjection = m_device.perspective( utils::toRadians( 90.0_degrees )
			, width / height
			, 0.01f
			, 100.0f );
#endif
		m_stagingBuffer->uploadUniformData( *m_updateCommandBuffer
			, m_sceneUbo->getDatas()
			, *m_sceneUbo
			, renderer::PipelineStageFlag::eVertexShader );
	}

	void RenderTarget::doInitialiseLights()
	{
		auto & lights = m_lightsUbo->getData( 0u );
		lights.lightsCount[0] = 1;
		common::DirectionalLight directional
		{
			{
				renderer::Vec4{ 1, 1, 1, 1 },
				renderer::Vec4{ 0.75, 1.0, 0.0, 0.0 }
			},
			renderer::Vec4{ 1.0, -0.25, -1.0, 0.0 }
		};
		lights.directionalLights[0] = directional;

		m_stagingBuffer->uploadUniformData( *m_updateCommandBuffer
			, m_lightsUbo->getDatas()
			, *m_lightsUbo
			, renderer::PipelineStageFlag::eFragmentShader );
	}
}
