
void xor_encrypt()
{
	char message_raw[1000];
	FILE* fp = fopen("tempFile", "r");
	fgets(message_raw,1000,fp);
	fclose(fp);
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
	char message_encrypted[message_length];
	for (i=0; i<message_length; i++)
	{
		message_encrypted[i] = message_raw[i]^key[i%key_length];
		
	}
	/*message_encrypted[message_length] = '\0';*/
	FILE *encrypted = fopen("encrypted","w");
	for (i = 0; i < message_length; ++i)
	{
		fprintf(encrypted,"%c", message_encrypted[i]);
	}
	fclose(encrypted);
	printf("\n");
}
