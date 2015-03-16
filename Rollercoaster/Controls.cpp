#include "Controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position	= glm::vec3(0.0, 10.0, 15);
glm::vec3 centre	= glm::vec3(0.0, 10.0, 0);
glm::vec3 up		= glm::vec3(0.0, 1.0, 0.0);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 70.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;



void ComputeMatrices(int width, int height)
{
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, (GLfloat)width / (GLfloat)height, 0.05f, 2000.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(position, centre, up);
}