#pragma once

class BlockID
{
public:
	unsigned char id;
};

class FullBlock
{
public:
	BlockID id;	// 1
	char filler[3];	// 4
};

class Block
{
public:
	char filler[4];	// 4
	FullBlock fullblock;	// 8
	char filler2[624];	// 632
	
	static Block* mWoodPlanks;
};

class BlockPos
{
public:
	int x;
	int y;
	int z;
	
public:
	BlockPos(float, float, float);
};

class BlockSource
{
public:
	void setBlock(int, int, int, BlockID, int);
};
