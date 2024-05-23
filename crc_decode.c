#include <stdio.h>
#include <string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
void main(void){
	char data[50],div[10],data1[50];
	int dl,divl,i,j;
	/*printf("\nEnter the code word::");
	scanf("%s",data);*/
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9996);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sad,sizeof(sad));
	listen(sd,10);
	cadl=sizeof(cad);
	cd=accept(sd,(struct sockaddr *)&cad,&cadl);
	recv(cd,data,sizeof(data),0);
	dl = strlen(data);
	printf("\nEnter the coefficients of generator polynomial::");
	scanf("%s",div);
	divl=strlen(div);
	strcpy(data1,data);
	
	for(i=0;i<dl-(divl-1);i++){
		if(data[i]=='1'){
			for(j = 0;j<divl;j++){
				if(data[i+j]==div[j]) data[i+j] = '0';
				else data[i+j] = '1';
			}
		}
	}
	j=0;
	for(i = dl-(divl-1);i<dl;i++) j = j+data[i]-48;
	//printf("%d",j);
	if(j==0){
		printf("\n Original data received\n");
		printf("\n Actual data::");
		for(i = 0;i<dl-(divl-1);i++) printf("%c",data1[i]);
		printf("\n");
		printf("CRC sum : ");
		for(i = dl-(divl-1);i<dl;i++) printf("%c",data[i]);
	}
	else printf("\n Data received is wrong\n");
	printf("\n");
}
