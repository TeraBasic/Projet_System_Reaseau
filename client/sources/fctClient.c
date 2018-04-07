#include <stdlib.h>
#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// fonction pour verifier si l'heure entrer par l utilisateur est correcte
int verif_temps(char *temp)
{
  if ((strcmp(temp, "23:59") <= 0))
    return 1;
  else
  {
    printf("(Attention !) [ heure Invalide ] \n");
    return 0;
  }
}

// fonction qui envoie au serveur la ville de départ, la ville d'arrivée ,entrées par le user.
// sous la forme (choixDeMenu;villeDepart;villeArrive)
void sendDonneesClient_DepArr(int socket_client, char *villeDepart, char *villeArrivee)
{

  char resultat[100];
  sprintf(resultat, "1;%s;%s", villeDepart, villeArrivee);
  // //////////// STRTOK /////////////

  char reponse_serveur[10000];
  send(socket_client, resultat, sizeof(resultat), MSG_CONFIRM);
  int a;
  while ((a = recv(socket_client, reponse_serveur, sizeof(reponse_serveur), 0)) > 0)
  {
    if (strcmp(reponse_serveur, "END") == 0)
    {
      printf("#<--------------------END----------------------># \n ");
      break;
    }
    
    if (strlen(reponse_serveur) == 0)
    {
      printf("Trajet Introuvable \n ");
    }
    printf("\n N Train  Depart  Arriver  Heure_D--A   Prix  \n ");
    printf("-----------------------------------------------\n ");
    printf("%s\n", reponse_serveur);
    printf("\n ");
    memset(resultat, 0, sizeof(resultat));
    memset(reponse_serveur, 0, sizeof(reponse_serveur));
  }
}

// une fonction qui envoie au serveur la ville de départ, la ville d'arrivée ,heure Depart ,entrées par le user.
// sous la forme (choixDeMenu;villeDepart;villeArrive;heureDepart)
void sendDonneesClient_DepArrHeure(int socket_client, char *villeDepart, char *villeArrivee, char *heureDepart)
{
  char reponse_serveur[10000];
  char resultat[100];

  sprintf(resultat, "2;%s;%s;%s", villeDepart, villeArrivee, heureDepart);

  send(socket_client, resultat, sizeof(resultat), MSG_CONFIRM);

  while (recv(socket_client, reponse_serveur, sizeof(reponse_serveur), 0) > 0)
  {
    if (strcmp(reponse_serveur, "END") == 0)
    {
      printf("#<--------------------END----------------------># \n ");
      break;
    }
    printf("Reponse du serveur: %s\n", reponse_serveur);
    printf("<------------------------------> \n ");

    memset(resultat, 0, sizeof(resultat));
    memset(reponse_serveur, 0, sizeof(reponse_serveur));
  }
}

// fonction qui envoie au serveur la ville de départ, la ville d'arrivée , heure Depart , heure d'arriver ,entrées par le user.
// sous la forme (choixDeMenu;villeDepart;villeArrive;heureDepart;heureArriver)
void sendDonneesClient3(int socket_client, char *villeDepart, char *villeArrivee, char *heureDepart, char *heureArrive)
{
  char reponse_serveur[10000];
  char resultat[100];

  sprintf(resultat, "3;%s;%s;%s;%s", villeDepart, villeArrivee, heureDepart,heureArrive);

  send(socket_client, resultat, sizeof(resultat), MSG_CONFIRM);

  while (recv(socket_client, reponse_serveur, sizeof(reponse_serveur), 0) > 0)
  {
    if (strcmp(reponse_serveur, "END") == 0)
    {
      printf("#<--------------------END----------------------># \n ");
      break;
    }
    printf("Reponse du serveur: %s\n", reponse_serveur);
    printf("<------------------------------> \n ");

    memset(resultat, 0, sizeof(resultat));
    memset(reponse_serveur, 0, sizeof(reponse_serveur));
  }
}

// fonction qui envoie la ville de départ, la ville d'arrivée entrées par le user pour avoir le train le moins chere .
// sous la forme (choixDeMenu;villeDepart;villeArriver)
void sendDonneesClientBestPrice(int socket_client, char *villeDepart, char *villeArrivee)
{

  char resultat[100];
  sprintf(resultat, "4;%s;%s", villeDepart, villeArrivee);

  char reponse_serveur[1000];
  send(socket_client, resultat, sizeof(resultat), MSG_CONFIRM);

  while (recv(socket_client, reponse_serveur, sizeof(reponse_serveur), 0) > 0)
  {
    if (strcmp(reponse_serveur, "END") == 0)
    {
      printf("#<--------------------END----------------------># \n ");
      break;
    }
    printf("Reponse du serveur: %s\n", reponse_serveur);
    printf("<------------------------------> \n ");

    memset(resultat, 0, sizeof(resultat));
    memset(reponse_serveur, 0, sizeof(reponse_serveur));
  }
}
