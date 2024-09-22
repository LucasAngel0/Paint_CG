#ifndef PONTO_H
#define PONTO_H

#define MAXIMO 1000



typedef struct Cor //estrutura de cor
{
    float Red;     
    float Green;   
    float Blue;    
} Cor;
typedef struct Ponto
{
    float x;   // largura
    float y;   // altura
    Cor cor;   
} Ponto;

typedef struct Pontos
{
    int QtdPontos;    
    Ponto pontos[MAXIMO];  
} Pontos;


Pontos * CriaL_Pontos();
void ImprimePontos(Pontos * L_Pontos);
void ExcluiPontos(Pontos * L_Pontos);
void SalvaPontos(const char * nomeArquivoPontos, Pontos * L_Pontos);
void CarregaPontos(const char * nomeArquivoPontos, Pontos * L_Pontos);

int AddPonto(float mouseX, float mouseY, Pontos * L_Pontos);
int RemovePonto(int chave, Pontos * L_Pontos);
int SelecionaPonto(float mouseX, float mouseY, Pontos * L_Pontos);
void DesenhaPonto(Pontos * L_Pontos);

#endif // PONTO_H
