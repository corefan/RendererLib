#include "Buffer/VkUniformBuffer.hpp"

#include "Core/VkDevice.hpp"
#include "Core/VkPhysicalDevice.hpp"

namespace vk_renderer
{
	namespace
	{
		uint32_t doGetAlignedSize( uint32_t size, VkDeviceSize align )
		{
			uint32_t result = 0u;
			auto align32 = uint32_t( align );

			while ( size > align )
			{
				size -= align32;
				result += align32;
			}

			return result + align32;
		}
	}

	UniformBuffer::UniformBuffer( renderer::Device const & device
		, uint32_t count
		, uint32_t size
		, renderer::BufferTargets target
		, renderer::MemoryPropertyFlags flags )
		: renderer::UniformBufferBase{ device
			, count
			, size
			, target
			, flags }
	{
		m_buffer = m_device.createBuffer( count * getAlignedSize( getElementSize() )
			, target | renderer::BufferTarget::eUniformBuffer
			, flags );
	}

	uint32_t UniformBuffer::getAlignedSize( uint32_t size )const
	{
		return doGetAlignedSize( size
			, static_cast< Device const & >( m_device ).getPhysicalDevice().getProperties().limits.minUniformBufferOffsetAlignment );
	}
}
