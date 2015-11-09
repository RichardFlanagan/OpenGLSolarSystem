#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
//layout (location = 1) in vec4 Colour;

out vec4 Colour0;
out vec4 LightIntensity0;

// Transforms
uniform mat4 gModelToWorldTransform;
uniform mat4 gWorldToViewTransform;
uniform mat4 gProjectionTransform;

// Ambient light parameters
uniform vec3 gAmbientLightIntensity;

// Directional light parameters
uniform vec3 gDirectionalLightIntensity;
uniform vec3 gDirectionalLightDirection;

// Material constants
uniform float gKa;
uniform float gKd;


/*
	Calculate the transformation matrix for this vertex
*/
void calculateTransformationMatrix(out vec4 transform){
	vec4 vertexPositionInModelSpace = vec4(Position, 1);
	vec4 vertexInWorldSpace = gModelToWorldTransform * vertexPositionInModelSpace;
	vec4 vertexInCameraSpace = gWorldToViewTransform * vertexInWorldSpace;
	vec4 vertexInClipSpace = gProjectionTransform * vertexInCameraSpace;
	transform = vertexInClipSpace;
}

/*
	Calculate the light intensity at this vertex
*/
void calculateLightIntensity(out vec4 lightIntensity){
	// Calculate the ambient light intensity at the vertex : Ia = Ka * ambientLightIntensity
	vec4 ambientLightIntensity = gKa * vec4(gAmbientLightIntensity, 1.0);

	// Calculate the directional light intensity at the vertex
	// Find the normal in world space and normalise it
	vec3 normalInWorldSpace = (gModelToWorldTransform * vec4(Normal, 0.0)).xyz;
	normalInWorldSpace = normalize(normalInWorldSpace);
	// Setup the light direction and normalise it
	vec3 lightDirection = normalize(-gDirectionalLightDirection);

	// Id = kd * lightItensity * N.L
	// Calculate N.L
	float diffuseFactor = dot(normalInWorldSpace, lightDirection);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);
	// N.L * light source colour * intensity
    vec4 diffuseLightIntensity = gKd * vec4(gDirectionalLightIntensity, 1.0f) * diffuseFactor;
   
	// Final vertex colour is the product of the vertex colour and the total light intensity at the vertex 
	lightIntensity = ambientLightIntensity + diffuseLightIntensity;
}
                                                       
void main(){  
	calculateTransformationMatrix(gl_Position);
	calculateLightIntensity(LightIntensity0);

	if(Position.x > -0.01f && Position.x < 0.01f){
		Colour0 = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(Position.y > -0.01f && Position.y < 0.01f){
		Colour0 = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	} 
	else if(Position.z > -0.01f && Position.z < 0.01f){
		Colour0 = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	} 
	else{
		Colour0 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}