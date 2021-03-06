﻿/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#include "Descriptor/DescriptorSetPool.hpp"

#include "Descriptor/DescriptorSet.hpp"
#include "Descriptor/DescriptorSetLayout.hpp"

namespace renderer
{
	DescriptorSetPool::DescriptorSetPool( DescriptorSetLayout const & layout, uint32_t maxSets )
		: m_layout{ layout }
		, m_maxSets{ maxSets }
	{
	}

	void DescriptorSetPool::allocate( uint32_t count )const
	{
		assert( m_allocated + count <= m_maxSets );
		m_allocated = std::min( m_allocated + count, m_maxSets );
	}

	void DescriptorSetPool::deallocate( uint32_t count )const
	{
		assert( m_allocated >= count );
		m_allocated -= count;
	}
}
