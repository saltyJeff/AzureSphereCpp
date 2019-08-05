#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>
// needed for "operator new" and "operator delete"
#include <new>

#include <applibs/log.h>
#include <applibs/gpio.h>

// use randomly generated numbers so the compiler can't optimize them out
#include "MakeRand.h"
#include "AnnoyingMakeRand.h"
// try out a STL container
#include <vector>

int main(void) {
	// Play with references to prove they work
	char* msg = "General Kenobi";
	char*& msgRef = msg;
	Log_Debug("%s\n", msg);
	msgRef = "You are a bold one.";
	Log_Debug("%s\n", msg);

	// Play with static allocated class instances to prove they work
	MakeRand rando;
	const int randsToGenerate = 5;
	msgRef = "Here is a random number from your static instance: %d ( %d / %d )\n";
	for (int i = 0; i < randsToGenerate; i++) {
		Log_Debug(msg, rando.makeRand(), i+1, randsToGenerate);
	}

	// Play with dynamic allocated class instances to prove they work
	MakeRand* randoPtr = new MakeRand();
	msgRef = "Here is a random number from your dynamic instance: %d ( %d / %d )\n";
	for (int i = 0; i < randsToGenerate; i++) {
		Log_Debug(msg, randoPtr->makeRand(), i+1, randsToGenerate);
	}
	delete randoPtr;

	// Play with inheritance to prove it works
	AnnoyingMakeRand* annoyingPtr = new AnnoyingMakeRand();
	std::vector<int> vec; // Also try a STL container
	for (int i = 0; i < randsToGenerate; i++) {
		vec.push_back(annoyingPtr->makeRand());
	}
	delete annoyingPtr;

	Log_Debug("Dumping contents of the annoying vector:\n");
	for (int i : vec) {
		Log_Debug("%d\n", i);
	}

	// the rest of the blink demo
	int fd = GPIO_OpenAsOutput(9, GPIO_OutputMode_PushPull, GPIO_Value_High);
    if (fd < 0) {
        Log_Debug(
            "Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
            strerror(errno), errno);
        return -1;
    }

    const struct timespec sleepTime = {1, 0};
    while (true) {
        GPIO_SetValue(fd, GPIO_Value_Low);
        nanosleep(&sleepTime, NULL);
        GPIO_SetValue(fd, GPIO_Value_High);
        nanosleep(&sleepTime, NULL);
    }
}