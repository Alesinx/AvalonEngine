#pragma once

#include "Avalon/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Avalon
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat4(const std::string& name, Vec4 value) const;
		void UploadUniformMat4(const std::string& name, Mat4 value) const;


	private:
		bool ReadFile(const std::string& filepath, std::string& result);
		std::unordered_map<GLenum, std::string> PreprocessShaderFile(const std::string& source);
		void CompileShaderCode(std::unordered_map<GLenum, std::string>& shaderSources);
		GLenum DetermineShaderType(const std::string& type);

	private:
		uint32_t mRendererID;
	};
}
