#pragma once

#include "Avalon/Renderer/Shader.h"

namespace Avalon
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);

	private:
		uint32_t mRendererID;
	};
}