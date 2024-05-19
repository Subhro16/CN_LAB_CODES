//C code to decode a user provided dataword using checksum procedure.provide output alongwith data
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>

int main(){
	char data[100];
	int t,c,k,dl,sl,i,j=0,sum[100],x,power=1;
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr*)&sad,sizeof(sad));
	listen(sd,10);
	cadl=sizeof(cad);
	cd=accept(sd,(struct sockaddr*)&cad,&cadl);
	recv(cd,data,sizeof(data),0);
	dl=strlen(data);
	
	//***this done to mandate seglen must in pow of 2**********
	while(1){
		printf("\nEnter the segment length : ");
		scanf("%d",&sl);
		for(i=1;i<=sl;i++){
			if(pow(2,i)==sl){
				j=1;
				break;
			}
		}
		if(j==1){
			break;
		}
		else{
			printf("\n Segment length must be power of 2\n");
		}
	}
	for(i=0;i<sl;i++){
		sum[i]=0;
	}
	for(i=dl;i>0;i=i-sl){
		c=0;
		k=sl-1;
		for(j=i-1;j>=i-sl;j--){
			t=(sum[k]+data[j]-48)+c;
			sum[k]=t%2;
			c=t/2;
			k--;
		}
		if(c==1){
			for(j=sl-1;j>=0;j--){
				t=sum[j]+c;
				sum[j]=t%2;
				c=t/2;
			}
		}
	}
	j=0;
	for(i=0;i<sl;i++){
		if(sum[i]!=1){
			j++;
			break;
		}
	}
	if(j==0){
		printf("\n data recv ok \n");
		printf("\n ACTUAL data IS: \n");
		for(i=0;i<dl-sl;i++){
			printf("%c",data[i]);
		}
	}
	else{
		printf("%d data recv wrong \n");
	}
	close(cd);
	close(sd);
	return 0;
}
/*
Your code is designed to decode a dataword using a checksum procedure. Here's a brief overview of how it works:

1. It sets up a socket connection to receive the encoded data from a specified address and port.
2. It receives the dataword.
3. It prompts the user to enter the segment length and ensures that it is a power of 2.
4. It calculates the checksum of the received dataword.
5. It checks if the calculated checksum matches the received checksum. If they match, it prints the actual data; otherwise, it indicates that the received data is wrong.

There are a few things to note in your code:

1. The code assumes that the received data is in the format where the checksum bits are appended at the end of the dataword.
2. It uses a socket connection, so you need to ensure that a sender program is running to send data to this receiver program.
*/
/*
The provided C code decodes a user-provided data word using a checksum procedure and checks for errors during transmission. Here's a breakdown of the code:

**Initialization:**

* Character array `data` stores the received data word.
* Variables for loop counters, data length, segment length, and checksum calculations.
* Network socket-related variables are used for receiving data (unlike the previous code for sending).

**Segment Length Validation (Receiver Side):**

* Similar to the previous code, the user is prompted to enter the segment length.
* The code ensures the segment length is a power of 2.

**Receiving Data:**

* Network socket setup (bind, listen, accept) establishes a connection to receive data.
* `recv` function retrieves the data word from the network and stores it in the `data` array.
* `dl` stores the received data length.

**Checksum Calculation (Receiver Side):**

* An array `sum` is initialized with zeros to store the received checksum bits for each segment.
* The loop iterates through the data in segments (from end to beginning).
* The inner loop iterates through each character in the current segment.
* The checksum calculation is identical to the sender code, using modulo-2 addition with carry handling to recreate the checksum based on the received data.

**Error Detection:**

* The code checks if all the calculated checksum bits (`sum`) are 1.
* If all are 1, it indicates a successful reception (no errors during transmission).
* Otherwise, an error message is displayed.

**Extracting Original Data:**

* If there are no errors (checksum bits are all 1), the original data is extracted by removing the appended checksum bits from the received data word.
* Only the characters before the checksum (data length minus segment length) are printed as the actual data.

**Network Cleanup:**

* The network sockets are closed.

**Improvements:**

* The code focuses on the core functionality of receiving and decoding data using checksum.
* It avoids unnecessary functionalities like padding the data (present in the sender code).
* Error handling for network operations could be added for robustness.

Overall, this code effectively demonstrates receiving and decoding data using a checksum procedure, allowing for basic error detection during data transmission.
*/
