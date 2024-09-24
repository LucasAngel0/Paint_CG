#ifndef MATRIZ_H
#define MATRIZ_H
//ESTRUTURA PARA A MATRIZ 3x1

typedef struct M3x1
{
    float matriz[3][1];     // Matriz para armazenar uma matriz 3x1
} M3x1;

//ESTRUTURA PARA A MATRIZ 3x3

typedef struct M3x3
{
    float matriz[3][3];   // Matriz para armazenar uma matriz 3x3
} M3x3;


//DECLARAÇÕES DAS FUNÇÕES
M3x1 * criaM3x1(float x, float y);
M3x1 * MultiplicaM3x3PorM3x1(M3x3 * Mt3x3, M3x1 * Mt3x1);
M3x3 * criaM3x3();
M3x3 * MultiplicaM3x3(M3x3 * M1, M3x3 * M2);

M3x3 * MultiplicaMComposta(float centralX, float centralY, M3x3 * matrizTransformacao);

M3x3 * criaMTranslacao(float finalX, float finalY);
M3x3 * CriaMRotacao(float angulo);
M3x3 * CriaMEscalar(float escala);

M3x3 * CriaMTranslacaoInversa(float finalX, float finalY);
M3x3 * CriaMRotacaoInversa(float angulo);
M3x3 * CriaMEscalarInversa(float escala);

M3x3 * CriaMReflexaoX();
M3x3 * CriaMReflexaoY();
M3x3 * CriaMReflexaoOrigem();

M3x3 * CriaMCisalhamentoX(float corte);
M3x3 * CriarMCisalhamentoY(float corte);

#endif // MATRIZ_H