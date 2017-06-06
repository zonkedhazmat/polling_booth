#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void xor_decrypt(void);


int main()
{	
	xor_decrypt();
	
	return 0;
}

void xor_decrypt()
{
	char message_raw[1000];
	FILE* fp = fopen("encrypted", "r");
	while (fgets(message_raw,1000,fp))
	{
	message_raw[strlen(message_raw) -1] = '\0';
	int message_length = strlen(message_raw);
	char key[message_length];
	int i;
	/*srand(message_length);*/
	for (i=0; i<message_length; i++)
	{
		key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[rand() % 36];
	}
	int key_length = strlen(key);
	char message_decrypted[message_length];
	for (i=0; i<message_length; i++)
	{
		message_decrypted[i] = message_raw[i]^key[i%key_length];
		printf("%c", message_decrypted[i]);
	}
	/*message_encrypted[message_length] = '\0';*/
	}
}
