/*
This file belongs to RendererLib.
See LICENSE file in root folder
*/
#pragma once

#include "VkRendererPrerequisites.hpp"

#include <Descriptor/DescriptorSetBinding.hpp>

namespace vk_renderer
{
	/**
	*\brief
	*	Classe de base des attaches.
	*/
	class DescriptorSetBinding
	{
	public:
		virtual ~DescriptorSetBinding() = default;
		inline operator VkWriteDescriptorSet const &()const
		{
			return m_write;
		}

	protected:
		VkWriteDescriptorSet m_write;
	};
	/**
	*\brief
	*	Attache de type sampler + texture.
	*/
	class CombinedTextureSamplerBinding
		: public renderer::CombinedTextureSamplerBinding
		, public DescriptorSetBinding
	{
	public:
		CombinedTextureSamplerBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, TextureView const & texture
			, Sampler const & sampler
			, renderer::ImageLayout layout
			, uint32_t index );

	private:
		TextureView const & m_view;
		Sampler const & m_sampler;
		VkDescriptorImageInfo m_info;
		VkImageLayout m_layout;
	};
	/**
	*\brief
	*	Attache de type sampler.
	*/
	class SamplerBinding
		: public renderer::SamplerBinding
		, public DescriptorSetBinding
	{
	public:
		SamplerBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, Sampler const & sampler
			, uint32_t index );

	private:
		Sampler const & m_sampler;
		VkDescriptorImageInfo m_info;
	};
	/**
	*\brief
	*	Attache de type texture échantillonnée.
	*/
	class SampledTextureBinding
		: public renderer::SampledTextureBinding
		, public DescriptorSetBinding
	{
	public:
		SampledTextureBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, TextureView const & texture
			, renderer::ImageLayout layout
			, uint32_t index );

	private:
		TextureView const & m_view;
		VkDescriptorImageInfo m_info;
	};
	/**
	*\brief
	*	Attache de type texture de stockage.
	*/
	class StorageTextureBinding
		: public renderer::StorageTextureBinding
		, public DescriptorSetBinding
	{
	public:
		StorageTextureBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, TextureView const & texture
			, uint32_t index );

	private:
		TextureView const & m_view;
		VkDescriptorImageInfo m_info;
	};
	/**
	*\brief
	*	Attache de type tampon uniforme.
	*/
	class UniformBufferBinding
		: public renderer::UniformBufferBinding
		, public DescriptorSetBinding
	{
	public:
		UniformBufferBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, UniformBuffer const & uniformBuffer
			, uint32_t offset
			, uint32_t range
			, uint32_t index );

	private:
		Buffer const & m_uniformBuffer;
		VkDescriptorBufferInfo m_info;
	};
	/**
	*\brief
	*	Attache de type tampon de stockage.
	*/
	class StorageBufferBinding
		: public renderer::StorageBufferBinding
		, public DescriptorSetBinding
	{
	public:
		StorageBufferBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, Buffer const & storageBuffer
			, uint32_t offset
			, uint32_t range
			, uint32_t index );

	private:
		Buffer const & m_buffer;
		VkDescriptorBufferInfo m_info;
	};
	/**
	*\brief
	*	Attache de type tampon de texels.
	*/
	class TexelBufferBinding
		: public renderer::TexelBufferBinding
		, public DescriptorSetBinding
	{
	public:
		TexelBufferBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, Buffer const & storageBuffer
			, BufferView const & view
			, uint32_t index );

	private:
		Buffer const & m_buffer;
		BufferView const & m_view;
		VkDescriptorBufferInfo m_info;
	};
	/**
	*\brief
	*	Attache de type tampon uniforme dynamique.
	*/
	class DynamicUniformBufferBinding
		: public renderer::DynamicUniformBufferBinding
		, public DescriptorSetBinding
	{
	public:
		DynamicUniformBufferBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, UniformBuffer const & uniformBuffer
			, uint32_t offset
			, uint32_t range
			, uint32_t index );

	private:
		Buffer const & m_uniformBuffer;
		VkDescriptorBufferInfo m_info;
	};
	/**
	*\brief
	*	Attache de type tampon de stockage dynamique.
	*/
	class DynamicStorageBufferBinding
		: public renderer::DynamicStorageBufferBinding
		, public DescriptorSetBinding
	{
	public:
		DynamicStorageBufferBinding( renderer::DescriptorSetLayoutBinding const & layoutBinding
			, DescriptorSet const & descriptorSet
			, Buffer const & storageBuffer
			, uint32_t offset
			, uint32_t range
			, uint32_t index );

	private:
		Buffer const & m_buffer;
		VkDescriptorBufferInfo m_info;
	};
}
