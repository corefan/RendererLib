#pragma once

#include "Prerequisites.hpp"

#include <Renderer/Connection.hpp>
#include <Renderer/Device.hpp>
#include <Renderer/Pipeline.hpp>
#include <Renderer/PipelineLayout.hpp>
#include <Renderer/Sampler.hpp>
#include <Renderer/SwapChain.hpp>

#include <Utils/UtilsSignal.hpp>

#include <wx/panel.h>

#include <array>

namespace vkapp
{
	class RenderPanel
		: public wxPanel
	{
	public:
		RenderPanel( wxWindow * parent
			, wxSize const & size
			, renderer::Renderer const & vulkan );
		~RenderPanel();

	private:
		/**
		*\~french
		*\brief
		*	Crée le device logique.
		*\~english
		*\brief
		*	Creates the logical device.
		*/
		void doCreateDevice( renderer::Renderer const & vulkan );
		/**
		*\~french
		*\brief
		*	Crée la swap chain.
		*\~english
		*\brief
		*	Creates the swap chain.
		*/
		void doCreateSwapChain();
		/**
		*\~french
		*\brief
		*	Crée la texture.
		*\~english
		*\brief
		*	Creates the texture.
		*/
		void doCreateTexture();
		/**
		*\~french
		*\brief
		*	Crée le tampon de variables uniformes.
		*\~english
		*\brief
		*	Creates the uniform variables buffer.
		*/
		void doCreateUniformBuffer();
		/**
		*\~french
		*\brief
		*	Crée le descriptors layout/pool/set.
		*\~english
		*\brief
		*	Creates the descriptors layout/pool/set.
		*/
		void doCreateDescriptorSet();
		/**
		*\~french
		*\brief
		*	Crée la passe de rendu.
		*\~english
		*\brief
		*	Creates the render pass.
		*/
		void doCreateRenderPass();
		/**
		*\~french
		*\brief
		*	Crée le tampon de sommets.
		*\~english
		*\brief
		*	Creates the vertex buffer.
		*/
		void doCreateVertexBuffer();
		/**
		*\~french
		*\brief
		*	Crée le tampon de transfert.
		*\~english
		*\brief
		*	Creates the transfer buffer.
		*/
		void doCreateStagingBuffer();
		/**
		*\~french
		*\brief
		*	Crée le pipeline de rendu.
		*\~english
		*\brief
		*	Creates the rendering pipeline.
		*/
		void doCreatePipeline();
		/**
		*\~french
		*\brief
		*	Enregistre les commandes de dessin d'une frame, pour chaque back buffer.
		*\~english
		*\brief
		*	Records the commands necessary to draw one frame, for each back buffer.
		*/
		void doPrepareFrames();
		/**
		*\~french
		*\brief
		*	Dessine la scène.
		*\~english
		*\brief
		*	Draws the scene.
		*/
		void doDraw();
		/**
		*\~french
		*\brief
		*	Réinitialise la swap chain et toutes ses dépendances.
		*\remarks
		*	Peut être nécessaire en cas de redimensionnement de la fenêtre, par exemple.
		*\~english
		*\brief
		*	Resets the swap chain and all needed dependencies.
		*\remarks
		*	Can be necessary, for example when the window is resized.
		*/
		void doResetSwapChain();
		/**
		*\~french
		*\brief
		*	Fonction appelée par le timer de rendu.
		*\~english
		*\brief
		*	Function called by the render timer.
		*/
		void onTimer( wxTimerEvent & event );
		/**
		*\~french
		*\brief
		*	Fonction appelée lors du redimensionnement de la fenêtre.
		*\~english
		*\brief
		*	Function called when the window is resized.
		*/
		void onSize( wxSizeEvent & event );

	private:
		wxTimer * m_timer{ nullptr };
		renderer::DevicePtr m_device;
		renderer::SwapChainPtr m_swapChain;
		renderer::RenderPassPtr m_renderPass;
		renderer::ShaderProgramPtr m_program;
		renderer::PipelineLayoutPtr m_pipelineLayout;
		renderer::PipelinePtr m_pipeline;
		renderer::VertexBufferPtr< TexturedVertexData > m_vertexBuffer;
		renderer::StagingBufferPtr m_stagingBuffer;
		renderer::TexturePtr m_texture;
		renderer::SamplerPtr m_sampler;
		renderer::DescriptorSetLayoutPtr m_descriptorLayout;
		renderer::DescriptorSetPoolPtr m_descriptorPool;
		renderer::DescriptorSetPtr m_descriptorSet;
		renderer::UniformBufferPtr< utils::Mat4 > m_uniformBuffer;
		std::vector< TexturedVertexData > m_vertexData;
		std::vector< renderer::FrameBufferPtr > m_frameBuffers;
		std::vector< renderer::CommandBufferPtr > m_commandBuffers;
		utils::Connection< renderer::SwapChain::OnReset > m_swapChainReset;
	};
}