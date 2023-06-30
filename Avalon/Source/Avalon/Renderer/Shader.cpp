#include "AvalonPch.h"
#include "Shader.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Avalon
{
	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Shader> ShaderLibrary::Add(const std::string& name, std::shared_ptr<Shader> shader)
	{
		AVALON_CORE_ASSERT(!Exists(name), "Shader alreay exists");
		mShaderMap[name] = shader;

		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		std::shared_ptr<Shader> shader = Shader::Create(name, filepath);
		Add(name, shader);

		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		AVALON_CORE_ASSERT(Exists(name), "Shader not found");
		return mShaderMap[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return mShaderMap.find(name) != mShaderMap.end();
	}
}