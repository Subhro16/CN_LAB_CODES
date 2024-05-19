//Even Parity checking using C programming
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
	int sd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9000);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sd,(struct sockaddr *)&sad,sizeof(sad));
	printf("Enter your bitstream : ");
	scanf("%s",str);
	int len=strlen(str);
	int check=0;
	for(int i=0;i<len;i++){
		if(str[i]=='1'){
			check++;		
		}
	}
	if(check%2==0){
		str[len]='0';	
	}
	else{
		str[len]='1';
	}
	str[len+1]='\0';
	send(sd,str,sizeof(str),0);
	close(sd);	
}
