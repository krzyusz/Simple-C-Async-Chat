#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strcat
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h> // biblioteka do programowania wielowątkowego
#define port 8080
int client_sock;./j
struct sockaddr_in addr;
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
         // zerowanie potrzebnych tablic
         bzero(buff, 100);
         bzero(message,115);
     n = 0;
     // wpisanie zawartosci z wejscia konsoli do buff
         while ((buff[n++] = getchar()) != '\n');
         // laczenie lancuchow tekstowych
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
 
//inicjowanie zmiennych odpowiadajacych za dzialanie wielowatkowe programu
pthread_t thread_send, thread_recv;
 
// Twrzoenie socket'a
client_sock = socket(AF_INET, SOCK_STREAM, 0);
if (client_sock<0) {
perror("Wystapil blad przy tworzeniu socketu...\n");
}
puts("Pomyslnie utworzono socket..");
bzero(&addr, sizeof(addr));
 
//przypisanie IP i portu do socketu
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
addr.sin_port = htons(port);
 
// Laczenie wczesniej utworzonego socketa z socketem drugiego klienta
if (connect(client_sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
perror("Nie udalo sie polaczyc z drugim klientem...");
}
 
puts("Polaczono z klientem..");
 
// tworzenie osobnych watkow do obslugi wysylania i odbierania wiadomosci
pthread_create(&thread_send, NULL, send_message, NULL);
pthread_create(&thread_recv, NULL, receive_message, NULL);
 
while(1);//utrzymywanie dzialania funkcji main
 
return 0;
}
