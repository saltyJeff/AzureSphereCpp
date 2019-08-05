#include "MakeRand.h"
#include <applibs/log.h>
#include <cstdlib> // use the C++-ify version of the standard library

// make sure Ctors/Dtors work
MakeRand::MakeRand() {
	Log_Debug("Aloha\n");
}
MakeRand::~MakeRand() {
	Log_Debug("Aloha but the other one\n");
}

int MakeRand::makeRand() {
	return std::rand();
}