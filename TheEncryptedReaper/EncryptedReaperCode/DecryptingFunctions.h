#pragma once


char XorDecryptionFunction[] = 
//"#include <Windows.h>\n\n\n"

"VOID XOR_EASY(unsigned char* payload, size_t payload_size) {\n"
	"\tfor (size_t i = 0; i < payload_size; i++) {\n"
		"\t\tpayload[i] = payload[i] ^ KEY;\n"
	"\t}\n"
"}\n"

"int main() {\n"
	"\tHRSRC res = FindResource(NULL, MAKEINTRESOURCE(MY_PAYLOAD), RT_RCDATA);\n"
	"\tHGLOBAL resHandle = LoadResource(NULL, res);\n"
	"\tunsigned char* rawData = (unsigned char*) LockResource(resHandle);\n"
	"\tSIZE_T Size = SizeofResource(NULL, res);\n"
	"\tunsigned char* Encryptedbuffer = (unsigned char*) malloc(Size); \n"
	"\tmemcpy(Encryptedbuffer, rawData, Size);\n"
	"\tXOR_EASY(Encryptedbuffer, Size);\n"
	"\treturn 0;\n"
"}\n";




char AesDecryptionFunction[] =
//"#include <Windows.h>\n\n\n"

"int main() {\n"
	"\tHRSRC res = FindResource(NULL, MAKEINTRESOURCE(MY_PAYLOAD), RT_RCDATA);\n"
	"\tHGLOBAL resHandle = LoadResource(NULL, res);\n"
	"\tunsigned char* rawData = (unsigned char*) LockResource(resHandle);\n"
	"\tSIZE_T Size = SizeofResource(NULL, res);\n"
	"\tunsigned char* Encryptedbuffer = (unsigned char*) malloc(Size); \n"
	"\tmemcpy(Encryptedbuffer, rawData, Size);\n"
	"\tstruct AES_ctx ctx;\n"
	"\tAES_init_ctx_iv(&ctx, key, iv);\n"
	"\tAES_CBC_decrypt_buffer(&ctx, Encryptedbuffer, Size);\n"
	"\treturn 0;\n"
"}\n";




char Rc4DecryptionFunction[] = 
//"#include <Windows.h>\n\n\n"

"typedef struct{\n"
	"\tDWORD	Length;\n"
	"\tDWORD	MaximumLength;\n"
	"\tPVOID	Buffer;\n"
"} USTRING;\n"

"typedef NTSTATUS(NTAPI* fnSystemFunction032)(\n"
	"\tstruct USTRING* data,\n"
	"\tconst struct USTRING* Key\n"
");\n"


"#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)\n"
"#define KEYSIZE 16 \n"


"BOOL Rc4EncDecPayload(unsigned char* Rc4Key, unsigned char* pPayload, SIZE_T sPayloadSize) {\n"
	"\tNTSTATUS STATUS = 0x0;\n"
	"\tUSTRING Key = { 0 };\n"
	"\tUSTRING Data = { 0 };\n"
	"\tKey.Buffer = Rc4Key;\n"
	"\tKey.Length = Key.MaximumLength = KEYSIZE;\n"
	"\tData.Buffer = pPayload;\n"
	"\tData.Length = Data.MaximumLength = sPayloadSize;\n"
	"\tfnSystemFunction032 SysFunc32 = (fnSystemFunction032)GetProcAddress(LoadLibraryA(\"Advapi32.dll\"), \"SystemFunction032\");\n"
	"\tif (!NT_SUCCESS(STATUS = SysFunc32(&Data, &Key))) {\n"
		"\t\treturn FALSE;\n"
	"\t}\n"
	"\treturn TRUE;\n"
"}\n"


"int main() {\n"
	"\tHRSRC res = FindResource(NULL, MAKEINTRESOURCE(MY_PAYLOAD), RT_RCDATA);\n"
	"\tHGLOBAL resHandle = LoadResource(NULL, res);\n"
	"\tunsigned char* rawData = (unsigned char*) LockResource(resHandle);\n"
	"\tSIZE_T Size = SizeofResource(NULL, res);\n"
	"\tunsigned char* Encryptedbuffer = (unsigned char*) malloc(Size); \n"
	"\tmemcpy(Encryptedbuffer, rawData, Size);\n"
	"\tif (!Rc4EncDecPayload(Rc4Key, Encryptedbuffer, Size)) {\n"
		"\t\treturn -1;\n"
	"\t}\n"
	"\treturn 0;\n"
"}\n";