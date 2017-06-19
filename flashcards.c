#include <stdio.h>
/*WHAT STILL NEEDS TO BE DONE:
	1. DONE Change color, printNum, and sepFile to be global variables. Otherwise their values don't hold across functions.
	2. Add an option for displaying part of the line or reading the title from a file
	3. Fix the color so that it actually has an option to turn it off. Currently, the colors are always defined. 
	4. Design a nice welcome screen and an options screen.*/

/*TO UPLOAD TO GITHUB:
	Copy file to cPrograms. Run this code:
	"git add geoTheorems.c
	git commit -m "Commit message"
	git push" */
#define MAXLENGTH 1000 // MAXLENGTH stands for 1,000

/*Functions*/
int fill(char card[], FILE *fp, int sepFile);
int compare(char ans[], char card[]);
int bgetline(char s[], int putNl);
int options(void);
int info(int max, FILE *fp, char name[]);

/*Global Variables*/
int line = 0;
int sepFile = 0;//For reading from a separate file to get the card text, or using the first part of the answer
int printNum = 1; //Whether or not to print numDone
int color; //For colored or not colored text
int numCards = 1;
int numSets = 1;

int main()
{
	//chars
	char ans[MAXLENGTH]; //Character array to hold user's input
	char card[MAXLENGTH]; //Character array to hold text to compare input to
	char name[MAXLENGTH]; //Character array to hold filename
	char cardSets[MAXLENGTH]; //Character array to hold names of card sets
	char nl; //For catching newlines
	char yOrN; //Yes or no

	//ints
	int i, j, k;
	int getTheorem = 1;
	int compareThem = 0;
	int override = 0;
	int correct, incorrect;
	int numDone; //Number of cards done
	int call; //For calling functions
	int putNl; //For telling bgetline not to add a nl to the array
	int max;
	int sepFile;

	//FILEs
	FILE *fp; //A pointer to use in opening the file

	max = MAXLENGTH;
	numDone = 0;
	correct = incorrect = 0;


	printf("Would you like to change any options? (y/n): ");
	yOrN = getchar();
	nl = getchar();

	if (yOrN == 'y')
	{
		call = options();
	}

	if (color == 1)
	{
		//Defines the colors in ANSI escape codes
		#define KNRM  "\x1B[0m" //Default
		#define KRED  "\x1B[31m" //Red
		#define KGRN  "\x1B[32m" //Green
		#define KYEL  "\x1B[33m" //Yellow/orange
		#define KBLU  "\x1B[34m" //Blue
		#define KMAG  "\x1B[35m" //Purple
		#define KCYN  "\x1B[36m" //Light/bright blue
		#define KWHT  "\x1B[37m" //White
	}

	char fileLine[MAXLENGTH];

	fp = fopen("cardSets", "r"); //This is done here so that fill() won't reopen the file each time.
	numSets = 0;

	for (i = 0; fileLine[0] != '$' && i<MAXLENGTH-1; i++)
	{
		fgets(fileLine, max, fp); //Reads a line from the file
		++numSets;

	}
	printf("Number of cards: %i.\n", numCards);
	fclose(fp);

	#define NUMSETS numSets

	putNl = 0;
	printf("Would you like a list of the card sets available? (y/n): ");
	yOrN = getchar();
	nl = getchar();

	if (yOrN == 'y')
	{
		fp = fopen("cardSets", "r");
		for (i = 0; i < NUMSETS; i++){
			fgets(cardSets, max, fp); //Reads a line from the file
			printf("Set %i: %s\n", i+1, cardSets);
		}
		printf("\n");
	}

	printf("Enter the name of the file you would like to open: ");
	call = bgetline(name, putNl);
	printf("\nFilename: %s\n", name);
	putNl = 1;
	#define FILENAME name //Replaces FILENAME with the contents of array "name"

	call = info(max, fp, name);
	#define NUMCARDS numCards //The number of lines in the file for the cards.

	fp = fopen(FILENAME, "r"); //This is done here so that fill() won't reopen the file each time. It must be reopened after info, because info closes it.

	printf("This is a flashcard program. \n\n");
	printf("Line: %i\n", line);
	printf("numCards: %i\n", numCards);

	for (i = 0; i < NUMCARDS-1; ++i){
	/*	for (k = 0; k < 25; k++)
			printf("\n"); */

		j = fill(card, fp, sepFile);
		printf("Begin: \n");
		getTheorem = bgetline(ans, putNl);

		printf("Comparing...\n");
		compareThem = compare(ans, card);
		if (compareThem == 1)
		{
			printf("Would you like to override? (y/n) \n");
			override = getchar();
			nl = getchar();

			/*Lets you override the program if you think you got close enough */
			if (override == 'y')
			{
				++correct;
				printf("Override successful.\n");
			}
			else
			{
				++incorrect;
				printf("No override.\n");
			}
		}

		if (printNum == 1)
		{
			++numDone;
			printf("You have completed %i cards. There are %i cards left in the deck.\n", numDone, (NUMCARDS-1)-numDone);
		}

	}
}

/****Fills an array from a file****/

int fill(char card[], FILE *fp, int sepFile){
	int i, max;
	char c;
	i = 0;
	max = MAXLENGTH;

	fgets(card, max, fp); //Reads a line from the file

	printf("________________________________________________________________________________\n\n");
	printf("Line: %i\n\n", line);
	for (i = 0; i < line; ++i){
		printf("%c", card[i]);
	}
	if (card[i] != 32)
	{
		for (i = i; card[i] != 32; ++i)
			printf("%c", card[i]);
	}
	printf("\n");
	return 0;

}

/****Compare the user input and the actual text****/

int compare(char ans[], char card[]){
	int i, correct, k, incorrect;
	incorrect = 0;
	k = 0;
	correct = 0;
	for (i = 0; ans[i] != '\0'; i++){ //i starts out at 0. Test to see if the end of 'ans' has been reached.
//		printf("i: %i\n", i); // Print the value of i, which is the place it's at in 'ans'. For error checking.
		if (ans[i] != card[k])//If the current character in 'ans' is not equal to the current character in 'card',
		{
			++incorrect; //Add one to incorrect
			++k;
		}
		else if (ans[i] == card[k])
		{
			++correct;
			++k;
		}

	}
	if (incorrect > 5) //Don't count it wrong unless there are more than five letters wrong.
	{
		printf(KRED "Incorrect. You got %i letters wrong. \n\n\n" KNRM, incorrect);
		printf("%s\n", card); //Print what should have been entered, so that the user can check it.
		return 1;
	}
	else
	{
		printf(KYEL "Correct! You got %i letters right and %i letters wrong. \n\n\n" KNRM, correct, incorrect);
		return 0;
	}
}

/****Takes the user's input and puts it in an array****/

int bgetline(char s[], int putNl){
	int i;
	int c;
	int nl;


	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n' && putNl == 1)
	{
		s[i] = c;
		++i;
	}
	else nl = c;
	s[i] = '\0';
	return i;
}
/*Lets the user set options*/
int options(void){
  char yOrN;
	char s[MAXLENGTH];
	int nl;
	int i;
	int c;
	int changeOption;
	int n;
	n = 0;

	if (color == 1)
		{
			printf("1. Color (enabled)\n");
		}
	else
		{
			printf("1. Color (disabled)\n");
		}
	if (printNum == 1)
		{
			printf("2. Print number of cards left in deck after each card (enabled)\n");
		}
		else
		{
			printf("2. Print number of cards left in deck after each card (disabled)\n");
		}
	if (sepFile == 1)
		{

			printf("3. Read text for cards as part of the answer (instead of reading the text from a separate file).\n");
		}
		else
		{
			printf("3. Read text for cards from a separate file (instead of giving part of the answer as a hint).\n");
		}
	printf("To change an option, enter the number next to it. When you are done, press $: \n");

	while (changeOption != '$')
	{
		changeOption = getchar();
		nl = getchar();

		if (changeOption != '$') //Converts changeOption from an interger in ASCII to an interger (The input number is in ASCII)
		{
			n = changeOption - '0';
			changeOption = n;
		}

		if (changeOption == 0)
		{
			printf("Leaving options...\n");
      return 0;
		}
		/*Colored text*/
		else if (changeOption == 1)
		{
			if (color == 1)
			{
				color = 0;
				printf("Color is disabled.\n");
			}
			else
			{
				color = 1;
				printf("Color is enabled.\n");
			}
		}
		/*Print number of cards left in deck*/
		else if (changeOption == 2)
		{
			if (printNum == 1)
			{
				printNum = 0;
				printf("Print number of cards left in deck after each card is disabled.\n\n");
			}
			else
			{
				printNum = 1;
				printf("Print number of cards left in deck after each card is enabled.\n\n");
			}
		}
		/*Where to get the card text from*/
		else if (changeOption == 3)
		{
			if (sepFile == 1)
			{
				sepFile = 0;
				printf("Read text for cards from a separate file (instead of giving part of the answer as a hint).\n");

			}
			else
			{
				sepFile = 1;
				printf("Read text for cards as part of the answer (instead of reading the text from a separate file).\n");
			}
		}
		else if (changeOption == '$')
		{
			printf("Leaving options...\n\n");
			continue;

		}

		else printf("\n\nSorry, I did not understand that. Please try again.\n\n");
//		printf("changeOption: %i\n", changeOption);

		if (color == 1)
			{
				printf("\n1. Color (enabled)\n");
			}
			else
			{
				printf("\n1. Color (disabled)\n");
			}
		if (printNum == 1)
			{
				printf("2. Print number of cards left in deck after each card (enabled)\n");
			}
			else
			{
				printf("2. Print number of cards left in deck after each card (disabled)\n");
			}
		if (sepFile == 1)
			{
				printf("3. Read text for cards as part of the answer (instead of reading the text from a separate file).\n\n");
			}
			else
			{
				printf("3. Read text for cards from a separate file (instead of giving part of the answer as a hint).\n\n");
			}
	}
	if (sepFile == 1)
	{
		printf("How much of the answer for each card do you want read for the card text? ");
		for (i = 0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i )
			s[i] = c;

		nl = c;
		s[i] = '\0';

		for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) //Code copied from aToI that converts from array to int
			line = 10 * line + (s[i] - '0');
		printf("%i letters of the answer.\n\n", line);
	}
  return 0;
}

/*Sets the number of cards*/
int info(int max, FILE *fp, char name[]){
	int i;
	char fileLine[MAXLENGTH];

	fp = fopen(FILENAME, "r"); //This is done here so that fill() won't reopen the file each time.
	numCards = 0;

	for (i = 0; fileLine[0] != '$' && i<MAXLENGTH-1; i++)
	{
		fgets(fileLine, max, fp); //Reads a line from the file
		++numCards;

	}
	printf("Number of cards: %i.\n", numCards);
	fclose(fp);

	return 0;

}
