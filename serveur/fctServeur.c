#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "fctServeur.h"

// fonction qui s'occupe de la recuperation de donnee depuis le fichier text
void recup_donne(struct trainInfo *textarea)
{
  FILE *fp;
  int j = 0;
  char ch;
  char line[150];
  int line_num = 0;

  // tableau de ma structure pour stocker chaque information sur un train
  // ouverture du fichier Trains.txt
  if ((fp = fopen("Trains.txt", "r")) == NULL)
  {
    printf("Failure pour lecture!");
    exit(0);
  }
	
  while (fgets(line,150, fp) != NULL)
  {
    char temp[45] = " ";
    line_num++;
    unsigned int label = 0;
    for (unsigned int i = 0; i < strlen(line); i++)
    {
      ch = line[i];
      if (ch != ';')
      {
        temp[j++] = ch;
      }
      else
      {
        j = 0;
        label++;
        switch (label)
        {
        case 1:
          strcpy(textarea[line_num].numero, temp);
          break;
        case 2:
          strcpy(textarea[line_num].depart, temp);
          break;
        case 3:
          strcpy(textarea[line_num].destination, temp);
          break;
        case 4:
          strcpy(textarea[line_num].tempsDepart, temp);
          break;
        case 5:
          strcpy(textarea[line_num].tempsDestination, temp);
          break;
        case 6:
          textarea[line_num].prix = atof(temp);
          break;
        case 7:
          strcpy(textarea[line_num].reduc, temp);
          break;
        default:
          break;
        }
        memset(temp, 0, sizeof(temp));
      }
    }
  }
  promoAction(textarea);
  fclose(fp);
}

void promoAction(struct trainInfo *t)
{
  for(int i=0;i<getTaille(t);i++)
  {
  if(strcmp(t[i].reduc,"REDUC") == 0)
    {
      t[i].prix = t[i].prix -(t[i].prix * 20/100);
    }
  else if(strcmp(t[i].reduc,"SUPPL") == 0)
    {
      t[i].prix = t[i].prix + (t[i].prix * (10/100));
    }
  }
}

// fonction qui renvoit la taille du tableau de structure
// dans notre cas une case vide contient 0.0
int getTaille(struct trainInfo *tab)
{
  int nbr = 0;
  for(int i =0 ; i<25 ;i++)
  {
    if(tab[i].prix != 0.0)
    {
      nbr ++;
    }
  }
  return nbr;
}

// fonction qui fait la recherche d une voyage selon son prix
// utiliser dans la fonction best_price()
struct trainInfo searchByPrice(struct trainInfo *textarea,float prix)
{
  
    int z = getTaille(textarea);
     printf(" ==== > %d\n",z);
    for(int i =1 ; i<z;i++)
    {
      if(textarea[i].prix == prix)
      {
        return textarea[i];
      }
    }
}

// fonction qui cherche et qui renvoie le trajet le moins chere 
  struct trainInfo best_price(struct trainInfo *textarea)
  {
    struct trainInfo tr ;
    float bestP = textarea[1].prix;
     int z = getTaille(textarea);
    
    for(int i =1 ; i<z ;i++)
    {
      
      if(textarea[i].prix < bestP)
      {
        bestP = textarea[i].prix;
      }
    }
    tr = searchByPrice(textarea,bestP);
    return tr;
  }

  //-----------la fonction search ---------------------------------------------
  // fonction qui cherche les voyage possible en fonction de la gare de depart & arriver
  void search(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive)
  {
    int n = 0;
    for (int i = 1; i < 20; i++)
    {
      if ((strcmp(textarea[i].depart, depart) == 0))
      {
        if ((strcmp(textarea[i].destination, arrive) == 0))
        {
          textarea_copy[n] = textarea[i];
          n++;
        }
      }
    }
  }

  // fonction qui renvoie les trains possible en fonction du depart ,arrive , heure depart
  void searchByTime(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive, char *time)
  {
    int n = 0;
    int z = getTaille(textarea);
    for (int i = 1; i < z; i++)
    {
         // promoAction(&textarea[i]);
      if (strcmp(textarea[i].depart, depart) == 0 && strcmp(textarea[i].destination, arrive) == 0 && (strcmp(textarea[i].tempsDepart, time) >= 0))
      {
        textarea_copy[n] = textarea[i];
        n++;
      }
    }
  }
// fonction qui renvoie les voyages possible en fonction du depart arrive heure depart heure d'arriver
void searchByTimeInterval(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive, char *time1, char *time2)
{
  int n = 0;
  for (int i = 1; i < 20; i++)
  {       
    if ((strcmp(textarea[i].depart, depart) == 0 )&& (strcmp(textarea[i].destination, arrive) == 0))
    {      
      if ((strcmp(textarea[i].tempsDepart, time1) >= 0) ) 
      {          
        if((strcmp(textarea[i].tempsDestination, time2) <= 0)) 
        {
          textarea_copy[n] = textarea[i];
          n++;
        }
      }
    }
  }
}

// qui s'occupe du traitement de la requete client et le repondre 
// la fct recoit la requete du client sous la forme choixdeLaRecherche;villeDepart;villeArriver;....
  void receptionDemande(int socket_service)
  {
    struct trainInfo textarea[100];
    struct trainInfo r[25];
    char resultat[2000];
    recup_donne(textarea);
    // on applique les promotion apres avoir stocke les informations sur les trajets

    char message_client[100];
    char message_save[100];
    char *token = " ";
    char *tokenI[25];
    while (read(socket_service, message_client, 100) > 0)
    {
      strcpy(message_save, message_client);
      int i = 1;
      token = strtok(message_save, ";");
      while (token != NULL)
      {
        //affectation
        tokenI[i] = token;
        token = strtok(NULL, ";");
        i++;
      }
      int mode = atoi(tokenI[1]);
      char *depart = tokenI[2];
      char *arrive = tokenI[3];
      char *tempsDepart = tokenI[4];
      char *tempsArrive = tokenI[5];

      switch (mode)
      {
      case 1:
        search(textarea, r, depart, arrive);
        break;
      case 2:
        searchByTime(textarea, r, depart, arrive, tempsDepart);
        break;
      case 3:
        searchByTimeInterval(textarea,r,depart,arrive,tempsDepart, tempsArrive);
        break;
      case 4:
          search(textarea, r, depart, arrive);
          struct trainInfo t [20];
          t[0]=best_price(r);
          memset(&r, 0, sizeof(r)+1);
           r[0]=t[0];
        break;
      }

      for (int z = 0; z < 20; z++)
      {
        if (r[z].prix == 0.00)
          break;

        sprintf(resultat, "%s  %s %s  %s %s  %.2f", r[z].numero, r[z].depart, r[z].destination, r[z].tempsDepart, r[z].tempsDestination, r[z].prix);
        sleep(1);
        write(socket_service, resultat, sizeof(resultat));
        //Initialiser le buffer
        memset(message_client, 0, sizeof(message_client));
        memset(message_save, 0, sizeof(message_save));
        memset(resultat, 0, sizeof(resultat));
      }

      // envoyer le message END au serveur pour le prevenir que la reponse du seveur et terminer
      sleep(1);
      char *endMsg = "END";
      send(socket_service, endMsg, sizeof(char) * 12, 0);

      memset(&r, 0, sizeof(r));
      memset(resultat, 0, sizeof(resultat));
      memset(message_save, 0, sizeof(message_save));
      memset(message_client, 0, sizeof(message_client));
    }
  }
  void finfils(int sig)
  {
    wait(&sig);
  }

  // crrer des processus fils qui s occupe de chaque client
  // pour avoir plusieur client qui se connecte a la mm fois 
  void fctServeur(int socket_service)
  {
    struct sigaction a;

    switch (fork())
    {
    case 0:
      // on appel ici la fct serveur ;
      receptionDemande(socket_service);

      // appres le traitement de la fct serveur
      // appel a finfils = > tuer les fils
      finfils(sigaction(SIGCHLD, &a, NULL));
      break;
    }
  }
