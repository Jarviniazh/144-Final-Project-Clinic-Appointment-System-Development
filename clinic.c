

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int count = 0; // number of eligible records 

    // Display each patient record
    for (i = 0; i < max; i++)
    {
        // Patient records that have a zero value for the patient number should NOT be displayed.
        if (patient[i].patientNumber != 0)
        {
            if (count == 0)
            {
                displayPatientTableHeader(); // Display the table header
            }
            displayPatientData(&patient[i], fmt);
            count++;
        }
    }

    // Check if there is no eligible record
    if (count == 0)
    {
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            printf("\n");
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            printf("\n");
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i;
    int emptyIndex = -1; // index of free element to store new record, initial with -1 (no free element yet)

    //Find a free element
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0 && emptyIndex == -1) //check if patient array has a free element
        {
            emptyIndex = i; // the index position of the free element
        }
    }

    //check if there is a free element
    if (emptyIndex != -1)
    {
        //Add new record
        patient[emptyIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[emptyIndex]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int input; // User input
    int result; // search result

    // Search patient record based on patient number
    printf("Enter the patient number: ");
    input = inputIntPositive();
    result = findPatientIndexByPatientNum(input, patient, max); //store the index of found record
    printf("\n");

    // Check if the record exist
    if (result == -1) // not exist
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[result]); // call for edit option
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int input; // User input
    int result; // search result
    int selection; // user's selection to remove a record

    // Search patient record based on patient number
    printf("Enter the patient number: ");
    input = inputIntPositive();
    result = findPatientIndexByPatientNum(input, patient, max); //store the index of found record
    printf("\n");

    // Check if the record exist
    if (result == -1) // not exist
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else
    {
        //display the record to the user in "form" format
        displayPatientData(&patient[result], FMT_FORM);
        //prompt for confirmation to remove the record
        printf("\nAre you sure you want to remove this patient record? (y/n): ");

        selection = (inputCharOption("yn") == 'y');
        if (selection)
        {
            //patient information should be set to a safe empty state to make it available again for a new record
            patient[result].patientNumber = 0;
            patient[result].name[0] = '\0';
            patient[result].phone.description[0] = '\0';
            patient[result].phone.number[0] = '\0';
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data)
{
    int i, j;
    int isAllRecords = 1; // Display all records
    int includeDateField = 1; //Display all appointment need date column
    int found; //flag, to link the patient number within 2 text data file

    displayScheduleTableHeader(&data->appointments[0].date, isAllRecords);

    // Sort all the appointments
    sortAppointmentByTime(data->appointments, data->maxAppointments);

    // Display all data
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0) // Only display valid data
        {
            found = 0; // Reset found flag for each appointment
            for (j = 0; j < data->maxPatient && !found; j++)
            {
                // Matching the patient data in patients with patient number in appointment, so the record display correct info for this patient
                if (data->patients[j].patientNumber == data->appointments[i].patientNumber)
                {
                    // Display all data
                    displayScheduleData(&data->patients[j], &data->appointments[i], includeDateField); 
                    found = 1; // Set found flag when matching patient is found
                }
            }
        }
    }
    printf("\n");
}



// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data)
{
    int i,j;
    int includeDateField = 0; // No need to include date column
    int isAllRecords = 0; // Only display selected records 
    int count = 0; // number of eligible records
    struct Date searchDate = { 0 }; // temp structure to store input
    struct Appointment sortTemp[MAX_INPUTS] = { {0} }; // temp structure to store matched appointment for later sorting
    int tempCount = 0; // number of matched records stored in sortTemp
    
    // Get date from user input
    searchDate = inputAppointmentDate();

    printf("\n");
    //Search the appointment and display all results found
    for (i = 0; i < data->maxAppointments; i++)
    {
        // Check if the record is valid and the input date match any records 
        if (data->appointments[i].patientNumber != 0 &&
            findMatchedAppointment(&data->appointments[i], &searchDate))
        {
            sortTemp[tempCount] = data->appointments[i];
            tempCount++;
        }
    }

    //Sort the matched appointments
    if (tempCount > 0)
    {
        sortAppointmentByTime(sortTemp, tempCount);
    }

    // Display sorted appointments
    for (i = 0; i < tempCount; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            // Matching the patient data in patients with patient number in appointments, so the record display correct info for this patient
            if (data->patients[j].patientNumber == sortTemp[i].patientNumber) 
            {
                // only display the header once
                if (count == 0) 
                {
                    // Display the table header with the input dates
                    displayScheduleTableHeader(&searchDate, isAllRecords);
                }
                displayScheduleData(&data->patients[j], &sortTemp[i], includeDateField);
                count++;
            }
        }
    }

            
    // Check if there is no eligible record
    if (count == 0)
    {
        printf("*** No appointment found ***\n");
    }
    printf("\n");
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int patientNumber; // the user's patient number
    int hour, mins; // User input of appointment time
    int i;
    int validTime; // flag, input time is valid for an appointment
    int successAppoint = 0; //flag, an appointment is successfully made
    int reEnter; // flag, need to reenter all date info
    struct Date searchDate = { 0 }; // temp structure to store input

    // Prompt the patient number that need add a new appointment
    printf("Patient Number: ");
    patientNumber = inputIntPositive(); 
    
    do
    {
        // Get date from user input
        searchDate = inputAppointmentDate();       
        reEnter = 0;
   
        // Until a valid time inputed and appointment is booked
        do
        {
            printf("Hour (0-23)  : ");
            hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            mins = inputIntRange(0, 59);

            validTime = 0;

            // Check if the input time is within working hours and interval is enough for an appointment
            if (hour >= OPENING_HOUR && (hour < CLOSING_HOUR || (hour == CLOSING_HOUR && mins == 0)) && 
                mins % APPOINT_INTERVAL == 0)
            {
                validTime = 1;
                //Check is there any time overlaps
                for (i = 0; i < maxAppointments && validTime; i++)
                {
                    if (appointments[i].patientNumber != 0 &&
                        findMatchedAppointment(&appointments[i], &searchDate) &&
                        appointments[i].time.hour == hour &&
                        appointments[i].time.min == mins)
                    {
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        validTime = 0;
                        reEnter = 1;
                    }
                }

                // If the time slot is vaild, store the appointment info to an enmpty record
                if (validTime)
                {
                    for (i = 0; i < maxAppointments && !successAppoint; i++)
                    {
                        if (appointments[i].patientNumber == 0)
                        {
                            appointments[i].patientNumber = patientNumber;
                            appointments[i].date.year = searchDate.year;
                            appointments[i].date.month = searchDate.month;
                            appointments[i].date.day = searchDate.day;
                            appointments[i].time.hour = hour;
                            appointments[i].time.min = mins;
                            printf("\n*** Appointment scheduled! ***\n\n");
                            successAppoint = 1;
                        }
                    } 
                }               
            }
            else // input out off working time or no enough time interval for an appointment
            {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in %d minute intervals.\n\n", OPENING_HOUR, CLOSING_HOUR, APPOINT_INTERVAL);
            }
        } while (!successAppoint && !reEnter);
    } while (!successAppoint);
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int patientNumber; // the user's patient number
    int i;
    int foundNumber = 0; // flag, found the input patient number
    int selection; // User choice
    int foundAppointment = 0; //flag, found the input input date of the patient
    int patientIndex; // The patient index of the input patient number
    struct Date searchDate = { 0 }; // temp structure to store input

    //Prompt the patient number to remove
    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    //Validate the patientNumber is in the system
    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].patientNumber == patientNumber)
        {
            foundNumber = 1;
        }
    }

    if (foundNumber)
    {
        // Get date from user input
        searchDate = inputAppointmentDate();

      //Check if the input data is avaiable in the system
        for (i = 0; i < maxAppointments && !foundAppointment; i++)
        {
            if (appointments[i].patientNumber == patientNumber &&
                findMatchedAppointment(&appointments[i], &searchDate))

            {
                foundAppointment = 1;
                //Find the patient index based on the patient number
                patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
                printf("\n");
                //Display the patient info
                displayPatientData(&patients[patientIndex], FMT_FORM);
                //prompt for confirmation to remove the record
                printf("Are you sure you want to remove this appointment (y,n): ");

                selection = (inputCharOption("yn") == 'y');
                if (selection)
                {
                    //patient information should be set to a safe empty state to make it available again for a new record
                    appointments[i].patientNumber = 0;
                    printf("\nAppointment record has been removed!\n\n");
                }
                else
                {
                    printf("Operation aborted.\n\n");
                }           
            }
        }
    }  
    if (!foundAppointment && foundNumber) {
        printf("ERROR: Appointment record not found!\n\n");
    }
    else if (!foundNumber) {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }   
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int input; // User input
    int result; // search result

    // Search patient record based
    printf("Search by patient number: ");
    input = inputIntPositive();
    result = findPatientIndexByPatientNum(input, patient, max); //store the index of found record
    printf("\n");

    // Check if the record exist
    if (result == -1) // not exist
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[result], FMT_FORM); // display the record to the user in "form" format
    }
    clearInputBuffer();
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char input[PHONE_LEN + 1]; // User input
    int i;
    int isFound = 0; // flag, if any record is found

    printf("Search by phone number: ");
    inputCString(input, PHONE_LEN, PHONE_LEN);
    printf("\n");
    displayPatientTableHeader();

    // Check if the record exist
    for (i = 0; i < max; i++)
    {
        if (strncmp(patient[i].phone.number, input, PHONE_LEN) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE); // display the patient record in "tabular" format
            isFound = 1; // change the flag to 1 
        }
    }

    // Check if record is not found
    if (isFound != 1)
    {
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int maxPatientNumber; // current highest patient number
    int newPatientNumber; // next highest patient number

    // find the current highest patient number
    maxPatientNumber = patient[0].patientNumber;
    for (i = 0; i < max; i++)
    {
        if (maxPatientNumber < patient[i].patientNumber)
        {
            maxPatientNumber = patient[i].patientNumber;
        }
    }
    newPatientNumber = maxPatientNumber + 1;
    return newPatientNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int index = -1; // index of the record, initial with -1 (record can't be located) 
    int i;
    int isFound = 0; // flag, if find the patient number

    for (i = 0; i < max && isFound != 1; i++)
    {
        if (patientNumber == patient[i].patientNumber) //record is found
        {
            index = i; // the index position of the matched element
            isFound = 1; // change the flag to 1 to stop loop
        }
    }
    return index;
}

// Sort appointment by date and time
void sortAppointmentByTime(struct Appointment appoints[], int max)
{
    struct Appointment temp = {0}; // temporary variable used for bubble sorting the appointment data
    int i, j;

    for (i = 0; i < max - 1; i++) 
    {
        for (j = 0; j < max - i - 1; j++) 
        {
            // Comparing the date and time 
            if ((appoints[j].date.year > appoints[j + 1].date.year) ||
                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month > appoints[j + 1].date.month) ||
                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day > appoints[j + 1].date.day) ||
                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day == appoints[j + 1].date.day &&
                    appoints[j].time.hour > appoints[j + 1].time.hour) ||
                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day == appoints[j + 1].date.day &&
                    appoints[j].time.hour == appoints[j + 1].time.hour &&
                    appoints[j].time.min > appoints[j + 1].time.min)) 
            {
                // Swap appoints[j] and appoints[j+1]
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }
}

// Check if an appointment matches the given date
int findMatchedAppointment(const struct Appointment* appoints, const struct Date* searchDate)
{
    int result = 0;

    if (appoints->date.year == searchDate->year &&
        appoints->date.month == searchDate->month &&
        appoints->date.day == searchDate->day)
    {
        result = 1;
    }

    return result;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char name[NAME_LEN + 1];
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n", patient->patientNumber);

    // Enter new patient name
    printf("Name  : ");
    inputCString(name, 0, NAME_LEN);

    // Copy the input name to structure
    strcpy(patient->name, name);
    printf("\n");

    // Enter patient info
    inputPhoneData(&patient->phone);
}



// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection; // user choice

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');

    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL"); // Copy description to structure
        printf("Contact: CELL\n");

        // prompt the user for a 10-digit phone number
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN); //assign the entered value to the phone number member.
        printf("\n");
        break;

    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: HOME\n");

        // prompt the user for a 10-digit phone number
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN); //assign the entered value to the phone number member.
        printf("\n");
        break;

    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: WORK\n");

        // prompt the user for a 10-digit phone number
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN); //assign the entered value to the phone number member.
        printf("\n");
        break;

    case 4:
        strcpy(phone->description, "TBD");
        //phone number should be set to a safe empty state
        phone->number[0] = '\0';
        break;
    }
}

// Get user input for date of an appointment
struct Date inputAppointmentDate(void) {
    struct Date appointmentDate = { 0 };
    int year, month, day; // User input of appointment date
    int daysInMonth; // Number of days in a month

    // User input for year
    printf("Year        : ");
    year = inputIntPositive(); 

    // User input for month
    printf("Month (1-12): ");
    month = inputIntRange(1, 12); 

    // Calculate the number of days in the input month
    daysInMonth = getDaysInMonth(year, month); 

    // User input for day
    printf("Day (1-%02d)  : ", daysInMonth);
    day = inputIntRange(1, daysInMonth); 

    // Constructing the date
    appointmentDate.year = year;
    appointmentDate.month = month;
    appointmentDate.day = day;

    return appointmentDate;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int total = 0; //total number of records read from the file
    FILE* fp = NULL; // file pointer
    
    // open the text data
    fp = fopen(datafile, "r");
    
    //Check if the file was opened successfully
    if (fp != NULL) 
    {
        // Read the patient data and store to patient array
        while (total < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]",
            &patients[total].patientNumber,
            patients[total].name,
            patients[total].phone.description,
            patients[total].phone.number) >= 3)
        {
            total++; // Count the total number of records read from the file and stored to the array
        }
        fclose(fp); //Close the file
    }
    else
    {
        printf("Failed to open file: %s\n", datafile);
    }
    return total; 
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int total = 0; //total number of records read from the file
    FILE* fp = NULL; // file pointer

    // open the text data
    fp = fopen(datafile, "r");

    //Check if the file was opened successfully
    if (fp != NULL)
    {
        // Read the patient data and store to patient array
        while (total < max && fscanf(fp, "%d,%d,%d,%d,%d,%d", 
            &appoints[total].patientNumber, 
            &appoints[total].date.year, 
            &appoints[total].date.month, 
            &appoints[total].date.day, 
            &appoints[total].time.hour,
            &appoints[total].time.min) == 6)
        {
            total++; // Count the total number of records read from the file and stored to the array
        }     
        fclose(fp); //Close the file
    }
    else
    {
        printf("Failed to open file: %s\n", datafile);
    }
    return total;
}