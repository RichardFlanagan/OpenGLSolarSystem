#include "VBO.h"
#include <string>
#include <vector>
#include "ModelLoader.h"

VBO::VBO(std::string pathToModel) {
	vertexBufferObject = -1;
	vertexListSize = 0;
	modelPath = pathToModel;
}


void VBO::loadModel() {
	ModelLoader modelLoader;
	assert(modelLoader.loadModelFromObjFile(modelPath));

	std::vector<ModelVertex> vertices = modelLoader.getVertices();
	vertexListSize = vertices.size();

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertex) * vertexListSize, &vertices[0], GL_STATIC_DRAW);
}

GLuint VBO::getVertexBufferObject() const {
	return vertexBufferObject;
}

GLuint VBO::getVertexListSize() const {
	return vertexListSize;
}

std::string VBO::getModelPath() const {
	return modelPath;
}
