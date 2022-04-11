/*Reference: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c*/
/*Modified By Abhishek Suryawanshi*/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>

#define PORT 8080
#define MAX  10000

void datasend(int new_socket ){

   char buff[MAX];
   int n;

   while(1){
   
       bzero(buff,MAX);

        read(new_socket,buff,sizeof(buff));
	printf("From Client:%s \t To Client:",buff);
	bzero(buff,MAX);
	n=0;
	while((buff[n++]=getchar( ))!='\n');
	write(new_socket,buff,sizeof(buff));

	if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
   
   }

}



int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	//char buffer[1024] = {0};

	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
        
       printf("\r\n Waiting for client to connect ...\r\n");

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("\n\r Successfully connected with Client\n\r");
	
        
	datasend(new_socket);

	close(server_fd);

	return 0;
}

