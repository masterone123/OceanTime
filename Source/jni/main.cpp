#include <jni.h>
#include <android/log.h>
#include "Substrate.h"
#include "mcpe.h"

#define LOG_TAG "OceanTime"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

bool isBonusChestPlaced = 0;

static void (*real_Biome_initBiomes)();
static void hook_Biome_initBiomes()
{
	real_Biome_initBiomes();
	
	int total = 0;
	int other = 0;
	
	for (int i=0; i<256; i++)
	{
		if (Biome::mBiomes[i])
		{
			total++;
			
			if (Biome::mBiomes[i] != Biome::deepOcean)
			if (Biome::mBiomes[i] != Biome::hell)
			if (Biome::mBiomes[i] != Biome::mushroomIsland)
			if (Biome::mBiomes[i] != Biome::mushroomIslandShore)
			if (Biome::mBiomes[i] != Biome::ocean)
			if (Biome::mBiomes[i] != Biome::river)
			if (Biome::mBiomes[i] != Biome::roofedForest)
			if (Biome::mBiomes[i] != Biome::sky)
			if (Biome::mBiomes[i] != Biome::stoneBeach)
			{
				other++;
				
				if (i > 100)	Biome::mBiomes[i] = Biome::deepOcean;
				else	Biome::mBiomes[i] = Biome::ocean;
			}
		}
	}
	
	LOGI("%d biomes in total, %d of them are replaced. ", total, other);
}

static bool (*real_BonusChestFeature__place)(BonusChestFeature*, BlockSource&, BlockPos const&, Random&);
static bool hook_BonusChestFeature__place(BonusChestFeature* self, BlockSource& blocksource, BlockPos const& blockpos, Random& par3)
{
	if (!isBonusChestPlaced)
	{
		BlockPos plankpos
		(
			blockpos.x, 
			62, 
			blockpos.z
		);
		
		self -> _setBlockAndData
		(
			blocksource, 
			plankpos, 
			Block::mWoodPlanks -> fullblock
		);
		
		LOGI("Placed plank at %d, %d, %d", plankpos.x, plankpos.y, plankpos.z);
	}
	
	if (real_BonusChestFeature__place(self, blocksource, blockpos, par3))
	{
		isBonusChestPlaced = 1;
		return 1;
	}
	return 0;
}

JNIEXPORT jint JNI_OnLoad(JavaVM*vm,void*)
{
	LOGI("Ocean Time! ");
	
	MSHookFunction
	(
		(void* )&Biome::initBiomes, 
		(void* )&hook_Biome_initBiomes, 
		(void**)&real_Biome_initBiomes
	);
	
	MSHookFunction
	(
		(void* )&BonusChestFeature::_place, 
		(void* )&hook_BonusChestFeature__place, 
		(void**)&real_BonusChestFeature__place
	);
	
	return JNI_VERSION_1_6;
}
