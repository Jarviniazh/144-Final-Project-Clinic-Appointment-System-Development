

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

// Validates the user input is an integer
int inputInt(void)
{
	int input; // Value entered
	char lastChar; // The last character stored after user input
	do
	{
		scanf("%d%c", &input, &lastChar);
		if (lastChar != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (lastChar != '\n');
	return input;
}

// Validates the value entered is greater than 0
int inputIntPositive(void)
{
	int input; // Value entered
	do
	{
		scanf("%d", &input);
		if (input < 0)
		{
			clearInputBuffer();
			printf("ERROR! Value must be > 0: ");
		}
	} while (input < 0);
	return input;
}

// Validates the value entered is between the two arguments received by the function
int inputIntRange(int lowerBound, int upperBound)
{
	int input; // Value entered
	int isInt; // Flag, the value entered is in the range
	do
	{
		isInt = scanf("%d", &input);
		clearInputBuffer();
		if (isInt != 1)
		{
			printf("Error! Input a whole number: ");
		}
		else if (input < lowerBound || input > upperBound)
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
		}
	} while (isInt != 1 || input < lowerBound || input > upperBound);
	return input;
}

// Validate the entered character matches any of the characters in the received C string argument.
char inputCharOption(const char charOption[])
{
	char input; // Character entered
	do
	{
		scanf("%c", &input);
		clearInputBuffer();
		//printf("input is %c \n", input); //debug
	

		if (strchr(charOption, input) == NULL)
		{
			printf("ERROR: Character must be one of [%s]: ", charOption);
		}
	} while (strchr(charOption, input) == NULL);

	return input;
}

// Obtain user input for a C string value with a length
void inputCString(char* input, int minLen, int maxLen)
{
	char userInput[MAX_INPUTS + 1]; // String to store user input
	int length; // String length

	do
	{
		scanf("%[^\n]", userInput);
		clearInputBuffer();
		// Get the length of string entered
		length = strlen(userInput);

		// Check the entered string is fulfill the requirements
		if (minLen == maxLen && length != minLen)
		{
			printf("Invalid %d-digit number! Number: ", minLen);
			//printf("ERROR: String length must be exactly %d chars: ", minLen);
		}
		else if (length > maxLen)
		{
			printf("ERROR: String length must be no more than %d chars: ", maxLen);
		}
		else if (length < minLen)
		{
			printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);
		}

	} while (length < minLen || length > maxLen);

	// Copy user input string to input
	strcpy(input, userInput);
	input[maxLen] = '\0'; // Clear the array for next call
}

// Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* phone)
{
	int i;
	int isValidate = 1; // Flag, the phone number entered is valid 

	// Check if the array is NULL or if the array size is not exactly 10 characters long
	if (phone == NULL || strlen(phone) != 10)
	{
		printf("(___)___-____");
	}
	else
	{
		for (i = 0; i < 10 && isValidate == 1; i++)
		{
			// Check if the array not only contains digits (0-9) 
			if (!(phone[i] >= '0' && phone[i] <= '9'))
			{
				isValidate = 0;
			}
		}

		if (isValidate == 1) // the array only contains 0-9 and exactly 10 char long
		{
			printf("(%c%c%c)%c%c%c-%c%c%c%c", phone[0], phone[1], phone[2], phone[3], phone[4],
				phone[5], phone[6], phone[7], phone[8], phone[9]);
		}
		else
		{
			printf("(___)___-____");
		}
	}
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Declare number of days in each month based on the user input year and month
int getDaysInMonth(int year, int month)
{
	int daysInMonth; // Number of days in a month
	
	//Check leap year for Feb
	if (month == 2) 
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			daysInMonth = 29; // Leap year
		}
		else {
			daysInMonth = 28;
		}
	}
	// Month has 30 days
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		daysInMonth = 30;
	}
	//Month has 31 days
	else
	{
		daysInMonth = 31;
	}

	return daysInMonth;
}


