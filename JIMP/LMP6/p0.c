    #include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    #define BUFSIZE 8192
    #define MAXLINES 100000
     
     int main( int argc, char **argv ) {
        	int ile_linii;
        	char buf[BUFSIZE], *kopia[MAXLINES];
        	int slowa[100000];
        	int opcja = argc > 1 ? atoi(argv[1]) : 1;
        	FILE *in= argc > 2 ? fopen( argv[2], "r" ) : stdin;
     
        	for(int i = 0 ; i < MAXLINES ; i++)
        		slowa[i] = 0;
     
        	if(opcja > 2 || opcja < 1) {
        		fprintf(stderr, "%d: zła opcja", atoi(argv[1]));
        		return EXIT_FAILURE;
        	}
        	for(int i = 3 ; i < argc ; i++){
        	if( argv[i] == NULL) {
        		fprintf( stderr, "%s: błąd: proszę podac napis do wyszukiwania\n", argv[i] );
        		return EXIT_FAILURE;
        	}
        	}
     
        	if( in == NULL ) {
        		fprintf( stderr, "%s: błąd: nie mogę czytać pliku %s\n", argv[0], argv[2] );
        		return EXIT_FAILURE;
        	}
     
     
    ile_linii = 0;
    while( fgets( buf, BUFSIZE, in) != NULL)
    {
    	if(ile_linii < MAXLINES)
    	{
    		if((kopia[ile_linii] = malloc((strlen(buf)+1) * sizeof(char))) == NULL)
    		{
    			fprintf(stderr, "%s: blad: zbyt wiele danych\n", argv[0]);
    			return EXIT_FAILURE;
    		}
    		strcpy(kopia[ile_linii], buf);
    		ile_linii++;
    	}
    	else
    	{
    		fprintf(stderr, "%s: za duzo linii\n", argv[0]);
    		return EXIT_FAILURE;
    	}
    }
     
    int or = 0;
    int pom = 0;
    int pom2 = 0;
    int tab[9999];
    for(int i = 0 ; i < 9999 ; i++)
	    tab[i]=0;
    switch(opcja)
    {
    	case 1:
		if(argc>3){
    		for(int j = 0 ; j < ile_linii ; j++){
			for(int i = 3; i < argc ; i++){
				if( strstr( kopia[j], argv[i] ) == NULL ){
		        		pom = 1;
					break;
  			}
		}
		if(pom==0){
			printf("%i. %s",j , kopia[j]);
			pom2++;
		}
		pom = 0;
		}
		if(pom2 == 0) 
			printf("Podane słowa nie występują w pliku\n");
     		}else
			printf("Nie podano słów do wyszukania\n");	
	break; 
    	case 2:
    	for(int i = 0; i < ile_linii; i++)
    	{
    		for(int j = 3; j < argc; j++)
    		{
    			if(strstr(kopia[i], argv[j]) != NULL)
    			{	
				if(tab[i]==0)
					printf("%i. %s", i, kopia[i]);
				tab[i]=1;
    				or = 1;
      			}
    		}
    	}
     
    	if(or != 1)
    	{
    		printf("Brak szukanych wyrazow\n");
    		return EXIT_FAILURE;
    	}
     
    	break;
    }
     
    return EXIT_SUCCESS;
    }
