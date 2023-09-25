#include "systemcalls.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/

	int ret = system(cmd);
	//ret = ret; //avoid unused variable warning
	//pid_t pid;
	//int status;
	/*pid = wait(&status);
	if (pid == -1){
		printf("wait returned error\n");
		perror("wait");
		return false;
	}
	if (WIFEXITED (status)){
                printf ("Normal termination with exit status=%d\n",
                        WEXITSTATUS (status));
	
	}
    if (WIFSIGNALED (status)){
        printf ("Killed by signal=%d%s\n",
			WTERMSIG (status),
            WCOREDUMP (status) ? " (dumped core)" : "");
		return false;
	}

    if (WIFSTOPPED (status)){
		printf ("Stopped by signal=%d\n",
			WSTOPSIG (status));
		return false;
	}

    if (WIFCONTINUED (status)){
		printf ("Continued\n");

	}*/
	if (ret == -1){
		return false;
	}
	
    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
	/*Path expansion is being performed by exec(),
	 * this is contrary to my understanding of what
	 * is taught in lecture. Whatever the reason,
	 * this will prevent this.*/
	if (command[0] && strchr(command[0], '/') == NULL) {
        va_end(args);
        return false;
    }

	pid_t pid = fork();

	/*
	 *Fork will return the pid of the child if 
	 *in the parent thread and 0 if in the 
	 *child thread.
	 */

	if(pid > 0){ //this thread is parent
		printf("Hello from parent/n");
		int ret;
		int status;
		//loop not neccesary, wait is blocking
		ret = wait(&status);
		if(ret == -1){
			//wait error
			return false;
		}
		if (WIFEXITED (status)){
                	printf ("Normal termination with exit status=%d\n",
                        	WEXITSTATUS (status));
			if(WEXITSTATUS (status) == 0){
				return true;
			}
		}

	        if (WIFSIGNALED (status)){
        	        printf ("Killed by signal=%d%s\n",
                	        WTERMSIG (status),
                        	WCOREDUMP (status) ? " (dumped core)" : "");
               		 return false;
        	}

       		if (WIFSTOPPED (status)){
                	printf ("Stopped by signal=%d\n",
                        	WSTOPSIG (status));
             		return false;
       		}

        	if (WIFCONTINUED (status)){
                	printf ("Continued\n");

       		}
		return false;


		
	}
	else if(!pid){ //this thread is child

		//we exec in child thread because 
		//exec will replace the thread.
		//execv means exec vector allowing
		//us to to pass the list of args.
		printf("Hello from child/n");
		execv(command[0], command);
	}
	else if(pid == -1){ //fork() encountered an error
		return(false);
	}

    va_end(args);

    return false;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
	int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
	if (fd < 0) { perror("open"); abort(); }
	pid_t pid = fork();
	
	/*
	 *Fork will return the pid of the child if 
	 *in the parent thread and 0 if in the 
	 *child thread.
	 */

	if(pid > 0){ //this thread is parent
		int ret;
		int status;
		//loop not neccesary, wait is blocking
		ret = wait(&status);
		if(ret == -1){
			//wait error
			return false;
		}
		if (WIFEXITED (status)){
                	printf ("Normal termination with exit status=%d\n",
                        	WEXITSTATUS (status));
			if(WEXITSTATUS (status) == 0){
				return true;
			}
		}

	        if (WIFSIGNALED (status)){
        	        printf ("Killed by signal=%d%s\n",
                	        WTERMSIG (status),
                        	WCOREDUMP (status) ? " (dumped core)" : "");
               		 return false;
        	}

       		if (WIFSTOPPED (status)){
                	printf ("Stopped by signal=%d\n",
                        	WSTOPSIG (status));
             		return false;
       		}

        	if (WIFCONTINUED (status)){
                	printf ("Continued\n");

       		}
		return true;


		
	}
	else if(!pid){ //this thread is child
		
		//will make stdout redirect to fd, refer to I/O redirection
		if (dup2(fd, 1) < 0) { perror("dup2"); abort(); }
		close(fd);
		//we exec in child thread because 
		//exec will replace the thread.
		//execv means exec vector allowing
		//us to to pass the list of args.
		execv(command[0], command);
		
	}
	else if(pid == -1){ //fork() encountered an error
		return(false);
	}


    va_end(args);

    return true;
}
