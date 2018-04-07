#ifndef _FCTCLIENT_H_
#define  _FCTCLIENT_H_
#include <stdbool.h>
#include <stdio.h>
#define VILLE 30
#define HEURE 10

extern int verif_temps(char *temp);
extern void sendDonneesClient_DepArr(int socket_client, char *villeDepart, char *villeArrivee);
extern void sendDonneesClient_DepArrHeure(int socket_client, char *villeDepart, char *villeArrivee, char *heureDepart);
extern void sendDonneesClient3(int socket_client, char *villeDepart, char *villeArrivee, char *heureDepart, char *heureArrive);
extern void sendDonneesClientBestPrice(int socket_client, char *villeDepart, char *villeArrivee);




#endif				/*  _FCTCLIENT_H_ */
