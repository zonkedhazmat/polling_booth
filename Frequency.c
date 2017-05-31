#include <stdio.h>

int main() {
    FILE *fb;
    char data[255];
    int c=0;
    int count[75] = {0};
    fb = fopen("Input.txt", "r");
    fgets(data, 255, fb);

    /* Start finding frequency*/
    while (data[c] != '\0')
    {
        if( data[c] >= '0' && data[c] <= 'z')
        count[data[c] - '0']++;

        c++;
    }
    for (c = 0; c < 75; c++)
    {
        /** Printing only those characters
            whose count is at least 1 */

        if (count[c] != 0)
            printf("%c occurs %d times in the entered string.\n",c+'a',count[c]);
    }
    
    return 0;
}
