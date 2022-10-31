#include <Windows.h>


#define AESKEYSIZE 32
#define IVKEYSIZE 16

VOID AesPad(PVOID pOldPayload, SIZE_T sOldSize, PVOID* pNewPayload, SIZE_T* psNewSize);

