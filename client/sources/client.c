#include <stdlib.h>
#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include "fctClient.h"


int main()
{

  int socket_client;
  struct sockaddr_in serveur;
  char villeDepart[VILLE];
  char villeArrivee[VILLE];
  char heureDepart[HEURE];
  char heureArrive[HEURE];

  // creation de socket
  socket_client = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_client == -1)
  {
    perror("Erreur lors de la creation du socket");
    exit(0);
  }

  printf("---- Creation Socket : Done ----\n");

  serveur.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveur.sin_family = AF_INET;
  serveur.sin_port = htons(8080);

  if (connect(socket_client, (struct sockaddr *)&serveur, sizeof(serveur)) < 0)
  {
    perror("Connexion echoue");
    exit(0);
  }

  printf("---- Connexion avec le serveur : Done ----\n");

  while (1)
  {
    int choixEntree;
    printf("\n|-------------------------------Veuillez choisir le mode de recherche  ------------------------------------------------|\n");
    printf("|                                                                                                                      |\n");
    printf("| 1 - Trouver un trajet a partir d'une ville de depart et une ville d'arrivee.                                         |\n");
    printf("| 2 - Trouver un trajet a partir d'une ville de depart, une ville d'arrivee et l'heure de départ.                      |\n");
    printf("| 3 - Trouver un trajet a partir d'une ville de depart, une ville d'arrivee et l'heure de départ & l'heure d'arriver.  |\n");
    printf("| 4 - Trouver le trajet le moins chere entre Deux Ville .                                                              |\n");
    printf("|----------------------------------------------------------------------------------------------------------------------|\n");

    printf("Tapez 1 | 2 | 3 | 4\n");
    scanf("%d", &choixEntree);

    switch (choixEntree)
    {
    case 1:
      
      printf("Entrez la ville de départ (ex: Grenoble):\n");
      scanf("%s", villeDepart);
      do{
      printf("Entrez la ville d'arrivee (ex: Valence):\n");
      scanf("%s", villeArrivee); }while(strcmp(villeDepart,villeArrivee) == 0);
      sendDonneesClient_DepArr(socket_client, villeDepart, villeArrivee);
      break;
    case 2:

      printf("Entrez la ville de départ (ex: Grenoble):\n");
      scanf("%s", villeDepart);
      do {
      printf("Entrez la ville d'arrivee (ex: Valence):\n");
      scanf("%s", villeArrivee);} while (strcmp(villeDepart,villeArrivee) == 0);
      do
      {
        printf("Entrez l'heure de départ sous la forme (hh:mm)\n");
        scanf("%s", heureDepart);
      } while (verif_temps(heureDepart) == 0);

      sendDonneesClient_DepArrHeure(socket_client, villeDepart, villeArrivee, heureDepart);
      break;
    case 3:

      printf("Entrez la ville de départ (ex: Grenoble):\n");
      scanf("%s", villeDepart);
      do {
      printf("Entrez la ville d'arrivee (ex: Valence):\n");
      scanf("%s", villeArrivee);} while (strcmp(villeDepart, villeArrivee) ==0);
      do
      {
        printf("Entrez l'heure de départ sous la forme (hh:mm)\n");
        scanf("%s", heureDepart);
      } while (verif_temps(heureDepart) == 0);

      do
      {
        printf("Entrez la deuxime heure de depart sous la forme (hh:mm)\n");
        scanf("%s", heureArrive);
      } while (verif_temps(heureDepart) == 0 || strcmp(heureDepart, heureArrive) == 0);
      sendDonneesClient3(socket_client, villeDepart, villeArrivee, heureDepart, heureArrive);
      break;
    case 4:
      printf("Entrez la ville de départ (ex: Grenoble):\n");
      scanf("%s", villeDepart);
      do {
      printf("Entrez la ville d'arrivee (ex: Valence):\n");
      scanf("%s", villeArrivee);} while (strcmp(villeDepart, villeArrivee) == 0);
      sendDonneesClientBestPrice(socket_client, villeDepart, villeArrivee);
      break;
    }
  }

  close(socket_client);

  return 0;
}
