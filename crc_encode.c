#include <stdio.h>
#include <string.h>
void main(void){
	char data[50],divisor[10],data1[50];
	int dl,divl,i,j;
	printf("\nEnter the input data::");
	gets(data);
	printf("\nEnter the coefficients of generator polynomial::");
	gets(divisor);
	dl = strlen(data);
	divl=strlen(divisor);
	
	for(i = 0;i<divl-1;i++) data[dl+i] = '0';
	data[dl+i] = '\0';
	printf("\nUpdated dividend::%s",data);
	strcpy(data1,data);
	for(i=0;i<dl;i++){
		if(data1[i]=='1'){
			for(j = 0;j<divl;j++){
				if(data1[i+j]==divisor[j]) data1[i+j] = '0';
				else data1[i+j] = '1';
			}
		}
	}
	for(i = dl;i<dl+(divl-1);i++) data[i] = data1[i];
	printf("\nThe codeword is::%s",data);
}
