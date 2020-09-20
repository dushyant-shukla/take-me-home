#pragma once
#include <stdlib.h>
#include <iostream>

class GameObjectUtility {

public:

	enum class CHARACTER_STATE {
		STAND,
		JUMP,
		WALK,
		DEAD
	};

	friend std::ostream& operator<<(std::ostream& out, const CHARACTER_STATE& v) {
		if (v == CHARACTER_STATE::STAND) {
			out << "CURRENT CHARACTER STATE :: STAND" << std::endl;
		}
		else if (v == CHARACTER_STATE::JUMP) {
			out << "CURRENT CHARACTER STATE :: JUMP" << std::endl;
		}
		else if (v == CHARACTER_STATE::WALK) {
			out << "CURRENT CHARACTER STATE :: WALK" << std::endl;
		}
		else if (v == CHARACTER_STATE::DEAD) {
			out << "CURRENT CHARACTER STATE :: DEAD" << std::endl;
		}

		return out;
	}

	enum class OBJECT_TYPE {
		PLAYER,
		ENEMY_PATROL,
		ENEMY_JUMP,
		ENEMY_TURRET,
		BULLET,
		MISSILE,
		PLAYER_START_SCREEN,
		PLAYER_VICTORY_SCREEN,
		HOME,
		NUM
	};
};