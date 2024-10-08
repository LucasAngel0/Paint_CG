#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "ponto.h"

#include "matriz.h"

Cor vermelha = { 1.0, 0.0, 0.0 };

Pontos * CriaL_Pontos()
{
    // Ponteiro da lista de pontos
    Pontos * L_Pontos = (Pontos *)malloc(sizeof(Pontos));
    L_Pontos->QtdPontos = 0;
    return L_Pontos;
}

void ImprimePontos(Pontos * L_Pontos)
{
    // Se a lista de pontos não foi criada ou a quantidade de pontos for zero
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel imprimir pontos!\n");
    }
    // Imprimir ponto
    else {
        for (int i = 0; i < L_Pontos->QtdPontos; i++) {
            printf("Ponto %d: x: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
                i + 1,
                L_Pontos->pontos[i].x,
                L_Pontos->pontos[i].y,
                L_Pontos->pontos[i].cor.Red,
                L_Pontos->pontos[i].cor.Green,
                L_Pontos->pontos[i].cor.Blue
            );
        }
    }
}


void ExcluiPontos(Pontos * L_Pontos)
{
    // Se a lista de pontos não está vazia
    if (L_Pontos != NULL) {
        // Liberar os pontos
        free(L_Pontos);
    }
}


void SalvaPontos(const char *nomeArquivoPontos, Pontos *L_Pontos)
{
    // Verifica se a lista de pontos é válida
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("A lista de pontos está vazia ou não foi criada. Nada para salvar.\n");
        return;
    }

    // Abre o arquivo para escrita
    FILE *arquivo = fopen(nomeArquivoPontos, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para salvar os pontos.\n", nomeArquivoPontos);
        return;
    }

    // Salva a quantidade de pontos
    fprintf(arquivo, "%d\n", L_Pontos->QtdPontos);

    // Salva cada ponto no arquivo
    for (int i = 0; i < L_Pontos->QtdPontos; i++) {
        fprintf(arquivo, "%.1f %.1f %.1f %.1f %.1f\n",
            L_Pontos->pontos[i].x,
            L_Pontos->pontos[i].y,
            L_Pontos->pontos[i].cor.Red,
            L_Pontos->pontos[i].cor.Green,
            L_Pontos->pontos[i].cor.Blue);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Pontos salvos com sucesso no arquivo %s.\n", nomeArquivoPontos);
}

void CarregaPontos(const char *nomeArquivoPontos, Pontos *L_Pontos)
{
    // Abre o arquivo para leitura
    FILE *arquivo = fopen(nomeArquivoPontos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para carregar os pontos.\n", nomeArquivoPontos);
        return;
    }

    // Lê a quantidade de pontos armazenados no arquivo
    if (fscanf(arquivo, "%d", &L_Pontos->QtdPontos) != 1) {
        printf("Erro ao ler a quantidade de pontos do arquivo.\n");
        L_Pontos->QtdPontos = 0; // Reseta a lista de pontos
        fclose(arquivo);
        return;
    }

    // Verifica se o número de pontos é válido
    if (L_Pontos->QtdPontos < 0 || L_Pontos->QtdPontos > MAXIMO) {
        printf("Número de pontos inválido no arquivo.\n");
        L_Pontos->QtdPontos = 0; // Reseta a lista de pontos
        fclose(arquivo);
        return;
    }

    // Lê cada ponto do arquivo
    for (int i = 0; i < L_Pontos->QtdPontos; i++) {
        if (fscanf(arquivo, "%f %f %f %f %f",
                   &L_Pontos->pontos[i].x,
                   &L_Pontos->pontos[i].y,
                   &L_Pontos->pontos[i].cor.Red,
                   &L_Pontos->pontos[i].cor.Green,
                   &L_Pontos->pontos[i].cor.Blue) != 5) {
            printf("Erro ao ler os dados do ponto %d do arquivo.\n", i + 1);
            L_Pontos->QtdPontos = i; // Ajusta o número de pontos lidos corretamente
            break;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Pontos carregados com sucesso do arquivo %s.\n", nomeArquivoPontos);
}

int AddPonto(float mouseX, float mouseY, Pontos * L_Pontos)
{
    // Se a lista de pontos não foi criada ou está cheia, não é possível adicionar mais pontos
    if (L_Pontos == NULL || L_Pontos->QtdPontos == MAXIMO) {
        printf("Lista de pontos nao foi criada ou esta cheia! Nao e possivel adicionar o ponto!\n");
        return 0;
    }
    // Adicionar o ponto
    else {
        // Adicionando na lista a posição x e y, assim como a cor vermelha fixa para os pontos
        L_Pontos->pontos[L_Pontos->QtdPontos].x = mouseX;
        L_Pontos->pontos[L_Pontos->QtdPontos].y = mouseY;
        L_Pontos->pontos[L_Pontos->QtdPontos].cor = vermelha;
        L_Pontos->QtdPontos++;

        printf("Ponto adicionado com sucesso!\n");
        return 1;
    }
}


int RemovePonto(int key, Pontos * L_Pontos)
{
    // Se a lista de pontos não foi criada ou a quantidade de pontos for zero
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel excluir o ponto!\n");
        return 0;
    }
    // Excluir um ponto
    else {
        // Laço para percorrer a lista de pontos a partir da key do ponto até o final da lista
        // Para não quebrar a integridade da lista
        for (int i = key; i < L_Pontos->QtdPontos; i++) {
            L_Pontos->pontos[i] = L_Pontos->pontos[i + 1];
        }

        // Diminuir uma unidade da quantidade de pontos
        L_Pontos->QtdPontos--;

        printf("Ponto excluido com sucesso!\n");
        return 1;
    }
}


int SelecionaPonto(float mouseX, float mouseY, Pontos * L_Pontos)
{
    int tolerancia = 12; 

    // Se a lista de pontos não foi criada ou a quantidade de pontos for zero
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel selecionar o ponto!\n");
        return -1;
    }
    // Selecionar o ponto
    else {
        // Procurar na lista de pontos algum ponto que esteja sendo clicado pelo mouse
        for (int i = 0; i < L_Pontos->QtdPontos; i++) {
            if (mouseX <= L_Pontos->pontos[i].x + tolerancia && mouseX >= L_Pontos->pontos[i].x - tolerancia) { // O 3 é o valor de tolerância para a região de detecção
                
                if (mouseY <= L_Pontos->pontos[i].y + tolerancia && mouseY >= L_Pontos->pontos[i].y - tolerancia) { // O valor é 3 porque é metade do size do ponto
                    printf("Ponto selecionado com sucesso!\n");
                    return i;
                }
            }
        }

        printf("Ponto nao encontrado na lista!\n");
        return -1;
    }
}

void DesenhaPonto(Pontos * L_Pontos)
{
    glPointSize(6.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < L_Pontos->QtdPontos; i++) {
        // Imprimindo os valores e intensidades de cores RGB
        glColor3f(L_Pontos->pontos[i].cor.Red, L_Pontos->pontos[i].cor.Green, L_Pontos->pontos[i].cor.Blue);
        // Posicionando o ponto na largura e altura corretas do mouse
        glVertex2f(L_Pontos->pontos[i].x, L_Pontos->pontos[i].y);


    }

    glEnd();
}
int TransladaPonto(int key,Pontos *L_Pontos,M3x3 * MTranslacaoPonto){
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel transladar o ponto!\n");
        return 0;
    }
        else {
        // Criar a matriz3Por1 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm as coordenadas originais do ponto
        M3x1 * MCompostaPonto = criaM3x1(L_Pontos->pontos[key].x, L_Pontos->pontos[key].y);

        // Realizar a multiplicação gerando a matriz composta
        MCompostaPonto = MultiplicaM3x3PorM3x1(MTranslacaoPonto, MCompostaPonto);

        // Atualizar a posição do ponto a partir do resultado do cálculo da transformação
        L_Pontos->pontos[key].x = MCompostaPonto->matriz[0][0];
        L_Pontos->pontos[key].y = MCompostaPonto->matriz[0][1];  

        return 1;
    }
}


int RotacionaPonto(int key, Pontos * L_Pontos, M3x3 * MRotacaoPonto){

    // Se a lista de pontos não foi criada ou a quantidade de pontos for zero
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel rotacionar o ponto!\n");
        return 0;
    }
    // Rotacionar ponto
    else {
        // Criar a matriz3Por1 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm as coordenadas originais do ponto
        M3x1 * MCompostaPonto = criaM3x1(L_Pontos->pontos[key].x, L_Pontos->pontos[key].y);

        // Realizar a multiplicação gerando a matriz composta
        MCompostaPonto = MultiplicaM3x3PorM3x1(MRotacaoPonto, MCompostaPonto);

        // Modifica a posição do ponto a partir do resultado do cálculo da rotação
        L_Pontos->pontos[key].x = MCompostaPonto->matriz[0][0];
        L_Pontos->pontos[key].y = MCompostaPonto->matriz[0][1];

        return 1;
    }

    
}

int RefletePonto(int key, Pontos * L_Pontos, M3x3 * MReflexaoPonto){
    if (L_Pontos == NULL || L_Pontos->QtdPontos == 0) {
        printf("Lista de pontos nao foi criada ou nao ha pontos! Nao e possivel refletir o ponto!\n");
        return 0;
    }
    // Refletir ponto
    else {
        // Criar a matriz3Por1 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm as coordenadas originais do ponto
        M3x1 * MCompostaPonto = criaM3x1(L_Pontos->pontos[key].x, L_Pontos->pontos[key].y);

        // Realizar a multiplicação gerando a matriz composta
        MCompostaPonto = MultiplicaM3x3PorM3x1(MReflexaoPonto, MCompostaPonto);

        // Modifica a posição do ponto a partir do resultado do cálculo da rotação
        L_Pontos->pontos[key].x = MCompostaPonto->matriz[0][0];
        L_Pontos->pontos[key].y = MCompostaPonto->matriz[0][1];

        return 1;
    }

}

