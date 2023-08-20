#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
	//Open logging with default name, no flags, and LOG_USER facility
	openlog(NULL, 0, LOG_USER); 
    if (argc != 3) {
        printf("%s: The number of arguments must be exactly 2\n", argv[0]);
        syslog(LOG_ERR, "Invalid number of arguments: %s", argv[0]);
        return 1;
    }
    
    const char *writefile = argv[1];
    const char *writestr = argv[2];
    
    //printf(writefile);
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    //Create File
    int fileDesc = creat(writefile, 0664); //read write for owner and group
    if (fileDesc == -1){                   // read for everyone else
		printf("Error creating file!\n");
		syslog(LOG_ERR, "Error creating file!");
		return 1;
	}
	
	//Write to file
	ssize_t wroteBytes = write(fileDesc, writestr, strlen(writestr));
	if (wroteBytes == -1){
		printf("Error writing to file!\n");
		syslog(LOG_ERR, "Error writing to file!");
		return 1;
	}
	
	return 0;
}
