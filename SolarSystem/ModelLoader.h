/*
File: ModelLoader.h
Author: Richard Flanagan
Description:
*/
#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>
#include <vector>

#include "ModelVertex.h"

class ModelLoader{
public:
	ModelLoader() {};
	~ModelLoader() {};
	bool loadModelFromObjFile(std::string path);
	std::vector<ModelVertex>& getVertices();

private:
	std::vector<ModelVertex> vertices;
};


inline std::vector<ModelVertex>& ModelLoader::getVertices(){
	return vertices;
}

#endif // MODEL_LOADER_H