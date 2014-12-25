#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_DADOS 32
#define MAX_RESULTADO 1024

using namespace std;

int frequencias[MAX_RESULTADO];
int dados[MAX_DADOS];
int totalProbabilidades = 0;
int modificador = 0;
int dificuldade = 0;
bool plot = true;
bool verbose = false;


void plottar(){
	int i;
	FILE *gnuplot = popen("gnuplot -persistent", "w");
	fprintf(gnuplot, "set title \"Distribuição de Probabilidades\"; set xlabel \"Valor Obtido\"; set ylabel \"Frequencia\";");
	fprintf(gnuplot, "plot '-' with filledcurve\n");
	//printa dados
	for(i=0;frequencias[i]==0;i++);
	while(frequencias[i]!=0){
		fprintf(gnuplot, "%d %d\n",i,frequencias[i]);
		i++;
	}
	fprintf(gnuplot, "e\n");
	fflush(gnuplot);
}

float calculaProbabilidadeSucesso(){
	int frequenciaSucesso = 0;
	for(int i=0; i<MAX_RESULTADO; i++){
		if(i >= dificuldade){
			frequenciaSucesso += frequencias[i];
		}
	}
	return  (100.0*frequenciaSucesso)/totalProbabilidades;
}

void calculaProbabilidades(int index, int acumulado){
	for(int i=1; i<=dados[index]; i++){
		if(0 == dados[index+1]){
			int frequenciaCalculada = i + acumulado + modificador;
			if(0 <= frequenciaCalculada){
				frequencias[frequenciaCalculada]++;
			}
			totalProbabilidades++;
		}else{
			calculaProbabilidades(index+1,acumulado+i);
		}
	}
}

int main(int argc, char* argv[]){
	int indexDadoAtual = 0;
	for(int i=1; i<argc; i++){
		if(0==strcmp(argv[i],"--help")){
			cout << "Este programa calcula todos os possíveis resultados positivos obtidos através da rolagem de dados de n lados e usa GNUplot para compor o gráfico das possibilidades. O número maximo de dados é 32 e a soma máxima de seus resultados é 1024, porque eu tenho preguiça de declarar vetor dinamicamente. Uso:" << endl;
			cout << argv[0] << " <--help> <--mod x> <--dif y> <--noplot> <--verbose> [k1 k2 k3 ... k32]" << endl;
			cout << "--help\t\tMostra esta mensagem" << endl;
			cout << "--mod x\t\tAdiciona o modificador x ao calculo (1, 2, -1, -2, etc)" << endl;
			cout << "--dif y\t\tDificuldade do teste. Se presente o programa calcula a probabilidade de se obter um valor igual ou maior que y ao se fazer o teste" << endl;
			cout << "--noplot\t\tValores não serão plottados pelo GNUplot" << endl;
			cout << "--verbose\t\tEscreve valores obtidos na tela" << endl;
			cout << "[k1 k2 k3 ... k32]\tCada k representa o número de faces de um dado a ser calculado. Multiplos dados de mesma face devem ser declarados como valores repetidos, ja que cada número indepentende representa um unico dado" << endl;
			cout << "Exemplos de uso:" << endl;
			cout << "\t" << argv[0] << " 4 6" << endl;
			cout << "\t" << argv[0] << " --mod 1 6 6" << endl;
			cout << "\t" << argv[0] << "--mod -2 --dif 7 20" << endl;
			return 0;
		}else if(0==strcmp(argv[i],"--mod")){
			modificador = atoi(argv[++i]);
		}else if(0==strcmp(argv[i],"--dif")){
			dificuldade = atoi(argv[++i]);
		}else if(0==strcmp(argv[i],"--noplot")){
			plot = false;	
		}else if(0==strcmp(argv[i],"--verbose")){
			verbose = true;
		}else{
			dados[indexDadoAtual] = atoi(argv[i]);
			indexDadoAtual++;
		}
	}

	calculaProbabilidades(0,0);

	if(verbose){
		for(int i=0; i<1000; i++){
			if(0 < frequencias[i]){
				cout << "Valor: " << i << " Frequencia: " << frequencias[i] << endl;
			}
		}
	}

	if(dificuldade > 0){
		cout << "Probabilidade de sucesso: " << calculaProbabilidadeSucesso() << "%" << endl;
	}

	if(plot){
		plottar();
	}
	return 0;
}
