#include "Image/GlSampler.hpp"

#include "Core/GlDevice.hpp"

namespace gl_renderer
{
	Sampler::Sampler( renderer::Device const & device
		, renderer::WrapMode wrapS
		, renderer::WrapMode wrapT
		, renderer::WrapMode wrapR
		, renderer::Filter minFilter
		, renderer::Filter magFilter
		, renderer::MipmapMode mipFilter
		, float minLod
		, float maxLod
		, float lodBias
		, renderer::BorderColour borderColour
		, float maxAnisotropy
		, renderer::CompareOp compareOp )
		: renderer::Sampler{ device
			, wrapS
			, wrapT
			, wrapR
			, minFilter
			, magFilter
			, mipFilter
			, minLod
			, maxLod
			, lodBias
			, borderColour
			, maxAnisotropy
			, compareOp }
	{
		glLogCall( gl::GenSamplers, 1, &m_sampler );
		glLogCall( gl::BindSampler, 0u, m_sampler );
		glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_MIN_FILTER, convert( minFilter, mipFilter ) );
		glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_MAG_FILTER, convert( magFilter ) );
		glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_WRAP_S, convert( wrapS ) );
		glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_WRAP_T, convert( wrapT ) );
		glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_WRAP_R, convert( wrapR ) );
		glLogCall( gl::SamplerParameterf, m_sampler, GL_SAMPLER_PARAMETER_MIN_LOD, minLod );
		glLogCall( gl::SamplerParameterf, m_sampler, GL_SAMPLER_PARAMETER_MAX_LOD, maxLod );

		if ( device.getFeatures().samplerAnisotropy
			&& maxAnisotropy > 1.0f )
		{
			glLogCall( gl::SamplerParameterf, m_sampler, GL_SAMPLER_PARAMETER_MAX_ANISOTROPY, maxAnisotropy );
		}

		if ( compareOp != renderer::CompareOp::eAlways )
		{
			glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_COMPARE_MODE, GL_SAMPLER_PARAMETER_COMPARE_REF_TO_TEXTURE );
			glLogCall( gl::SamplerParameteri, m_sampler, GL_SAMPLER_PARAMETER_COMPARE_FUNC, convert( compareOp ) );
		}

		float fvalues[4] = { 0.0f };
		int ivalues[4] = { 0 };

		switch ( borderColour )
		{
		case renderer::BorderColour::eFloatTransparentBlack:
			glLogCall( gl::SamplerParameterfv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, fvalues );
			break;

		case renderer::BorderColour::eIntTransparentBlack:
			glLogCall( gl::SamplerParameteriv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, ivalues );
			break;

		case renderer::BorderColour::eFloatOpaqueBlack:
			fvalues[3] = 1.0f;
			glLogCall( gl::SamplerParameterfv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, fvalues );
			break;

		case renderer::BorderColour::eIntOpaqueBlack:
			ivalues[3] = 255;
			glLogCall( gl::SamplerParameteriv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, ivalues );
			break;

		case renderer::BorderColour::eFloatOpaqueWhite:
			fvalues[0] = 1.0f;
			fvalues[1] = 1.0f;
			fvalues[2] = 1.0f;
			fvalues[3] = 1.0f;
			glLogCall( gl::SamplerParameterfv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, fvalues );
			break;

		case renderer::BorderColour::eIntOpaqueWhite:
			ivalues[0] = 255;
			ivalues[1] = 255;
			ivalues[2] = 255;
			ivalues[3] = 255;
			glLogCall( gl::SamplerParameteriv, m_sampler, GL_SAMPLER_PARAMETER_BORDER_COLOR, ivalues );
			break;
		}
	}

	Sampler::~Sampler()
	{
		glLogCall( gl::DeleteSamplers, 1, &m_sampler );
	}
}
