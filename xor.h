void xor_encrypt()
{
	char *message_raw = NULL; /* Pointer to message to be encrypted */
	size_t size = 0; /* Initialise size of message */
	FILE* fp = fopen("EncodedOutput.txt", "r"); /* Open compressed file */
	fseek(fp,0,SEEK_END); /* Scan for size of file */
	size = ftell(fp);
	rewind(fp); /* Reset cursor of scanner */
	message_raw =  malloc((size + 1) * sizeof(*message_raw));
	fread(message_raw,size,1,fp); /*Put file data into char */
	message_raw[size] = '\0'; /* Nullcharacter */
	printf("%s\n", message_raw); /* Checking */
	char key[size]; /* Initialise key with same size as file */
	int i;
		for (i=0; i<size; i++) /* Random key creation for XOR */
		{
			key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
		}
		char message_encrypted[size]; /* Apply XOR */
		for (i=0; i<size; i++)
		{
			message_encrypted[i] = (message_raw[i]) ^ key[i];
	
		}

		FILE *encrypted = fopen("encrypted","w"); /* File to store encrypted
		data */
		fwrite(message_encrypted, 1, size, encrypted); 
		fclose(encrypted);
		fclose(fp);
		printf("%s\n", message_encrypted);
}

void xor_decrypt()
{
	char *message_raw = NULL; /* Pointer to message to be decrypted */
	size_t size = 0; /* Initialise size of message */
	FILE* fp = fopen("encrypted", "r"); /* Open file to be decrypted */
	fseek(fp,0,SEEK_END); /* Scan for size of file */
	size = ftell(fp);
	rewind(fp); /* Reset cursor of scanner */
	message_raw =  malloc((size + 1) * sizeof(*message_raw));
	fread(message_raw,size,1,fp); /*Put file data into char */
	message_raw[size] = '\0'; /* Nullcharacter */
	if (message_raw == NULL)
	{
	    printf("Error allocating memory!");
	}
	char key[size]; /* Initialise key with same size as file */
	int i;
		for (i=0; i<size; i++)
		{
			key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
		}
		char message_decrypted[size]; /* Apply XOR again for decryption */
		for (i=0; i<size; i++)
		{
			message_decrypted[i] = message_raw[i]^key[i];
		}
		if (message_decrypted != NULL)
		{
		    printf("Decryption Success");
		    printf("\n");
		}
		fclose(fp);
}
