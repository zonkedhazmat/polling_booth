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
	int c, i;
	FILE* encrypted = fopen("encrypted", "r");
	char *message_raw;
	size_t n = 0;

	if (encrypted == NULL)
	{
		printf("File can't be opened.");
	}

	fseek(encrypted, 0, SEEK_END);
	long f_size = ftell(encrypted);
	fseek(encrypted, 0, SEEK_SET);
	message_raw = malloc(f_size);

	while ((c = fgetc(encrypted)) != EOF)
	{
		message_raw[n++] = (char) c;
	}
	/*message_raw[n] = '\0';*/
	
	int message_length = strlen(message_raw);
	char key[message_length];
	srand(message_length);
	for (i=1; i<message_length; i++)
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


	printf("\n");
	
}
