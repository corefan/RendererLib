/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "GlShaderProgram.hpp"

#include "GlDevice.hpp"

namespace gl_renderer
{
	namespace
	{
		std::string doRetrieveCompilerLog( GLuint shaderName )
		{
			std::string log;
			int infologLength = 0;
			int charsWritten = 0;
			glGetShaderiv( shaderName, GL_INFO_LOG_LENGTH, &infologLength );

			if ( infologLength > 0 )
			{
				std::vector< char > infoLog( infologLength + 1 );
				glGetShaderInfoLog( shaderName, infologLength, &charsWritten, infoLog.data() );
				log = infoLog.data();
			}

			if ( !log.empty() )
			{
				log = log.substr( 0, log.size() - 1 );
			}

			return log;
		}

		bool doCheckCompileErrors( bool compiled
			, GLuint shaderName )
		{
			auto compilerLog = doRetrieveCompilerLog( shaderName );

			if ( !compilerLog.empty() )
			{
				if ( !compiled )
				{
					std::cerr << compilerLog << std::endl;
				}
				else
				{
					std::cout << compilerLog << std::endl;
				}
			}
			else if ( !compiled )
			{
				std::cerr << "Shader compilation failed" << std::endl;
			}

			return compiled;
		}

		std::string doRetrieveLinkerLog( GLuint programName )
		{
			std::string log;
			int infologLength = 0;
			int charsWritten = 0;
			glGetProgramiv( programName, GL_INFO_LOG_LENGTH, &infologLength );

			if ( infologLength > 0 )
			{
				std::vector< char > infoLog( infologLength + 1 );
				glGetProgramInfoLog( programName, infologLength, &charsWritten, infoLog.data() );
				log = infoLog.data();
			}

			if ( !log.empty() )
			{
				log = log.substr( 0, log.size() - 1 );
			}

			return log;
		}
	}

	ShaderProgram::ShaderProgram( renderer::Device const & device )
		: renderer::ShaderProgram{ device }
		, m_program{ glCreateProgram() }
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		for ( auto shaderName : m_shaders )
		{
			glDeleteShader( shaderName );
		}

		glDeleteProgram( m_program );
	}

	void ShaderProgram::createModule( std::string const & shader
		, renderer::ShaderStageFlag stage )
	{
		auto shaderName = glCreateShader( convert( stage ) );

		std::vector< char > buffer( shader.size() + 1 );

#if defined( _MSC_VER )
		strncpy_s( buffer.data(), shader.size() + 1, shader.c_str(), shader.size() );
#else
		strncpy( buffer.data(), shader.c_str(), shader.size() );
#endif

		auto length = int( shader.size() );
		auto data = buffer.data();
		glShaderSource( shaderName, 1, const_cast< const char ** >( &data ), &length );
		glCompileShader( shaderName );
		int compiled = 0;
		glGetShaderiv( shaderName, GL_COMPILE_STATUS, &compiled );

		if ( !doCheckCompileErrors( compiled != 0, shaderName ) )
		{
			glDeleteShader( shaderName );
			throw std::runtime_error{ "Shader compilation failed." };
		}

		m_shaders.push_back( shaderName );
		glAttachShader( m_program, shaderName );
	}

	void ShaderProgram::createModule( renderer::ByteArray const & fileData
		, renderer::ShaderStageFlag stage )
	{
		throw std::runtime_error{ "Shader compilation from SPIR-V is not supported." };
	}

	void ShaderProgram::link()
	{
		int attached = 0;
		glGetProgramiv( m_program, GL_ATTACHED_SHADERS, &attached );
		glLinkProgram( m_program );
		int linked = 0;
		glGetProgramiv( m_program, GL_LINK_STATUS, &linked );
		auto linkerLog = doRetrieveLinkerLog( m_program );
		bool result = false;

		if ( linked
			&& attached == int( m_shaders.size() )
			&& linkerLog.find( "ERROR" ) == std::string::npos )
		{
			if ( !linkerLog.empty() )
			{
				std::cout << "ShaderProgram::link - " << linkerLog << std::endl;
			}
		}
		else
		{
			if ( !linkerLog.empty() )
			{
				std::cerr << "ShaderProgram::link - " << linkerLog << std::endl;
			}

			if ( attached != int( m_shaders.size() ) )
			{
				std::cerr << "ShaderProgram::link - The linked shaders count doesn't match the active shaders count." << std::endl;
			}
		}
	}
}