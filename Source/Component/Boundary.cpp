#include "Boundary.h"
#include "GameObject.h"
#include "Transform.h"
#include "TileType.h"

#include <iostream>


Boundary::Boundary() : Component(COMPONENT_TYPE::COMPONENT_BOUNDARY) {
}

Boundary::~Boundary() {
}

void Boundary::Update() {
	// mark active flag to false
	Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	glm::vec3 position = pTransform->GetPosition();
	if (std::abs(startPosition.x - position.x) >= distance || position.x <= 0 || (position.x + pTransform->GetScale().x) >= MAP_WIDTH * TILE_SIZE) {
		this->GetOwner()->SetIsActive(false);
	}
}

void Boundary::Serialize(Json::Value componentData) {
}

void Boundary::Initialize() {
}

void Boundary::HandleEvent(Event* pEvent) {
}

void Boundary::SetStartPosition(glm::vec3 position) {
	startPosition = position;
}

void Boundary::SetDistance(float value) {
	distance = value;
}