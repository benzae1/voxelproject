#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stb_image.h>


class Texture {
public:
    unsigned int ID;

    Texture(const char* path, bool flipVertically = true);

    void bind(unsigned int unit = 0) const;
    void unbind() const;

private:
    int width, height, nrChannels;
};

#endif