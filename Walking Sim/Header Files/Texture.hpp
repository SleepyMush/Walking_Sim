#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <string>

#include <iostream>


class Texture {
private:
    GLuint textureID;
    int width, height, nrChannels;

public:
    Texture(std::string filepath) {
        unsigned char* data;
        data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
        if (!data)
        {
            std::string error = "Failed to load texture at " + filepath;
            std::cout << error << "/n";
        }

        GLint format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;
        if (nrChannels == 1)
            format = GL_RED;

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
       // glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

    }

    void cleanUp() {
        glDeleteTextures(1, &textureID);
    }

    void bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
};