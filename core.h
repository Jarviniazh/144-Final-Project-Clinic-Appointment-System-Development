

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define MAX_INPUTS 100 //The maximum size of string from user input

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Validates the user input is an integer
int inputInt(void);

// Validates the value entered is greater than 0
int inputIntPositive(void);

// Validates the value entered is between the two arguments received by the function
int inputIntRange(int lowerBound, int upperBound);

// Validate the entered character matches any of the characters in the received C string argument.
char inputCharOption(const char charOption[]);

// Obtain user input for a C string value with a length
void inputCString(char* input, int minLen, int maxLen);

// Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* phone);

// Declare number of days in each month based on the user input year and month
int getDaysInMonth(int year, int month);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
