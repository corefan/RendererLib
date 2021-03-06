﻿/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#include "Pipeline/MultisampleState.hpp"

namespace renderer
{
	MultisampleState::MultisampleState( MultisampleStateFlags flags
		, SampleCountFlag rasterisationSamples
		, bool sampleShadingEnable
		, float minSampleShading
		, bool alphaToCoverageEnable
		, bool alphaToOneEnable )
		: MultisampleState{ flags
			, rasterisationSamples
			, sampleShadingEnable
			, minSampleShading
			, 0u
			, alphaToCoverageEnable
			, alphaToOneEnable }
	{
	}

	MultisampleState::MultisampleState( MultisampleStateFlags flags
		, SampleCountFlag rasterisationSamples
		, bool sampleShadingEnable
		, float minSampleShading
		, uint32_t sampleMask
		, bool alphaToCoverageEnable
		, bool alphaToOneEnable )
		: m_flags{ flags }
		, m_rasterizationSamples{ rasterisationSamples }
		, m_sampleShadingEnable{ sampleShadingEnable }
		, m_minSampleShading{ minSampleShading }
		, m_sampleMask{ sampleMask }
		, m_alphaToCoverageEnable{ alphaToCoverageEnable }
		, m_alphaToOneEnable{ alphaToOneEnable }
		, m_hash
		{ uint64_t(
			( uint64_t( m_sampleShadingEnable ) << 63 )
			| ( uint64_t( m_sampleMask ) << 30 )
			| ( uint64_t( m_alphaToCoverageEnable ) << 29 )
			| ( uint64_t( m_alphaToOneEnable ) << 28 )
			| ( uint64_t( m_rasterizationSamples ) << 21 )
		) }
	{
	}
}
