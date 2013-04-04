#include "StringSdcard.h"

void writeStringToSdcard(String data, String fname){
	if(fname.find("/mnt/sdcard/", 0) == String::npos){
		String sBuff = "/mnt/sdcard/";
		sBuff += fname;
		fname = sBuff;
	}

	MAHandle hFile = maFileOpen(fname.c_str(), MA_ACCESS_READ_WRITE);
	if(hFile < 0){
		return;
	}

	int rez = maFileExists(hFile);
	if(rez){
		rez = maFileTruncate(hFile, 0);
	}else{
		rez = maFileCreate(hFile);
	}

	rez = maFileWrite(hFile, data.c_str(), data.length());

	rez = maFileClose(hFile);
}

String readStringFromSdcard(String fname){
	if(fname.find("/mnt/sdcard/", 0) == String::npos){
		String sBuff = "/mnt/sdcard/";
		sBuff += fname;
		fname = sBuff;
	}

	String sRes = "";

	MAHandle fl = maFileOpen(fname.c_str(), MA_ACCESS_READ);
	if(fl < 0){
		return sRes;
	}

	int rez = maFileExists(fl);
	if(!rez){
		return sRes;
	}

	int szFile = maFileSize(fl);

	static char data[2048];
	rez = maFileRead(fl, data, szFile);
	rez = maFileClose(fl);
	sRes += data;
	return sRes;
}
