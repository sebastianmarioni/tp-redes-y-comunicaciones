#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
int main()
{
    WSADATA wsa;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.");


    char cadena[100];
	int sockfd;
	struct sockaddr_in servaddr;
	FILE *myf = fopen("chat_cliente.txt", "a");
	time_t t;
	struct tm *tm;
	char hora[100];
	char *tmp;
	char sendline[100]="Usando el puerto 22000\n";



	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	servaddr.sin_addr.s_addr = inet_addr( "127.0.0.1");

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (!strstr(cadena,"adios") && !strstr(sendline,"adios")){
        bzero(cadena,100);
        t = time(NULL);
        tm = localtime(&t);
        strftime(hora,100, "\n yo (%H:%M) -> ",tm);
        printf( "%s" ,hora);
        gets(sendline);
        fputs(tmp,myf);
        tmp= strcat(hora,sendline);
        write(sockfd,sendline,strlen(sendline)+1);
        if (!strstr(cadena,"adios")){
            strftime(hora, 100 , "\n otro usuario (%H:%M) -> ", tm);
            read(sockfd,cadena,100);
            tmp= strcat(hora,cadena);
            printf("%s",tmp);
            fputs(tmp,myf);
        }
    }
    printf("\n\n Conversacion finalizada \n\n");
    printf("\n\n -----Se genero el archivo chat_cliente.txt -----\n\n");
	fclose(myf);

	//FALTA CERRAR EL SOCKET CREO.. BUSCAR COMO HACERLO
	 WSACleanup();

}
