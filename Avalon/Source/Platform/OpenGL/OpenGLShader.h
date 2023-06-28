#pragma once

#include "Avalon/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Avalon
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return mName; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformMat4(const std::string& name, Mat4 value) const;


	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreprocessShaderFile(const std::string& source);
		void CompileShaderCode(std::unordered_map<GLenum, std::string>& shaderSources);
		GLenum DetermineShaderType(const std::string& type);

	private:
		uint32_t mRendererID;
		std::string mName;
	};
}
