#include <stdio.h>

int S[5];
int PD[8000];

int rec(int n, int m){
	if(PD[n]!=0) return PD[n];
	if(n==0) return 1;
	if(n<0)  return 0;
	if(m<0)  return 0;
	
	PD[n] = rec(n-S[m],m) + rec(n,m-1);
	return PD[n];
}

int main(){
	int valor;

	S[0] = 1;
	S[1] = 5;
	S[2] = 10;
	S[3] = 25;
	S[4] = 50;
	scanf("%d",&valor);
	printf("%d\n", rec(valor,4));
	return 0;
}

