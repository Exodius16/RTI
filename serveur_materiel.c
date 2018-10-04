#include "serveur_materiel.h"
 
int clients = 0; 

int main()
{	
	int ret = 0;
	
	printf("\n * * * * * * * * * * Serveur materiel - Bienvenue * * * * * * * * * * \n\n");
	
	printf("Création du thread serveur ...");
	
	ret = pthread_create (& th_serveur_materiel, NULL, fn_serveur_materiel, NULL);
	if(!ret)
	{
		printf("\t OK \n");
		pthread_join(th_serveur_materiel, NULL);
	}
	else
	{
		printf("\t Erreur de création du Thread Serveur \n");
	}
	
	
	return 0;
}

void * fn_serveur_materiel()
{
	int ret = 0;
   	//printf("Je suis le Thread serveur de l'application: %ld \n", pthread_self());
   	
   	printf("Création du thread serveur du protocol CIMP ...");
   	
   	ret = pthread_create (&th_serveur_CIMP, NULL, fn_serveur_CIMP, NULL);
	if(!ret)
	{
		printf("\t OK \n");
		pthread_join(th_serveur_CIMP, NULL);
	}
	else
	{
		printf("Erreur de création du Thread Serveur checkin \n");
	}
   
	return 0;
}

void * fn_serveur_CIMP()
{
	int ret = 0, i, j;
	SOCKET csockTemp;
	
	char *temp;
	
	//LoadProperties();
	loadCSV2();
	
	for (i=0; i<25; i++) 
	{
		csock[i] = -1;
	}
   	
   	printf("Création des thread clients ...");
   	
	for(int i = 0; i < nbClients; i++)
	{
		ret = pthread_create (& th_clients[i], NULL, fn_client, &i);
		if(!ret)
		{
			printf("\t OK");
		}
		else
		{
			printf("Erreur de création du Thread Client %d \n", i);
		}
	}
	printf("\n\n");
	
	sock = SocketServeur(port);
	
	clients = 0;
	while(1)
	{
		csockTemp = Accept(sock);
		for (j=0; j<25 && csock[j] != -1; j++);
		
		if (j >= 25)
		{
			printf("Plus de connexion disponible;\n");
		}
		else
		{
			printf("\nConnexion d'un client.\n");
					
			pthread_mutex_lock(&mutexClients);////LOCK
			csock[j] = csockTemp;
			clients++;
			pthread_cond_signal(&conditionClients);		
			pthread_mutex_unlock(&mutexClients);////UNLOCK
		}
		sleep(1);  
	}
	
	closesocket(sock);
   	
	return 0;
}

void * fn_client(void *client)
{
	int test;
	char user[17], password[33];
	int i, leave = 0, stop;
	SOCKET csockTest;
	
	char buffer[256];
	char type[16];
	char message[240];
	
	while(1)
	{  		
		// 1. Attente d'un client à traiter
		pthread_mutex_lock(&mutexClients);////LOCK
		
		pthread_cond_wait(&conditionClients, &mutexClients);//bloque jusqu'as ce que condition est envoyé ET que mutex est dispo
		
		csockTest = csock[clients-1];
		csock[clients-1] = -1;
		clients--;
		printf("Socket %d connectée.\n\n", csockTest);
		
		pthread_mutex_unlock(&mutexClients);////LOCK
		
		stop = 0;
		while(!stop)
	 	{	
			test = Receive(csockTest, buffer);
			printf("Message reçus: %s \n", buffer);
		
			leave = 0;
			
			strcpy(type, strtok(buffer, ";"));
			strcpy(message, strtok(NULL, "\0"));
		
			if(strcmp(type, "LOGIN") == 0)
			{	
				strcpy(user, strtok(message, ";"));
				strcpy(password, strtok(NULL, ";"));
			
				printf("utilisateur: %s | ", user);
				printf("Mot de passe: %s \n", password);
			
				for(i=0; i<50 && leave==0; i++)
				{
					if((strcmp(users[i].user, user) == 0) && (strcmp(users[i].password, password) == 0))
					{
						strcpy(buffer, "ok\0");
						
						printf("Utilisateur trouvé, connexion acceptée \n\n");
			
						leave = 1;
					}
				}
				
				if(!leave)
				{
					strcpy(buffer, "no\0");
					printf("Utilisateur non trouvé, connexion refusée \n\n");
				}
			
				test = Send(csockTest, buffer, sizeof(buffer));
			}
		}
	}
	
	closesocket(csockTest);
	
	return 0;
}

void loadCSV2()
{
	char temp[200];
	FILE *f;
	int i;
	
	
	f=fopen("csv/login.csv","r+b");
	if(!f)
	{
		printf("Fichier login.csv impossible à ouvrir !");
	}


	i = 0;
	while ( fgets( temp, 60, f) != NULL )
	{
		strcpy(users[i].user, strtok(temp,";")); // appel d'initialisation de strtok. Séparateur = ';'
		strcpy(users[i].password, strtok(NULL,";")); // remplace le prochain séparateur trouvé par 0,
		printf("ligne login: %s - %s\n", users[i].user, users[i].password);
		i++;
	}
	
	fclose(f);
}
