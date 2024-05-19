//C code to encode a user provided dataword using checksum procedure
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){

	//*******************START CODE FOR CHECKSUM SENDER*****************//
	char data[100],data1[100];
	int t,c,k,dl,sl,i,j=0,sum[100];
	printf("\n enter the data \n");
	scanf("%s",data);
	dl=strlen(data);

	//****this done to mandet seglen in pow of 2*********
	while(1){
		printf("\n enter the segment length \n");
		scanf("%d",&sl);
		for(i=1;i<=sl/2;i++){
			if(pow(2,i)==sl){
				j=1;
				break;
			}
		}
		if(j==1){
			break;
		}
		else{
			printf("\n segment length must in pow of 2\n");
		}	
	}
	int sd,cd,cadl,sadl;
	struct sockaddr_in sad,cad;
	char str[50];
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr*)&sad,sizeof(sad));
	//***********************************************************************
	
	//if data length not divisible by segl, adding 0 at front of data
	if(dl%sl!=0){
		i=sl-(dl%sl);
		for(j=0;j<i;j++){
			data1[j]='0';
		}
		strcat(data1,data);
		strcpy(data,data1);
		dl=dl+i;
	}
	//******************************
	for(i=0;i<sl;i++){
		sum[i]=0;
	}
	for(i=dl;i>0;i=i-sl){
		c=0;
		k=sl-1;
		for(j=i-1;j>=i-sl;j--){
			t=(sum[k]+(data[j]-48)+c);
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
	printf("\n Checksum = ");
	for(i=0;i<sl;i++){
		if(sum[i]==0){
			sum[i]=1;
		}
		else{
			sum[i]=0;
		}
		printf("%d",sum[i]);
		data[dl+i]=sum[i]+48;
	}
	data[dl+i]='\0';
	printf("\n code word is: %s",data);
	send(sd,data,sizeof(data),0);	
	//********************END CODE FOR CHECKSUM SENDER***************//
	return 0;
}
/*
Your code is designed to encode a dataword using a checksum procedure. Here's a brief overview of how it works:

1. It takes a dataword as input from the user.
2. It prompts the user to enter a segment length and ensures that it is a power of 2.
3. It creates a socket connection to send the encoded data to a specified address and port.
4. It adds zeros at the front of the data if the data length is not divisible by the segment length.
5. It calculates the checksum by performing bitwise addition.
6. It complements the checksum to obtain the final code word.
7. It sends the code word to the specified address and port using the socket connection.

Please let me know if you have any specific questions or need further clarification on any part of the code.
*/
/*
The provided C code implements a checksum procedure for encoding a user-provided data word. Here's a breakdown and explanation of the code:

**Initialization:**

* Character arrays `data` and `data1` store the user input and potentially modified data.
* Variables for loop counters, data length, segment length, and checksum calculations.
* Network socket-related variables are commented out (unused in this context).

**Segment Length Validation:**

* User is prompted for data and segment length.
* A loop ensures the segment length is a power of 2 (commonly used for checksum calculations).

**Data Padding (Optional):**

* This section checks if the data length is divisible by the segment length.
* If not, leading zeros are added to make the length a multiple of the segment length.
* This ensures equal-sized segments for checksum calculation.

**Checksum Calculation:**

* An array `sum` is initialized with zeros to store checksum bits for each segment.
* The loop iterates through the data in segments (from end to beginning).
* Inner loop iterates through each character in the current segment.
* The checksum calculation involves adding the current data character (converted to integer) and the previous carry (`c`) to the corresponding `sum` element.
* The result is adjusted using modulo 2 (`%2`) to get the checksum bit and a carry bit (`c`).
* Additional logic handles potential overflow and corrects the checksum bits.

**Checksum Inversion (Optional):**

* The loop iterates through the `sum` array, inverting the checksum bits (0 becomes 1 and vice versa) before appending them to the data.
* This is a common practice in checksum calculations.

**Sending Encoded Data (Commented Out):**

* The commented section includes network socket creation and connection code (likely unused for basic functionality).
* It attempts to send the encoded data through a socket, suggesting the potential for sending the data over a network.

**Output:**

* The calculated checksum bits are printed.
* The modified data with appended checksum bits is printed as the "code word."

**Note:**

* The network socket functionality is commented out and not relevant to the core checksum calculation.
* The checksum implementation uses a simple modulo-2 addition with carry handling. More robust checksum algorithms like CRC (Cyclic Redundancy Check) exist, offering better error detection capabilities.

This code provides a basic implementation of checksum encoding for user-provided data. It can be further improved by:

* Implementing error handling for user input.
* Handling different data types (not just characters).
* Using a more robust checksum algorithm (e.g., CRC).
* Removing the commented-out network functionality if not used.
*/
