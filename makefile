.SILENT:

all:					serveur_materiel

serveur_materiel:		serveur_materiel.c csv.o sockets.o
					#echo creation serveur
					gcc serveur_materiel.c -g csv.o sockets.o -o serveur_materiel -Wall -lpthread
					
#client_checkin:		client_checkin.c sockets.o
#					#echo creation client
#					gcc client_checkin.c -g sockets.o -o client_checkin -Wall -lpthread
					
sockets.o:			librairies/sockets/sockets.c librairies/sockets/sockets.h
					#echo creation sockets.o
					gcc librairies/sockets/sockets.c -c -Wall
					
csv.o:				librairies/csv/csv.c librairies/csv/csv.h
					#echo creation sockets.o
					gcc librairies/csv/csv.c -c -Wall
