#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

typedef struct auta{		//definovanie struktury s jednotlivymi prvkami
	char kategoria[53];
	char znacka[53];
	char predajca[103];
	int cena;
	int rok_vyroby;
	char stav_vozidla[203];
	struct auta *dalsi;  
} auta;

auta *nacitanie(FILE**vstup, auta *prvy, int *pocet_zaznamov) 
{	
	int znak, pocet=1;
	auta *aktualny;
	aktualny=(auta*)malloc(sizeof(auta));
	prvy=aktualny;
	
	*vstup=fopen("auta.txt", "r");
   	  if(*vstup==NULL)
	  {
		printf("Zaznamy neboli nacitane \n");
	  }
	
	  else
	  {
	 	 do
	     {   	
			if(znak=getc(*vstup)=='$')
			  znak=getc(*vstup);
			
	    	fgets(aktualny->kategoria, 53, *vstup);
	    	fgets(aktualny->znacka, 53, *vstup);
	    	fgets(aktualny->predajca, 103, *vstup);
	    	fscanf(*vstup, "%d\n", &aktualny->cena);
	    	fscanf(*vstup, "%d\n", &aktualny->rok_vyroby);
	    	fgets(aktualny->stav_vozidla, 203, *vstup);
	    	
	    	aktualny->dalsi=(auta*)malloc(sizeof(auta));
	    	aktualny=aktualny->dalsi;
	    	aktualny->dalsi=NULL;
	    	pocet++;  //pocitanie jednotlivych struktur		
	     }
	     while(!feof(*vstup));
	       fclose(*vstup);
	    
	     aktualny=NULL;
	     *pocet_zaznamov=pocet-1; 
       	printf("Nacitalo sa %d zaznamov \n", *pocet_zaznamov);
	  }
  return prvy; 
}

void vypisanie(auta *prvy) 
{
	int pocet=1;
	auta *aktualny;
	auta *dalsi;
	aktualny=prvy;
	
	  while(aktualny->dalsi!=NULL)
	    { 
			printf("%d. \n", pocet);
	    	printf("kategoria: %s", aktualny->kategoria);
	    	printf("znacka: %s", aktualny->znacka);
	    	printf("predajca: %s", aktualny->predajca);
	   		printf("cena: %d\n", aktualny->cena);
	   		printf("rok_vyroby: %d\n", aktualny->rok_vyroby);
	   		printf("stav_vozidla: %s", aktualny->stav_vozidla); 
	   		
	    	aktualny=aktualny->dalsi;
	    	pocet++; //pocitanie struktur
	    }
	  putchar('\n');
}

auta *pridanie(auta *prvy, int *pocet_zaznamov)
{
	int pozicia; 
	auta *aktualny;
	auta *pomocny;
	scanf("%d", &pozicia);

	if(pozicia==1)
	{
		pomocny=prvy;
		aktualny=(auta*)malloc(sizeof(auta));
		prvy=aktualny;
		aktualny->dalsi=pomocny;
		
		gets(aktualny->kategoria);
		gets(aktualny->kategoria);
	    gets(aktualny->znacka);
	    aktualny->znacka[strlen(aktualny->znacka)]='\n';
	    gets(aktualny->predajca);
	    scanf("%d\n", &aktualny->cena);
	    scanf("%d\n", &aktualny->rok_vyroby);
	    gets(aktualny->stav_vozidla);
	    //odriadkovavanie (donutene)
	    aktualny->kategoria[strlen(aktualny->kategoria)]='\n';
	  	aktualny->predajca[strlen(aktualny->predajca)]='\n';
	    aktualny->stav_vozidla[strlen(aktualny->stav_vozidla)]='\n';
	    
	    return prvy;
	}

	if((pozicia>1) && (pozicia<=(*pocet_zaznamov)))
	{
		auta* referencia=prvy; //referencia na zaciatok
		int ratanie=1;
		while(ratanie<pozicia-1)	//prejdenie zoznamu po n
		{
		  prvy=prvy->dalsi;
		  ratanie++;
		}
		pomocny=prvy->dalsi;
		aktualny=(auta*)malloc(sizeof(auta));
		prvy->dalsi=aktualny;
		aktualny->dalsi=pomocny;
		
		gets(aktualny->kategoria);
		gets(aktualny->kategoria);
	    gets(aktualny->znacka);
	    aktualny->znacka[strlen(aktualny->znacka)]='\n';
	    gets(aktualny->predajca);
	    scanf("%d\n", &aktualny->cena);
	    scanf("%d\n", &aktualny->rok_vyroby);
	    gets(aktualny->stav_vozidla);
	    
	    aktualny->kategoria[strlen(aktualny->kategoria)]='\n';
	  	aktualny->predajca[strlen(aktualny->predajca)]='\n';
	    aktualny->stav_vozidla[strlen(aktualny->stav_vozidla)] = '\n';
	    return referencia;
	}
	
	else //ak je n vyzsie ako pocet zaznamov - pridavanie na koniec 
	{
		auta* referencia=prvy;
		int ratanie=1;
		while(prvy->dalsi!=NULL)	//prejdenie az na koniec zoznamu
		{
		  prvy=prvy->dalsi;
		  ratanie++;
		}
		aktualny=(auta*)malloc(sizeof(auta));
		pomocny->dalsi=prvy->dalsi;
		prvy->dalsi=pomocny;
		prvy=pomocny;
		prvy->dalsi=NULL;
			
		gets(aktualny->kategoria);
		gets(aktualny->kategoria);
	    gets(aktualny->znacka);
	    aktualny->znacka[strlen(aktualny->znacka)]='\n';
	    gets(aktualny->predajca);
	    scanf("%d\n", &aktualny->cena);
		scanf("%d\n", &aktualny->rok_vyroby);
	    gets(aktualny->stav_vozidla);
	    
	    aktualny->kategoria[strlen(aktualny->kategoria)]='\n';
	    aktualny->predajca[strlen(aktualny->predajca)]='\n';
	    aktualny->stav_vozidla[strlen(aktualny->stav_vozidla)]='\n';
		
	  return referencia;
	}		
}

auta *zmazanie(auta *prvy, int *pocet_zaznamov)
{
	int ratanie=0;
	char znaky[53];
	scanf("%s", &znaky);
	strlwr(znaky); //zmeni velke pismena na male
	auta *aktualny, *pomocny; 
	pomocny=prvy;
	aktualny=prvy;
	
	while(1)
	{
	  if(aktualny==NULL)	
	  break; 
		if(strstr(strlwr(aktualny->znacka), znaky)) //porovnavanie znakov
		{
		  if(prvy==aktualny)
		  {
			prvy=prvy->dalsi;
		  }
			
		  else
		  {
			while(pomocny->dalsi!=aktualny)
			  pomocny=pomocny->dalsi;
			pomocny->dalsi=aktualny->dalsi;
		  }
		  (*pocet_zaznamov)--;  //odratavanie zo zoznamu/vypisu
		  ratanie++; //pocitanie vymazanych prvkov
		}
	  aktualny=aktualny->dalsi;
	}
  printf("Vymazalo sa %d zaznamov\n", ratanie);
  return prvy;
}

void vypis_podla_ceny(auta *prvy) 
{
	int cena, pocet=1;
	auta *aktualny;
	auta *dalsi;
	aktualny=prvy;
	scanf("%d", &cena);

	while(aktualny->dalsi!=NULL)
	{ 
	  if(aktualny->cena<=cena)		//podmienka ceny
	  {
		printf("%d. \n", pocet);
	    printf("kategoria: %s", aktualny->kategoria);
	    printf("znacka: %s", aktualny->znacka);
	    printf("predajca: %s", aktualny->predajca);
	   	printf("cena: %d\n", aktualny->cena);
	   	printf("rok_vyroby: %d\n", aktualny->rok_vyroby);
	   	printf("stav_vozidla: %s", aktualny->stav_vozidla); 
	   	pocet++;
	  }
	  aktualny=aktualny->dalsi;
    }
	if(pocet==1) 
	  {
		printf("V ponuke su len auta s vyssou cenou\n");
	  }
}

int main()
{
	FILE *vstup;
	auta *prvy;
	auta *aktualny;
	char znak;
	int freigeben, pocet_zaznamov;
	
	do 
	{
		switch(znak=getchar())			
		{
			case 'n': prvy=nacitanie(&vstup, prvy, &pocet_zaznamov); break;
			case 'v': vypisanie(prvy); break;
			case 'p': prvy=pridanie(prvy, &pocet_zaznamov); break;
			case 'z': prvy=zmazanie(prvy,&pocet_zaznamov); break;
			case 'h': vypis_podla_ceny(prvy); break;
		}
	}
	while(znak!='k');
}
