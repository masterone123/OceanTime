#pragma once

class Feature
{
public:
	void _setBlockAndData(BlockSource&, BlockPos const&, FullBlock const&) const;
};

class BonusChestFeature : public Feature
{
public:
	bool _place(BlockSource&, BlockPos const&, Random&) const;
};
