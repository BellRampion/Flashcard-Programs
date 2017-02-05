#include <stdio.h>
/*WHAT STILL NEEDS TO BE DONE:
	1. DONE Fix typos in theorems.
	2. DONE Add a variable to show how many cards the user has already done and how many are left
	3. Copy the rest of the theorems and corollaries to theorems.
	4. Add the postulates to theorems.*/

/*TO UPLOAD TO GITHUB: 
	Copy file to cPrograms. Run this code: 
	"git add geotheorems.c
	git commit -m "Commit message"
	git push" */
#define MAXLENGTH 1000 // MAXLENGTH stands for 1,000
#define NUMTHEOREMS 58 //The number of lines in theorems


/*Functions*/
int fill(char s2[], FILE *fp);
int compare(char s1[], char s2[]);
int bgetline(char s1[]);

int main()
{
	char s1[MAXLENGTH]; //Character array to hold user's input
	char s2[MAXLENGTH]; //Character array to hold text to compare input to
	char nl; //For catching newlines
	char yOrN; //Yes or no
	int i, j;  
	int getTheorem = 1; 
	int compareThem = 0;
	int override = 0;
	int correct, incorrect;
	int numDone, printNum; //Number of cards done and number of cards left in deck
	numDone = printNum = 0;
	correct = incorrect = 0;
	FILE *fp;
	fp = fopen("theorems", "r"); //This is done here so that fill() won't reopen it each time. 
	/*Option to print the place the user is in the deck*/
	printf("Would you like to have the number of cards completed and the number left printed after each card? (y/n):\n");
	yOrN = getchar();
	nl = getchar();
	
	if (yOrN == 'y')
	{
		printNum = 1;
	}
	else printNum = 0;
	
	printf("When prompted, type in the theorems and postulates from Jacob's Geometry: first theorems with their corollaries, then the postulates. The theorem/postulate/corollary that you should type will be printed after you have entered your input. If the program did not compare it correctly, you may override the program. \n");
	
	for (i = 0; i < NUMTHEOREMS - 1; ++i){
		j = fill(s2, fp);
		printf("Begin: \n");
		getTheorem = bgetline(s1);

		printf("Comparing...\n");
		compareThem = compare(s1, s2);
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
			printf("You have completed %i cards. There are %i cards left in the deck.\n", numDone, NUMTHEOREMS-numDone);
		}
		
	}
}

int fill(char s2[], FILE *fp){ //Fills an array from a file
	int i, max;
	char c;
	i = 0;
	max = MAXLENGTH;
	
	fgets(s2, max, fp); //Reads a line from theorems
	
	printf ("%s\n", s2); //Print the string
	return 0;
		
}

int compare(char s1[], char s2[]){ //Compare the user input and the actual theorem
	int i, correct, k, incorrect;
	incorrect = 0;
	k = 0;
	correct = 0;
	for (i = 0; s1[i] != '\0'; i++){ //i starts out at 0. Test to see if the end of 's1' has been reached.
//		printf("i: %i\n", i); // Print the value of i, which is the place it's at in 's1'. For error checking.  
		if (s1[i] != s2[k])//If the current character in 's1' is not equal to the current character in 's2',
		{
			++incorrect; //Add one to incorrect
			++k;
		}
		else if (s1[i] == s2[k])
		{
			++correct;
			++k;
		}
			
	}
//	printf("The theorem/postulate/corollary: %s \n", s2);
	if (incorrect > 5) //Don't count it wrong unless there are more than five letters wrong.
	{
		printf("Incorrect. You got %i letters wrong. \n", incorrect);
		return 1;
	}
	else 
	{
		printf("Correct! You got %i letters right and %i letters wrong. \n", correct, incorrect);
		return 0; 
	}	
}

int bgetline(char s1[]){ //Takes the user's input and puts it in an array
	int c;
	int i;
	
	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i)
		s1[i] = c;
	if (c == '\n')
	{
		s1[i] = c;
		++i;
	}
	s1[i] = '\0';
	return 0;
}
