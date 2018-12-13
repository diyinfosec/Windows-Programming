/*
 * Author: Ramprasad Ramshankar 
 * Alias: diyinfosec
 * Date: 09-Dec-2018
 * Purpose: Simple program to show how to read a file using Windows API
 * Language:  C
 */

#include <Windows.h> //Included for Windows API file functions - CreateFile and ReadFile
#include <stdio.h> //Included for fprintf and printf statements
#include <iostream> //Included for a getch() call in the end

#define READ_BUFFER_SIZE 1000 //Size of the buffer that holds data read from the file.


int main(int argc, char *argv[])
{

	/*
		This program performs the following steps:
		1. Obtain "file name with path" as an input to the program
		2. Use CreateFile to obtain a handle to the file.
		3. Use ReadFile to read the contents of the file READ_BUFFER_SIZE bytes at a time. 
		4. Close the file handle using CloseHandle.
	*/

	// Note: If you are using Visual Studio to run the program then give the commandline arguments as per:
	// https://stackoverflow.com/questions/3697299/passing-command-line-arguments-in-visual-studio-2010
	if (argc != 2)
	{
		fprintf(stderr, "Usage: winFileRead filename_with_path \n");
		fprintf(stderr, "Example: winFileRead D:\\test\\abcd.txt \n");
		return 1;
	}
	
	
	//Getting the name of the file from program input
	LPSTR lpFileName = argv[1];

	/* The CreateFile function allows you to specify all the glorious ways in which you can open a file. */
	HANDLE hFile = CreateFileA(
		lpFileName,       // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // handle to an attribute template file

	/*
		If the CreateFile function fails, the return value is INVALID_HANDLE_VALUE.
		Using GetLastError() to print the error details.
	*/
	if (hFile == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());
		return 2;
	}


	//Declaring the variables required for calling ReadFile. 
	BOOL bErrorFlag;
	DWORD dwBytesToRead = READ_BUFFER_SIZE;	
	LPTSTR lpvDataBuffer[READ_BUFFER_SIZE] = {0};
	DWORD dwActualBytesRead=1;

	/*
	 The first call to ReadFile reads the first "dwBytesToRead" bytes from the file. Any subsequent calls will start reading from 
	 the file pointer position at end of the previous call. Even if EOF is reached ReadFile will continue the attempt to read the file
	 i.e. bErrorFlag will still return true. You need to explicitly check and stop calling ReadFile if the number of bytes read by ReadFile
	 becomes zero. 
	*/
	do
	{
		bErrorFlag=ReadFile(
			hFile,           // open file handle
			lpvDataBuffer,      // store the data that is read
			dwBytesToRead,  // number of bytes to read
			&dwActualBytesRead, // pointer to number of bytes that were actually read
			NULL);           // no overlapped structure

		printf("\n Buffer is: %s", lpvDataBuffer);
		printf("\n Bytes actually read %d", dwActualBytesRead);
	} while (bErrorFlag = true && dwActualBytesRead > 0);

	/*
	 Though not explicitly required, you should close the File handle when you are done reading the file. Some good reasons
	 to do so can be found here: https://stackoverflow.com/questions/29535973/is-it-necessary-to-close-files-after-reading-only-in-any-programming-language
	*/
	if (CloseHandle(hFile)==0)
	{
		fprintf(stderr, " Unable to close File Handle: %x\n", GetLastError());
		return 3;
	}
	
	// Added a getchar() to avoid automatically terminating the process after printing all the output. 
	getchar();
}
