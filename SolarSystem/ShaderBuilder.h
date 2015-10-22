#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#include <string>
#include <GL/freeglut.h>

class ShaderBuilder{
public:
	GLuint getModelToWorldTransformLocation() const;
	GLuint getWorldToViewTransformLocation() const;
	GLuint getProjectionTransformLocation() const;
private:
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;

	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	std::string readFileToString(char* filename) const;
	void buildShaders();
};

#endif // SHADER_BUILDER_H