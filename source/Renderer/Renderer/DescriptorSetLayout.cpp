/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "DescriptorSetLayout.hpp"

#include <algorithm>

namespace renderer
{
	DescriptorSetLayout::DescriptorSetLayout( Device const & device
		, DescriptorSetLayoutBindingArray && bindings )
		: m_bindings{ std::move( bindings ) }
	{
	}

	DescriptorSetLayoutBinding const & DescriptorSetLayout::getBinding( uint32_t index )const
	{
		auto it = std::find_if( m_bindings.begin()
			, m_bindings.end()
			, [index]( DescriptorSetLayoutBinding const & lookup )
		{
			return lookup.getBindingPoint() == index;
		} );

		if ( it == m_bindings.end() )
		{
			throw std::range_error{ "Descriptor set layout binding was not found." };
		}

		return *it;
	}
}