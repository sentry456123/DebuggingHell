#include "texture.h"

#include "fs.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* imagePath) noexcept
{
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cerr << "Failed to load texture from " << imagePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	switch (nrChannels) {
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	default:
		std::cerr << "Unknown image type" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	mWidth = width;
	mHeight = height;
}

Texture::~Texture(void) noexcept
{
	glDeleteTextures(1, &mTextureID);
}
