//Práca s poľom štruktúr. Vytvorte pole záznamov o tovare v potravinách. Jednotlivé záznamy majú obsahovať názov tovaru, výrobcu, množstvo a jednotkovú cenu. Názov tovaru aj výrobca budú uvedené jedným slovom. Množstvo a cena sú desatinné čísla. Zoznam udržiavajte stále usporiadaný podľa názvov tovarov.
//
//Umožnite používateľovi pridať nový tovar a vypísať aktuálny tovar usporiadaný podľa názvu. Zo štandardného vstupu načítajte a spracujte nasledujúce príkazy (príkazy čítajte až do konca vstupu):
//
//vloz nazov vyrobca mnozstvo cena -- Načíta atribúty tovaru a vloží ho do poľa. Ak je pole krátke, treba pole zväčšiť (najlepšie na dvojnásobnú dĺžku). Pri pridávaní záznamu do poľa, je potrebné nájsť miesto, kam sa má nový záznam pridávať. Všetky záznamy, od tejto pozície ďalej, posunúť na pozíciu o jednu vyššie a na voľné miesto zapísať nový záznam.
//vypis -- Vypíše prvky pola podľa ukážky nižšie.
//Pomôcka:
//
//Ukážka vstupu:
//vloz JablkaJonagold AppleVillage 10 0.35
//vloz HruskyCervene NovoFruct 15 0.30
//vypis
//vloz Ananas BonoFruct 30 1.29
//vloz Pomarance VitaC 25 0.69
//vypis
//Výstup pre ukážkový vstup:
//Nazov=HruskyCervene, Vyrobca=NovoFruct, Mnozstvo=15.000000, JednotkovaCena=0.300000
//Nazov=JablkaJonagold, Vyrobca=AppleVillage, Mnozstvo=10.000000, JednotkovaCena=0.350000
//
//Nazov=Ananas, Vyrobca=BonoFruct, Mnozstvo=30.000000, JednotkovaCena=1.290000
//Nazov=HruskyCervene, Vyrobca=NovoFruct, Mnozstvo=15.000000, JednotkovaCena=0.300000
//Nazov=JablkaJonagold, Vyrobca=AppleVillage, Mnozstvo=10.000000, JednotkovaCena=0.350000
//Nazov=Pomarance, Vyrobca=VitaC, Mnozstvo=25.000000, JednotkovaCena=0.690000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tovar{
	char nazov[102];
	char vyrobcu[102];
	double mnozstvo;
	double cena;
	struct tovar *dalsi;
} TOVAR;

int main(){
  TOVAR *p_prvy, *p_posledny, *pomoc1, *pomoc2, *p_help;
  p_prvy=NULL;
  int i,pomocne,a;
  i=0;
  pomocne=0;
  a=0;
  char vyber[6], nazov[102];
  while(1){
  vyber[0]='\0';
  scanf("%s",vyber);
  if(vyber[0]=='\0')return 0;
    if(vyber[0]=='v'&&vyber[1]=='l'&&vyber[2]=='o'&&vyber[3]=='z'){
    	a=0;
    	scanf("%s",nazov);
    	pomoc1=p_prvy;
    	pomoc2=p_prvy;
      	if (p_prvy == NULL) {
	    	p_prvy =(TOVAR *) malloc(sizeof(TOVAR));
			strcpy(p_prvy->nazov,nazov);
          	scanf("%s",(p_prvy->vyrobcu));
          	scanf("%lf",&(p_prvy->mnozstvo));
          	scanf("%lf",&(p_prvy->cena));
	   		(p_prvy)->dalsi = NULL;
	   		p_posledny = p_prvy;
    		i++;
    		pomocne=1;}
	  	else if(strcmp(nazov,p_prvy->nazov)<0){
	  		p_help = (TOVAR *)malloc(sizeof(TOVAR));
	  		strcpy(p_help->nazov,nazov);
          	scanf("%s",(p_help->vyrobcu));
          	scanf("%lf",&(p_help->mnozstvo));
          	scanf("%lf",&(p_help->cena));
          	p_help->dalsi=p_prvy;
          	p_prvy=p_help;
          	pomocne=1;}
	  	while(pomocne==0&&(pomoc2->dalsi != NULL)&&(strcmp(nazov,pomoc2->nazov)>=0)){
	  		if(strcmp(nazov,p_prvy->nazov)==0){
	  			  pomocne=1;
				  break;}
	  		else{pomoc2=pomoc2->dalsi;
	  			if(a==5)pomoc1=pomoc1->dalsi;
	  			a=5;}}
		  if(pomocne==0) {
		   		p_help = (TOVAR *)malloc(sizeof(TOVAR));
				strcpy(p_help->nazov,nazov);
          		scanf("%s",(p_help->vyrobcu));
          		scanf("%lf",&(p_help->mnozstvo));
          		scanf("%lf",&(p_help->cena));
	    		if(pomoc2->dalsi==NULL){
	    			p_help->dalsi = NULL;
	    			(p_posledny)->dalsi = p_help;
	    			(p_posledny) = p_help;}
				else {
					p_help->dalsi=pomoc1->dalsi;
					pomoc1->dalsi=p_help;}
	    		i++;
	    	}
		pomocne=0; 
    }
    if(vyber[0]=='v'&&vyber[1]=='y'&&vyber[2]=='p'&&vyber[3]=='i'&&vyber[4]=='s'){
	    pomoc1=p_prvy;
	  	while (pomoc1 != NULL) { 
	    printf("Nazov=%s, Vyrobca=%s, Mnozstvo=%lf, JednotkovaCena=%lf \n",pomoc1->nazov,pomoc1->vyrobcu,pomoc1->mnozstvo,pomoc1->cena);		
	    pomoc1 = pomoc1->dalsi;}
	}
  }
  return 0;
}