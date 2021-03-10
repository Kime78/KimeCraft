#pragma once
#include <glm/glm.hpp>

class Camera
{
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 view;

public:
	Camera();
	void handle_input();
	void upload_uniform();
};