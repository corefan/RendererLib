/*
This file belongs to RendererLib.
See LICENSE file in root folder
*/
#pragma once

#include "Core/VkConnection.hpp"

#include <Core/Device.hpp>

namespace vk_renderer
{
	/**
	*\brief
	*	Classe contenant les informations liées au GPU logique.
	*/
	class Device
		: public renderer::Device
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*\param[in] vk_renderer
		*	L'instance de Renderer.
		*\param[in] connection
		*	La connection à l'application.
		*/
		Device( Renderer const & renderer
			, renderer::ConnectionPtr && connection );
		/**
		*\brief
		*	Destructeur.
		*/
		~Device();
		/**
		*\copydoc	renderer::Device::createRenderPass
		*/
		renderer::RenderPassPtr createRenderPass( renderer::RenderPassAttachmentArray const & attaches
			, renderer::RenderSubpassPtrArray && subpasses
			, renderer::RenderSubpassState const & initialState
			, renderer::RenderSubpassState const & finalState )const override;
		/**
		*\copydoc	renderer::Device::createRenderSubpass
		*/
		renderer::RenderSubpassPtr createRenderSubpass( renderer::PipelineBindPoint pipelineBindPoint
			, renderer::RenderSubpassState const & state
			, renderer::RenderSubpassAttachmentArray const & inputAttaches
			, renderer::RenderSubpassAttachmentArray const & colourAttaches
			, renderer::RenderSubpassAttachmentArray const & resolveAttaches
			, renderer::RenderSubpassAttachment const * depthAttach
			, renderer::UInt32Array const & preserveAttaches )const override;
		/**
		*\copydoc	renderer::Device::createPipelineLayout
		*/
		renderer::PipelineLayoutPtr createPipelineLayout( renderer::DescriptorSetLayoutCRefArray const & setLayouts
			, renderer::PushConstantRangeCRefArray const & pushConstantRanges )const override;
		/**
		*\copydoc	renderer::Device::createDescriptorSetLayout
		*/
		renderer::DescriptorSetLayoutPtr createDescriptorSetLayout( renderer::DescriptorSetLayoutBindingArray && bindings )const override;
		/**
		*\copydoc	renderer::Device::createTexture
		*/
		renderer::TexturePtr createTexture( renderer::ImageLayout initialLayout )const override;
		/**
		*\copydoc	renderer::Device::createSampler
		*/
		renderer::SamplerPtr createSampler( renderer::WrapMode wrapS
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
			, renderer::CompareOp compareOp )const override;
		/**
		*\copydoc	renderer::Device::createBuffer
		*/
		renderer::BufferBasePtr createBuffer( uint32_t size
			, renderer::BufferTargets target
			, renderer::MemoryPropertyFlags memoryFlags )const override;
		/**
		*\copydoc	renderer::Device::createBufferView
		*/
		renderer::BufferViewPtr createBufferView( renderer::BufferBase const & buffer
			, renderer::PixelFormat format
			, uint32_t offset
			, uint32_t range )const override;
		/**
		*\copydoc	renderer::Device::createUniformBuffer
		*/
		renderer::UniformBufferBasePtr createUniformBuffer( uint32_t count
			, uint32_t size
			, renderer::BufferTargets target
			, renderer::MemoryPropertyFlags memoryFlags )const override;
		/**
		*\copydoc	renderer::Device::createSwapChain
		*/
		renderer::SwapChainPtr createSwapChain( renderer::UIVec2 const & size )const override;
		/**
		*\copydoc	renderer::Device::createSemaphore
		*/
		renderer::SemaphorePtr createSemaphore()const override;
		/**
		*\copydoc	renderer::Device::createFence
		*/
		renderer::FencePtr createFence( renderer::FenceCreateFlags flags )const override;
		/**
		*\copydoc	renderer::Device::createCommandPool
		*/
		renderer::CommandPoolPtr createCommandPool( uint32_t queueFamilyIndex
			, renderer::CommandPoolCreateFlags const & flags )const override;
		/**
		*\copydoc	renderer::Device::createShaderProgram
		*/
		virtual renderer::ShaderModulePtr createShaderModule( renderer::ShaderStageFlag stage )const override;
		/**
		*\copydoc	renderer::Device::createQueryPool
		*/
		renderer::QueryPoolPtr createQueryPool( renderer::QueryType type
			, uint32_t count
			, renderer::QueryPipelineStatisticFlags pipelineStatistics )const override;
		/**
		*\brief
		*	Attend que le périphérique soit inactif.
		*/
		void waitIdle()const override;
		/**
		*\copydoc	renderer::Device::frustum
		*/
		renderer::Mat4 frustum( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const override;
		/**
		*\copydoc	renderer::Device::perspective
		*/
		renderer::Mat4 perspective( renderer::Angle fovy
			, float aspect
			, float zNear
			, float zFar )const override;
		/**
		*\copydoc	renderer::Device::ortho
		*/
		renderer::Mat4 ortho( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const override;
		/**
		*\~french
		*\brief
		*	Récupère les propriétés mémoire requises pour le tampon donné.
		*\param[in] buffer
		*	Le tampon.
		*return
		*	Les propriétés mémoire.
		*\~english
		*\brief
		*	Retrieves the memory requirements for given buffer.
		*\param[in] buffer
		*	The buffer.
		*return
		*	The memory requirements.
		*/
		VkMemoryRequirements getBufferMemoryRequirements( VkBuffer buffer )const;
		/**
		*\~french
		*\brief
		*	Récupère les propriétés mémoire requises pour le tampon donné.
		*\param[in] image
		*	L'image.
		*return
		*	Les propriétés mémoire.
		*\~english
		*\brief
		*	Retrieves the memory requirements for given buffer.
		*\param[in] image
		*	The image.
		*return
		*	The memory requirements.
		*/
		VkMemoryRequirements getImageMemoryRequirements( VkImage image )const;
		/**
		*\~french
		*\return
		*	L'API de rendu.
		*\~english
		*\return
		*	The rendering API.
		*/
		inline Renderer const & getRenderer()const
		{
			return m_renderer;
		}
		/**
		*\~french
		*\return
		*	La connection à l'application.
		*\~english
		*\return
		*	The connection to the application.
		*/
		inline Connection const & getConnection()const
		{
			return *m_connection;
		}
		/**
		*\~french
		*\return
		*	La surface de présentation.
		*\~english
		*\return
		*	The presentation surface.
		*/
		inline auto getPresentSurface()const
		{
			return m_connection->getPresentSurface();
		}
		/**
		*\~french
		*\return
		*	Les capacités de la surface de présentation.
		*\~english
		*\return
		*	The presentation surface's capabilities.
		*/
		inline auto getSurfaceCapabilities()const
		{
			return m_connection->getSurfaceCapabilities();
		}
		/**
		*\brief
		*	Le VkDevice.
		*/
		inline operator VkDevice const &()const
		{
			return m_device;
		}

#define VK_LIB_DEVICE_FUNCTION( fun ) PFN_##fun fun;
#	include "Miscellaneous/VulkanFunctionsList.inl"

	private:
		/**
		*\copydoc	renderer::Device::enable
		*/
		void doEnable()const override
		{
		}
		/**
		*\copydoc	renderer::Device::disable
		*/
		void doDisable()const override
		{
		}

	private:
		Renderer const & m_renderer;
		PhysicalDevice const & m_gpu;
		ConnectionPtr m_connection;
		VkDevice m_device{ VK_NULL_HANDLE };
	};
}
