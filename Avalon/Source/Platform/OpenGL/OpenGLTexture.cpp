#include "AvalonPch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

Avalon::OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
	mWidth(width), mHeight(height)
{
	mInternalFormat = GL_RGBA8;
	mDataFormat = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
	glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);

	glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Avalon::OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
	mPath(path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	AVALON_CORE_ASSERT(data, "Failed to load image: {0}", stbi_failure_reason());
	mWidth = width;
	mHeight = height;

	if (channels == 4)
	{
		mInternalFormat = GL_RGBA8;
		mDataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		mInternalFormat = GL_RGB8;
		mDataFormat = GL_RGB;
	}

	AVALON_CORE_ASSERT(mInternalFormat & mDataFormat, "Format not supported");

	glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
	glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);

	glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

Avalon::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &mRendererID);
}

void Avalon::OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	AVALON_CORE_ASSERT(mDataFormat == GL_RGBA || mDataFormat == GL_RGB, "Data format not set");

	uint32_t bpp = mDataFormat == GL_RGBA ? 4 : 3;
	AVALON_CORE_ASSERT(size == mWidth * mHeight * bpp, "Data must be entire texture!");

	glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
}

void Avalon::OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, mRendererID);
}
