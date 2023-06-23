#include "AvalonPch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Avalon
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSource = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcessShaderFile(shaderSource);
		CompileShaderCode(shaderSources);
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

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, Mat4 matrix) const
	{
		GLint location = glGetUniformLocation(mRendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());

			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			AVALON_CORE_ERROR("Could not open file '{0}' ", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcessShaderFile(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "//@shaderType";
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			// Get the type string
			size_t eol = source.find_first_of("\r\n", pos);
			if(eol == std::string::npos)
			{
				AVALON_CORE_ERROR("Syntax error while processing shader sources");
				return shaderSources;
			}

			size_t begin = pos + strlen(typeToken) + 1;
			std::string typeStr = source.substr(begin, eol - begin);

			GLuint type = DetermineShaderType(typeStr);
			if (type == 0)
			{
				AVALON_CORE_ERROR("Invalid shader type specified");
				return shaderSources;
			}

			// Get the specific shader source code and put it in the unordered map
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[DetermineShaderType(typeStr)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::CompileShaderCode(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		const GLuint program = glCreateProgram();

		std::vector<GLenum> shaderIDs(shaderSources.size());
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
			shaderIDs.push_back(shader);
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

		// Always detach shaders after a successful link.
		for (GLenum id : shaderIDs)
			glDetachShader(program, id);
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
