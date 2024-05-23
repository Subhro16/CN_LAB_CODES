#include <stdio.h>
#include <math.h>
#include <string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void){
	char data[100];
	int data1[100],data2[100];
	int dl,r,i=0,j=0,k=0,z,c;
	printf("\nEnter the dataword::");
	scanf("%s",data);
	dl=strlen(data);
	
	while(1){
		if(pow(2,i)>=dl+i+1){
			break;
		} i++;
	}
	r=i;
	printf("\n No. of redundant bits::%d \n",r);
	
	for(i=0;i<dl;i++){
		data1[i] = data[i]-48;
	}
	for(i=0;i<r;i++){
		z=pow(2,i);
		data2[z] = 999;
	}
	for(i=dl+r;i>=1;i--){
		if(data2[i]!=999){
			data2[i]=data1[j];
			j++;
		}
	}
	for(i=0;i<r;i++){
		z=pow(2,i);
		c=0;
		for(j=z;j<=dl+r;j=z+k){
			for(k=j;k<z+j;k++){
				if(k <= dl+r){
					if(data2[k]!= 999){
					c = c+data2[k];
					}
				}
			}
		}
		data2[z] = c%2;
	}
	printf("Codeword is::");
	j = 0;
	
	for(i = dl+r;i>=1;i--){
		printf("%d ",data2[i]);
	}
	int sd,cadl;
	struct sockaddr_in sad,cad;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9690);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr *)&sad,sizeof(sad));
	send(sd,data2,dl+r,0);
	printf("\n");
	close(sd);
	return 0;
}
