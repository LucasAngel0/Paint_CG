#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "matriz.h"

M3x1 * criaM3x1(float x, float y)
{
    M3x1 * Mt3x1 = (M3x1 *)malloc(sizeof(M3x1));

    // Inicializando a M3x1 com os valores do ponto nos eixo x e y
    Mt3x1->matriz[0][0] = x;
    Mt3x1->matriz[1][0] = y;
    Mt3x1->matriz[2][0] = 1.0;

    return Mt3x1;
}



M3x1 * MultiplicaM3x3PorM3x1(M3x3 * Mt3x3, M3x1 * Mt3x1)
{
    // Caso as variáveis passadas não tenham dados
    if (Mt3x3 == NULL || Mt3x1 == NULL) {
        return 0;
    }
    // Multiplicar M3x3 por M3x1
    else {
        // Inicializando uma M3x1 para contar a matriz composta da transformação
        M3x1 * MComposta = criaM3x1(0.0, 0.0);

        // Laço para percorrer as linhas da matriz
        for (int i = 0; i < 3; i++) {
            // Realizando a multiplicação de uma M3x3 por uma M3x1
            MComposta->matriz[i][0] = Mt3x3->matriz[i][0] * Mt3x1->matriz[0][0] + Mt3x3->matriz[i][1] * Mt3x1->matriz[1][0] + Mt3x3->matriz[i][2] * Mt3x1->matriz[2][0];
        }

        return MComposta;
    }
}

M3x3 * criaM3x3()
{
    M3x3 * Mt3x3 = (M3x3 *)malloc(sizeof(M3x3));

    // Inicializando a M3x3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Se a linha for igual a coluna inicializa com 1, caso contrário com 0
            if (i == j) {
                Mt3x3->matriz[i][j] = 1;
            } else {
                Mt3x3->matriz[i][j] = 0;
            }
        }
    }

    return Mt3x3;
}
M3x3 * criaMTranslacao(float finalX, float finalY)
{
    // Inicializando uma matriz3Por3
    M3x3 * MTranslacao = criaM3x3();

    // Inicializando a matriz para a translação
    MTranslacao->matriz[0][2] = finalX;
    MTranslacao->matriz[1][2] = finalY;

    return MTranslacao;
}

M3x3 * MultiplicaM3x3(M3x3 * M1, M3x3 * M2)
{
    // Caso as variáveis passadas não tenham dados
    if (M1 == NULL || M2 == NULL) {
        return 0;
    }
    // Multiplicar duas M3x3
    else {
        M3x3 * MComposta = criaM3x3();

        // Laço para percorrer as linhas da matriz
        for (int i = 0; i < 3; i++) {
            // Laço para percorrer as colunas da matriz
            for (int j = 0; j < 3; j++) {
                MComposta->matriz[i][j] = M1->matriz[i][0] * M2->matriz[0][j] + M1->matriz[i][1] * M2->matriz[1][j] + M1->matriz[i][2] * M2->matriz[2][j];
            }
        }

        return MComposta;
    }
}

M3x3 * MultiplicaMComposta(float centralX, float centralY, M3x3 * MTransformacao)
{
    // Criar a matriz3Por3 para auxiliar nos cálculos
    // Primeiramente, a matriz é uma matriz identidade
    M3x3 * MComposta = criaM3x3();

    // Criar matriz translação com os pontos centrais
    M3x3 * matrizCentral = criaMTranslacao(centralX, centralY);

    // Realizar a multiplicação das matrizes
    // Primeiro passo da transformação, multiplicar a matriz translação central pela matriz transformação
    MComposta = MultiplicaM3x3(matrizCentral, MTransformacao);

    // Criar matriz translação com os pontos da diferença entre a origem e o centro
    M3x3 * matrizOrigemCentral = criaMTranslacao(0 - centralX, 0 - centralY);

    // Realizar a multiplicação das matrizes
    // Segundo passo da transformação, multiplicar a matriz resultante pela matriz referente a origem
    MComposta = MultiplicaM3x3(MComposta, matrizOrigemCentral);

    return MComposta;
}



M3x3 * CriaMRotacao(float angulo)
{
    // Inicializando uma matriz3Por3
    M3x3 * MRotacao = criaM3x3();

    // Inicializando a matriz para a rotação
    MRotacao->matriz[0][0] = cosf(angulo);
    MRotacao->matriz[0][1] = -sinf(angulo);
    MRotacao->matriz[1][0] = sinf(angulo);
    MRotacao->matriz[1][1] = cosf(angulo);

    return MRotacao;

}
M3x3 * CriaMEscalar(float escala)
{
    M3x3 * MEscalar = criaM3x3();

    // Inicializando a matriz para a escala
    MEscalar->matriz[0][0] = escala;
    MEscalar->matriz[1][1] = escala;

    return MEscalar;
}
M3x3 * CriaMTranslacaoInversa(float finalX, float finalY)
{
    // Inicializando uma matriz3Por3
    M3x3 * MTranslacaoInversa = criaM3x3();

    // Inicializando a matriz para a translação inversa
    MTranslacaoInversa->matriz[0][2] = -finalX;
    MTranslacaoInversa->matriz[1][2] = -finalY;

    return MTranslacaoInversa;
}

M3x3 * CriaMRotacaoInversa(float angulo)
{
    // Inicializando uma matriz3Por3
    M3x3 * MRotacaoInversa = criaM3x3();

    // Inicializando a matriz para a rotação inversa
    MRotacaoInversa->matriz[0][0] = cosf(angulo);
    MRotacaoInversa->matriz[0][1] = sinf(angulo);
    MRotacaoInversa->matriz[1][0] = -sinf(angulo);
    MRotacaoInversa->matriz[1][1] = cosf(angulo);

    return MRotacaoInversa;
}

M3x3 * CriaMEscalarInversa(float escala)
{
    M3x3 * MEscalarInversa = criaM3x3();

    // Inicializando a matriz para a escala inversa
    MEscalarInversa->matriz[0][0] = 1 / escala;
    MEscalarInversa->matriz[1][1] = 1 / escala;

    return MEscalarInversa;
}

M3x3 * CriaMReflexaoX()
{
    M3x3 * MReflexaoEixoX = criaM3x3();

    // Inicializando a matriz para a reflexão no eixo X
    MReflexaoEixoX->matriz[0][0] = -1;

    return MReflexaoEixoX;
}

M3x3 * CriaMatrizReflexaoY()
{
    M3x3 * MReflexaoEixoY = criaM3x3();

    // Inicializando a matriz para a reflexão no eixo Y
    MReflexaoEixoY->matriz[1][1] = -1;

    return MReflexaoEixoY;
}

M3x3 * CriaMReflexaoOrigem()
{
    M3x3 * MReflexaoOrigem = criaM3x3();

    // Inicializando a matriz para a reflexão na origem
    MReflexaoOrigem->matriz[0][0] = -1;
    MReflexaoOrigem->matriz[1][1] = -1;

    return MReflexaoOrigem;
}
M3x3 * CriaMCisalhamentoX(float corte)
{
    M3x3 * MReflexaoEixoX = criaM3x3();

    // Inicializando a matriz para o cisalhamento no eixo X
    MReflexaoEixoX->matriz[0][1] = corte;

    return MReflexaoEixoX;
}

M3x3 * CriarMCisalhamentoY(float corte)
{
    M3x3 * MReflexaoEixoY = criaM3x3();

    // Inicializando a matriz para o cisalhamento no eixo Y
    MReflexaoEixoY->matriz[1][0] = corte;

    return MReflexaoEixoY;
}