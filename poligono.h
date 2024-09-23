#ifndef POLIGONO_H
#define POLIGONO_H

#define MAX_POLIGONOS 1000

#include <stdbool.h>

#include "reta.h"

typedef struct PontoPoligono
{
    Ponto ponto;   			       // Ponto para armazenar um ponto dos cantos do polígono
    struct PontoPoligono * prox;   // Ponteiro para o próximo ponto dos cantos do polígono
} PontoPoligono;

typedef struct Poligono
{
    int qtdLados;   		   // Quantos lados tem o polígono
    Ponto centroide;    	   // Ponto para armazenar o ponto central do polígono (centróide)
    PontoPoligono * inicial;   // PontoPoligono para o ponto inicial do polígono
} Poligono;

typedef struct Poligonos
{
    int qtdPoligonos;    	     	     // Quantidade de polígonos na lista
    Poligono poligonos[MAX_POLIGONOS];   // Dados dos polígonos da lista de polígonos
} Poligonos;


Poligonos * CriaL_Poligonos();
void ImprimeL_Poligonos(Poligonos * L_Poligonos);
void ExcluiPoligonos(Poligonos * L_Poligonos);
void SalvaPoligonos(const char * nomeArquivoPoligonos, Poligonos * L_Poligonos);
void CarregaPoligonos(const char * nomeArquivoPoligonos, Poligonos * L_Poligonos);

PontoPoligono * criarPontoPoligono(float mouseX, float mouseY);
void AddPontoPoli(PontoPoligono ** pontoPoligonoInicial, float mouseX, float mouseY);
void imprimePontos(PontoPoligono * pontoPoligonoInicial);
PontoPoligono * BuscaUltimoPonto(PontoPoligono * pontoPoligonoInicial);

int AddPoligono(float mouseX, float mouseY, int statusObjeto, Poligonos * L_Poligonos);
void FinalizaPoligono(int statusObjeto, Poligonos * L_Poligonos);
void CentroidePoligono(int chave, Poligonos * L_Poligonos);
int RemovePoligono(int chave, Poligonos * L_Poligonos);
int SelecionaPoligono(float mouseX, float mouseY, Poligonos * L_Poligonos);
int VerificaPontoPoligono(Poligonos * poligono,float mouseX, float mouseY,int i);
void DesenhaPoligono(Poligonos * L_Poligonos);

int TransladaPoligono(int key, Poligonos * L_Poligonos, M3x3 *MTranslacaoPoligono);


#endif // POLIGONO_H
