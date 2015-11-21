#version 330


////////////////////////////// (OLD CODE) //////////////////////////////


/*
in vec4 LightIntensity0;
in vec4 Colour0;
out vec4 FragColor;


void main(){
    FragColor = Colour0 * LightIntensity0;
}
*/

////////////////////////////// (NEW CODE) //////////////////////////////

in vec3 glPosition0;
in vec3 Position0;
in vec3 Normal0;

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

uniform mat4 gModelToWorldTransform;
out vec4 FragColor;


void calculateLightIntensity(out vec4 lightIntensity){
	// Find the normal in world space and normalise it
	vec3 normalInWorldSpace = (gModelToWorldTransform * vec4(Normal0, 0.0)).xyz;
	normalInWorldSpace = normalize(normalInWorldSpace);

	// Setup the light direction and normalise it
	//vec3 lightDirection = normalize(-gDirectionalLightDirection);
	vec3 lightDirection = normalize(glPosition0); // Sun is at 0,0,0, so the light vector is the pos of this point

	// Get the view vector
	//vec3 camPos = vec3(0.0f, 20.0f, 40.0f);
    vec3 viewVector = normalize(gCameraPositionLocation - glPosition0);  // normalize(gCameraPositionLocation - Position0);


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


void calculateColour(out vec4 colour){
	float offset = 0.03f;
	if(Position0.x > -offset && Position0.x < offset){
		colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(Position0.y > -offset && Position0.y < offset){
		colour = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	} 
	else if(Position0.z > -offset && Position0.z < offset){
		colour = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	} 
	else{
		colour = vec4(gModelColourLocation.xyz, 1.0f);
	}
}


void calcAmbientLight(out vec4 ambientLight){
	// Ia = Ka * ambientLightIntensity
	ambientLight = gKa * vec4(gAmbientLightIntensity, 1.0);
	ambientLight = clamp(ambientLight, 0.0f, 1.0f);
}


void calcDiffuseLight(in vec3 normalInWorldSpace, in vec3 lightDirection, out vec4 diffuseLight){	
	// Calculate N.L
	float diffuseFactor = dot(normalInWorldSpace, lightDirection);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);
	
	// Id = kd * lightItensity * N.L
    diffuseLight = gKd * vec4(gDirectionalLightIntensity, 1.0f) * diffuseFactor;
	diffuseLight = clamp(diffuseLight, 0.0f, 1.0f);
}


void calcSpecularLight(in vec3 normalInWorldSpace, in vec3 lightDirection, out vec4 specularLight){
    vec3 viewVector = normalize(gCameraPositionLocation);

	// Calculate (N.H)**a
	vec3 H = normalize(-lightDirection+viewVector);
	float nha = pow(dot(normalInWorldSpace, H), 30);

	// Is = ks * lightIntensity * (N.H)**a
	specularLight = gKs * vec4(gSpecularLightIntensity, 1.0f) * nha;
	specularLight = clamp(specularLight, 0.0f, 1.0f);
}


void calcLightIntensity(out vec4 lightIntensity){
	vec3 normalInWorldSpace = normalize((gModelToWorldTransform * vec4(Normal0, 0.0)).xyz);
	vec3 lightDirection = normalize((gModelToWorldTransform * vec4(-1.0f)).xyz);

	vec4 ambientLight;
	calcAmbientLight(ambientLight);

	vec4 diffuseLight;
	calcDiffuseLight(normalInWorldSpace, lightDirection, diffuseLight);
	
	lightDirection = normalize((gModelToWorldTransform * vec4(0.0f, 0.0f, 0.0f, 0.0f)).xyz);
	vec4 specularLight;
	calcSpecularLight(normalInWorldSpace, lightDirection, specularLight);
	
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