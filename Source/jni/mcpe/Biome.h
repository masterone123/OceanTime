#pragma once

class Biome
{
public:
	static Biome* mBiomes[256];
	
	static Biome* deepOcean;			// Deep Ocean
	static Biome* hell;					// Nether
	static Biome* mushroomIsland;		// Mushroom Fields
	static Biome* mushroomIslandShore;	// Mushroom Field Shore
	static Biome* ocean;				// Ocean
	static Biome* river;				// River
	static Biome* roofedForest;			// Dark Forest
	static Biome* sky;					// The End
	static Biome* stoneBeach;			// Stone Shore
	
public:
	static void initBiomes();
};
