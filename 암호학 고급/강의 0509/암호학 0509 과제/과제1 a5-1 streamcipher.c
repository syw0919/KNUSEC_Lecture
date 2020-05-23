#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define KSLEN 64	// Keystream Length
#define KLEN 64		// Key Length
#define XLEN 19		// Register X Length
#define YLEN 22		// Register Y Length
#define ZLEN 23		// Register Z Length

#define CHBX register_x[8]	// Checking bit X
#define CHBY register_y[10]	// Checking bit Y
#define CHBZ register_z[10]	// Checking bit Z

#define MAJ ( CHBX & CHBY | ( CHBX ^ CHBY ) & CHBZ )	// Majority

int main(){
	int8_t keystream[KSLEN];
	int8_t key[KLEN];
	int8_t register_x[XLEN], register_y[YLEN], register_z[ZLEN];
	int i, j;
	
	srand(time(0));
	
	for(i=0;i<KLEN;i++)
		key[i] = rand()%2;
	
	printf("Randomly given key: ");
	for(i=0;i<KLEN;i++)
		printf("%d", key[i]);
	
	memcpy(register_x, key, XLEN);
	printf("\n\nRegister X: ");
	for(i=0;i<XLEN;i++)
		printf("%d", register_x[i]);
	
	memcpy(register_y, key+XLEN, YLEN);
	printf("\nRegister Y: ");
	for(i=0;i<YLEN;i++)
		printf("%d", register_y[i]);
	
	memcpy(register_z, key+XLEN+YLEN, ZLEN);
	printf("\nRegister Z: ");
	for(i=0;i<ZLEN;i++)
		printf("%d", register_z[i]);
	
	for(i=0;i<KSLEN;i++){
		int8_t keystreambit = 0;
		bool boolx = CHBX == MAJ, booly = CHBY == MAJ, boolz = CHBZ == MAJ;
		
		if(boolx){
			keystreambit ^= register_x[XLEN-1];
			int8_t temp = register_x[13] ^ register_x[16] ^ register_x[17] ^ register_x[18];
			
			for(j=XLEN-1;j>0;j--)
				register_x[j] = register_x[j-1];
			
			register_x[0] = temp;
		}
		
		if(booly){
			keystreambit ^= register_y[YLEN-1];
			int8_t temp = register_y[20] ^ register_y[21];
			
			for(j=YLEN-1;j>0;j--)
				register_y[j] = register_y[j-1];
			
			register_y[0] = temp;
		}
		
		if(boolz){
			keystreambit ^= register_z[ZLEN-1];
			int8_t temp = register_z[7] ^ register_z[20] ^ register_z[21] ^ register_z[22];
			
			for(j=ZLEN-1;j>0;j--)
				register_z[j] = register_z[j-1];

			register_z[0] = temp;
		}
		
		keystream[i] = keystreambit;
	}
	
	printf("\n\nKeystream: ");
	for(i=0;i<KSLEN;i++)
		printf("%d", keystream[i]);
	
	return 0;
}
