#include "Health.h"

Health::Health():Component(COMPONENT_TYPE::COMPONENT_HEALTH), damage(0.0f) {
}

Health::~Health() {
}

void Health::Update() {

}

void Health::Serialize(Json::Value json) {
}

void Health::Initialize() {
}

void Health::HandleEvent(Event* pEvent) {
}

int Health::GetLives() {
	return lives;
}

void Health::SetLives(int value) {
	lives = value;
}

float Health::GetDamage() {
	return damage;
}

void Health::SetDamage(float value) {
	damage = value;
}