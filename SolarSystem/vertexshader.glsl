#version 330

layout (location = 0) in vec3 Position; // Position of the vertex
layout (location = 1) in vec3 Normal; // Vertex normal

out vec3 glPosition0; // The transformed position
out vec3 Position0; // The original position
out vec3 Normal0; // The vertex normal

// Transformations
uniform mat4 gModelToWorldTransform;
uniform mat4 gWorldToViewTransform;
uniform mat4 gProjectionTransform;




/*
	Calculate the transformation for this vertex.
*/
void transformationPosition(out vec4 transform){
	vec4 vertexPositionInModelSpace = vec4(Position, 1);
	vec4 vertexInWorldSpace = gModelToWorldTransform * vertexPositionInModelSpace;
	vec4 vertexInCameraSpace = gWorldToViewTransform * vertexInWorldSpace;
	vec4 vertexInClipSpace = gProjectionTransform * vertexInCameraSpace;
	transform = vertexInClipSpace;
}

    
	
	                                                   
void main(){  
	transformationPosition(gl_Position);
	
	glPosition0 = gl_Position.xyz;
	Position0 = Position;
	Normal0 = Normal;
}