/**************************************************************
* Class::  CSC-415-01 Fall 2025
* Name:: Will Young
* Student ID::924230057
* GitHub Name::Woyoung21
* Project:: Assignment 2 – Buffer and Structures
*
* File:: will_young_HW2_main.c
*
* Description:: This assignment is to help us better understand
* coding in C, working with structs, employing safe memory 
* practices and continuing to develop our planning and 
* debugging skills. We start by populating our struct using
* safe memory practices with the requested data. The requested
* message field is cut to fit into the hard coded memory 
* allotment that is provided. We then write that data by calling
* a prvoded function. We then create some logical
* infrastructure to push an unkown amount of c-strings to the 
* buffer, which we also created using safe memory practices.
* When the buffer is full, it is committed and the process 
* starts over again. Once we reach NULL, we break out of the
* loop and commit whatever is left in buffer. We then call 
* checkIT and deallocate the memory we created. Throughout the 
* program, there are commented out debugging statements that 
* were used to ensure the program is progressing as expected.
*
**************************************************************/
#include "assignment2.h"
#include <stdio.h> // for printf
#include <stdlib.h> // for malloc/free
#include <string.h> // for strncpy


int main(int argc, char * argv[]) {

    //step 4:
    //Populate struct fields with requested values. Heavy use of debugging
    //comments that are commented out. To note, the message field is only
    //a partial of what argv[3] sent, in order to keep it within the provided
    //memory allocation in the .h file.

    //printf("\n-----------------------------------------------------\n");
    //printf("\nStep 4\n");
    //printf("\n-----------------------------------------------------\n");

    struct personalInfo *newpInfo = malloc(sizeof(*newpInfo));
    newpInfo->firstName = argv[1];
    newpInfo->lastName = argv[2];
    newpInfo->studentID = 924230057;
    newpInfo->level = SENIOR;
    newpInfo->languages = KNOWLEDGE_OF_JAVA |
                        KNOWLEDGE_OF_JAVASCRIPT |
                        KNOWLEDGE_OF_PYTHON |
                        KNOWLEDGE_OF_CPLUSPLUS |
                        KNOWLEDGE_OF_HTML |
                        KNOWLEDGE_OF_ARM_ASSEMBLER;

    //size of message in coming in from argv[3]
    //size of message[100] field of struct
    //size of contents of message[100]
    
    int sizeofMessageA = strlen(argv[3]);
    int sizeofMessageF = sizeof(newpInfo->message);
    int lenofMessageF = strlen(newpInfo->message);

    //debugging comments to test size and contents of message components
    //printf("\nSize of message field in argv[3]: %d\n", sizeofMessageA);
    //printf("\nSize of message field in struct: %d\n", sizeofMessageF);
    //printf("\nLength of message field in struct: %d\n", lenofMessageF);
    //printf("\n-----------------------------------------------------\n");


    
    //Copy contents of argv[3] into message field up to 99 chars
    //to stay within the hardcoded memory allocation provided to
    //us. Then append null terminator to 100th element of
    //message[100] field
    strncpy(newpInfo->message, argv[3], sizeofMessageF-1);
    newpInfo->message[99] = '\0';

    //This is strictly for debugging. Get new length of contents in 
    //message field after strncpy(), then show it's contents.
    //int newlenofMessageF = strlen(newpInfo->message);
    //printf("\nNew length of message field in struct: %d\n", sizeofMessageF);

    // debug comment to ensure struct is being filled properly
    // with the appropriate information
    //printf("\n-----------------------------------------------------\n");
    //printf("This is the structs first name: %s\n", newpInfo->firstName);
    //printf("This is the structs last name: %s\n", newpInfo->lastName);
    //printf("This is the structs studentID: %d\n", newpInfo->studentID);
    //printf("This is the structs gradeLevel: %d\n", newpInfo->level);
    //printf("This is the structs knownLanguages: %d\n", newpInfo->languages);
    //printf("This is the structs message field: %s\n", newpInfo->message);
    //printf("\n-----------------------------------------------------\n");
    

    //step 5
    //printf("\n-----------------------------------------------------\n");
    //printf("\nStep 5\n");
    //printf("\n-----------------------------------------------------\n");

    //debug to see if function returns 0 which would indicate a successful
    //execution
    int callVal = writePersonalInfo(newpInfo);

    //printf("Results of writePersonalInfo function %02d: ", callVal);

    

    //step 6
    //printf("\n-----------------------------------------------------\n");
    //printf("\nStep 6\n");
    //printf("\n-----------------------------------------------------\n");

    

    //Create new allocated memory for the buffer at BLOCK_SIZE. Since we are receiving
    //an unspecified number of c-strings and we also don't know how big each one is,
    //we created some while loops and conditional statements to help push these c-strings
    //to the buffer while also making sure we don't run over the alloted memory. There is 
    //a special check if the c-string being pushed is bigger than what is available in the
    //buffer. In that insatnce, the c-string is partially pushed to max out the buffer,
    //the buffer is committed, then the remaining c-string is pushed to the buffer starting
    //at the beginning of the buffer. Once we hit NULL, we exit this loop and whatever is left
    //in the buffer is committed. During step 6, I heavily relied on printf statements to 
    //ensure that I could keep track of how many iterations were preformed until I reach NULL,
    //as well as the size of the incoming c-string, the current index of the buffer, the amount
    //of buffer remaining. In our rare case where the c-string needed to be split, we also
    //kept track of what was being committed and what was left to be committed. These printf
    //statements helped me visually track each iteration as well as when I finally broke out of 
    //the loop because NULL was reached.

    char * buffer = malloc(BLOCK_SIZE);
    const char * cString = getNext();
    int bufIndex = 0;
    int remaining_buffSpace = BLOCK_SIZE;
    int count = 1;

    while (cString != NULL) {

        int sizeCS = strlen(cString);
        

        //printf("\n1.) Starting buffIndex: %d during %d iterations\n", bufIndex, count);
        //printf("\n2.) Starting remaining_buffSpace: %d during %d iterations\n", remaining_buffSpace, count);
        //printf("\n3.) Current cString size: %d during %d iterations\n", sizeCS, count);
        

        if (sizeCS >= remaining_buffSpace) {

            int remainingCSString =  sizeCS - remaining_buffSpace;
            int committedCSString = sizeCS - remainingCSString;
            //copies up to the full buffer
            memcpy(buffer + bufIndex, cString, remaining_buffSpace);


            //printf("\n6.)Here is the buffIndex: %d during the first copy\n", bufIndex);
            //printf("\n7.)Here is the size of cString that was committed to the buff: %d during the first copy\n", committedCSString);
            //printf("\n8.)Here is the size of cString that is left: %d during the first copy\n", remainingCSString);


            //commits the full buff
            commitBlock(buffer);
            bufIndex = 0;
            remaining_buffSpace = BLOCK_SIZE;

            //printf("\n9.) Here is the new buffIndex: %d after the 1st commit\n", bufIndex);
            //printf("\n10.) Here is the remaining space in the buffer %d after the 1st commit\n", remaining_buffSpace);


            //copies what was left of cString into buffer
            memcpy(buffer + bufIndex, cString + committedCSString, remainingCSString);
            bufIndex = bufIndex + remainingCSString;
            remaining_buffSpace = BLOCK_SIZE - remainingCSString;
            

            //printf("\n11.) Here is the new buffIndex: %d after the 2nd copy at the end of %d iteration\n", bufIndex, count);
            //printf("\n12.) Here is the remaining space in the buffer %d after the 2nd copy at the end of %d iteration\n", remaining_buffSpace, count);
            //printf("\n-----------------------------------------------------\n");
        }
        else {

            memcpy(buffer + bufIndex, cString, sizeCS);
            bufIndex = bufIndex + sizeCS;
            remaining_buffSpace = remaining_buffSpace - sizeCS;
            
            
            //printf("\n4.) Here is the new buffIndex: %d at the end of %d iteration\n", bufIndex, count);
            //printf("\n5.) Here is the remaining space in the buffer %d at the end of %d iteration\n", remaining_buffSpace, count);
            //printf("\n-----------------------------------------------------\n");
        }

        cString = getNext();
        count++;
    }

    //printf("\n*****************************************************\n");
    //printf("\nI finally hit NULL terminator and exited the while loop\n");
    //printf("\n*****************************************************\n");

    //commit anything left in the buffer after reaching NULL
    if (bufIndex > 0) {

        commitBlock(buffer);
        //printf("\nCommitting last partial block\n");
    }

    //step 7
    //printf("\n-----------------------------------------------------\n");
    //printf("\nStep 7\n");
    //printf("\n-----------------------------------------------------\n");

    //call checkIt function to see if we have completed the assignment
    checkIt();

    //freeing newly allocated memory per our coding standards
    free(newpInfo);
    free(buffer);
    
    return 0;
}