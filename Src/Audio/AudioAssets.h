#pragma once

#define AUDIO_GAME_START "Resources/Sound/game_start.wav"
#define AUDIO_EAT_GHOST "Resources/Sound/eat_ghost.wav"
#define AUDIO_DEATH_1 "Resources/Sound/death_1.wav"
#define AUDIO_POWER_SNACK "Resources/Sound/power_pellet.wav"
#define AUDIO_MUNCH "Resources/Sound/munch.wav"
#define AUDIO_SIREN "Resources/Sound/siren_1.wav"
#define AUDIO_RETREATING "Resources/Sound/retreating.wav"

#define VOLUME 50
#define VOLUME_MUNCH 10
#define VOLUME_SIREN 60

enum class Sounds {
	None,
	PowerSnack,
	EatGhost,
	Death,
	Munch,
	GameStart,
	Siren,
	Retreating
};