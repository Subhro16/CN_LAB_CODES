#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main(){
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	
	sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	sad.sin_family = AF_INET;
	sad.sin_port = htons(49000);
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sd,(struct sockaddr *)&sad,sizeof(sad));
	listen(sd,10);
	
	cadl=sizeof(cad);
	cd=accept(sd,(struct sockaddr *)&cad,&cadl);
	
	recv(cd,str,sizeof(str),0);
	printf("Client says: %s\n",str);

	close(cd);
	close(sd);
}
/*
I'd be glad to explain the code, combining the strengths of previous responses and addressing potential issues:

**Code Breakdown:**

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sd, cd, cadl; // Socket descriptors
    struct sockaddr_in sad, cad; // Address structures

    char str[50]; // Buffer for data transmission

    // Create a TCP socket
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Configure server address
    sad.sin_family = AF_INET;
    sad.sin_port = htons(49000); // Port number (converted to network byte order)
    sad.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces (localhost for clarity)

    // Bind the socket to the address
    if (bind(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen for incoming connections (queue length of 10)
    if (listen(sd, 10) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Server listening on port %d\n", ntohs(sad.sin_port));

    // Accept a connection
    cadl = sizeof(cad); // Pass address length to accept
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);
    if (cd < 0) {
        perror("accept failed");
        exit(1);
    }

    // Receive data from the client
    int received = recv(cd, str, sizeof(str), 0);
    if (received < 0) {
        perror("recv failed");
        exit(1);
    }

    // Print the received message
    printf("Client says: %s\n", str);

    // Close the client socket
    close(cd);

    // Close the server socket
    close(sd);

    return 0;
}
```

**Explanation:**

1. **Header Inclusions:**
   - `stdio.h`: Provides standard input/output functions like `printf` for user interaction.
   - `arpa/inet.h`: Defines functions for internet protocol family sockets, including `socket`, `htons`, `inet_addr`, and `accept`.
   - `string.h`: Offers string manipulation functions, used for `memset` (not explicitly shown here) to initialize memory.
   - `unistd.h`: Contains various system call definitions, including `close` for closing sockets.

2. **Variable Declarations:**
   - `sd`, `cd`: Socket descriptors for server and client sockets, respectively.
   - `cadl`: Stores the size of the client address structure for `accept`.
   - `sad`, `cad`: Structures of type `sockaddr_in` to hold server and client address information.
   - `str`: Character array to store the received message from the client (size 50).

3. **Socket Creation:**
   - `sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);` creates a TCP socket (stream-based) in the IPv4 address family.
   - Error handling is added using `perror` and `exit` in case socket creation fails.

4. **Server Address Configuration:**
   - `sad.sin_family = AF_INET;`: Sets the address family to IPv4.
   - `sad.sin_port = htons(49000);`: Sets the port number to 49000, converted to network byte order using `htons`.
   - `sad.sin_addr.s_addr = INADDR_ANY;`: Binds the socket to all available interfaces (localhost for illustrative purposes). This allows connections from any client on the same network. You might want to consider a specific interface or IP address for production use.

5. **Socket Binding:**
   - `bind(sd, (struct sockaddr *)&sad, sizeof(sad))` binds the socket `sd` to the address specified in `sad`.
   - Error handling is included using `perror` and `exit` in case binding fails.

6. **Listening for Connections:**
   - `listen(sd, 10)` puts the socket in listening mode, where it can accept
*/
