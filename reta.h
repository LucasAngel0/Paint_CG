#ifndef RETA_H
#define RETA_H

#define MAXIMO 1000

#include "ponto.h"
typedef struct Reta
{
    Ponto inicial;  
    Ponto central;  
    Ponto final;    
} Reta;

typedef struct Retas
{
    int QtdRetas;           
    Reta retas[MAXIMO];   
} Retas;


Retas * CriaL_Retas();
void ImprimeL_Retas(Retas * L_Retas);
void ExcluiL_Retas(Retas * L_Retas);
void SalvaL_Retas(const char * ArquivoRetas, Retas * L_Retas);
void CarregaL_Retas(const char * ArquivoRetas, Retas * L_RetasArquivo);

int Add_Retas(float mouseX, float mouseY, int statusObjeto, Retas * L_Retas);
int RemoveReta(int chave, Retas * L_Retas);
int Seleciona_Reta(float mouseX, float mouseY, Retas * L_Retas);
int VerificaPontoReta(float mouseX, float mouseY, float x1, float y1, float x2, float y2);
void desenharRetas(Retas * L_Retas);

#endif // RETA_H
