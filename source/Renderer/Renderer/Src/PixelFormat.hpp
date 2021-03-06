/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#ifndef ___Renderer_PixelFormat_HPP___
#define ___Renderer_PixelFormat_HPP___
#pragma once

#include "Enum/ImageAspectFlag.hpp"

namespace renderer
{
	/**
	*\~french
	*\brief
	*	Dit si le renderer::PixelFormat donné est un format utilisable pour les tampons de profondeur et stencil.
	*\param[in] format
	*	Le renderer::PixelFormat à tester.
	*\return
	*	\p true s'il l'est...
	*\~english
	*\brief
	*	Tells if the given renderer::PixelFormat is usable in depth and stencil buffers.
	*\param[in] format
	*	The renderer::PixelFormat.
	*\return
	*	\p true if it is usable in depth and stencil buffers.
	*/
	bool isDepthStencilFormat( renderer::PixelFormat format )noexcept;
	/**
	*\~french
	*\brief
	*	Dit si le renderer::PixelFormat donné est un format utilisable pour les tampons de stencil.
	*\param[in] format
	*	Le renderer::PixelFormat à tester.
	*\return
	*	\p true s'il l'est...
	*\~english
	*\brief
	*	Tells if the given renderer::PixelFormat is usable in stencil buffers.
	*\param[in] format
	*	The renderer::PixelFormat.
	*\return
	*	\p true if it is usable in stencil buffers.
	*/
	bool isStencilFormat( renderer::PixelFormat format )noexcept;
	/**
	*\~french
	*\brief
	*	Dit si le renderer::PixelFormat donné est un format utilisable pour les tampons de profondeur.
	*\param[in] format
	*	Le renderer::PixelFormat à tester.
	*\return
	*	\p true s'il l'est...
	*\~english
	*\brief
	*	Tells if the given renderer::PixelFormat is usable in depth buffers.
	*\param[in] format
	*	The renderer::PixelFormat.
	*\return
	*	\p true if it is usable in depth buffers.
	*/
	bool isDepthFormat( renderer::PixelFormat format )noexcept;
	/**
	*\~english
	*\brief
	*	Tells if given pixel format is a compressed pixel format.
	*\param[in] format
	*	The pixel format.
	*\~french
	*\brief
	*	Dit si le format de pixels donné est un format compressé.
	*\param[in] format
	*	Le format de pixel.
	*/
	bool isCompressedFormat( PixelFormat format )noexcept;
	/**
	*\~french
	*\brief
	*	Dit si le renderer::PixelFormat donné est un format utilisable pour les tampons de profondeur et/ou stencil.
	*\param[in] format
	*	Le renderer::PixelFormat à tester.
	*\return
	*	\p true s'il l'est...
	*\~english
	*\brief
	*	Tells if the given renderer::PixelFormat is usable in depth and/or stencil buffers.
	*\param[in] format
	*	The renderer::PixelFormat.
	*\return
	*	\p true if it is usable in depth and/or stencil buffers.
	*/
	inline bool isDepthOrStencilFormat( renderer::PixelFormat format )noexcept
	{
		return isDepthStencilFormat( format )
			|| isStencilFormat( format )
			|| isDepthFormat( format );
	}
	/**
	*\~french
	*\brief
	*	Récupère le masque d'aspects correspondant au renderer::PixelFormat donné.
	*\param[in] format
	*	Le renderer::PixelFormat.
	*\return
	*	Les aspects.
	*\~english
	*\brief
	*	Retrieves the aspects mask matching given renderer::PixelFormat.
	*\param[in] format
	*	The renderer::PixelFormat.
	*\return
	*	The aspects.
	*/
	ImageAspectFlags getAspectMask( renderer::PixelFormat format )noexcept;
	/**
	*\~english
	*\brief
	*	Gets the name of the given element.
	*\param[in] value
	*	The element.
	*\return
	*	The name.
	*\~french
	*\brief
	*	Récupère le nom de l'élément donné.
	*\param[in] value
	*	L'élément.
	*\return
	*	Le nom.
	*/
	std::string getName( renderer::PixelFormat value );
}

#endif
