﻿#pragma once

#include <Prerequisites.hpp>

namespace vkapp
{
	struct TexturedVertexData
	{
		renderer::Vec4 position;
		renderer::Vec2 uv;
	};

	static wxString const AppName = wxT( "15-Instantiation" );

	class RenderPanel;
	class MainFrame;
	class Application;
}
