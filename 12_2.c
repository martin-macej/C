//Napíšte funkciu unsigned int invert(unsigned x, int i, int n), ktorá invertuje (zmení 0 na 1 a naopak) v čísle x od pozície i, n bitov. Ostatné bity zostanú nezmenené.
//
//Túto funkciu si môžete otestovať v programe, ktorý číta riadok zo štandardného vstupu obsahujúci 3 celé čísla. Prvé číslo reprezentuje číslo, ktoré sa má invertovať, zapísané v desiatkovej sústave. Druhé číslo reprezentuje pozíciu, od ktorej sa majú bity invertovať (počítame od 0 od najvyššej pozície) a posledné číslo reprezentuje počet bitov, ktoré sa budú invertovať.
//
//Príklad:
//x = 123 (1111011)
//invert(x, 1, 2)
//x: 75 (1001011)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int invert(unsigned int x, int i, int n)
{
  char bin[10];
  int A=0, a;
  while(x!=0){
  	bin[A]=x%2;
    x/=2;
    A++;
  }
  for(a=0; a<A; a++){
    if((a>=A-i-n)&&(a<=A-i-1))bin[a]=1-bin[a];
    x+=bin[a]*pow(2,a);
  }
  return x;
}

int main()
{
  int i, j, x, ii, nn;

  scanf("%d %d %d", &x, &ii, &nn);
  
  printf("x = %d ", x);
  printf("(");
  for (j = 0, i = 31; i >= 0; i--)
  {
    if (x & (1<<i))
      j = 1;
    if (j)
    {
      if (x & (1<<i))
        printf("1");
      else
        printf("0");
    }
  }
  printf(")\n");

  printf("invert(x, %d, %d)\n", ii, nn);
  x = invert(x, ii, nn);

  printf("x: %d ", x);
  printf("(");
  for (j = 0, i = 31; i >= 0; i--)
  {
    if (x & (1<<i))
      j = 1;
    if (j)
    {
      if (x & (1<<i))
        printf("1");
      else
        printf("0");
    }
  }
  printf(")\n");

  return 0;
}
