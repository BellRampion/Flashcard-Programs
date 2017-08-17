/* ----------Virtual Book of Centuries---------- */
/*I've always wanted to make a virtual Book of Centuries so that I could keep multiple things per year in one. This program does just that. The user can choose whether to read from or write to the "book." */



#include <stdio.h>

#define MAXLENGTH 100000 // MAXLENGTH has a value of 100,000
#define FILENAME date

int atoi(char s[]); //Converts the number string to an interger. IF STDLIB IS INCLUDED, CHANGE NAME TO BATOI TO AVOID CONFLICT, OR COMMENT OUT FUNCTION.
int read(char date[], char text[], FILE *fp); /*Reads an entry*/
int write(char text[], char date[], FILE *fp); /*Writes an entry*/
int bgetline(char s[]);

int century;
int years;
char windows;

int main(){

    //ints
	int readOrWrite;
	int c;
	int readFunct; // For calling read
	int i;
	int writeFunct; // For calling write
    int yOrN;


    //chars
    char nl;
    char text[MAXLENGTH];
    char date[4]; //Holds the date and whether the year is AD or BC

    //FILEs
    FILE *fp;

    printf("Is this a Windows computer? (y/n):\n");
    yOrN = getchar();
    nl = getchar();
    if (yOrN == 'y')
        windows = 'y';
    else windows = 'n';
    yOrN = 0;

    printf("Enter any character to start. Press $ to close the program:\n");

    while ((c=getchar()) != '$')
    {
    	printf("Do you want to read or write? (r/w): "); /* Asks the user if they want to read information or write it */
    	readOrWrite = getchar();
    	nl = getchar();
    	if (readOrWrite == 'r') /* If answer is read, */
    	{
            printf("Type the date you wish to read from. Include 'a' or 'b' at the end of the date to represent AD or BC. (e. g. 1777a): \n");
            i = bgetline(date);
    		readFunct = read(date, text, fp); /* Run code in function "read" */

    	}

    	else if (readOrWrite == 'w') // If the user wants to write,
    	{
            printf("Type the date you wish to write to. Include 'a' or 'b' at the end of the date to represent AD or BC. (e. g. 1777a): \n");
            i = bgetline(date);
    		writeFunct = write(text, date, fp); // Run the code in function write
    	}
        else printf("I did not understand that input. Please rerun the program and try again.\n");

        printf("\nPress any key except $ to run the program again. Press $ to close: \n");
    }
    return 0;

}

int read(char date[], char text[], FILE *fp){ /* Function for reading from a year */
    int numLines = 0;
    int max = MAXLENGTH;
    int i, j;
    char fileLine[MAXLENGTH];

    //printf("Opening file.\n");
    //printf("Opening %s\n", date);
    fp = fopen(FILENAME, "r");
    //printf("Opened %s\n", FILENAME);
    //printf("Determining file length.\n");
    for (i = 1; fileLine[0] != '$' && i<MAXLENGTH-1; i++)
	{
    //    printf("Fileline %i\n", i);
		fgets(fileLine, max, fp); //Reads a line from the file
		numLines++;
    //    printf("Number of lines: %i\n", numLines);
	}
    fclose(fp); //Closes file so that fgets() starts reading from the beginning
    fp = fopen(FILENAME, "r");

    //printf("Retrieving text.\n");
    printf("\n\n");
    for (i = 0; i < numLines; i++){
        fgets(text, max, fp);
        for (j = 0; text[j] != '\0'; j++){
            printf("%c", text[j]);
        }

    }
//    printf("text: %s\n", text);

    fclose(fp);
    return 0;
}

int write(char text[], char date[], FILE *fp){

    int i, j, l;
    i = j = l = 0;
    int c;
    int nl;

    char command[MAXLENGTH];
    char temp[100];

    if (windows == 'n')
    {
        fp = fopen("linuxCommand", "r");
        fgets(temp, 6, fp);
        //printf("Temp: %s\n", temp);
        fclose(fp);
        for (i = 0; i < 5; i++){
            command[i] = temp[i];
            if (temp[i] == '\n')
            {
                i--;
                //printf("Deleting newline...\n");
            }
        }
        //printf("Command: %s\n", command);
        command[i] = 32; //Doesn't advance i because then the '\0' wouldn't be overwritten.
        i++;

        for (i = i; i < MAXLENGTH && date[j] != '\0'; i++){
            command[i] = date[j];
            j++;
        }
    }
    else if (windows == 'y')
    {
        fp = fopen("windowsCommand", "r");
        fgets(temp, 11, fp);
        fclose(fp);
        printf("Functionality for Windows has not been developed yet. Please be patient.");
    }
    else {
        printf("Error: it was not determined if this computer is running windows.");
        return 1;
    }
    i++;
    command[i] = '\0';

    #define PRGMPARAM command
    popen(PRGMPARAM, "w");


    /*fp = fopen(FILENAME, "a");
    printf("Type your entry (less than 100,000 characters):\n");
    int i;
	int c;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i)
		text[i] = c;
	if (c == '\n')
	{
		text[i] = c;
		++i;
	}
	text[i] = '\0';

    fprintf(fp, "%s\n$", text); */


}

int atoi(char s[]){ //Convert an array to an interger
	int i, n;
	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0');

	return n;

}

int bgetline(char s[]){
	int i;
	int c;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i)
		s[i] = c;
	/*if (c == '\n')
	{
		s[i] = c;
		++i;
	}*/
	s[i] = '\0';
	return i;
}
