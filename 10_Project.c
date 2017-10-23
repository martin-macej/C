#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznamy{
	char signatura[12];
	char ISBN[15];
	char nazov_knihy[102];
	char autori[102];
	int datum_vypozicky;
	int cislo_preukazu;
	struct zaznamy *dalsi;
}ZAZNAMY;

void K(ZAZNAMY **p_prvy, ZAZNAMY **p_konecny){
	ZAZNAMY *p_pomocny;
	if((*p_prvy)!=NULL){
		while  ((*p_prvy) != NULL) {
    	p_pomocny = *p_prvy;
    	(*p_prvy) = (*p_prvy)->dalsi;
    	free((void*)p_pomocny);
    	*p_konecny = *p_prvy;
		}
	}
}

void N(ZAZNAMY **p_prvy, ZAZNAMY **p_konecny){
	FILE *f;
	ZAZNAMY *p_aktualny;
	char pomoc[3], c;
	int pocet=0;
	K(p_prvy, p_konecny);
	if((f=fopen("kniznica.txt", "r"))==NULL)printf("Zaznamy neboli nacitane\n");
	else {
		fgets(pomoc, 4, f);
		fscanf(f, "%c", &c);
		if(strcmp(pomoc, "***")==0){
			*p_prvy = (ZAZNAMY *) malloc(sizeof(ZAZNAMY));
			do{fgets((*p_prvy)->signatura, 12, f);}while(strlen((*p_prvy)->signatura) == 1);
			do{fgets((*p_prvy)->ISBN, 15, f);}while(strlen((*p_prvy)->ISBN) == 1);
			do{fgets((*p_prvy)->nazov_knihy, 102, f);}while(strlen((*p_prvy)->nazov_knihy) == 1);
			do{fgets((*p_prvy)->autori, 102, f);}while(strlen((*p_prvy)->autori) == 1);
			fscanf(f, "%d", &(*p_prvy)->datum_vypozicky);
			fscanf(f, "%d", &(*p_prvy)->cislo_preukazu);
			pocet++;
			(*p_prvy)->dalsi = NULL;
			*p_konecny = *p_prvy;
			fscanf(f, "%c", &c);
			do{fgets(pomoc, 4, f);}while(strlen(pomoc) == 1);
			fscanf(f, "%c", &c);
			while(strcmp(pomoc, "***")==0){
				p_aktualny = (ZAZNAMY *) malloc(sizeof(ZAZNAMY));
				do{fgets(p_aktualny->signatura, 12, f);}while(strlen(p_aktualny->signatura) == 1);
				do{fgets(p_aktualny->ISBN, 15, f);}while(strlen(p_aktualny->ISBN) == 1);
				do{fgets(p_aktualny->nazov_knihy, 102, f);}while(strlen(p_aktualny->nazov_knihy) == 1);
				do{fgets(p_aktualny->autori, 102, f);}while(strlen(p_aktualny->autori) == 1);
				fscanf(f, "%d", &p_aktualny->datum_vypozicky);
				fscanf(f, "%d", &p_aktualny->cislo_preukazu);
				pocet++;
				p_aktualny->dalsi = NULL;
				(*p_konecny)->dalsi = p_aktualny;
				*p_konecny = p_aktualny;
				strcat(pomoc, "a");
				fscanf(f, "%c", &c);
				do{fgets(pomoc, 4, f);}while(strlen(pomoc) == 1);
				fscanf(f, "%c", &c);
				}
		}
		if(fclose(f)==EOF)printf("Subor sa nepodarilo zatvorit.\n");
		printf("Nacitalo sa %d zaznamov\n", pocet);
	}
}

void V(ZAZNAMY *p_prvy){
	ZAZNAMY *p_aktualny;
	int i=1;
	p_aktualny = p_prvy;
	while(p_aktualny!=NULL){
		printf("%d.\n",i++);
		printf("signatura: %s",p_aktualny->signatura);
		printf("isbn: %s",p_aktualny->ISBN);
		printf("nazov: %s",p_aktualny->nazov_knihy);
		printf("autori: %s",p_aktualny->autori);
		printf("datum: %d\n",p_aktualny->datum_vypozicky);
		printf("preukaz: %d\n",p_aktualny->cislo_preukazu);
		p_aktualny = p_aktualny->dalsi;
	}
}

void P(ZAZNAMY **p_prvy){
	ZAZNAMY *p_aktualny, *p_pomocny, *p_pomoc1, *p_predchadzajuci;
	int poradie, i=0, zmena=0;
	char enter;
	scanf("%d", &poradie);
	p_aktualny = *p_prvy;
	if(*p_prvy==NULL){
		*p_prvy = (ZAZNAMY *) malloc(sizeof(ZAZNAMY));
		scanf("%c", &enter);
		gets((*p_prvy)->signatura);
		strcat((*p_prvy)->signatura, "\n");
		gets((*p_prvy)->ISBN);
		strcat((*p_prvy)->ISBN, "\n");
		gets((*p_prvy)->nazov_knihy);
		strcat((*p_prvy)->nazov_knihy, "\n");
		gets((*p_prvy)->autori);
		strcat((*p_prvy)->autori, "\n");
		scanf("%d", &(*p_prvy)->datum_vypozicky);
		scanf("%d", &(*p_prvy)->cislo_preukazu);
		(*p_prvy)->dalsi = NULL;
	}
	else {
		while(p_aktualny!=NULL){
			++i;
			if((i==poradie&&poradie==1)||(i+1==poradie&&poradie!=1)){
				p_pomocny = (ZAZNAMY *) malloc(sizeof(ZAZNAMY));
				scanf("%c", &enter);
				gets(p_pomocny->signatura);
				strcat(p_pomocny->signatura, "\n");
				gets(p_pomocny->ISBN);
				strcat(p_pomocny->ISBN, "\n");
				gets(p_pomocny->nazov_knihy);
				strcat(p_pomocny->nazov_knihy, "\n");
				gets(p_pomocny->autori);
				strcat(p_pomocny->autori, "\n");
				scanf("%d", &p_pomocny->datum_vypozicky);
				scanf("%d", &p_pomocny->cislo_preukazu);
				if(poradie==1){
					p_pomocny->dalsi = (*p_prvy)->dalsi;
					p_pomoc1 = p_pomocny;
					p_pomocny = *p_prvy;
					*p_prvy = p_pomoc1;
					(*p_prvy)->dalsi = p_pomocny;
				}
				else {
					p_pomocny->dalsi = p_aktualny->dalsi;
					p_aktualny->dalsi = p_pomocny;
				}
				zmena=1;
			}
			p_predchadzajuci=p_aktualny;
			p_aktualny = p_aktualny->dalsi;
		}
		if(zmena==0){
			p_predchadzajuci->dalsi = (ZAZNAMY *) malloc(sizeof(ZAZNAMY));
			scanf("%c", &enter);
			gets(p_predchadzajuci->dalsi->signatura);
			strcat(p_predchadzajuci->dalsi->signatura, "\n");
			gets(p_predchadzajuci->dalsi->ISBN);
			strcat(p_predchadzajuci->dalsi->ISBN, "\n");
			gets(p_predchadzajuci->dalsi->nazov_knihy);
			strcat(p_predchadzajuci->dalsi->nazov_knihy, "\n");
			gets(p_predchadzajuci->dalsi->autori);
			strcat(p_predchadzajuci->dalsi->autori, "\n");
			scanf("%d", &p_predchadzajuci->dalsi->datum_vypozicky);
			scanf("%d", &p_predchadzajuci->dalsi->cislo_preukazu);
			p_predchadzajuci->dalsi->dalsi = NULL;
		}
	}
}

void Z(ZAZNAMY **p_prvy){
	ZAZNAMY *p_aktualny, *p_predchadzajuci, *p_pomocny;
	char meno[102], meno2[102], c;
	char *pomoc;
	int i=0, pocet=0;
	scanf("%c",&c);
	gets(meno);
	strlwr(meno);
	p_predchadzajuci = *p_prvy;
	p_aktualny = *p_prvy;
	while(p_aktualny!=NULL){
		strcpy(meno2, p_aktualny->autori);
		strlwr(meno2);
		pomoc = strstr(meno2, meno);
		if(pomoc!=NULL){
			if(i==0){
				p_pomocny = *p_prvy;
				*p_prvy = (*p_prvy)->dalsi;
				free((void *)p_pomocny);
				p_predchadzajuci = (*p_prvy);
				p_aktualny = (*p_prvy);
				i--;
			}
			else {
				p_predchadzajuci->dalsi = p_aktualny->dalsi;
				p_pomocny = p_aktualny;
				p_aktualny = p_aktualny->dalsi;
				free((void *)p_pomocny);
			}
			pocet++;
		}
		else {
			p_predchadzajuci = p_aktualny;
			p_aktualny = p_aktualny->dalsi;
		}	
		i++;
	}
	printf("Vymazalo sa %d zaznamov\n", pocet);
}

void H(ZAZNAMY *p_prvy){
	ZAZNAMY *p_aktualny;
	int cislo_preukazu, i=1;
	scanf("%d", &cislo_preukazu);
	p_aktualny = p_prvy;
	while(p_aktualny!=NULL){
		if(p_aktualny->cislo_preukazu==cislo_preukazu){
			printf("%d.\n",i++);
			printf("signatura: %s",p_aktualny->signatura);
			printf("isbn: %s",p_aktualny->ISBN);
			printf("nazov: %s",p_aktualny->nazov_knihy);
			printf("autori: %s",p_aktualny->autori);
			printf("datum: %d\n",p_aktualny->datum_vypozicky);
			printf("preukaz: %d\n",p_aktualny->cislo_preukazu);
		}
		p_aktualny = p_aktualny->dalsi;
	}
	if(i==1)printf("Pre dane cislo preukazu neevidujeme vypozicky\n");
}

void A(ZAZNAMY *p_prvy){
	ZAZNAMY *p_aktualny;
	int rok, i=0;
	scanf("%d", &rok);
	p_aktualny = p_prvy;
	while(p_aktualny!=NULL){
		if(p_aktualny->datum_vypozicky<=rok){
			p_aktualny->datum_vypozicky=p_aktualny->datum_vypozicky+10000;
			i++;
		}
		p_aktualny = p_aktualny->dalsi;
	}
	printf("Aktualizovalo sa %d zaznamov\n",i);
}

int main(){
	char volba;
	ZAZNAMY *p_prvy, *konecny;
	while(1){
		scanf("%c",&volba);
		switch(volba){
			case 'n' : {
				N(&p_prvy, &konecny);
			}break;
			case 'v' : {
				V(p_prvy);
			}break;
			case 'p' : {
				P(&p_prvy);
			}break;
			case 'z' : {
				Z(&p_prvy);
			}break;
			case 'h' : {
				H(p_prvy);
			}break;
			case 'a' : {
				A(p_prvy);
			}break;
			case 'k' : {
				K(&p_prvy, &konecny);
				return 0;
			}break;
		}
	}
	return 0;
}