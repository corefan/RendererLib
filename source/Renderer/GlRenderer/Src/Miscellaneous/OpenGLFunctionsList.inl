/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/

// Functions from GL/gl.h
#ifndef GL_LIB_BASE_FUNCTION
#	define GL_LIB_BASE_FUNCTION( x )
#endif

GL_LIB_BASE_FUNCTION( BindTexture )
GL_LIB_BASE_FUNCTION( Clear )
GL_LIB_BASE_FUNCTION( ClearColor )
GL_LIB_BASE_FUNCTION( ClearDepth )
GL_LIB_BASE_FUNCTION( ClearStencil )
GL_LIB_BASE_FUNCTION( CullFace )
GL_LIB_BASE_FUNCTION( DeleteTextures )
GL_LIB_BASE_FUNCTION( DepthFunc )
GL_LIB_BASE_FUNCTION( DepthMask )
GL_LIB_BASE_FUNCTION( DepthRange )
GL_LIB_BASE_FUNCTION( Disable )
GL_LIB_BASE_FUNCTION( DrawArrays )
GL_LIB_BASE_FUNCTION( Enable )
GL_LIB_BASE_FUNCTION( Finish )
GL_LIB_BASE_FUNCTION( FrontFace )
GL_LIB_BASE_FUNCTION( GenTextures )
GL_LIB_BASE_FUNCTION( GetError )
GL_LIB_BASE_FUNCTION( GetFloatv )
GL_LIB_BASE_FUNCTION( GetIntegerv )
GL_LIB_BASE_FUNCTION( GetString )
GL_LIB_BASE_FUNCTION( GetTexImage )
GL_LIB_BASE_FUNCTION( GetTexLevelParameterfv )
GL_LIB_BASE_FUNCTION( GetTexLevelParameteriv )
GL_LIB_BASE_FUNCTION( GetTexParameterfv )
GL_LIB_BASE_FUNCTION( GetTexParameteriv )
GL_LIB_BASE_FUNCTION( LineWidth )
GL_LIB_BASE_FUNCTION( LogicOp )
GL_LIB_BASE_FUNCTION( PolygonMode )
GL_LIB_BASE_FUNCTION( ReadBuffer )
GL_LIB_BASE_FUNCTION( ReadPixels )
GL_LIB_BASE_FUNCTION( Scissor )
GL_LIB_BASE_FUNCTION( TexImage1D )
GL_LIB_BASE_FUNCTION( TexImage2D )
GL_LIB_BASE_FUNCTION( TexParameteri )
GL_LIB_BASE_FUNCTION( TexSubImage1D )
GL_LIB_BASE_FUNCTION( TexSubImage2D )
GL_LIB_BASE_FUNCTION( Viewport )

#undef GL_LIB_BASE_FUNCTION

#ifndef GL_LIB_FUNCTION
#	define GL_LIB_FUNCTION( x )
#endif

GL_LIB_FUNCTION( ActiveTexture )
GL_LIB_FUNCTION( AttachShader )
GL_LIB_FUNCTION( BeginQuery )
GL_LIB_FUNCTION( BindBuffer )
GL_LIB_FUNCTION( BindBufferBase )
GL_LIB_FUNCTION( BindBufferRange )
GL_LIB_FUNCTION( BindFramebuffer )
GL_LIB_FUNCTION( BindImageTexture )
GL_LIB_FUNCTION( BindSampler )
GL_LIB_FUNCTION( BindVertexArray )
GL_LIB_FUNCTION( BlendColor )
GL_LIB_FUNCTION( BlendEquationSeparatei )
GL_LIB_FUNCTION( BlendFuncSeparatei )
GL_LIB_FUNCTION( BlitFramebuffer )
GL_LIB_FUNCTION( BufferStorage )
GL_LIB_FUNCTION( CheckFramebufferStatus )
GL_LIB_FUNCTION( ClearBufferfi )
GL_LIB_FUNCTION( ClearBufferfv )
GL_LIB_FUNCTION( ClearBufferiv )
GL_LIB_FUNCTION( ClearBufferuiv )
GL_LIB_FUNCTION( ClientWaitSync )
GL_LIB_FUNCTION( ClipControl )
GL_LIB_FUNCTION( CompileShader )
GL_LIB_FUNCTION( CompressedTexSubImage1D )
GL_LIB_FUNCTION( CompressedTexSubImage2D )
GL_LIB_FUNCTION( CompressedTexSubImage3D )
GL_LIB_FUNCTION( CopyBufferSubData )
GL_LIB_FUNCTION( CopyImageSubData )
GL_LIB_FUNCTION( CreateProgram )
GL_LIB_FUNCTION( CreateShader )
GL_LIB_FUNCTION( CreateShaderProgramv )
GL_LIB_FUNCTION( DeleteBuffers )
GL_LIB_FUNCTION( DeleteFramebuffers )
GL_LIB_FUNCTION( DeleteProgram )
GL_LIB_FUNCTION( DeleteQueries )
GL_LIB_FUNCTION( DeleteSamplers )
GL_LIB_FUNCTION( DeleteShader )
GL_LIB_FUNCTION( DeleteSync )
GL_LIB_FUNCTION( DeleteVertexArrays )
GL_LIB_FUNCTION( DispatchCompute )
GL_LIB_FUNCTION( DrawArraysInstancedBaseInstance )
GL_LIB_FUNCTION( DrawBuffers )
GL_LIB_FUNCTION( DrawElementsBaseVertex )
GL_LIB_FUNCTION( DrawElementsInstanced )
GL_LIB_FUNCTION( DrawElementsInstancedBaseVertexBaseInstance )
GL_LIB_FUNCTION( EnableVertexAttribArray )
GL_LIB_FUNCTION( EndQuery )
GL_LIB_FUNCTION( FenceSync )
GL_LIB_FUNCTION( FlushMappedBufferRange )
GL_LIB_FUNCTION( FramebufferTexture1D )
GL_LIB_FUNCTION( FramebufferTexture2D )
GL_LIB_FUNCTION( FramebufferTexture3D )
GL_LIB_FUNCTION( FramebufferTextureLayer )
GL_LIB_FUNCTION( GenBuffers )
GL_LIB_FUNCTION( GenFramebuffers )
GL_LIB_FUNCTION( GenQueries )
GL_LIB_FUNCTION( GenSamplers )
GL_LIB_FUNCTION( GenerateMipmap )
GL_LIB_FUNCTION( GenVertexArrays )
GL_LIB_FUNCTION( GetProgramInfoLog )
GL_LIB_FUNCTION( GetProgramInterfaceiv )
GL_LIB_FUNCTION( GetProgramiv )
GL_LIB_FUNCTION( GetProgramResourceiv )
GL_LIB_FUNCTION( GetProgramResourceIndex )
GL_LIB_FUNCTION( GetProgramResourceName )
GL_LIB_FUNCTION( GetQueryObjectui64v )
GL_LIB_FUNCTION( GetQueryObjectuiv )
GL_LIB_FUNCTION( GetShaderInfoLog )
GL_LIB_FUNCTION( GetShaderiv )
GL_LIB_FUNCTION( InvalidateBufferSubData )
GL_LIB_FUNCTION( LinkProgram )
GL_LIB_FUNCTION( MapBufferRange )
GL_LIB_FUNCTION( MemoryBarrier )
GL_LIB_FUNCTION( PatchParameteri )
GL_LIB_FUNCTION( PolygonOffsetClampEXT )
GL_LIB_FUNCTION( QueryCounter )
GL_LIB_FUNCTION( SamplerParameterf )
GL_LIB_FUNCTION( SamplerParameterfv )
GL_LIB_FUNCTION( SamplerParameteri )
GL_LIB_FUNCTION( SamplerParameteriv )
GL_LIB_FUNCTION( ShaderSource )
GL_LIB_FUNCTION( StencilFuncSeparate )
GL_LIB_FUNCTION( StencilMaskSeparate )
GL_LIB_FUNCTION( StencilOpSeparate )
GL_LIB_FUNCTION( TexBufferRange )
GL_LIB_FUNCTION( TexImage2DMultisample )
GL_LIB_FUNCTION( TexImage3D )
GL_LIB_FUNCTION( TexImage3DMultisample )
GL_LIB_FUNCTION( TexStorage1D )
GL_LIB_FUNCTION( TexStorage2D )
GL_LIB_FUNCTION( TexStorage2DMultisample )
GL_LIB_FUNCTION( TexStorage3D )
GL_LIB_FUNCTION( TexStorage3DMultisample )
GL_LIB_FUNCTION( TexSubImage3D )
GL_LIB_FUNCTION( TextureView )
GL_LIB_FUNCTION( Uniform1fv )
GL_LIB_FUNCTION( Uniform1iv )
GL_LIB_FUNCTION( Uniform1uiv )
GL_LIB_FUNCTION( Uniform2fv )
GL_LIB_FUNCTION( Uniform2iv )
GL_LIB_FUNCTION( Uniform2uiv )
GL_LIB_FUNCTION( Uniform3fv )
GL_LIB_FUNCTION( Uniform3iv )
GL_LIB_FUNCTION( Uniform3uiv )
GL_LIB_FUNCTION( Uniform4fv )
GL_LIB_FUNCTION( Uniform4iv )
GL_LIB_FUNCTION( Uniform4uiv )
GL_LIB_FUNCTION( UniformMatrix2fv )
GL_LIB_FUNCTION( UniformMatrix3fv )
GL_LIB_FUNCTION( UniformMatrix4fv )
GL_LIB_FUNCTION( UnmapBuffer )
GL_LIB_FUNCTION( UseProgram )
GL_LIB_FUNCTION( VertexAttribDivisor )
GL_LIB_FUNCTION( VertexAttribPointer )
GL_LIB_FUNCTION( VertexAttribIPointer )

#undef GL_LIB_FUNCTION

#ifndef GL_LIB_FUNCTION_OPT
#	define GL_LIB_FUNCTION_OPT( x )
#endif

GL_LIB_FUNCTION_OPT( ClearTexImage )
GL_LIB_FUNCTION_OPT( DispatchComputeIndirect )
GL_LIB_FUNCTION_OPT( MultiDrawArraysIndirect )
GL_LIB_FUNCTION_OPT( MultiDrawElementsIndirect )
GL_LIB_FUNCTION_OPT( ShaderBinary )
GL_LIB_FUNCTION_OPT( SpecializeShader )

#undef GL_LIB_FUNCTION_OPT

// Functions from Window.h or WinGDI.h
#ifndef WGL_LIB_BASE_FUNCTION
#	define WGL_LIB_BASE_FUNCTION( x )
#endif

WGL_LIB_BASE_FUNCTION( CreateContext )
WGL_LIB_BASE_FUNCTION( DeleteContext )
WGL_LIB_BASE_FUNCTION( MakeCurrent )

#undef WGL_LIB_BASE_FUNCTION

// Extended WGL functions
#ifndef WGL_LIB_FUNCTION
#	define WGL_LIB_FUNCTION( x )
#endif

WGL_LIB_FUNCTION( SwapIntervalEXT )

#undef WGL_LIB_FUNCTION

#ifndef WGL_LIB_FUNCTION_OPT
#	define WGL_LIB_FUNCTION_OPT( x )
#endif

#undef WGL_LIB_FUNCTION_OPT
