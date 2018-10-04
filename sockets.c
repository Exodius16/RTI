#include "sockets.h"

SOCKET SocketServeur(int port) // utilisation des méthides "socket()" et "bind()"
{
	SOCKET sock;
	SOCKADDR_IN sin = { 0 };

	printf("Création socket serveur ...");
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    exit(1);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if(bind (sock, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
	    perror("bind()");
	    exit(2);
	}
	
	printf("\t OK \n");
		
	return sock;
}

SOCKET Accept(SOCKET sock) // utilisation des méthodes "listen()" et "accept"
{
	SOCKET csock;
	SOCKADDR_IN csin = { 0 };
	
	if(listen(sock, 5) == SOCKET_ERROR)
	{
	    perror("listen()");
	    exit(2);
	}

	csock = accept(sock, (SOCKADDR *)&csin, &csin);
	if(csock == INVALID_SOCKET)
	{
	    perror("accept()");
	    exit(3);
	}
	else
		printf("Connexion des sockets ... \tOK \n\n");
		
	return csock;
}

SOCKET SocketClient(char *ip, int port) // utilisation des méthides "socket()" et "commit()"
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };
	
	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    exit(1);
	}

	const char *hostname = ip;
	struct hostent *hostinfo = NULL;

	hostinfo = gethostbyname(hostname);
	if (hostinfo == NULL)
	{
	    	fprintf (stderr, "Unknown host %s.\n", hostname);
	    	exit(EXIT_FAILURE);
	}
	
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
	    	perror("connect()");
	    	exit(2);
	}
	
	return sock;
}

/*int Connect(SOCKET sock, SOCKADDR_IN sin)
{
	sin.sin_addr = *(IN_ADDR *);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
	    	perror("connect()");
	    	exit(2);
	}
	
	return 0;
}*/

int Send(SOCKET sock, char *data, int nbrBytes)
{
	if((nbrBytes = send(sock, data, nbrBytes, 0)) < 0)
	{
	    perror("send()");
	    return -1;
	}
	
	return nbrBytes;
}

int Receive(SOCKET sock, char *data) // renvoi le nombre de bytes reçus, vérifier qu'on a récupéré tout les paquets
{
	int nbrBytes = 0;
	
	//do
	//{
		if((nbrBytes = recv(sock, data, sizeof(*data), 0)) < 0)
		{
		    perror("recv()");
		    return -1;
		}
	//} while (nbrBytes > 0 && nbrBytes < sizeof(data) - 1 );
		
	return nbrBytes;
}
