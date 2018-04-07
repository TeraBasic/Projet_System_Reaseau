#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "fctServeur.h"

// verfier si bien une ville et deservie par la gare
int existeDepart(struct trainInfo textarea[100],char *ville)
{
    for(int i=1;i<20;i++)
    {
        if(strcmp(textarea[i].depart,ville) == 0)
            return 1;
    }
    return 0;
}

int existeDestination(struct trainInfo textarea[100],char *ville)
{
    for(int i=1;i<20;i++)
    {
        if(strcmp(textarea[i].destination,ville) == 0)
            return 1;
    }
    return 0;
}


int main()
{
  int socket_listener, socket_service;
  int n = 0;
  // structure pour la socket d'ecoute et la socket de service
  struct sockaddr_in serveur_ad, client_ad;
  // creation de la socket
  socket_listener = socket(AF_INET, SOCK_STREAM, 0);
  // tester si la Socket est bien creer
  if (socket_listener == 0)
  {
    perror("Erreur lors de la creation de la socket ");
    exit(0);
  }
  printf("----Creation de Socket : Done--- \n");
  serveur_ad.sin_family = AF_INET;
  serveur_ad.sin_addr.s_addr = htonl(INADDR_ANY);
  serveur_ad.sin_port = htons(8080);

  // l'attachement d'une socket a une adresse se fait par le bind
  // le bind retourne -1 en cas d'erreur
  if (bind(socket_listener, (struct sockaddr *)&serveur_ad, sizeof(serveur_ad)) < 0)
  {
    perror("le Bind a echoue");
    exit(0);
  }

  printf("----Binding : Done--- \n");

  // Ouverture du service
  listen(socket_listener, 3);
  int c = sizeof(struct sockaddr_in);
  
// j'ai mis boucle infinie ici parce que le serveur doit être actif pour toujours
  while (1)
  {
    printf("----Attente de connexions--- \n");

    socket_service = accept(socket_listener, (struct sockaddr *)&client_ad, (socklen_t *)&c);
    n++;
    printf("----%d pers Connecter --- \n", n);
    if (socket_service < 0)
    {
      perror("Erreur lors de l accept de la connexions");
    }
    printf("----Connexion avec un client : Done ---- \n");
    fctServeur(socket_service);
  }
  return 0;
}
