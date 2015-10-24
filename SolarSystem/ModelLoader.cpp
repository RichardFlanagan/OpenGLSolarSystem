/**
aitmesh.cpp
@author Richard Flanagan, A00193644
*/

#include "ModelLoader.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

/*
Load the obj file, and convert the data into a list of aitVertex objects.
@param std::string The path to the obj file (including filename)
@return bool for success of operation
*/
bool ModelLoader::loadModelFromObjFile(std::string path) {

	//
	// Initialize file input
	//
	std::filebuf file; // File input object
	if (!file.open(path, std::ios::in)) { // If file is invalid/can't open
		return false; // Return as error
	}
	std::istream inputStream(&file); // File reader object

	//
	// Parse file
	//
	std::vector<glm::vec3> vVectors; // The list of vertex position vec3s
	std::vector<glm::vec3> vnVectors; // The list of vertex normal vec3s

	std::string line = ""; // The string which will hold the next line from the istream

	while (getline(inputStream, line)) { // While where is more lines to get, get the line and assign to the line var

		std::string tag = ""; // The string which will hold the current tag
		float x = 0, y = 0, z = 0; // Holds the x,y,z values of the vectors/normals

		std::istringstream in(line);
		in >> tag;

		//
		// v Geometric vertex: x, y, z, (w)
		//
		if (tag == "v") {
			in >> x >> y >> z; // Get the values form the string
			vVectors.push_back(glm::vec3(x, y, z)); // Add the generated vec3 to the list
		}

		//
		// vn Normal vector: i, j, k
		//
		else if (tag == "vn") {
			in >> x >> y >> z; // Get the values form the string
			vnVectors.push_back(glm::vec3(x, y, z)); // Add the generated vec3 to the list
		}

		//
		// f Face: v1(/vt1)(/vn1), (v2)(/vt2)(/vn2), (v3)(/vt3)(/vn3), ...
		//
		else if (tag == "f") {
			std::string faceVertexInfo = ""; // The face's vertex as described in the obj file
			while (in >> faceVertexInfo) { // While there is another vertex described

				int vIndex = 0,	// The index+1 of the position vertex in the vVector
					vtIndex = 0, // The index+1 of the texture vertex in the vtVector
					vnIndex = 0; // The index+1 of the normal in the vnVector

				std::istringstream faceVertexInfoStream(faceVertexInfo); // The stringstream which reads the elements in the face vertex
				std::string str = ""; // The string which holds the output from getline 

				getline(faceVertexInfoStream, str, '/'); // Get the v element from the stream
				vIndex = atoi(str.c_str()); // Convert the element into a number

				getline(faceVertexInfoStream, str, '/'); // Get the vt element from the stream
				vtIndex = atoi(str.c_str()); // Convert the element into a number

				getline(faceVertexInfoStream, str, '/'); // Get the vn element from the stream
				vnIndex = atoi(str.c_str()); // Convert the element into a number

											 // Create a new aitvertex and add it to the vertices list
				vertices.push_back(
					ModelVertex(
						vVectors[vIndex - 1],
						vnVectors[vnIndex - 1]
						)
					);
			}
		}
	}

	// If we have at least 1 vertex, return true
	return (vertices.size() > 0);
}