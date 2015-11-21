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

in vec3 Position0;
in vec3 Normal0;
uniform mat4 gModelToWorldTransform;
out vec4 FragColor;

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



void calculateLightIntensity(out vec4 lightIntensity){
	// Find the normal in world space and normalise it
	vec3 normalInWorldSpace = (gModelToWorldTransform * vec4(Normal0, 0.0)).xyz;
	normalInWorldSpace = normalize(normalInWorldSpace);

	// Setup the light direction and normalise it
	vec3 lightDirection = normalize(-gDirectionalLightDirection);

	// Get the view vector
	vec3 camPos = vec3(0.0f, 20.0f, 40.0f);
    vec3 viewVector = (gCameraPositionLocation-Position0);


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
	lightIntensity = ambientLightIntensity + diffuseLightIntensity-diffuseLightIntensity + specularLightIntensity-specularLightIntensity;
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


void main(){
	vec4 LightIntensity0;
	calculateLightIntensity(LightIntensity0);

	vec4 Colour0;
	calculateColour(Colour0);

    FragColor = Colour0 * LightIntensity0;
}