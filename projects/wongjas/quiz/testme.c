#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char character_set = "abcdefghijklmnopqrstuvwxyz@#![](){} "[rand() % 36]; //Character pool lower case letters & special characters

    return character_set; //Returns a random character from the pool
}

char *inputString()
{
    char character_set[] = "abcdefghijklmnopqrstuvwxyz"; //Decided include all lower cases of the alphabet and a space
     
    char word[5]; //Size 6  because we need to include null at the end, decided not to use malloc, so we will get a warning, which is disabled in my makefile
    int i;

    for (i = 0; i<5; i++){ //Loop through character_set and randomly assign a character to the word index (0-4 for 5 characters) 
	word[i] = character_set[rand() % 26];
    }

    return word; //Returns a random string
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
