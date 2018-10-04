#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct login
{
	char *user;
	char *password;
	struct login* psuivant;
} LOGIN;

void loadCSV(char* fichier, char* sep, LOGIN* dest);

#endif
