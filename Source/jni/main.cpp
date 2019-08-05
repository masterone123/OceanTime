#include <jni.h>
#include <android/log.h>
#include "Substrate.h"
#include "mcpe.h"

#define LOG_TAG "OceanTime"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))


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
			
			if (Biome::mBiomes[i] != Biome::beaches)
			if (Biome::mBiomes[i] != Biome::deepOcean)
			if (Biome::mBiomes[i] != Biome::hell)
			if (Biome::mBiomes[i] != Biome::mushroomIsland)
			if (Biome::mBiomes[i] != Biome::mushroomIslandShore)
			if (Biome::mBiomes[i] != Biome::ocean)
			if (Biome::mBiomes[i] != Biome::river)
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


JNIEXPORT jint JNI_OnLoad(JavaVM*vm,void*)
{
	LOGI("Ocean Time! ");
	
	MSHookFunction(
	(void* )&Biome::initBiomes, 
	(void* )&hook_Biome_initBiomes, 
	(void**)&real_Biome_initBiomes
	);
	
	return JNI_VERSION_1_6;
}
