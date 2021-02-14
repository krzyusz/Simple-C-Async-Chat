#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strcat
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h> // biblioteka do programowania wielowątkowego
#define port 8080
int socket_desc , client_sock , s_len;
struct sockaddr_in addr , client;
char imie[15]="";
char message[115]="";
char d[1] = ":";
void *receive_message(){
while(1){
    char buff[100];
            bzero(buff, 100);     
            recv(client_sock, buff, sizeof(buff),0);
            printf("%s", buff);
}
}
 
void *send_message(){
while(1){
                           char buff[100];
         int n=0;
                  bzero(buff, 100);
         bzero(message,115);
         while ((buff[n++] = getchar()) != '\n');
         strcat(message,imie);
strcat(message,buff);
send(client_sock, message, sizeof(message),0);
}
}
 
 
int main(int argc , char *argv[])
{
    //pobieranie imienia z wejscia konsoli
    printf("Podaj imie: ");
    int n=0;
    while ((imie[n++] = getchar()) != '\n');
    imie[n-1] = 0;
    strcat(imie,d);
    //-------------------------------------
 
pthread_t thread_send, thread_recv;
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
 
//Przypisanie adresu i portu 
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
addr.sin_port = htons(port);
 
//Bindowanie socketu z adresem i portem
if(bind(socket_desc,(struct sockaddr *)&addr , sizeof(addr))<0){
perror("Problem z bindowaniem");
return 1;
}
puts("Bindowanie socketu udane");
 
//nasluchiwanie przychodzacych polaczen na socket
listen(socket_desc , 2);
puts("Nasluchiwanie przychodzacych polaczen...");
 
 
s_len = sizeof(struct sockaddr_in);
 
// akceptacja przychodzącego połączenia 
client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&s_len);
if(client_sock<0){
perror("Blad przy polaczeniu");
return 1;
}
puts("Zaakceptowano polaczenie");
 
// tworzenie osobnych watkow do obslugi wysylania i odbierania wiadomosci
pthread_create(&thread_send, NULL, send_message, NULL);
pthread_create(&thread_recv, NULL, receive_message, NULL);
 
while(1);//utrzymywanie dzialania funkcji main
return 0;
}
