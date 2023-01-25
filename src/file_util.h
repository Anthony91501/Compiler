/**
  * 
  * Author: Tom Terhune 
  * 	E-mail: ter1023@pennwest.edu
  * Author: Karl Miller
  * 	E-mail: mil7865@pennnwest.edu
  * Author: Anthony Stepich
  * 	E-mail: ste4864@pennwest.edu
  * 
  * Program 1 - fileopen
  * Group 3
  * CSC 460 - Language Translation
  */

#ifndef file_util_h
#define file_util_h


#include <stdbool.h>
#include <stdio.h>

/* 
-------------------------------------------------------------------------------
                Globally Accesible struct(s)                                       
-------------------------------------------------------------------------------
*/
#pragma region structs
/* Describing the states of the machine */
enum COMPFILES_STATE {
    COMPFILES_STATE_NO_NAME_PROVIDED = 0,
    COMPFILES_STATE_NAME_NEEDS_VALIDATION = 1,
    COMPFILES_STATE_NAME_VALIDATED = 2
};

/*
    CompFile is a globally accesible struct which maintains references to the loaded files.

    It has a number of functions closely associated to it. In that way it is a class-like, but a singleton. There is only one CompFile that ever should exist.
*/
struct TCompFiles {
    /* A file pointer to an open input file. */
    FILE * in;
    /* A file pointer to an open output file. */
    FILE * out;
    /* A file pointer to an open tmp file. */
    FILE * temp;
    /* A file pointer to an open listing file. */
    FILE * listing;
    /* Determines the status of input file validation. */
    short input_file_state;
    /* Determines the status of output file validation. */
    short output_file_state;
    /* 1 indicates that a user requested to terminate the program. */
    short terminate_requested;
    /* The default filename. */
    char * input_file_name;
    /* the last filename provided by the user */
    char * lastUserProvidedFilename;
};
struct TCompFiles CompFiles;

/* 

    Initializes CompFiles struct to default values. 

*/
void CompFiles_Init();


void CompFiles_DeInit();

/* 
    Validates an input file name and sets the value in the struct.

    Returns:
        0 if an input file was validated and loaded into the struct.
        1 if the user requested to terminate the program. 
*/
short CompFiles_ValidateInputFile(const char * filename);

/*
    Validates an output file name and sets the value in the struct.

    Returns:
        0 if an output file was validated and loaded into the struct.
        1 if the user requested to terminate the program.
*/
short CompFiles_ValidateOutputFile(const char * filename);



/* CompFiles_LoadInputFile loads a new file pointer as the input file. If there is a file already loaded, it closes that file first. */
void CompFiles_LoadInputFile(FILE * newInputFile);

/* CompFiles_LoadOutputFile loads a new file pointer as the output file. If there is a file already loaded, it closes that file first. */
void CompFiles_LoadOutputFile(FILE * newOutputFile);

/* CompFiles_LoadTempFile loads a new file pointer as the temp file. If there is a file already loaded, it closes that file first. */
void CompFiles_LoadTempFile(FILE * newTempFile);

/* CompFiles_LoadListingFile loads a new file pointer as the listing file. If there is a file already loaded, it closes that file first. */
void CompFiles_LoadListingFile(FILE * newListingFile);



#pragma endregion structs

/* 
-------------------------------------------------------------------------------
 file operations                                                
-------------------------------------------------------------------------------
*/
#pragma region fileops

/*

    backupFile renames an existing file, adding the extension '.bak' to the end of it. For example 'outFile.out' will become 'outFile.out.bak'.

                    Authors:    klm127
                    Created On: 1/22/2023
                    Covered by Unit Tests
*/
void backupFile(const char * filename);

enum FILE_EXISTS_ENUM {
    FILE_EXISTS = 1,
    FILE_DOES_NOT_EXIST = 0
};
/*
    fileExists checks whether a file given by filename exists.

    parameters:
        - char * filename : the filename to check.
    returns short:
        - 1 if the file exists.
        - 0 if the file does not exist.

                    Authors:    klm127
                    Created On: 1/19/2023
                    Covered by Unit Tests

*/
short fileExists(const char * filename);

#pragma endregion fileops

/* 
-------------------
filename functions                                                
------------------
*/
#pragma region filenames

/*
    The enum FILENAME_EXTENSION_PARSE describes possible return values from filenameHasExtension which indicate different ways which a filename may be invalid.
        no period :         -1
        ends in period:     -2
        starts with period: -3
*/
enum FILENAME_EXTENSION_PARSE {
    FILENAME_HAS_NO_PERIOD = -1,
    FILENAME_ENDS_IN_PERIOD = -2,
    FILENAME_IS_ONLY_PERIOD = -3,
    FILENAME_IS_DIRECTORY = -4
};

/*
    filenameHasExtension checks whether a filename has an extension. It validates that a string would be a valid path but with one additional condition: it must have a period in the file name portion of the path followed by at least one character. 

    parameters:
        - char * filename : the string to check

    returns int:
        - the index of the '.' character in the string if it exists.
        otherwise, one of the negative FILE_EXTENSION_PARSE enums indicating why the filename is invalid;
            (-1) means there was no period.
            (-2) means it ended in a period.
            (-3) means it is only a period.
            (-4) means it ends in a slash and is a directory.

                    Authors:    klm127
                    Created On: 1/19/2023
                    Covered by Unit Tests

*/
int filenameHasExtension(const char * filename);

/*
    addExtension modifies the string given by filename by concatenating the string given by extension.

    addExtension returns a pointer to a new, concatenated string. This string is allocated with `malloc`. When you are done with it, the memory should be cleared with `free` to avoid memory leaks.
    
    parameters:
        char * filename - the char array to modify
        char * extension - the char array to append

                    Authors:    thomasterh99, klm127
                    Created On: 1/18/2023
                    Covered by Unit Tests
*/
char * addExtension(const char* filename, const char* extension);

/*
    removeExtension modifices the string given in parameters by copying the characters of the string up to the index of the last period.

    PRECONDITION:
        filename has been validated to have a correct extension (not leading with a '.', not ending with a '.')

    parameters:
        char * filename - the char array to modfify

    returns:
        a pointer to a new, extensionless string. This string is allocated with `malloc`. When you are done with it, the memory should be cleared with `free` to avoid memory leaks.

                    Authors:    thomasterh99, klm127
                    Created On: 1/22/2023
                    Covered by Unit Tests

*/
char * removeExtension(const char * filename);



#pragma endregion filenames

/* 
----------------
prompt functions                                                
----------------
*/
#pragma region prompts
enum USER_OUTPUT_OVERWRITE_SELECTION {
    USER_OUTPUT_OVERWRITE_REENTER_FILENAME_SELECTED = 1,
    USER_OUTPUT_OVERWRITE_OVERWRITE_EXISTING_FILE = 2,
    USER_OUTPUT_OVERWRITE_DEFAULT_FILENAME = 3,
    USER_OUTPUT_TERMINATE_PROGRAM = 4,
    USER_OUTPUT_TERMINATE_INVALID_ENTRY = -1
};
/*
    promptUserOverwriteSelection prompts the user as to what they want to do about an output file already existing. It prints a prompt and parses the user response to one of the USER_OUTPUT_OVERWRITE_SELECTION enums. It does NOT loop.

    returns short corresponding to one of the enums of USER_OTUPUT_OVERWRITE_SELECTION

                    Authors:    klm127, thomasterh99, anthony91501
                    Created On: 1/20/2023
                    Covered by Unit Tests

*/
short promptUserOverwriteSelection();
/*
    function: char * getString()
    
    getString scans a string character by character until recieving a null termination character or a new line

    parameters: none

    returns: a pointer to a new character array given by the user with a size of the number of characters + 4 for the possible extension
    This string is allocated with `malloc`. 
    When you are done with it, the memory should be cleared with `free` to avoid memory leaks.

                    Authors:    thomaserh99
                    Created On: 1/23/2023
                    Covered by Unit Tests
*/
char * getString();
/*
    function: promptInputFilename()
    
    promptFilename calls the function getString to recieve a filename from the user and returns it

    parameters:

    mutates: Will set the 'terminate requested' flag in CompFiles if the user inputs only a \\n. 

    returns: char * inputfilename to be verified

                    Authors:    thomaserh99
                    Created On: 1/23/2023
                    Covered by Unit Tests
*/
char * promptInputFilename();
/*
    function: promptOutputFilename()
    
    promptFilename calls the function getString to recieve an output filename from the user and returns
        the user entered filename or the default filename (inputfilename + .out)

    parameters:


    returns: char * output filename to be verified

                    Authors:    thomaserh99
                    Created On: 1/23/2023
                    NOT Covered by Unit Tests
*/
char * promptOutputFilename();



#pragma endregion prompts


#endif

