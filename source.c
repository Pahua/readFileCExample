#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
//Multi thread
//#include <pthread.h> 	//For doing a thread.
//#include <unistd.h> 	//For using usleep.
//Socket 
#include <stdio.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h> 
#include <stdlib.h>	//for doing an exit
//#include <strings.h> 	//for using a bzero 
//#include <unistd.h> 	//for read & write
#include <string.h>  	//to use strlen
#include <sys/stat.h> //to determine size of file

//To compile RUN gcc  node.c -o node -lpthread.

//Default error message from C.
void error(const char *msg) {
	perror(msg);
	exit(1);
}

//Configuration file reader function.
char * readFile() {

	FILE *fr;
	char *message;
	fr = fopen("elapsed.txt", "r");
	/*create variable of stat*/
	struct stat stp = { 0 };
	/*These functions return information about a file. No permissions are required on the file itself*/
	stat("elapsed.txt", &stp);
	/*determine the size of data which is in file*/
	int filesize = stp.st_size;
	/*allocates the address to the message pointer and allocates memory*/
	message = (char *)malloc(sizeof(char) * filesize);

	if (fread(message, 1, filesize - 1, fr) == -1) {
		printf("\nerror in reading\n");
		/**close the read file*/
		fclose(fr);
		/*free input string*/
		free(message);
	}
	printf("\n\tEntered Message for Encode is = %s", message);
	return message;
}

/*
//Thread Init
void *threadFunc(void *arg) {
	char *str;
	int i = 0;
	str = (char*)arg;
	while (i < 10) {
		usleep(1);
		printf("threadFunc says: %s\n", str);
		++i;
	}
	return NULL;
}
*/

/*
//Start a thread.
void threadInit() {
	pthread_t threadId;
	int i = 0;

	//Thread definition.
	pthread_create(&threadId, NULL, threadFunc, "processing...");

	//Thread connection.
	pthread_join(threadId, NULL // void ** return value could go here);

	while (i < 10) {
		usleep(1);
		printf("Initializing thread\n");
		++i;
	}
}
*/

/*
//Origin to Destiny.
void origin() {
	int sockfd, n;
	int portno = 1990;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("127.0.0.1");
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	printf("Please enter the message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0)
		error("ERROR writing to socket");
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if (n < 0)
		error("ERROR reading from socket");
	printf("%s\n", buffer);
}
*/

/*
//Destiny to Origin.
void destiny() {
	int sockfd, newsockfd, clilen;
	int portno = 1990;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		error("ERROR on accept");
	bzero(buffer, 256);
	n = read(newsockfd, buffer, 255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n", buffer);
	n = write(newsockfd, "I got your message", 18);
	if (n < 0) error("ERROR writing to socket");
}
*/

int main(void) {
	readFile();
	getchar();
}
