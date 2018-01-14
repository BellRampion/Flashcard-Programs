#include <stdio.h>

#define MAXLENGTH 1000 // MAXLENGTH stands for 1,000
#define NUMCARDS numCards //The number of lines in the file for the cards.
//Defines the colors in ANSI escape codes
#define KNRM  "\x1B[0m" //Default
#define KRED  "\x1B[31m" //Red
#define KGRN  "\x1B[32m" //Green
#define KYEL  "\x1B[33m" //Yellow/orange
#define KBLU  "\x1B[34m" //Blue
#define KMAG  "\x1B[35m" //Purple
#define KCYN  "\x1B[36m" //Light/bright blue
#define KWHT  "\x1B[37m" //White
#define FILENAME name //Replaces FILENAME with the contents of array "name"
#define FILENAME2 name2 //For the second filename
//A #define for debugging that takes the argument and prints its value with an expression before it
#define debugging(expr, x) (debug == 1) ? printf(#expr " %i\n", x) : x; 


/*Functions*/
int fill(char card[], FILE *fp);
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
int debug = 0;


int main()
{
	//chars
	char ans[MAXLENGTH]; //Character array to hold user's input
	char card[MAXLENGTH]; //Character array to hold text to compare input to
	char name[MAXLENGTH]; //Character array to hold filename
	char name2[MAXLENGTH]; //Char array for the second filename
	char cardSets[MAXLENGTH]; //Character array to hold names of card sets
	char fileLine[MAXLENGTH];
	char hint[MAXLENGTH]; //For the hint to be printed for each card
	char s[MAXLENGTH]; //For "read hint from card" code (stores length of answer to be gotten)
	char nl; //For catching newlines
	char yOrN; //Yes or no
	char c; 

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
	
	//FILEs
	FILE *fp; //A pointer to use in opening the file
	FILE *fp2; //A second pointer for files

	max = MAXLENGTH;
	numDone = 0;
	correct = incorrect = 0;
	
	printf("Would you like to turn debugging mode on? (y/n) [n]: ");
	c = getchar();
	debug = (c == 'y') ? 1 : 0;
	nl = getchar();


	printf("Would you like to change any options? (y/n): ");
	yOrN = getchar();
	nl = getchar();

	if (yOrN == 'y')
	{
		call = options();
	}	
	
	if (sepFile == 0)
	{
		printf("How much of the answer for each card do you want read for the card text? ");
		for (i = 0; i<MAXLENGTH-1 && (k=getchar()) !='$' && k !='\n'; ++i )
			s[i] = k;

		nl = k;
		s[i] = '\0';

		for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) //Code copied from aToI that converts from array to int
			line = 10 * line + (s[i] - '0');
		debugging(Amount ,line);
	}

	putNl = 0;
	printf("Would you like a list of the card sets available? (y/n): ");
	yOrN = getchar();
	nl = getchar();

	if (yOrN == 'y')
	{
		fp = fopen("cardSets", "r");
		for (i = 1; fgets(cardSets, max, fp) != NULL; i++){ //Starts at line 1; checks to see if the return after pulling a line from the file is NULL; increases the line number
			printf("Set %i: %s\n", i, cardSets);
		}
		printf("\n");
	}

	printf("Enter the name of the card set for the answers: ");
	call = bgetline(name, putNl);
	//printf("\nFilename: %s\n", name);
	putNl = 1;
	

	call = info(max, fp, name);
	

	fp = fopen(FILENAME, "r"); //This is done here so that fill() won't reopen the file each time. It must be reopened after info, because info closes it.
	if (sepFile == 1)
	{
		printf("Enter the name of the card set for the hints: ");
		putNl = 0;
		call = bgetline(name2, putNl);
		putNl = 1; 
		fp2 = fopen(name2, "r"); //Open the file for hints
	}

	printf("This is a flashcard program. \n\n");
	//printf("numCards: %i\n", numCards);
	//printf("NUMCARDS: %i\n", NUMCARDS);

	for (i = 0; i < NUMCARDS; ++i){
		
		j = fill(card, fp);
		
		if (sepFile == 0)
		{
			for (j = 0; j < line; ++j){
				printf("%c", card[j]);
			}
			if (card[j] != 32)
			{
				for (j = j; card[j] != 32; ++j)
					printf("%c", card[j]);
			}
			printf("\n");
		}
		else 
		{
			j = fill(hint, fp2);
			for (j = 0; j < MAXLENGTH && hint[j] != '\n'; j++){
				printf("%c", hint[j]);
			}
			printf(" ");
		}
		//printf("Begin: \n");
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
			printf("You have completed %i cards. There are %i cards left in the deck.\n", numDone, NUMCARDS-numDone);
		}
	}
	return 0;
}

/****Fills an array from a file****/

int fill(char card[], FILE *fp){
	int i, max;
	char c;
	i = 0;
	max = MAXLENGTH;

	fgets(card, max, fp); //Reads a line from the file

	printf("________________________________________________________________________________\n\n");
	//printf("Line: %i\n\n", line);
	
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
	for (k = 0; card[k] != '\0'; k++)
		;
	debugging(Length of card text:, k);
	debugging(Length of answer:, i);
	if (k > i) //If the card text is longer than the answer, increase incorrect enough to make sure it goes over the test limit
	{
		incorrect += 6;
	}
	
	if (k < i)
	{
		incorrect += 6; //If the card text is shorter than the answer, it's still wrong
	}
	
	if (incorrect > 5) //Don't count it wrong unless there are more than five letters wrong.
	{
		if (color == 1)
		{
			printf(KRED "Incorrect. You got %i letters wrong. \n\n\n" KNRM, incorrect);
			printf("%s\n", card); //Print what should have been entered, so that the user can check it.
		}
		else printf("Incorrect. You got %i letters wrong. \n\n\n", incorrect);
		return 1;
	}
	else
	{
		if (color == 1)
		{
			printf(KYEL "Correct! You got %i letters right and %i letters wrong. \n\n\n" KNRM, correct, incorrect);
			incorrect > 0 ? printf("%s\n", card) : i;
		}
		else
		{
			printf("Correct! You got %i letters right and %i letters wrong. \n\n\n", correct, incorrect);
			incorrect > 0 ? printf("%s\n", card) : i;
		}
		
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
	int nl;
	int i;
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
	if (sepFile == 0)
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
			if (sepFile == 0)
			{
				sepFile = 1;
				printf("Read text for cards from a separate file (instead of giving part of the answer as a hint).\n");

			}
			else
			{
				sepFile = 0;
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
		if (sepFile == 0)
			{
				printf("3. Read text for cards as part of the answer (instead of reading the text from a separate file).\n\n");
			}
			else
			{
				printf("3. Read text for cards from a separate file (instead of giving part of the answer as a hint).\n\n");
			}
	}
	
  return 0;
}

/*Sets the number of cards*/
int info(int max, FILE *fp, char name[]){
	int i;
	char fileLine[MAXLENGTH];

	fp = fopen(FILENAME, "r"); 
	numCards = 0;

	for (i = 0; fgets(fileLine, max, fp) != NULL && i<MAXLENGTH-1; i++)
	{
		++numCards;

	}
	debugging(Number of cards, numCards);
	fclose(fp);

	return 0;

}
