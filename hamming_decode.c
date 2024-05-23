#include <stdio.h>
#include <math.h>
#include <string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void){
	char data[100];
	int data1[100],data2[100];
	int dl,r,i=0,j=0,k=0,z,c,l; //11000101100
	/*printf("\nEnter the dataword::");
	scanf("%s",data);*/
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9690);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sad,sizeof(sad));
	listen(sd,10);
	cadl=sizeof(sad);
	cd=accept(sd,(struct sockaddr *)&cad,&cadl);
	recv(cd,data,strlen(data),0);
	printf("\nCodeword received : ");
	dl=strlen(data);
	
	while(1){
		if(pow(2,i)>=dl+1){
			break;
		} i++;
	}
	r=i;
	j=dl-1;
	
	for(i=1;i<=dl;i++){
		data1[i] = data[j]-48;
		j--;
	}
	l=1;
	int count = 0;
	
	for(i=0;i<r;i++){
		z=pow(2,i);
		c=0;
		for(j=z;j<=dl;j=z+k){
			for(k=j;k<z+j;k++){
				if(k <= dl){
					c = c+data1[k];
				}
			}
		}
		data2[l] = c%2;
		count = count + data2[l];
		l++;
		
	}
	if(count == 0){
		printf("Actual data received\n");
	}
	else{
		printf("Wrong data received");
		j = 0;
		for(i=r;i>=1;i--){
			if(data2[i]==1) j +=pow(2,(i-1));
		}
		printf("\n Error at position %d\n",j);
		if(data1[j]==0) data1[j]= 1;
		else data1[j] = 0;
		printf("Corrected Codeword is::");
		
		for(i = dl;i>=1;i--){
			printf("%d",data1[i]);
		}
		printf("\n");
	}
	close(cd);
	close(sd);
	return 0;
}
