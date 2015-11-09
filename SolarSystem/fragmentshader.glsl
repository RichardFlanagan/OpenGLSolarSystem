#version 330

in vec4 LightIntensity0;
in vec4 Colour0;
//in vec2 TexCoord0;

out vec4 FragColor;

//uniform sampler2D gTextureSampler;

void main(){
    FragColor = Colour0 * LightIntensity0;
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f) * LightIntensity0;
}