#include "Texture.h"
#include "Utility.h"
#include <stb_image.h>
#include <glad/glad.h>
#include <string>
#include <iostream>

namespace GGL
{
    GLuint LoadTexture(const std::string& path)
    {
        int w, h, bits;
        GLuint texId;
        stbi_set_flip_vertically_on_load(1);
		unsigned char* pixelBuffer = stbi_load(path.c_str(), &w, &h, &bits, 4);
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);
		return texId;
    }

	void BindTexture(unsigned int texId, unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texId);
	}

}