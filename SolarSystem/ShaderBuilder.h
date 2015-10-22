#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#include <string>
#include <GL/freeglut.h>
#include "ErrorState.h"

class ShaderBuilder : public ErrorState {
public:
	const GLuint getModelToWorldTransformLocation();
	const GLuint getWorldToViewTransformLocation();
	const GLuint getProjectionTransformLocation();
private:
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;

	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	const std::string readFileToString(char* filename);
	void buildShaders();
};

#endif // SHADER_BUILDER_H