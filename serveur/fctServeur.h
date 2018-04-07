#ifndef _FCTSERVEUR_H_
#define _FCTSERVEUR_H_
#define MESSAGE 100
#define RES 1000

typedef struct trainInfo _tr;

struct trainInfo
{
  char numero[7];
  char depart[20];
  char destination[20];
  char tempsDepart[20];
  char tempsDestination[20];
  float prix;
  char reduc[20];
} trainInfo;

extern void recup_donne(struct trainInfo *textarea);
extern void promoAction(struct trainInfo *t);
extern int getTaille(struct trainInfo *tab);
extern struct trainInfo searchByPrice(struct trainInfo *textarea,float prix);
extern struct trainInfo best_price(struct trainInfo *textarea);
extern void search(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive);
extern void searchByTime(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive, char *time);
extern void searchByTimeInterval(struct trainInfo *textarea, struct trainInfo textarea_copy[20], char *depart, char *arrive, char *time1, char *time2);
extern void receptionDemande(int socket_service);
extern void finfils(int sig);
extern void fctServeur(int socket_service);





#endif
