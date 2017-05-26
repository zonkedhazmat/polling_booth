#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char xor_encrypt(char message_raw);

int main()
{	
	char message[] = "what is going on";
	char encrypted = xor_encrypt(message);
	
	
	return 0;
}

char xor_encrypt(char message_raw)
{
	int message_length = strlen(message_raw);
	char key[message_length];
	int i;
	srand(message_length);
	for (i=1; i<message_length; i++)
	{
		key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[rand() % 36];
	}
	char key_length = strlen(key);

	for (i=0; i<message_length; i++)
	{
		message_raw[i] = message_raw[i]^key[i%key_length];
		printf("%d", message_raw[i]);
	}

	printf("\n");
}
