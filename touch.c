#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 200 
#define RSIZ 100
#define DATA_SIZE 200


int main(int argc, char **argv){

    if(argc == 1){printf("No file names given!\n"); exit(1);}         
    if(argc > 2){printf("Cannot have more than 1 file names!\n"); exit(1);}
    
    /* Variable to store user content */
    char data[DATA_SIZE];

    /* File pointer to hold reference to our file */
    FILE * fPtr;
    if(fPtr = fopen(argv[1], "r")){
    	printf("file already exsisits");
    	return 0;
    }

    /* 
     * Open file in w (write) mode. 
     * "data/file1.txt" is complete path to create file
     */
    fPtr = fopen(argv[1], "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }


    /* Input contents from user to store in file */
    printf("Enter contents to store in file : \n");
    fgets(data, DATA_SIZE, stdin);


    /* Write data to file */
    fputs(data, fPtr);


    /* Close file to save file data */
    fclose(fPtr);


    /* Success message */
    printf("File created and saved successfully. :) \n");
}
return 0;   
    
}

