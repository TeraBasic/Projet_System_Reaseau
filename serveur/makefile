#Macro dependances/paths 

SRC_SERVER = serveur.c fctServeur.c

OBJ_SERVER = serveur.o fctServeur.o
 
# Macros Execution
CC = gcc
EXE_SERVER = serveur


s: $(EXE_SERVER)


$(EXE_SERVER):  $(OBJ_SERVER)        
	gcc -o $(EXE_SERVER) $(OBJ_SERVER) 

fctServeur.o: fctServeur.c 
	gcc -I ./lib -c fctServeur.c -Wall

serveur.o: serveur.c
	gcc -I ./lib -c serveur.c -Wall

clean:
	@echo "Supression des objets"
	rm $(OBJ_SERVER)

run: 
	./$(EXE_SERVER)


