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
	int listen_fd,comm_fd;
	struct sockaddr_in servaddr;
	FILE *myf = fopen("chat_servidor.txt", "a");
	time_t t;
	struct tm *tm;
	char hora[100];
	char *tmp;
	char sendline[100]="Usando el puerto 22000\n";

	listen_fd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);

	bind(listen_fd, (struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(listen_fd,10);
	comm_fd=accept(listen_fd, (struct sockaddr*)NULL, NULL);

	printf("\n\n\t\t -----Se inicio el chat -----\n\n");
	fputs("\n\n\t\t  -----Se inicio el chat -----\n\n",myf);
	 printf("sdsd");

	while (!strstr(cadena,"adios") && !strstr(sendline,"adios")){
        bzero(cadena,100);
        t = time(NULL);
        tm = localtime(&t);
        strftime(hora,100, "\n otro usuario (%H:%M) -> ",tm);

        read(comm_fd,cadena,100);
        tmp= strcat(hora,cadena);
        printf( "%s" ,tmp);
        fputs(tmp,myf);
        if (!strstr(cadena,"adios")){
            strftime(hora, 100 , "\n yo(%H:%M) -> ", tm);
            printf("%s",hora);
            gets(sendline);
            tmp= strcat(hora,sendline);
            write(comm_fd,sendline,strlen(sendline));
            fputs(tmp,myf);
        }
	}
	printf("\n\n Conversacion final guardada \n");
	printf("Se genero el archivo de texto -> chat_servidor.txt");
	fclose(myf);
    WSACleanup();


}
