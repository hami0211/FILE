#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define	MaxFileName	256
#define	BlockSize 	4096

int main(int argc, char **argv)
{
	char inputFile[MaxFileName];
	int fd_1;
	int c;
	int readSize;
	char *buf;
	char *reverse;
	int blockSize = BlockSize;
	unsigned int fileSize;
	struct stat stbuf;
	int i;

	if(argc!=2){
		fprintf(stderr, "error\n");
		exit(1);
	}
	strcpy(inputFile,argv[1]);

	fd_1 = open(inputFile, O_RDONLY);
	if(fd_1<0){
		fprintf(stderr, "error\n");
		exit(1);
	}
	fstat(fd_1,&stbuf);
	fileSize = stbuf.st_size;

	buf = (char *)malloc(fileSize + 1);
	reverse = (char *)malloc(fileSize + 1);
	if(buf == NULL){
		fprintf(stderr, "error\n");
		exit(1);
	}

	readSize = read(fd_1, buf, fileSize);
	buf[fileSize] = '\0';
	for(i=0;i<fileSize;i++){
		reverse[i] = buf[fileSize-i-1];
	}
	reverse[fileSize] = '\0';

	fd_1 = open(inputFile, O_WRONLY | O_TRUNC);
	write(fd_1, reverse, fileSize);

	return 0;
}