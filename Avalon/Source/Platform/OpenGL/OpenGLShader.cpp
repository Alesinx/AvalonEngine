#include "AvalonPch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>

namespace Avalon
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSource;
		if (ReadFile(filepath, shaderSource))
		{
			std::unordered_map<GLenum, std::string> shaderSources = PreprocessShaderFile(shaderSource);
			CompileShaderCode(shaderSources);
		}
		else
		{
			AVALON_CORE_ERROR("Couldn't create OpenGLShader from file");
		}
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		CompileShaderCode(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(mRendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(mRendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, Vec4 value) const
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, Mat4 matrix) const
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	bool OpenGLShader::ReadFile(const std::string& filepath, std::string& result)
	{
		std::filesystem::path currentPath = std::filesystem::current_path();

		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());

			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();

			return true;
		}

		AVALON_CORE_ERROR("Could not open file '{0}' ", filepath);
		return false;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreprocessShaderFile(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "//@shaderType";
		size_t nextTypeTokenPos = source.find(typeToken, 0); 
		while (nextTypeTokenPos != std::string::npos)
		{
			// Get the type string
			size_t eol = source.find_first_of("\r\n", nextTypeTokenPos);
			if(eol == std::string::npos)
			{
				AVALON_CORE_ERROR("Syntax error while processing shader sources");
				return shaderSources;
			}

			size_t begin = nextTypeTokenPos + strlen(typeToken) + 1; //Start of shader type name (after "//@type " keyword)
			std::string typeStr = source.substr(begin, eol - begin);

			GLuint type = DetermineShaderType(typeStr);
			if (type == 0)
			{
				AVALON_CORE_ERROR("Invalid shader type specified");
				return shaderSources;
			}

			nextTypeTokenPos = source.find(typeToken, eol);
			std::string shaderCode;
			if (nextTypeTokenPos != std::string::npos)
				shaderCode = source.substr(eol, nextTypeTokenPos - eol);
			else
				shaderCode = source.substr(eol); // No more shader type definitions, just substring from eol until the end of the file.

			shaderSources[DetermineShaderType(typeStr)] = shaderCode;
		}

		return shaderSources;
	}

	void OpenGLShader::CompileShaderCode(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		const GLuint program = glCreateProgram();

		AVALON_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> shaderIDs;
		int shaderIDsIndex = 0;

		for (std::pair<const GLenum, std::string>& kv : shaderSources)
		{
			const GLenum type = kv.first;
			const GLchar* sourceCodeStr = kv.second.c_str();

			GLuint shader = glCreateShader(type);

			glShaderSource(shader, 1, &sourceCodeStr, 0);
			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				AVALON_CORE_ERROR("{0}", infoLog.data());
				AVALON_CORE_ASSERT(false, "Vertex shader compilation failure");
				break;
			}

			glAttachShader(program, shader);
			shaderIDs[shaderIDsIndex++] = shader;
		}

		mRendererID = program;
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shader.
			for (GLenum id : shaderIDs)
				glDeleteShader(id);

			AVALON_CORE_ERROR("{0}", infoLog.data());
			AVALON_CORE_ASSERT(false, "Shader link failure");

			return;
		}
		
		// Always detach and delete shaders after a successful link.
		for (GLenum id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

	GLenum OpenGLShader::DetermineShaderType(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		AVALON_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}
}
