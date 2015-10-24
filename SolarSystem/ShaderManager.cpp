#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Assertion.h"
#include "ShaderManager.h"

void ShaderManager::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType){
    GLuint shaderObj = glCreateShader(shaderType);
	ASSERTION(shaderObj==0, "Error creating shader type " + shaderType);

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
		ASSERTION(!success, ss.str());
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
	ASSERTION(shaderProgram==0, "Error creating shader program");

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
		ASSERTION(success==0, ss.str());
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::stringstream ss;
		ss << "Error linking shader program: " << errorLog << std::endl;
		ASSERTION(!success, ss.str());
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLocation = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    ASSERTION(gModelToWorldTransformLocation != 0xFFFFFFFF, "Error: gModelToWorldTransformLocation not valid");
    
	gWorldToViewTransformLocation = glGetUniformLocation(shaderProgram, "gWorldToViewTransform");
	ASSERTION(gWorldToViewTransformLocation != 0xFFFFFFFF, "Error: gWorldToViewTransformLocation not valid");
    
	gProjectionTransformLocation = glGetUniformLocation(shaderProgram, "gProjectionTransform"); 
	ASSERTION(gProjectionTransformLocation != 0xFFFFFFFF, "Error: gProjectionTransformLocation not valid");

	gAmbientLightIntensityLocation = glGetUniformLocation(shaderProgram, "gAmbientLightIntensity");
	ASSERTION(gAmbientLightIntensityLocation != 0xFFFFFFFF, "Error: gAmbientLightIntensityLocation not valid");
	
	gDirectionalLightIntensityLocation = glGetUniformLocation(shaderProgram, "gDirectionalLightIntensity");
	ASSERTION(gDirectionalLightIntensityLocation != 0xFFFFFFFF, "Error: gDirectionalLightIntensityLocation not valid");
	
	gDirectionalLightDirectionLocation = glGetUniformLocation(shaderProgram, "gDirectionalLightDirection");
	ASSERTION(gDirectionalLightDirectionLocation != 0xFFFFFFFF, "Error: gDirectionalLightDirectionLocation not valid");

	gKaLocation = glGetUniformLocation(shaderProgram, "gKa");
	ASSERTION(gKaLocation != 0xFFFFFFFF, "Error: gKaLocation not valid");
	
	gKdLocation = glGetUniformLocation(shaderProgram, "gKd");
	ASSERTION(gKaLocation != 0xFFFFFFFF, "Error: gKdLocation not valid");
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

const GLuint ShaderManager::getKaLocation() {
	return gKaLocation;
}
const GLuint ShaderManager::getKdLocation() {
	return gKdLocation;
}

void ShaderManager::loadShaders() {
	buildShaders();
}