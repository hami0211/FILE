#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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
	char *ptr;
	int blockSize = BlockSize;
	unsigned int fileSize;
	struct stat stbuf;

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
	if(buf == NULL){
		fprintf(stderr, "error\n");
		exit(1);
	}

	readSize = read(fd_1, buf, fileSize);
	buf[fileSize] = '\0';
	ptr = buf;
	while(*ptr){
		if(isalpha(*ptr)){
			if(isupper(*ptr)){
				*ptr = tolower(*ptr);
			}
		}
		ptr++;
	}

	fd_1 = open(inputFile, O_WRONLY | O_TRUNC);
	write(fd_1,buf,fileSize);

	return 0;
}