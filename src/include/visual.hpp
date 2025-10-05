#ifndef VISUAL_HPP
#define VISUAL_HPP

#include <string>

enum class cor{
    red = 0, 
    blue, 
    yellow,
    green,
    black,
    white,
    orange,
    gray,
    rainbow
};

enum class textura{
    none, 
    wood, 
    metal
};

class visual {
    private:
        cor color;
        textura texture;
    public:
        visual(cor c = cor::white, textura t = textura::none);

        const char* geraVertexShader() const;
        const char* geraFragmentShader() const;

        cor getColor() const { return color; }
        textura getTexture() const { return texture; }
};

#endif