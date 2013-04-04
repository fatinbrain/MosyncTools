/**
	\mainpage StringSdcard
	\brief Easy read/write String data from/to SDcard.     
	
	
	Here is 2 simple functitons to perform reading and writing String data from(to) device SD card.     
	
	
	May be useful to create import/export application functionality.
**/

/**
 * \file StringSdcard.h
 * \brief Functions to perform write/read operations with sdcard.
 * \version 1.0
 *
 * \note Functions process files at default location at /mnt/sdcard/your_file_name.
 */

#ifndef STRINGSDCARD_H_
#define STRINGSDCARD_H_

#include <ma.h>
#include <MAUtil/String.h>

using MAUtil::String;

/**
 * \brief Write string to sdcard.
 * @param data String to write.
 * @param fname Filename where to save data.
 */
void writeStringToSdcard(String data, String fname);

/**
 * \brief Read string from sdcard.
 * @param fname Filename from which read data.
 * @return Result of read.
 */
String readStringFromSdcard(String fname);

#endif /* STRINGSDCARD_H_ */
