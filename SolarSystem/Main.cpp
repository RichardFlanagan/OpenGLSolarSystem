#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>

#include "Assertion.h"
#include "ShaderBuilder.h"

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
std::string windowTitle = "A00193644 : Solar System";


int main(int argc, char** argv){

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle.c_str());

    GLenum res = glewInit();
    if (res != GLEW_OK) {
		std::stringstream ss;
		std::cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		ASSERTION(res != GLEW_OK, "");
    }

	ShaderBuilder a;
	std::cout << a.getErrorStatus();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glutMainLoop();
    
    return 0;
}