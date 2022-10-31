#pragma once
#include <Windows.h>


#define RC4KEYSIZE 16

VOID GenRandomisedBytes(unsigned char* Str, size_t Size); // Genetates Random Bytes

BOOL Rc4EncDecPayload(unsigned char* Rc4Key, unsigned char* pPayload, SIZE_T sPayloadSize); // Encrypts & Decrypts The Payload
