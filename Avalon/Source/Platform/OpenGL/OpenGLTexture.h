#pragma once

#include "Avalon/Renderer/Texture.h"
#include <glad/glad.h>

namespace Avalon
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return mWidth; }
		virtual uint32_t GetHeight() const override { return mHeight; }
		virtual Vec2 GetSize() const override { return Vec2(mWidth, mHeight); }
		virtual uint32_t GetRendererID() const override { return mRendererID; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string mPath;
		uint32_t mWidth;
		uint32_t mHeight;
		uint32_t mRendererID;
		GLenum mInternalFormat, mDataFormat;
	};
}

