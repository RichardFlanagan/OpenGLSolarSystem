#version 330


in vec3 glPosition0; // Transformed position
in vec3 Position0; // Local position
in vec3 Normal0; // Pixel normal
out vec4 FragColor; // Output the pixel colour

// Light Intensities
uniform vec3 gAmbientLightIntensity;
uniform vec3 gDiffuseLightIntensity;
uniform vec3 gSpecularLightIntensity;

// Material constants
uniform float gKa; // Ambient reflectivity
uniform float gKd; // Diffuse reflectivity
uniform float gKs; // Specular reflectivity

uniform vec3 gModelColourLocation; // Model Colour
uniform vec3 gCameraPositionLocation; // Camera Position
uniform mat4 gModelToWorldTransform; // Model to world transform




/*
	Calculate the colour of this fragment.
	This will also draw coloured xyz axis on the model.
*/
void calculateColour(out vec4 colour){
	float offset = 0.03f;
	if(Position0.x > -offset && Position0.x < offset){ // Draw the x axis in red
		colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(Position0.y > -offset && Position0.y < offset){ // Draw the y axis in blue
		colour = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	} 
	else if(Position0.z > -offset && Position0.z < offset){ // Draw the z axis in green
		colour = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	} 
	else{ // Draw the planet using its own colour
		colour = vec4(gModelColourLocation.xyz, 1.0f); 
	}
}




/*
	Calculate the ambient lighting for this fragment.
*/
void calcAmbientLight(out vec4 ambientLight){
	// Ia = Ka * ambientLightIntensity
	ambientLight = gKa * vec4(gAmbientLightIntensity, 1.0);
	ambientLight = clamp(ambientLight, 0.0f, 1.0f);
}




/*
	Calculate the diffuse lighting for this fragment.
*/
void calcDiffuseLight(in vec3 normalInWorldSpace, in vec3 lightDirection, out vec4 diffuseLight){	
	// Calculate N.L
	float diffuseFactor = dot(normalInWorldSpace, lightDirection);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);
	
	// Id = kd * lightItensity * N.L
    diffuseLight = gKd * vec4(gDiffuseLightIntensity, 1.0f) * diffuseFactor;
	diffuseLight = clamp(diffuseLight, 0.0f, 1.0f);
}




/*
	Calculate the specular lighting for this fragment.
*/
void calcSpecularLight(in vec3 normalInWorldSpace, in vec3 lightDirection, in vec3 viewVector, out vec4 specularLight){
	// Calculate (N.H)**a
	vec3 H = normalize(lightDirection+viewVector);
	float nha = pow(dot(normalInWorldSpace, H), 30);

	// Is = ks * lightIntensity * (N.H)**a
	specularLight = gKs * vec4(gSpecularLightIntensity, 1.0f) * nha;
	specularLight = clamp(specularLight, 0.0f, 1.0f);
}




/*
	Calculate the lighting for this fragment.
*/
void calcLightIntensity(out vec4 lightIntensity){
	// The corrected normal
	vec3 normalInWorldSpace = normalize((gModelToWorldTransform * vec4(Normal0, 0.0)).xyz);

	// The direction to the light source
	// Since it doesn't change relative to the origin (it is a point light at the origin), we can hard code it
	vec3 lightDirection = normalize((gModelToWorldTransform * vec4(-1.0f)).xyz);

	// The vector to the camera
	vec3 viewVector = normalize(gCameraPositionLocation);

	// Calculate ambient light
	vec4 ambientLight;
	calcAmbientLight(ambientLight);

	// Calculate diffuse point light
	vec4 diffuseLight;
	calcDiffuseLight(normalInWorldSpace, lightDirection, diffuseLight);
	
	// Calculate specular light
	vec4 specularLight;
	calcSpecularLight(normalInWorldSpace, lightDirection, viewVector, specularLight);
	
	// Calculate the composite light, and make sure it is between 0 and 1.
	lightIntensity = (ambientLight + diffuseLight + specularLight);
	lightIntensity = clamp(lightIntensity, 0.0f, 1.0f);
}




void main(){
	vec4 colour;
	calculateColour(colour);

	vec4 lightIntensity;
	calcLightIntensity(lightIntensity);

    FragColor = colour * lightIntensity;
}