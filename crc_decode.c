#include <stdio.h>
#include <string.h>
void main(void){
	char data[50],div[10],data1[50];
	int dl,divl,i,j;
	printf("\nEnter the code word::");
	scanf("%s",data);
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
	printf("%d",j);
	if(j==0){
		printf("\n Original data received\n");
		printf("\n Actual data::");
		for(i = 0;i<dl-(divl-1);i++) printf("%c",data1[i]);
	}
	else printf("\n Data received is wrong\n");
	printf("\n");
}
