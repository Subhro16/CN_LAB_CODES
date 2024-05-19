#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main(){
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9000);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sad,sizeof(sad));
	listen(sd,10);
	cadl=sizeof(cad);
	cd=accept(sd,(struct sockaddr *)&cad,&cadl);
	recv(cd,str,sizeof(str),0);
	int len=strlen(str);
	int check=0;
	for(int i=0;i<len;i++){
		if(str[i]=='1'){
			check++;
		}
	}
	if(check%2){
		printf("There is error in data");	
	}
	else{
		str[len-1]='\0';
		printf("No error in data. Received data : %s",str);
		return 0;
	}
	close(cd);
	close(sd);
}
