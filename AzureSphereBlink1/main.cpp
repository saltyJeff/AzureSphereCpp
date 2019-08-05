#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <new>

#include <applibs/log.h>
#include <applibs/gpio.h>

#include "MakeRand.h"

int main(void)
{
    // This minimal Azure Sphere app repeatedly toggles GPIO 9, which is the green channel of RGB
    // LED 1 on the MT3620 RDB.
    // Use this app to test that device and SDK installation succeeded that you can build,
    // deploy, and debug an app with Visual Studio, and that you can deploy an app over the air,
    // per the instructions here: https://docs.microsoft.com/azure-sphere/quickstarts/qs-overview
    //
    // It is NOT recommended to use this as a starting point for developing apps; instead use
    // the extensible samples here: https://github.com/Azure/azure-sphere-samples

    int fd = GPIO_OpenAsOutput(9, GPIO_OutputMode_PushPull, GPIO_Value_High);

	// Play with const references to prove they work
	char* msg = "General Kenobi";
	char*& msgRef = msg;
	msgRef = "You are a bold one.";
	Log_Debug("%s\n", msg);

	// Play with static allocated class instances to prove they work
	MakeRand rando;
	const int randsToGenerate = 5;
	msgRef = "Here is a random number: %d ( %d / %d )\n";
	for (int i = 0; i < randsToGenerate; i++) {
		Log_Debug(msg, rando.makeRand(), i+1, randsToGenerate);
	}

	// Play with dynamic allocated class instances to prove they work
	MakeRand* randoPtr = new MakeRand();
	for (int i = 0; i < randsToGenerate; i++) {
		Log_Debug(msg, randoPtr->makeRand(), i+1, randsToGenerate);
	}
	delete randoPtr;

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