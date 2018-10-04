#include "csv.h"

void loadCSV(char* fichier, char* sep, LOGIN* dest)
{
	char chaine[1024];
	char* token;
	FILE* fp = NULL;
	LOGIN* log;
	
	fp = fopen(fichier, "r+b");
	if(!fp)
	{
		printf("Problème d'ouverture du fichier %s !", fichier);
		return;
	}
	
	dest = (LOGIN*)malloc(sizeof(LOGIN));
	log = dest;
	
	while(fgets(chaine, 1024, fp))
	{
		if((token = strtok(chaine, ";")) != NULL)
		{
			log->user = token;
			printf("%s\n", log->user);
		}
		
		while((token = strtok(NULL, ";")) != NULL)
		{
			log->password = token;
			printf("%s\n", log->password);
		}
		
		log = log->psuivant;
		log = (LOGIN*)malloc(sizeof(LOGIN));
	}
	
	free(log);
	fclose(fp);
}
