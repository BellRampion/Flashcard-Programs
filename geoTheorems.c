#include <stdio.h>
/*WHAT STILL NEEDS TO BE DONE:
	1. Change fill() to start from the last place it read from and read the next line. 
	2. DONE Change compare to not test the current letter in 's1' against every letter in 's2'. 
	3. Copy the rest of the theorems and corollaries to theorems.
	4. Add the postulates to theorems.*/

#define MAXLENGTH 1000 // MAXLENGTH stands for 1,000


/*Functions*/
int fill(char s2[]);
int compare(char s1[], char s2[]);
int bgetline(char s1[]);

int main()
{
	char s1[MAXLENGTH]; //Character array to hold user's input
	char s2[MAXLENGTH]; //Character array to hold text to compare input to
	int i;  
	int getTheorem = 1; //
	int compareThem = 0;
	int override = 0;
	int correct, incorrect;
	correct = incorrect = 0;
	
	i = fill(s2);
	printf("When prompted, type in the theorems and postulates from Jacob's Geometry in order that they appear in the book. The theorem/postulate/corollary that you should type will be printed after you have entered your input. If the program did not compare it correctly, you may override the program. \n");
	printf("Begin: \n");
	getTheorem = bgetline(s1);

	printf("Comparing...\n");
	compareThem = compare(s1, s2);
	if (compareThem == 1)
	{
		printf("Would you like to override? (y/n) \n");
		override = getchar();
		
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
}

int fill(char s2[]){
	int i;
	char c;
	i = 0;
	FILE *fp;
	fp = fopen("theorems", "r");
	
	while ((c = fgetc(fp)) != ';' ){
		s2[i] = c;
		++i;
	}
	s2[i] = '\0';
	printf ("%s\n", s2);
		
}

int compare(char s1[], char s2[]){ 
	int i, correct, k, incorrect, m;
	incorrect = 0;
	k = 0;
	correct = 0;
	m = 0;
	for (i = 0; s1[i] != '\0'; i++){ //i starts out at 0. Test to see if the end of 's1' has been reached.
		printf("i: %i\n", i); // Print the value of i, which is the place it's at in 's1'. 
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
	printf("The theorem/postulate/corollary: %s \n", s2);
	if (incorrect > 5)
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

int bgetline(char s1[]){
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
