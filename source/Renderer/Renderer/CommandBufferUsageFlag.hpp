/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#ifndef ___Renderer_CommandBufferUsageFlag_HPP___
#define ___Renderer_CommandBufferUsageFlag_HPP___
#pragma once

#include <Utils/FlagCombination.hpp>

namespace renderer
{
	/**
	*\brief
	*	Enumération des utilisation de tampon de commandes.
	*/
	enum class CommandBufferUsageFlag
		: uint32_t
	{
		eOneTimeSubmit = 0x00000001,
		eRenderPassContinue = 0x00000002,
		eSimultaneousUse = 0x00000004,
	};
	Utils_ImplementFlag( CommandBufferUsageFlag )
}

#endif