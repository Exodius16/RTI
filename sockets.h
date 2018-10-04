#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

// Structures des sockets utilisées

//	struct sockaddr_in {
//	   uint8_t         sin_len;       /* longueur totale      */
//	   sa_family_t     sin_family;    /* famille : AF_INET     */
//	   in_port_t       sin_port;      /* le numéro de port    */
//	   struct in_addr  sin_addr;      /* l'adresse internet   */
//	   unsigned char   sin_zero[8];   /* un champ de 8 zéros  */
//	};

//	struct sockaddr {
//	   unsigned char   sa_len;         /* longueur totale 		*/
//	   sa_family_t     sa_family;      /* famille d'adresse 	*/
//	   char            sa_data[14];    /* valeur de l'adresse	*/
//	};

//	struct in_addr {
//	  in_addr_t	s_addr;
//	};

//	struct hostent {
//	   char    *h_name;       /* Nom officiel de l'hôte.   */
//	   char   **h_aliases;    /* Liste d'alias.            */
//	   int      h_addrtype;   /* Type d'adresse de l'hôte. */
//	   int      h_length;     /* Longueur de l'adresse.    */
//	   char   **h_addr_list;  /* Liste d'adresses.         */
//	}
//	#define h_addr  h_addr_list[0] /* pour compatibilité.  */
//	};

SOCKET SocketServeur(int port); // utilisation des méthides "socket()" et "bind()"
SOCKET SocketClient(char *ip, int port); // utilisation des méthides "socket()" et "commit()"
SOCKET Accept(SOCKET sock); // utilisation des méthodes "listen()" et "accept"
int Send(SOCKET sock, char *data, int nbrBytes); // Renvoi le nombre de bytes envoyés
int Receive(SOCKET sock, char *data); // renvoi le nombre de bytes reçus, vérifier qu'on a récupéré tout les paquets

#endif
