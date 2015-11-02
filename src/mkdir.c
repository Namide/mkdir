#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
//#include <conio.h>

void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int readO(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
		else
		{
			clearBuffer();
		}
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
		clearBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

int createDir(char* dir) {
	
	struct stat file_stat;
	if (stat(dir, &file_stat) < 0 ) {

		#if defined(_WIN32)
			mkdir(dir);
		#else 
			mkdir(dir, 0777); // notice that 777 is different than 0777
		#endif

		printf( "ok %s\n", dir );
		return 1;
	} else {
		printf( "!! %s existe deja !\n", dir );
	}
	return 0;
}

int charHas(char c)
{
	/*if ( isspace(c) ) {
		
		printf("Les espaces sont proscrits des noms de dossier\n");
		return 0;
	}*/
	
	char a[1] = "a";
	char z[1] = "z";
	char A[1] = "A";
	char Z[1] = "Z";
	char t[1] = "-";
	char u[1] = "_";
	char b[1] = "0";
	char n[1] = "9";
	
	//printf("char: %c\n", c);
	if ( 	(c >= *a && c <= *z) ||
			(c >= *A && c <= *Z) ||
			(c >= *b && c <= *n) ||
			c == *t || c == *u )
	{
		return 1;
	}
	
	
	/*printf("Test : \"%c\"\n", *a);
	printf("=== : \"%i\"\n", (c == *a));*/
	
	printf("Caractere special inapropriee : \"%c\"\n", c);
	return 0;	
}

int stringHasSpecial(char* s)
{
	/*
	while (*s)
	{
		if ( charHas(*s) == 0 ) {
			return 1;
		}
		s++;
	}
	*/
	
	
	char c;
	int i = 0;
	while (s[i])
	{
		c=s[i];
		if (charHas(c) < 1) {
			return 1;
		}
		i++;
	}
	
	
	
	/*for(i = 0; i<l; ++i) {
		if ( charHas(s[i]) > 0 ) {
			return 1;
		}
	}*/
	return 0;
}

char* createSubDir(char* parent, char* pre, char* name, char* result)
{
	strcpy(result, parent);
	strcat(result, pre);
	strcat(result, name);
	
	createDir(result);
	
	return result;
}

void createSubDirs(char* path, char* dir, char* num, char* name)
{
	#if defined(_WIN32)
		char sep[] = "\\";
	#else 
		char sep[] = "/";
	#endif
	
	char pre[256];
	strcpy(pre, sep); strcat(pre, num); strcat(pre, "_");
	
	/*char d1[256];
	strcpy(d1, dir); strcat(d1, pre); strcat(d1, "base");
	createDir(d1);*/
	char d1[256] = "";
	createSubDir(dir, pre, "base", d1);
	
		char d2[256] = "";
		createSubDir(d1, pre, "crea", d2);
		createSubDir(d1, pre, "elts", d2);
		createSubDir(d1, pre, "contenus", d2);
	
	createSubDir(dir, pre, "print", d1);
	
		createSubDir(d1, pre, "brochure", d2);
			
			char d3[256] = "";
			createSubDir(d2, pre, "brochure-crea", d3);
			createSubDir(d2, pre, "brochure-elts", d3);
			createSubDir(d2, pre, "brochure-maq", d3);
		
				char d4[256] = "";
				createSubDir(d3, sep, "version-en-cours", d4);
				createSubDir(d3, sep, "versions-precedentes", d4);
				createSubDir(d3, sep, "icono-bruts", d4);
				createSubDir(d3, sep, "icono-retouche", d4);
				createSubDir(d3, sep, "liaison", d4);
				createSubDir(d3, sep, "livrables", d4);
			
			createSubDir(d2, pre, "affiche", d3);
			
				createSubDir(d3, pre, "affiche-crea", d4);
				createSubDir(d3, pre, "affiche-elts", d4);
				createSubDir(d3, pre, "maquette", d4);
				
	createSubDir(dir, pre, "web", d1);
	createSubDir(dir, pre, "motion", d1);
	createSubDir(dir, pre, "autres", d1);
	createSubDir(dir, pre, "pour-archivage", d1);
}

int main (void)
{
	#if defined(_WIN32)
		char path[] = "T:\\";
	#else 
		char path[] = "/Volumes/10_Transferts/";
	#endif
	
	
	char dirNum[256];
	char dirName[256];
	
	
	while(1)
	{
		printf("\nENTREZ LE NUMERO DE DOSSIER\nPar exemple 13665 ou RH8564\n\n");
		//scanf("%s", dirNum); 
		readO(dirNum, 256);
		printf("\n");
		//printf( "Your name is: %s -- and your age is: %d\n", name, val );
		
		
		printf("ENTREZ LE NOM DE DOSSIER\nPar exemple CATCH-A-KING_site-2015\n\n");
		//scanf("%s", dirName); 
		readO(dirName, 256);
		printf("\n");
		
		char name[256] = "";
		strcat(name, dirNum);
		strcat(name, "_");
		strcat(name, dirName);
		
		char dir[256] = "";
		strcat(dir, path);
		strcat(dir, name);
		
		if ( stringHasSpecial(name) == 0 )
		{
			printf("\nCREATION DES REPERTOIRES:\n");
			if ( createDir(dir) > 0 ) {
				createSubDirs(path, dir, dirNum, dirName);
			}
			
			printf("\nTERMINE\n");
			//scanf("%s", dirName); 
			
			
			
			#if defined(_WIN32)
				char sys[256] = "explorer ";
			#else 
				char sys[256] = "open ";
			#endif
			
			strcat(sys, dir);
			system(sys);

			#if defined(_WIN32)
				return 0;
			#else 
				//system("osascript -e 'tell application \"Terminal\" to quit'");
				system("killall Terminal");
				return 0;
			#endif
		}
		else
		{
			printf("\nVOTRE NOM DE DOSSIER CONTIENT DES CARACTERES NON AUTORISES !\n");
			printf("Veuillez recommencer\n");
		}
		
		
		//I( "%s", dirName ); 
		//printf("(appuyez sur une touche pour quitter)");
		//getch();
		
	}
	
	/*char[256] sys = "explorer ";
	strcat(sys, dir);
	system(sys);*/
	
	return 0;
}

/*
	#ifdef _WIN32
	   //define something for Windows (32-bit and 64-bit, this part is common)
	   char path[] = "T:\\test-c\\";
	   char sep[] = "\";
	   #ifdef _WIN64
		  //define something for Windows (64-bit only)
	   #endif
	#elif __APPLE__
		char path[] = "/Volumes/10_Transferts/test-c/";
		char sep[] = "/";
	   #include "TargetConditionals.h"
		#if TARGET_IPHONE_SIMULATOR
			 // iOS Simulator
		#elif TARGET_OS_IPHONE
			// iOS device
		#elif TARGET_OS_MAC
			// Other kinds of Mac OS
		#else
		#   error "Unknown Apple platform"
		#endif
	#elif __linux__
		// linux
	#elif __unix__ // all unices not caught above
		// Unix
	#elif defined(_POSIX_VERSION)
		// POSIX
	#else
	#   error "Un
*/