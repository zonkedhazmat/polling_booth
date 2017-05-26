#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char xor_encrypt();

int main()
{	
	char encrypted = xor_encrypt();
	printf("%c", encrypted);
	
	
	return 0;
}

char xor_encrypt()
{
	char message_raw[100];
	printf("What do you want encrypted?>");
	fgets(message_raw,100,stdin);
	message_raw[strlen(message_raw) -1] = '\0';
	int message_length = strlen(message_raw);
	char key[message_length];
	int i;
	srand(message_length);
	for (i=1; i<message_length; i++)
	{
		key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[rand() % 36];
	}
	int key_length = strlen(key);
	char message_encrypted[message_length];
	for (i=0; i<message_length; i++)
	{
		message_encrypted[i] = message_raw[i]^key[i%key_length];
		printf("%c", message_encrypted[i]);
	}

	printf("\n");

}
