#include <Windows.h>
#include <stdio.h>
#include "XOR.h"

// The Most Simple Type Of XOR Encryption, It Takes Each Byte Against The KEY And Returns The Encrypted Buffer.
// We Used A For Loop To Iterate Through The Payload & Run The Algorithm Against Each One.

VOID XOR_EASY(unsigned char* payload, size_t payload_size) {

	for (size_t i = 0; i < payload_size; i++) {
		payload[i] = payload[i] ^ KEY;

		//Example: 0x46 = 0x46 ^ KEY which will return encrypted shellcode. 
	}
}


// Here We Are Going To Use A Slightly Better Encryption With Even & Odd Keys.

VOID XOR_EVEN_ODD(unsigned char* payload, size_t payload_size) {

	for (size_t i = 0; i < payload_size; i++) {
		if (i % 2 == 0) {
			payload[i] = payload[i] ^ EVEN_KEY;
		}
		else {
			payload[i] = payload[i] ^ ODD_KEY;
		}
	}

}

// Here It Is The Same Concept As The One Previous Except After The Else Statement We Add Another Layer Of Encryption

VOID XOR_LAYERED(unsigned char* payload, size_t payload_size) {

	for (size_t i = 0; i < payload_size; i++) {
		if (i % 2 == 0) {
			payload[i] = payload[i] ^ EVEN_KEY; // First Encryption
		}
		else {
			payload[i] = payload[i] ^ ODD_KEY;
		}
		payload[i] = payload[i] ^ (EVEN_KEY ^ ODD_KEY); // Second Layer Of Encryption
	}

}

// Since We Added Another Layer Of Encryption We Now Need To Decrypt It In A Different Way

VOID XOR_LAYERED_DECRYPT(unsigned char* payload, size_t payload_size) {

	for (size_t i = 0; i < payload_size; i++) {
		payload[i] = payload[i] ^ (EVEN_KEY ^ ODD_KEY); // Decrypting The Second Layer First

		if (i % 2 == 0) {
			payload[i] = payload[i] ^ EVEN_KEY; // Decrypting The First Layer
		}
		else {
			payload[i] = payload[i] ^ ODD_KEY;
		}
	}

}