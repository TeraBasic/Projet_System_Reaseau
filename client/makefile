SRC_CLIENT = sources/client.c sources/fctClient.c

OBJ_CLIENT = sources/client.o sources/fctClient.o
 
INCL_CLIENT = -Iheaders/

CC = gcc
EXE_CLIENT = bin/client


c: $(EXE_CLIENT)

$(EXE_CLIENT):  $(OBJ_CLIENT)        
	gcc $(OBJ_CLIENT) -o $(EXE_CLIENT)

$(EXE_SERVER):	$(OBJ_SERVER)        
	gcc -o $(EXE_SERVER) $(OBJ_SERVER) 

sources/client.o: sources/client.c
	gcc $(INCL_CLIENT) -c sources/client.c -o sources/client.o

sources/fctClient.o: sources/fctClient.c 
	gcc $(INCL_CLIENT) -c sources/fctClient.c -o sources/fctClient.o

clean:
	@echo "Supression des objets"
	rm $(OBJ_CLIENT)

run: 
	./$(EXE_CLIENT)

