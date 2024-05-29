/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Jarvinia Zhao
Student ID#: 143013233
Email      : jzhao169@myseneca.ca
Section    : NGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15 // Maximum length of name input
#define PHONE_DESC_LEN 4 // Maximum of phone description
#define PHONE_LEN 10 // Length of phone number


// MS#3 Additional macro's:
#define OPENING_HOUR 10 //Clinic operation starting hour
#define CLOSING_HOUR 14 //Clinic operation end hour
#define APPOINT_INTERVAL 30 //appointment minute interval


//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
struct Phone
{
    char description[PHONE_DESC_LEN + 1]; //store the phone description that can be any one of: CELL, HOME, WORK, TBD
    char number[PHONE_LEN + 1]; // store 10-digit phone number (example: "1112224444")
};


// Data type: Patient 
struct Patient
{
    int patientNumber; //store a unique patient number
    char name[NAME_LEN + 1]; // store patient's (pet's) name
    struct Phone phone; //A phone type for storing the patient's contact information
};

// ------------------- MS#3 -------------------

// Data type: Time
struct Time 
{
    int hour;// store appointment time hour
    int min; // store appointment time minute
};


// Data type: Date
struct Date
{
    int year; // store appointment date year
    int month; // store appointment date month
    int day; // store appointment date day
};


// Data type: Appointment
struct Appointment
{
    int patientNumber; // A unique patient number for linking appointments data with patients data
    struct Time time; // A Time type for storing the appointment's detailed time
    struct Date date; // A Date type for storing the appointment's date
};



// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data);


// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data);


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient);


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient);




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);

// Sort appointment by date and time
void sortAppointmentByTime(struct Appointment appoints[], int max);

// Check if an appointment matches the given date
int findMatchedAppointment(const struct Appointment* appoints, const struct Date* searchDate);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Get user input for date of an appointment
struct Date inputAppointmentDate(void);


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H

