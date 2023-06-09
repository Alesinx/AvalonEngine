#include "AvalonPch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

Avalon::OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
	mPath(path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	AVALON_CORE_ASSERT(data, "Failed to load image: {0}", stbi_failure_reason());
	//AVALON_CORE_ERROR("Failed to load image: {0}", stbi_failure_reason());
	mWidth = width;
	mHeight = height;

	glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
	glTextureStorage2D(mRendererID, 1, GL_RGB8, mWidth, mHeight);

	glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

Avalon::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &mRendererID);
}

void Avalon::OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, mRendererID);
}