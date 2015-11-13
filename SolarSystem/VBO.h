#ifndef VBO_H
#define VBO_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

class VBO {
public:
	VBO(std::string pathToModel);
	~VBO() {};

	void VBO::loadModel();

	GLuint getVertexBufferObject() const;
	GLuint getVertexListSize() const;
	std::string getModelPath() const;

private:
	GLuint vertexBufferObject;
	GLuint vertexListSize;
	std::string modelPath;
};

#endif // VBO_H