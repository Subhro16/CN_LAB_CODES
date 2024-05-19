#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main(){
	int sd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	
	sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	sad.sin_family = AF_INET;
	sad.sin_port = htons(49000);
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sd,(struct sockaddr *)&sad,sizeof(sad));
	
	printf("Enter your mess : ");
	scanf("%[^\n]s",str);
	send(sd,str,sizeof(str),0);
	
	close(sd);
}
/*
 **Here's a breakdown of the code's functionality:**

**1. Header Files:**
   - `stdio.h`: Provides standard input/output functions like `printf` and `scanf` for interaction.
   - `arpa/inet.h`: Defines functions for internet protocol family sockets, like `socket`, `htons`, `inet_addr`, and `connect`.
   - `string.h`: Offers string manipulation functions, although not explicitly used in this code.
   - `unistd.h`: Contains various system call definitions, including `close` for closing sockets.

**2. Main Function:**
   - Declares variables for:
     - `sd`: Socket descriptor to handle the connection.
     - `cadl`: Not used in the code.
     - `sad`: Structure to store server address information.
     - `cad`: Structure to store client address information (unused).
     - `str`: Character array to store the message to be sent.
   - Creates a TCP socket using `socket` with IPv4 (`AF_INET`), stream-based (`SOCK_STREAM`), and TCP (`IPPROTO_TCP`) options.
   - Sets up server address information in `sad`:
     - Address family (`sin_family`): IPv4.
     - Port number (`sin_port`): 49000, converted to network byte order using `htons`.
     - IP address (`sin_addr.s_addr`): 127.0.0.1 (localhost).
   - Connects to the server using `connect`.
   - Prompts the user to enter a message using `printf`.
   - Reads the message input using `scanf`.
   - Sends the message to the server using `send`.
   - Closes the socket using `close`.

**In essence, this code establishes a TCP connection with a server running on port 49000 on the same machine (localhost), prompts for a message, and sends that message to the server.**

*/
