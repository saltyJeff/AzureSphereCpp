#pragma once
#include "MakeRand.h"
class AnnoyingMakeRand: public MakeRand {
public:
	AnnoyingMakeRand();
	virtual ~AnnoyingMakeRand();

	virtual int makeRand();
};

