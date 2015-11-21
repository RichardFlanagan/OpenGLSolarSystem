#version 330

////////////////////////////// (OLD CODE) //////////////////////////////
/*
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

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

// Specular light parameters
uniform vec3 gSpecularLightIntensity;

// Material constants
uniform float gKa;
uniform float gKd;
uniform float gKs;

// Model Colour
uniform vec3 gModelColourLocation;
uniform vec3 gCameraPositionLocation;


/ *
	Calculate the transformation matrix for this vertex
* /
void calculateTransformationMatrix(out vec4 transform){
	vec4 vertexPositionInModelSpace = vec4(Position, 1);
	vec4 vertexInWorldSpace = gModelToWorldTransform * vertexPositionInModelSpace;
	vec4 vertexInCameraSpace = gWorldToViewTransform * vertexInWorldSpace;
	vec4 vertexInClipSpace = gProjectionTransform * vertexInCameraSpace;
	transform = vertexInClipSpace;
}

/ *
	Calculate the light intensity at this vertex
* /
void calculateLightIntensity(out vec4 lightIntensity){
	// Find the normal in world space and normalise it
	vec3 normalInWorldSpace = (gModelToWorldTransform * vec4(Normal, 0.0)).xyz;
	normalInWorldSpace = normalize(normalInWorldSpace);

	// Setup the light direction and normalise it
	vec3 lightDirection = normalize(-gDirectionalLightDirection);

	// Get the view vector
	vec3 camPos = vec3(0.0f, 20.0f, 40.0f);
    vec3 viewVector = (camPos-Position);


	//
	// Calculate the ambient light intensity at the vertex 
	//
	// Ia = Ka * ambientLightIntensity

	vec4 ambientLightIntensity = gKa * vec4(gAmbientLightIntensity, 1.0);



	//
	// Calculate the directional light intensity at the vertex
	//
	// Id = kd * lightItensity * N.L
	
	// Calculate N.L
	float diffuseFactor = dot(normalInWorldSpace, lightDirection);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);
	
	// Id = kd * lightItensity * N.L
    vec4 diffuseLightIntensity = gKd * vec4(gDirectionalLightIntensity, 1.0f) * diffuseFactor;



	//
	// Calculate the specular light
	//
	// Is = ks * lightIntensity * (N.H)**a

	// Calculate (N.H)**a
	vec3 H = normalize(lightDirection+viewVector);
	float nha = pow(dot(normalInWorldSpace, H), 30);

	// Is = ks * lightIntensity * (N.H)**a
	vec4 specularLightIntensity = gKs * vec4(gSpecularLightIntensity, 1.0f) * nha;


    //
	// Final vertex colour is the product of the vertex colour and the total light intensity at the vertex 
	//
	lightIntensity = ambientLightIntensity + diffuseLightIntensity + specularLightIntensity;
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
		Colour0 = vec4(gModelColourLocation.x, gModelColourLocation.y, gModelColourLocation.z, 1.0f);
	}
}
*/



////////////////////////////// (NEW CODE) //////////////////////////////




layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 Position0;
out vec3 Normal0;
out mat4 gModelToWorldTransform0;

// Transforms
uniform mat4 gModelToWorldTransform;
uniform mat4 gWorldToViewTransform;
uniform mat4 gProjectionTransform;




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


                                                       
void main(){  
	Position0 = Position;
	Normal0 = Normal;
	gModelToWorldTransform0 = gModelToWorldTransform;
	calculateTransformationMatrix(gl_Position);
}