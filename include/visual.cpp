#include "visual.hpp"

visual::visual(cor c, textura t) : color(c), texture(t) {}

const char* visual::geraVertexShader() const {
    return R"(
        #version 330 core
        //uniform float u_time;
        layout(location = 0) in vec2 vitor;
        void main() {
            //float offset = cos(u_time*10)*0.5;
            //vec2 pos = vec2(offset, offset);
            gl_Position = vec4(vitor, 0.0, 1.0);
        }
    )";
}

const char* visual::geraFragmentShader() const {
    switch (color) {
        case cor::blue:
            return R"(
                #version 330 core
                out vec4 fragColor;
                void main() {
                    fragColor = vec4(0.0, 0.0, 1.0, 1.0);
                }
            )";
        case cor::black:
        case cor::gray:
        case cor::green:
            return R"(
                #version 330 core
                out vec4 fragColor;
                void main() {
                    fragColor = vec4(0.0, 1.0, 0.0, 1.0);
                }
            )";
        case cor::orange:
            //break;
        case cor::red:
            return R"(
                #version 330 core
                out vec4 fragColor;
                void main() {
                    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
                }
            )";
        case cor::white:
            //break;
        case cor::yellow:
            //break;
        case cor::rainbow:
            return R"(
                #version 330 core
                uniform float u_time;
                out vec4 fragColor;
                void main() {
                    fragColor = vec4(abs(sin(u_time)), abs(sin(u_time*0.7)), abs(cos(u_time*1.3)), 1.0);
                }
            )";
        default:
            return R"(
                #version 330 core
                out vec4 fragColor;
                void main() {
                    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
                }
            )";
    }
}


/*
const char* triangulo::geraShader(){
    return R"(
    #version 330 core
    //uniform float u_time;
    layout(location = 0) in vec2 pos;
    void main() {
        //float offset = cos(u_time*10)*0.5;
        //vec2 pos = vec2(offset, offset);
        gl_Position = vec4(pos, 0, 1.0);
    }
    )";
}

const char* triangulo::geraShadCor(){
    return R"(
    #version 330 core
    uniform float u_time;
    out vec4 fragColor;
    void main() {
        float offset = cos(u_time*10)*0.8;
        float offsin = sin(u_time)*0.3;
        vec3 pos = vec3(offset, offsin, offsin);
        vec3 cor = vec3(1.0f, 0.3f, 0.5f);
        fragColor = vec4(cor + pos, 1.0f);
    }
    )";
}

*/
