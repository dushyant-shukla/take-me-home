#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class Boundary : public Component {

public:

	Boundary();
	~Boundary();

	void Update();
	// in the update method 
	// take the body component and check for hitting right and left wall and reverse the velocities accordingly
	void Serialize(Json::Value json);
	void Initialize();
	void HandleEvent(Event* pEvent);

	void SetStartPosition(glm::vec3 position);
	void SetDistance(float value);

private:
	glm::vec3 startPosition;
	float distance;
};
