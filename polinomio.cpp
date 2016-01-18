#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

#define MAX_GRAU_POLINOMIO 1000
#define ERRO 5.0/1000000000

double polinomio[11]; //O grau de um polinomio é guardado em sua posição 0;
double polinomioderivado[11];

void carregaPolinomio(){
	int i,j;

	i = 0;
	do{
		cout << "Grau do polinomio = ";
		cin >> polinomio[0];
	}while(polinomio[0] < 0 && polinomio[0] > MAX_GRAU_POLINOMIO);

	cout << "Coeficientes" << endl;
	
	j = polinomio[0];
	for(i=1; i<=polinomio[0]+1; i++){
		cout << "Termo ";
		0 == j ? cout << "independente" : cout << j;
		cout << ": ";

		cin >> polinomio[i];
		j--;
	}
}

void printPolinomio(){
	int i,j,grau;

	grau = polinomio[0];
	j = grau;
	cout << "P(x) = ";
	for(i=1; i<=grau+1; i++){
		if(i == grau+1){
			if(polinomio[i] != 0) cout << " + " << polinomio[i];
			cout << endl;
		}else if(polinomio[i] != 0){
			if(j != grau) cout << " + ";
			if(polinomio[i] != 1) cout << polinomio[i];
			cout << "X";
			if(j != 1) cout << "^" << j;
		}
		j--;
	}
}

void printPolinomioDerivado(){
        int i,j,grau;

        grau = polinomioderivado[0];
        j = grau;
        cout << "P(x) = ";
        for(i=1; i<=grau+1; i++){
                if(i == grau+1){
                        if(polinomioderivado[i] != 0) cout << " + " << polinomioderivado[i];
                        cout << endl;
                }else if(polinomioderivado[i] != 0){
                        if(j != grau) cout << " + ";
                        if(polinomioderivado[i] != 1) cout << polinomioderivado[i];
                        cout << "X";
                        if(j != 1) cout << "^" << j;
                }
                j--;
        }
}

void inicializaPolinomio(){
	polinomio[0] = 9;
	polinomio[1] = 1;
	polinomio[2] = -2 * sqrt(2);
	polinomio[3] = -13;
	polinomio[4] = 26 * sqrt(2);
	polinomio[5] = 59;
	polinomio[6] = -118 * sqrt(2);
	polinomio[7] = -107;
	polinomio[8] = 214 * sqrt(2);
	polinomio[9] = 60;
	polinomio[10] = -120 * sqrt(2);
}

double modulo(double in){return (in < 0) ? in*-1 : in;}

double calculaR(double n, double a0, double a1, double an){
	double e0, e1;

	e0 = n * modulo(a0 / a1);
	e1 = pow(modulo(a0 / an), 1.0/n);

	return (e0 < e1) ? e0 : e1;
}

void derivaF(){
	int j = 0;
	polinomioderivado[0] = polinomio[0] - 1;
	for(int i=polinomio[0]+1; i>0; i--){
		polinomioderivado[i] = polinomio[i] * j;
		j++;
	}
}

double f(double x){
	double xatual = 1;
	double retorno = 0;
	int i;
	for(i=polinomio[0]+1;i>0;i--){
		retorno += polinomio[i] * xatual;
		xatual *= x;
	}
	return retorno;
}

double df(double x){
	derivaF();
	double xatual = 1;
	double retorno = 0;
	int i;
	for(i=polinomioderivado[0]+1;i>0;i--){
		retorno += polinomioderivado[i] * xatual;
		xatual *= x;
	}
	return retorno;
}

double newtonRaphson(double a, double b){
	double xk, h, i;
	xk = (a + b) / 2;
	do{
		h = f(xk) / df(xk);
		//cout << "f(xk): " << f(xk) << " df(xk): " << df(xk) << " xk: " << xk  << endl;
		xk = xk - h;
	}while(modulo(h) > ERRO);

	return xk;
}

///////////////////////////////////////

int main(){
	double r, raiz;
	//Começando o algoritmo
	inicializaPolinomio();

	printPolinomio();
	derivaF();
	printPolinomioDerivado();

	r = calculaR(9,polinomio[1],polinomio[2],polinomio[10]);
	raiz = newtonRaphson(-1*r,r);

	printf("Raiz: %.15f\n",raiz);

	//Agora deflatamos o polinômio com briot ruffini
	//Repetimos tudo para o polinômio deflatado
	//Repete até que o polinômio seja de grau 1

	return 0;
}
