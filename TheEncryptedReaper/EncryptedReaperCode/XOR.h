#pragma once

#define KEY 0x45 // Put Your Key Here For XOREASY
#define EVEN_KEY 0x50 // Put Your Even Key Here For XOREVENODD
#define ODD_KEY 0x60 // Put Your ODD Key Here For XOREVENODD

VOID XOR_EASY(unsigned char* payload, size_t payload_size); // Lower Level Of Encryption

VOID XOR_EVEN_ODD(unsigned char* payload, size_t payload_size); // A Bit Stronger Level Of Encryption

VOID XOR_LAYERED(unsigned char* payload, size_t payload_size); // Layered Encryption And Stronger 

VOID XOR_LAYERED_DECRYPT(unsigned char* payload, size_t payload_size); // This Is To Decrypt The Layered Encryption