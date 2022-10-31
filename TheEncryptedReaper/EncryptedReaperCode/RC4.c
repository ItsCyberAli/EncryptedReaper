#include <Windows.h>
#include <stdio.h>



typedef struct
{
	DWORD	Length;
	DWORD	MaximumLength;
	PVOID	Buffer;

} USTRING;

typedef NTSTATUS(NTAPI* fnSystemFunction032)(
	struct USTRING* data,
	const struct USTRING* Key
	);

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define KEYSIZE 16;


VOID GenRandomisedBytes(unsigned char* Str, size_t Size) {
	for (int i = 0; i < Size; i++) {
		Str[i] = rand() % 256;
	}
}



BOOL Rc4EncDecPayload(unsigned char* Rc4Key, unsigned char* pPayload, SIZE_T sPayloadSize) {
	
	NTSTATUS STATUS = 0x0;

	USTRING Key = { 0 };
	USTRING Data = { 0 };

	Key.Buffer = Rc4Key;
	Key.Length = Key.MaximumLength = KEYSIZE;

	Data.Buffer = pPayload;
	Data.Length = Data.MaximumLength = sPayloadSize;



	fnSystemFunction032 SysFunc32 = (fnSystemFunction032)GetProcAddress(LoadLibraryA("Advapi32.dll"), "SystemFunction032");

	if (!NT_SUCCESS(STATUS = SysFunc32(&Data, &Key))) {
		printf("[!] \"%s\" [ FAILED ] \t0x%0.8X \n", "SystemFunction032", STATUS);
		return FALSE;
	}

	return TRUE;
}