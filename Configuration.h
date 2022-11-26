#pragma once

class Config final
{
	Config() = delete;
	~Config() = delete;
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

public:
	static constexpr float WindowWidth = 1024;
	static constexpr float WindowHeight = 768;
	static constexpr char* WindowTitle = "Fish Blastar";
	static constexpr unsigned int MaxFramerate = 60;

	static constexpr unsigned int SkyColor = 0xc2d7f9ff;
	static constexpr unsigned int SeaColor = 0x3cb8f2ff;

	static constexpr char* HeroImage = "./resources/hero.png";
	static constexpr char* Trash1Image = "./resources/trash_1.png";
    static constexpr char* Trash2Image = "./resources/trash_2.png";
    static constexpr char* FontPath = "./resources/Funhouse.ttf";

	static constexpr float TrashSpeed = 100;
	static constexpr float ProjectileSpeed = 200;
	static constexpr float HeroSpeed = 100;

	static constexpr unsigned int MaxProjectilesCount = 1;
	static constexpr unsigned int MaxTrashesCount = 5;

	static constexpr float ProjectileSize = 5;

	static constexpr float TrashSpawnPeriod = 3;
	static constexpr float TrashSpawnOffset = 50;

    static constexpr char* PopupTitle = "Game over";
    static constexpr char* PopupRestart = "Restart";
    static constexpr char* PopupTipLabel = "Press space to restart";
};
