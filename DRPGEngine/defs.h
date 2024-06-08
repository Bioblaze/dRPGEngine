#pragma once

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define FPS        60.0
#define LOGIC_RATE (FPS / 1000)

#define ITEMS_DIR "items"			// Directory that contains all Items to be loaded into the System.
#define NPC_DIR "npc"				// Directory that contains all NPCs to be loaded into the System.
#define WORLD_MAP "world.drpg-map"	// World Map File for the dRPG System

#define GAME_WINDOW_TITLE "" // Title for the SDL instantiated Window


// Entity types for Entity Class which can be a NPC or a Player.
enum game_entity {
	ENTITY_PLAYER,		// Player type Entity
	ENTITY_ENEMY,		// Enemy that can cause Battle between a Player
	ENTITY_VENDOR,		// NPC that when a Player interacts Opens up a Vendor
	ENTITY_NPC,			// NPC that will just say some sort of text above head before continuing about their day.
	ENTITY_MUTE,		// NPC that will not respond to Player interaction
	ENTITY_STORYTELLER,	// NPC that will have Dialog
	ENTITY_QUESTGIVER	// NPC that will Give a Quest when you interact
};

// Game Stats used in UI, Inventory, Item Benefit, etc 
enum game_stats {
	STAT_BRAWN,		// Brawn increases Attack 
	STAT_RESOLVE,	// Resolve increase MP
	STAT_ENDURANCE, // Endurance increases HP
	STAT_AGILITY,	// Agility increases Dodge Rate
	STAT_KNOWLEDGE, // Knowledge increases Hit Rate
	STAT_SPIRIT		// Spirit increases MP & HP Regen
};

// NPC/PC Gender Modifier
enum game_gender {
	GENDER_MALE,	// Decides the Audio Beeps, etc.
	GENDER_FEMALE,	// Decides the Audio Beeps, etc.
	GENDER_UNKNOWN	// Decides the Audio Beeps, etc.
};