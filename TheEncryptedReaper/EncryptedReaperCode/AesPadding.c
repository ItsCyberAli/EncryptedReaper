#include <Windows.h>
#include <stdio.h>
#include "AesPadding.h"


int roundUp(int numToRound, int multiple) {
	if (multiple == 0) {
		return numToRound;
	}
	int remainder = numToRound % multiple;
	if (remainder == 0) {
		return numToRound;
	}
	return numToRound + multiple - remainder;
}





VOID AesPad(PVOID pOldPayload, SIZE_T sOldSize, PVOID* pNewPayload, SIZE_T* psNewSize) {


	unsigned char Padd[16] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	unsigned char Nop[1] = { 0x90 };

	PVOID NewPayload = NULL;
	SIZE_T NewSize = NULL;


	if (sOldSize % 16 == 0) {
		printf("[i] The Shellcode is Already multiple of 16, Padding with 16 Nops Only \n");
		NewPayload = (PVOID)malloc(sOldSize + sizeof(Padd));
		memcpy(NewPayload, pOldPayload, sOldSize);
		memcpy((PVOID)((ULONG_PTR)NewPayload + sOldSize), Padd, sizeof(Padd));
		NewSize = sOldSize + sizeof(Padd);
		goto _end;
	}

	else {
		printf("[i] The Shellcode is Not multiple of 16\n");
		int MultipleBy16 = roundUp(sOldSize, 16); //calculating the `rounding up` number
		printf("[+] Constructing the Shellcode To Be Multiple Of 16, Target Size: %d \n", MultipleBy16);
		int HowManyToAdd = MultipleBy16 - sOldSize; //calculating how much we need to add to be multiple of 16
		printf("[i] HowManyToAdd : %d ||  sizeof(Padd) : %d \n", HowManyToAdd, sizeof(Padd));
		NewPayload = (PVOID)malloc(sOldSize + HowManyToAdd + sizeof(Padd));
		memcpy(NewPayload, pOldPayload, sOldSize); //adding the shellcode to our new shellcode to start the padding ...

		int j = 0;
		for (int i = 0; i <= HowManyToAdd; i++)
		{
			memcpy((PVOID)((ULONG_PTR)NewPayload + sOldSize + i), Nop, 1);
			j = i;
		}

		printf("[+] Added : %d \n", j);
		printf("[+] Done, Shellcode Size is : %ld \n", sOldSize + j);
		printf("[+] Padding with Extra 16 Nops ...\n");
		memcpy((PVOID)((ULONG_PTR)NewPayload + sOldSize + j), Padd, sizeof(Padd)); // adding extra 16 bytes of nopes to the end
		NewSize = sOldSize + j+ sizeof(Padd); //setting the size
		goto _end;
	}

_end:
	*pNewPayload = NewPayload;
	*psNewSize = NewSize;
	printf("[+] New Shellcode Size is : %ld \n", *psNewSize);
	return;
}

