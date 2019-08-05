#pragma once

class Biome
{
	public:
	static Biome* mBiomes[256];
	
	static Biome* beaches;
	static Biome* deepOcean;
	static Biome* hell;
	static Biome* mushroomIsland;
	static Biome* mushroomIslandShore;
	static Biome* ocean;
	static Biome* river;
	static Biome* sky;
	static Biome* stoneBeach;
	
	public:
	static void initBiomes();
};
