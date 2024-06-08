#pragma once
#include "defs.h"

typedef struct Entity     Entity;

struct Entity {
	int id;
	game_entity type; // Type of Game Entity
	game_gender gender; // Gender of Game Entity
	// EXP which will determine Level
	int exp;
	// Health
	int health;
	int max_health;
	// Mana
	int mana;
	int max_mana;
	// Game Stats
	int brawn;
	int resolve;
	int endurance;
	int agility;
	int knowledge;
	int spirit;
	// Location in World, which Map and which X/Y on that specific Map.
	int x;
	int y;
	int map;

};