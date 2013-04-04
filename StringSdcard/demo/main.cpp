#include <MAUtil/Moblet.h>
#include <conprint.h>

//include header
#include "StringSdcard/StringSdcard.h"

using namespace MAUtil;

void writeFunc(){
	printf("writing procedure\nTry to write data to SD card");

	String data = "StringSdcard\nDemoData";
	String filename = "StringSdcard.txt";

	writeStringToSdcard(data, filename);
	printf("check file /mnt/sdcard/StringSdcard.txt");
}

void readFunc(){
	printf("reading procedure\nTry to read data from SD card");

	String data;
	String filename = "StringSdcard.txt";

	data = readStringFromSdcard(filename);

	printf("[%s]", data.c_str());
}

void taskManager(int taskNum){
	switch (taskNum) {
		case 0:
			writeFunc();
			break;
		case 1:
			readFunc();
			break;
		default:
			break;
	}
}

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class MyMoblet : public Moblet
{
public:
	int task;

	/**
	 * Initialize the application in the constructor.
	 */
	MyMoblet()
	{
		printf("StringSdcard demo\nTap or press any key to perform action\n");
		task = 0;
	}

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			// Call close to exit the application.
			close();
		}

		taskManager(task++);
		// Print the key character.
		//printf("You typed: %c\n", keyCode);
	}

	/**
	 * Called when a key is released.
	 */
	void keyReleaseEvent(int keyCode, int nativeCode)
	{
	}

	/**
	 * Called when the screen is touched.
	 */
	void pointerPressEvent(MAPoint2d point)
	{
		// Print the x and y coordinate.
//		printf("You touched: %i %i\n", point.x, point.y);
		taskManager(task++);
	}
};

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new MyMoblet());
	return 0;
}
