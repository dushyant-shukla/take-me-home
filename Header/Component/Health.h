#pragma once

#include "Component.h"

class Health : public Component {

public:

	Health();
	~Health();

	void Update();
	void Serialize(Json::Value json);
	void Initialize();
	void HandleEvent(Event* pEvent);

	int GetLives();
	void SetLives(int value);

	float GetDamage();
	void SetDamage(float value);

private:

	float damage;
	int lives;
};