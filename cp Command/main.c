#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"


int main(int argc,char *argv[]) {

    char original_file_name[2048];  // It holds the name that belongs to file that we want to copy
    char copied_file_name[2048];    // It holds the name that belongs to copied file

    strcpy(original_file_name,"./");   // Firstly, our directory is where we run our c program.

    // It can not take argument which is less than 3 or bigger than 4.
    if(argc < 3 || argc > 4) {
        fprintf(stderr,"Syntax Error\n");
        exit(-1);
    }


    else if(argc == 3) {
        if(!strcmp(argv[1],"cp")) {
            strcat(original_file_name,argv[2]);
            int original_file = open(original_file_name,O_RDONLY); // Open file in Read_Only mode
            if(original_file < 0) {
                fprintf(stderr,"No such file or directory\n");  // If it can not open the specified file, it terminates itself.
                exit(-1);
            }
            else {
                strcpy(copied_file_name,"./copied_"); // If the number of argument is 3, created file name starts with "copied_"
                strcat(copied_file_name,argv[2]);
                int copied_file = open(copied_file_name,O_WRONLY | O_CREAT | O_EXCL,0777); // Create a file in Write_Only mode
                int size = lseek(original_file,0,2); // Find size of original file
                lseek(original_file,0,0);            // Go to starting position again
                char copied[size];                   // It holds bytes
                read(original_file,copied,size);     // put the bytes into array from original file
                write(copied_file,copied,size);      // put the bytes into created file from array

                // Close the files
                close(original_file);
                close(copied_file);
            }
        }
        else {
            fprintf(stderr,"Syntax Error\n");
            exit(-1);
        }
    }


    else if(argc == 4) {

        if(!strcmp(argv[1],"cp")) {
            strcat(original_file_name,argv[2]);
            int original_file = open(original_file_name,O_RDONLY); // Open file in Read_Only mode
            if(original_file < 0) {
                fprintf(stderr,"No such file or directory\n"); // If it can not open the specified file, it terminates itself.
                exit(-1);
            }
            else {
                strcpy(copied_file_name,"./");
                strcat(copied_file_name,argv[3]);   // When number of argument is 4 , user specifies the name for the created file.
                int copied_file = open(copied_file_name,O_WRONLY | O_CREAT,0777); // Create a file in Write_Only mode
                int size = lseek(original_file,0,2);   // Find size of original file
                lseek(original_file,0,0);              // Go to starting position again
                char copied[size];                     // It holds bytes
                read(original_file,copied,size);       // put the bytes into array from original file
                write(copied_file,copied,size);        // put the bytes into created file from array


                // Close the files
                close(original_file);
                close(copied_file);
            }
        }
        else {
            fprintf(stderr,"Syntax Error\n");
            exit(-1);
        }
    }




}
