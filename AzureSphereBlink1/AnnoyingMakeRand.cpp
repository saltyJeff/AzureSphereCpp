#include "AnnoyingMakeRand.h"
#include <applibs/log.h>
#include <cstdlib>

AnnoyingMakeRand::AnnoyingMakeRand() : MakeRand() {
	Log_Debug("ANNOYING WELCOME\n");
};
AnnoyingMakeRand::~AnnoyingMakeRand() {
	Log_Debug("ANNOYING GOODBYE\n");
}
int AnnoyingMakeRand::makeRand() {
	int baseRand = MakeRand::makeRand();
	Log_Debug("You know, if your number was in hex it would be: %X\n", baseRand);
	return baseRand;
}