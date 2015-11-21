#include "ShaderManager.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>


void ShaderManager::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType){
    GLuint shaderObj = glCreateShader(shaderType);
	assert(shaderObj != 0);

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    
	if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		std::stringstream ss;
		ss << "Error compiling shader type " << shaderType << ": " << InfoLog << std::endl;
		std::cout << ss.str() << std::endl;
		assert(false);
    }

    glAttachShader(shaderProgram, shaderObj);
}

const std::string ShaderManager::readFileToString(char* filename) {
	std::ifstream file (filename, std::ios::in);
	if (file.is_open()){
        std::stringstream ss;
        ss << file.rdbuf();
        ss << '\0';
		return ss.str();
	}
    return "";
}

void ShaderManager::buildShaders(){
    GLuint shaderProgram = glCreateProgram();
	assert(shaderProgram != 0);

	std::string VS = readFileToString("vertexShader.glsl");
	std::string FS = readFileToString("fragmentShader.glsl");

	addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
 	if (success == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::stringstream ss;
		ss << "Error linking shader program: " << errorLog << std::endl;
		assert(false);
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::stringstream ss;
		ss << "Error linking shader program: " << errorLog << std::endl;
		assert(false);
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLocation = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLocation != 0xFFFFFFFF);
    
	gWorldToViewTransformLocation = glGetUniformLocation(shaderProgram, "gWorldToViewTransform");
	assert(gWorldToViewTransformLocation != 0xFFFFFFFF);
    
	gProjectionTransformLocation = glGetUniformLocation(shaderProgram, "gProjectionTransform"); 
	assert(gProjectionTransformLocation != 0xFFFFFFFF);

	gAmbientLightIntensityLocation = glGetUniformLocation(shaderProgram, "gAmbientLightIntensity");
	assert(gAmbientLightIntensityLocation != 0xFFFFFFFF);
	
	gDirectionalLightIntensityLocation = glGetUniformLocation(shaderProgram, "gDirectionalLightIntensity");
	assert(gDirectionalLightIntensityLocation != 0xFFFFFFFF);
	
	gDirectionalLightDirectionLocation = glGetUniformLocation(shaderProgram, "gDirectionalLightDirection");
	assert(gDirectionalLightDirectionLocation != 0xFFFFFFFF);

	gSpecularLightIntensityLocation = glGetUniformLocation(shaderProgram, "gSpecularLightIntensity");
	assert(gSpecularLightIntensityLocation != 0xFFFFFFFF);

	gKaLocation = glGetUniformLocation(shaderProgram, "gKa");
	assert(gKaLocation != 0xFFFFFFFF);
	
	gKdLocation = glGetUniformLocation(shaderProgram, "gKd");
	assert(gKdLocation != 0xFFFFFFFF);

	gKsLocation = glGetUniformLocation(shaderProgram, "gKs");
	assert(gKsLocation != 0xFFFFFFFF);

	gModelColourLocation = glGetUniformLocation(shaderProgram, "gModelColourLocation");
	assert(gModelColourLocation != 0xFFFFFFFF);

	gCameraPositionLocation = glGetUniformLocation(shaderProgram, "gCameraPositionLocation");
	//assert(gCameraPositionLocation != 0xFFFFFFFF);
}

const GLuint ShaderManager::getModelToWorldTransformLocation() {
	return gModelToWorldTransformLocation;
}
const GLuint ShaderManager::getWorldToViewTransformLocation() {
	return gWorldToViewTransformLocation;
}
const GLuint ShaderManager::getProjectionTransformLocation() {
	return gProjectionTransformLocation;
}

const GLuint ShaderManager::getAmbientLightIntensityLocation() {
	return gAmbientLightIntensityLocation;
}
const GLuint ShaderManager::getDirectionalLightIntensityLocation() {
	return gDirectionalLightIntensityLocation;
}
const GLuint ShaderManager::getDirectionalLightDirectionLocation() {
	return gDirectionalLightDirectionLocation;
}
const GLuint ShaderManager::getSpecularLightIntensityLocation() {
	return gSpecularLightIntensityLocation;
}

const GLuint ShaderManager::getKaLocation() {
	return gKaLocation;
}
const GLuint ShaderManager::getKdLocation() {
	return gKdLocation;
}
const GLuint ShaderManager::getKsLocation() {
	return gKsLocation;
}
const GLuint ShaderManager::getModelColourLocation() {
	return gModelColourLocation;
}
const GLuint ShaderManager::getCameraPositionLocation() {
	return gCameraPositionLocation;
}

void ShaderManager::loadShaders() {
	buildShaders();
}