/*
 * TimeStamp.c
 *
 *  Created on: Oct 3, 2016
 *      Author: r
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Blocking wait
 */
void waitForSignal(int fd,struct timespec* t){
	char buf[2];
	//block
	while(read(fd,buf,1)<1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,t);
}

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Parameter <tty device>\n");
		exit(1);
	}

	char* path = argv[1];
	int ttyDevice = open(path,O_RDONLY | O_NOCTTY);
	if(ttyDevice<0){
		printf("error opening %s\n",path);
		exit(1);
	}

	struct timespec currentTime, lastTime;
	waitForSignal(ttyDevice, &lastTime);

	while(1){
		waitForSignal(ttyDevice,&currentTime);
		double diff = ((currentTime.tv_sec - lastTime.tv_sec) +
				(currentTime.tv_nsec-lastTime.tv_nsec)/(1E9));
		lastTime = currentTime;
		printf("%lfs\n",diff);
	}


	return 0;
}



























