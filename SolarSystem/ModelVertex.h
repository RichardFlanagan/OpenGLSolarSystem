/*
File: ModelVertex.h
Author: Richard Flanagan
Description:
*/
#ifndef MODEL_VERTEX_H
#define MODEL_VERTEX_H

#include <glm/glm.hpp>

struct ModelVertex
{
	glm::vec3 position;
	//glm::vec3 textureVertex;
	glm::vec3 normal;

	ModelVertex(const glm::vec3& pos, const glm::vec3& norm){
		position = pos;
		//textureVertex = glm::vec3(-1, -1, -1);
		normal = norm;
	}

	//ModelVertex(const glm::vec3& pos, const glm::vec3& tex, const glm::vec3& norm) {
	//	position = pos;
	//	textureVertex = tex;
	//	normal = norm;
	//}
};

#endif // MODEL_VERTEX_H