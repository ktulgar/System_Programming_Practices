#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc,char *argv[]) {



    // Firstly, locate the Pipe symbol
    int pipe_index;
    for(int i=0 ; i<argc ; i++) {
        if(strcmp("|",argv[i]) == 0) {
           pipe_index = i;
        }
    }


    // Secondly, determine the first command and its options
    char *first_command = argv[1];
    char *command1_arguments[pipe_index];
    command1_arguments[0] = first_command;
    int index;
    for(index=1 ; index<pipe_index - 1; index++) {
        command1_arguments[index] = argv[index+1];
    }
    command1_arguments[index] = NULL;


    // Thirdly , determine the second command and its options
    char *second_command = argv[pipe_index + 1];
    char *command2_arguments[argc - pipe_index ];
    command2_arguments[0] = second_command;
    for(index=1 ; index<(argc - pipe_index - 1); index++) {
        command2_arguments[index] = argv[pipe_index + index + 1];
    }

    command2_arguments[index] = NULL;


    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    // Child Process 1
    if(pid == 0) {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execvp(first_command,  command1_arguments);
    }

    else {

        pid = fork();

        // Child Process 2 from same parent
        if(pid == 0) {
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            execvp(second_command,  command2_arguments);
        }

        // Parent Process
        else {
            // Wait until children gets finished
            wait(NULL);

        }

    }



}
