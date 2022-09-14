#pragma once

#include "gl.h"

class Texture
{
public:
	Texture(const char* imagePath) noexcept;
	~Texture(void) noexcept;

	inline void Bind(void) noexcept
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	inline int Width(void) const noexcept { return mWidth; }
	inline int Height(void) const noexcept { return mHeight; }
		
protected:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;

};

