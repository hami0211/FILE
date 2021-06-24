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
	char outputFile[MaxFileName];
	int fd_1;
	int fd_2;
	int c;
	int readSize;
	char *buf;
	int offset;
	int blockSize = BlockSize;
	unsigned int fileSize;
	struct stat stbuf;

	if(argc!=3){
		fprintf(stderr, "error\n");
		exit(1);
	}
	strcpy(inputFile,argv[1]);
	strcpy(outputFile,argv[2]);

	fd_1 = open(inputFile, O_RDONLY);
	fd_2 = open(outputFile, O_WRONLY | O_TRUNC);
	if(fd_1<0){
		fprintf(stderr, "error\n");
		exit(1);
	}
	if(fd_2<0){
		fd_2 = open(outputFile, O_CREAT | O_WRONLY);
	}
	fstat(fd_1,&stbuf);
	fileSize = stbuf.st_size;

	buf = (char *)malloc(fileSize + 1);
	if(buf == NULL){
		fprintf(stderr, "error\n");
		exit(1);
	}
	offset = 0;

	readSize = read(fd_1, buf, fileSize);
	buf[fileSize] = '\0';

	write(fd_2,buf,fileSize);

	return 0;
}