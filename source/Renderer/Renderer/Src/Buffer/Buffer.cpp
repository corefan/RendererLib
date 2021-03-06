﻿/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#include "Buffer/Buffer.hpp"

namespace renderer
{
	BufferBase::BufferBase( Device const & device
		, uint32_t size
		, BufferTargets target
		, MemoryPropertyFlags flags )
		: m_device{ device }
		, m_size{ size }
	{
	}
}
