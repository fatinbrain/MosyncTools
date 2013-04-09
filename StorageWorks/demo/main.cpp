//Add include file to use StroageWorks class
#include "StorageWorks/StorageWorks.h"

#include <MAUtil/Moblet.h>
#include <conprint.h>

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class MyMoblet : public Moblet
{
private:
	StorageWorks sw;
	String storageName;
	int taskNum;
public:

	void verifyStorageExistense(){
		printf("storage [%s]", sw.getName().c_str());
		if(sw.exists()){
			printf(" exists\n");
		}else{
			printf(" does not exists\n");
		}
	}

	//********** demo tasks **************
	void task1(){
		printf("***task1*** verify storage existence\n");
		verifyStorageExistense();
	}

	void task2(){
		printf("***task2*** create and write to storage\n");
		sw.write("..::Data to write to MoSync storage::..");
	}

	void task3(){
		printf("***task3*** verify storage existence\n");
		verifyStorageExistense();
	}

	void task4(){
		printf("***task4*** read from storage\n");
		String data = sw.read();
		printf("data:\n[%s]", data.c_str());
	}

	void task5(){
		printf("***task5*** remove storage\n");
		sw.rm();
	}

	void task6(){
		printf("***task6*** verify storage existence\n");
		verifyStorageExistense();
	}


	void taskMan(int task){
		switch (task) {
			case 1:
				task1();
				break;
			case 2:
				task2();
				break;
			case 3:
				task3();
				break;
			case 4:
				task4();
				break;
			case 5:
				task5();
				break;
			case 6:
				task6();
				break;
			case 7:
				printf("...all tasks done.");
				break;
			default:
				close();
				break;
		}
	}
	/**
	 * Initialize the application in the constructor.
	 */
	MyMoblet()
	{
		taskNum = 0;
		storageName = "MoSyncStorage";
		sw.setStoreName(storageName);

		printf("StorageWorks demo program\nPress any key or tap to process tasks\n***********************\n");
		sw.test();

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

		taskMan(++taskNum);
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
		taskMan(++taskNum);
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
