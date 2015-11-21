/*
File: ShaderManager.h
Author: Richard Flanagan
Description:
*/
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

class ShaderManager {
public:
	ShaderManager() {};
	~ShaderManager() {};

	void loadShaders();

	const GLuint getModelToWorldTransformLocation();
	const GLuint getWorldToViewTransformLocation();
	const GLuint getProjectionTransformLocation();

	const GLuint getAmbientLightIntensityLocation();
	const GLuint getDiffuseLightIntensityLocation();
	const GLuint getSpecularLightIntensityLocation();

	const GLuint getKaLocation();
	const GLuint getKdLocation();
	const GLuint getKsLocation();

	const GLuint getModelColourLocation();
	const GLuint getCameraPositionLocation();

private:
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;

	GLuint gKaLocation;
	GLuint gKdLocation;
	GLuint gKsLocation;

	GLuint gAmbientLightIntensityLocation;
	GLuint gDiffuseLightIntensityLocation;
	GLuint gSpecularLightIntensityLocation;
	GLuint gModelColourLocation;
	GLuint gCameraPositionLocation;

	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	const std::string readFileToString(char* filename);
	void buildShaders();
};
#endif // SHADER_MANAGER_H