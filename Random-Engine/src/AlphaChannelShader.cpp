#include "AlphaChannelShader.hpp"
using namespace SRE;
AlphaChannelShader::AlphaChannelShader() {
	vertexShader = R"(#version 140
        in vec4 position;
        in vec3 normal;
        in vec2 uv;
        out vec2 vUV;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        void main(void) {
            gl_Position = projection * view * model * position;
            vUV = uv;
        }
        )";
	fragmentShader = R"(#version 140
        out vec4 fragColor;
        in vec2 vUV;
        
        vec4 color;
        uniform sampler2D tex;
        
        void main(void)
        {
			color = vec4(1.0, 1.0, 1.0, 0.5);
            fragColor = color * texture(tex, vUV);
        }
        )";
	shader = SRE::Shader::createShader(vertexShader, fragmentShader);
	shader->setBlend(BlendType::AlphaBlending);
	shader->setDepthTest(false);
}
AlphaChannelShader::~AlphaChannelShader() {
	delete shader;
}