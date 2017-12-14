#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

typedef struct autos{		//definovanie struktury s jednotlivymi prvkami
	char kategoria[53];
	char znacka[53];
	char predajca[103];
	int cena;
	int rok_vyroby;
	char stav_vozidla[203];
	struct autos *naechster;  
} autos;

autos *funkcia_n(FILE**datei, autos *anfang, int freigeben, int *t) 
{	
	int c, anzahl=1;
	autos *akt;
	akt = (autos*)malloc(sizeof(autos));
	anfang = akt;
	
	*datei=fopen("auta.txt", "r");
	if(*datei==NULL)
	{
		printf("Zaznamy neboli nacitane \n");
	}
	
	else
	{
	//nacitavanie so suboru a ukladanie do struktur
	  do
	    {   	
			if(c=getc(*datei)=='$')
			c=getc(*datei);
	    	fgets(akt->kategoria, 53, *datei);
	    	fgets(akt->znacka, 53, *datei);
	    	fgets(akt->predajca, 103, *datei);
	    	fscanf(*datei, "%d\n", &akt->cena);
	    	fscanf(*datei, "%d\n", &akt->rok_vyroby);
	    	fgets(akt->stav_vozidla, 203, *datei);
	    	
	    	akt->naechster=(autos*)malloc(sizeof(autos));
	    	akt = akt->naechster;
	    	akt->naechster=NULL;
	    	anzahl++;  //pocitanie jednotlivych struktur
	    		
	    }
	    while(!feof(*datei));
	    fclose(*datei);
	    
	    akt = NULL;
	    
	    *t=anzahl-1; 
	    
	printf("Nacitalo sa %d zaznamov \n", *t);
	}
	return anfang; 
}

void funkcia_v(autos *anfang) 
{
	int anzahl=1;
	autos *akt;
	autos *naechster;
	akt=anfang;
//vypis vsetkych struktur
	while(akt->naechster != NULL)
	    { 
			printf("%d. \n", anzahl);
	    	printf("kategoria: %s", akt->kategoria);
	    	printf("znacka: %s", akt->znacka);
	    	printf("predajca: %s", akt->predajca);
	   		printf("cena: %d\n", akt->cena);
	   		printf("rok_vyroby: %d\n", akt->rok_vyroby);
	   		printf("stav_vozidla: %s", akt->stav_vozidla); 
	    	
	    	
	    	akt = akt->naechster;
	    	anzahl++; //pocitanie struktur
	    }
	    putchar('\n');
}


autos *funkcia_p(autos *anfang, int *t)
{
	int n; 
	autos *akt;
	autos *neu;
	autos *vor;
	
	scanf("%d", &n);
	//pridanie zaznamu na uplny zaciatok
	if(n==1)
	{
		neu=anfang;
		akt=(autos*)malloc(sizeof(autos));
		anfang=akt;
		akt->naechster=neu;
		
		gets(akt->kategoria);
		gets(akt->kategoria);
	    gets(akt->znacka);
	    akt->znacka[strlen(akt->znacka)] = '\n';
	    gets(akt->predajca);
	    scanf("%d\n", &akt->cena);
	    scanf("%d\n", &akt->rok_vyroby);
	    gets(akt->stav_vozidla);
	    //odriadkovavanie (donutene)
	    akt->kategoria[strlen(akt->kategoria)] = '\n';
	  	akt->predajca[strlen(akt->predajca)] = '\n';
	    akt->stav_vozidla[strlen(akt->stav_vozidla)] = '\n';
	    
	    return anfang;
	}
	//pridanie zaznamu na nacitanu poziciu
	if((n>1) && (n<=(*t)))
	{
		autos* ref = anfang; //referencia na zaciatok
		int iterator = 1;
		
		while(iterator<n-1)	//prejdenie zoznamu po n
		{
			anfang = anfang->naechster;
			iterator++;
		}
		neu=anfang->naechster;
		akt=(autos*)malloc(sizeof(autos));
		anfang->naechster = akt;
		akt->naechster=neu;
		
		gets(akt->kategoria);
		gets(akt->kategoria);
	    gets(akt->znacka);
	    gets(akt->predajca);
	    scanf("%d\n", &akt->cena);
	    scanf("%d\n", &akt->rok_vyroby);
	    gets(akt->stav_vozidla);
	    
	    akt->kategoria[strlen(akt->kategoria)] = '\n';
	    akt->znacka[strlen(akt->znacka)] = '\n';
	  	akt->predajca[strlen(akt->predajca)] = '\n';
	    akt->stav_vozidla[strlen(akt->stav_vozidla)] = '\n';
	    return ref;
	}
	
	else //ak je n vyzsie ako pocet zaznamov - pridavanie na koniec 
	{
		autos* ref = anfang;
		int iterator = 1;
		
		while(anfang->naechster!=NULL)	//prejdenie az na koniec zoznamu
		{
			anfang = anfang->naechster;
			iterator++;
		}
		
		akt=(autos*)malloc(sizeof(autos));
		neu->naechster=anfang->naechster;
		anfang->naechster = neu;
		anfang=neu;
		anfang->naechster=NULL;
			
		gets(akt->kategoria);
		gets(akt->kategoria);
	    gets(akt->znacka);
	    akt->znacka[strlen(akt->znacka)] = '\n';
	    gets(akt->predajca);
	    scanf("%d\n", &akt->cena);
		scanf("%d\n", &akt->rok_vyroby);
	    gets(akt->stav_vozidla);
	    
	    akt->kategoria[strlen(akt->kategoria)] = '\n';
	    akt->predajca[strlen(akt->predajca)] = '\n';
	    akt->stav_vozidla[strlen(akt->stav_vozidla)] = '\n';
		
	    return ref;
	}		
}

autos *funkcia_z(autos *anfang, int *t)
{
	int anzahl=0;
	char zeichen[53];
	scanf("%s", &zeichen);
	strlwr(zeichen); //zmeni velke pismena na male
	
	autos *akt, *fall, *hilf;
	fall= NULL;
	hilf=anfang;
	akt=anfang;
	
	while(1)
	{
		if(akt->naechster==NULL)	
		break; 
		
		if(strstr(strlwr(akt->znacka), zeichen)) //porovnavanie znakov
		{
			if(anfang==akt)
			{
				anfang=anfang->naechster;
			}
			
			else
			{
				while(hilf->naechster!=akt)
				hilf=hilf->naechster;
			hilf->naechster = akt->naechster;
			}
			(*t)--;  //odratavanie zo zoznamu/vypisu
			anzahl++; //pocitanie vymazanych prvkov
		}
		akt=akt->naechster;
	}

	printf("Vymazalo sa %d zaznamov\n", anzahl);
	return anfang;
}

void funkcia_h(autos *anfang) 
{
	int preis, anzahl=1;
	autos *akt;
	autos *naechster;
	akt=anfang;
	
	scanf("%d", &preis);

	while(akt->naechster != NULL)
	    { 
			if(akt->cena <= preis)		//podmienka ceny
			{
			printf("%d. \n", anzahl);
	    	printf("kategoria: %s", akt->kategoria);
	    	printf("znacka: %s", akt->znacka);
	    	printf("predajca: %s", akt->predajca);
	   		printf("cena: %d\n", akt->cena);
	   		printf("rok_vyroby: %d\n", akt->rok_vyroby);
	   		printf("stav_vozidla: %s", akt->stav_vozidla); 
	   		anzahl++;
	    	}
	    	
	    	akt = akt->naechster;
	    }
	    
	    	if(anzahl==1) 
		{
			printf("V ponuke su len auta s vyssou cenou\n");
		}

}

int main()
{
	FILE *datei;
	autos *anfang;
	autos *akt;
	char a;
	int freigeben, t;
	
	do {
		switch(a=getchar())			
		{
			case 'n': anfang = funkcia_n(&datei, anfang, freigeben, &t); freigeben=1; break;
			case 'v': funkcia_v(anfang); break;
			case 'p': anfang = funkcia_p(anfang, &t); break;
			case 'z': anfang = funkcia_z(anfang,&t); break;
			case 'h': funkcia_h(anfang); break;
		}
	}
	while(a != 'k');
}
