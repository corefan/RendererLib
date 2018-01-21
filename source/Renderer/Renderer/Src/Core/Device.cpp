/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "Core/Device.hpp"

#include "Core/Renderer.hpp"
#include "Core/SwapChain.hpp"

namespace renderer
{
	Device::Device( Renderer const & renderer
		, Connection const & connection )
	{
	}

	Mat4 Device::infinitePerspective( Radians fovy
		, float aspect
		, float zNear )
	{
		float const range = tan( fovy / float( 2 ) ) * zNear;
		float const left = -range * aspect;
		float const right = range * aspect;
		float const bottom = -range;
		float const top = range;

		Mat4 result{ float{ 0 } };
		result[0][0] = ( float( 2 ) * zNear ) / ( right - left );
		result[1][1] = ( float( 2 ) * zNear ) / ( top - bottom );
		result[2][2] = -float( 1 );
		result[2][3] = -float( 1 );
		result[3][2] = -float( 2 ) * zNear;
		return result;
	}
}
