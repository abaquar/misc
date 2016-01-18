#include <stdio.h>
#include <math.h>

long nM[1024];
int nMult;

double potencia(int nX, int nK){
	int i,j,negativo;

	if(nK == 0) return 1;
	negativo = nK < 0;
	nK = abs(nK);

	nM[1]  = nX;
	i = 2;
	while(i <= nK){
		nM[i] = mul(nM[i>>1],nM[i>>1]);
		i = i << 1;
	}

	i = i >> 1;
	j = nK - i;
	nM[nK] = nM[i];

	while(j>0){
		i = i >> 1;
		if(i<=j){
			j -= i;
			nM[nK] = mul(nM[nK],nM[i]);
		}
	}

	return (negativo) ? 1.0/nM[nK] : nM[nK];
}

int mul(int a, int b){
	nMult++;
	return a*b;
}

main(){
	int nX,nK;
	nMult = 0;

	printf("[ X^k ]\n\n");
	printf("X >> ");
	scanf("%d",&nX);

	printf("K >> ");
	scanf("%d",&nK);

	printf("	Resultado esperado: %f\n",pow(nX,nK));
	printf("	Resultado obtido:   %f\n",potencia(nX,nK));
	printf("	Multiplicações:     %d\n",nMult);
}
