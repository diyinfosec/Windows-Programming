/*
 * Author: Ramprasad Ramshankar 
 * Alias: ramprams
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
	*/

	// Note: If you are using Visual Studio to run the program then give the commandline arguments as per:
	// https://stackoverflow.com/questions/3697299/passing-command-line-arguments-in-visual-studio-2010
	if (argc != 2)
	{
		fprintf(stderr, "Usage: winFileRead filename_with_path \n");
		fprintf(stderr, "Example: winFileRead D:\\test\\abcd.txt \n");
		return 1;
	}
	

	/*
		Function template for CreateFile:
			HANDLE CreateFileA(
			LPCSTR                lpFileName,
			DWORD                 dwDesiredAccess,
			DWORD                 dwShareMode,
			LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			DWORD                 dwCreationDisposition,
			DWORD                 dwFlagsAndAttributes,
			HANDLE                hTemplateFile
			);
	*/
	
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

	
	/*
		Function template for ReadFile
		BOOL ReadFile(
			HANDLE       hFile,
			LPVOID       lpBuffer,
			DWORD        nNumberOfBytesToRead,
			LPDWORD      lpNumberOfBytesRead,
			LPOVERLAPPED lpOverlapped
		)
	*/
	
	//Declaring the variables required for calling ReadFile. 
	BOOL bErrorFlag;
	DWORD dwBytesToRead = READ_BUFFER_SIZE;	
	LPTSTR lpvDataBuffer[READ_BUFFER_SIZE] = {0};
	DWORD dwActualBytesRead=1;

	/*To read an entire file you need to call the ReadFile function repeatedly till the actual number of bytes reduces to 0*/
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

	//Simply added a getchar() to avoid automatically terminating the process after printing all the output. 
	getchar();
}
