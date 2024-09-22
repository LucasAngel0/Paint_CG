#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "reta.h"

Cor azul = { 0.0, 0.0, 1.0 };
Cor preta = { 0.0, 0.0, 0.0 };

Retas * CriaL_Retas()
{
	// Ponteiro da lista de retas
	Retas * listaRetas = (Retas *)malloc(sizeof(Retas));
	listaRetas->QtdRetas = 0;
	return listaRetas;
}
void ImprimeL_Retas(Retas * L_Retas)
{
	// Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (L_Retas == NULL || L_Retas->QtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel imprimir retas!\n");
	}
	// Imprimir retas
	else {
		for (int i = 0; i < L_Retas->QtdRetas; i++) {
			printf("Ponto: %d:\n", i + 1);

			printf("Inicial:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
				L_Retas->retas[i].inicial.x,
				L_Retas->retas[i].inicial.y,
				L_Retas->retas[i].inicial.cor.Red,
				L_Retas->retas[i].inicial.cor.Green,
				L_Retas->retas[i].inicial.cor.Blue
			);

			printf("Central:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
				L_Retas->retas[i].central.x,
				L_Retas->retas[i].central.y,
				L_Retas->retas[i].central.cor.Red,
				L_Retas->retas[i].central.cor.Green,
				L_Retas->retas[i].central.cor.Blue
			);

			printf("Final:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
				L_Retas->retas[i].final.x,
				L_Retas->retas[i].final.y,
				L_Retas->retas[i].final.cor.Red,
				L_Retas->retas[i].final.cor.Green,
				L_Retas->retas[i].final.cor.Blue
			);
		}
	}
}

void ExcluiL_Retas(Retas * L_Retas)
{
    // Se a lista de retas não está vazia
    if (L_Retas != NULL) {
        // Liberar as retas
        free(L_Retas);
    }
}

void SalvaL_Retas(const char *ArquivoRetas, Retas *L_Retas)
{
    // Verifica se a lista de retas é válida
    if (L_Retas == NULL || L_Retas->QtdRetas == 0) {
        printf("A lista de retas está vazia ou não foi criada. Nada para salvar.\n");
        return;
    }

    // Abre o arquivo para escrita
    FILE *arquivo = fopen(ArquivoRetas, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para salvar as retas.\n", ArquivoRetas);
        return;
    }

    // Salva a quantidade de retas
    fprintf(arquivo, "%d\n", L_Retas->QtdRetas);

    // Salva cada reta no arquivo
    for (int i = 0; i < L_Retas->QtdRetas; i++) {
        Reta *retaAtual = &L_Retas->retas[i];

        // Salva os pontos da reta (inicial, central e final)
        fprintf(arquivo, "%.1f %.1f %.1f %.1f %.1f ", 
            retaAtual->inicial.x, 
            retaAtual->inicial.y, 
            retaAtual->inicial.cor.Red, 
            retaAtual->inicial.cor.Green, 
            retaAtual->inicial.cor.Blue);

        fprintf(arquivo, "%.1f %.1f %.1f %.1f %.1f ", 
            retaAtual->central.x, 
            retaAtual->central.y, 
            retaAtual->central.cor.Red, 
            retaAtual->central.cor.Green, 
            retaAtual->central.cor.Blue);

        fprintf(arquivo, "%.1f %.1f %.1f %.1f %.1f\n", 
            retaAtual->final.x, 
            retaAtual->final.y, 
            retaAtual->final.cor.Red, 
            retaAtual->final.cor.Green, 
            retaAtual->final.cor.Blue);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Retas salvas com sucesso no arquivo %s.\n", ArquivoRetas);
}


void CarregaL_Retas(const char *ArquivoRetas, Retas *L_Retas)
{
    // Abre o arquivo para leitura
    FILE *arquivo = fopen(ArquivoRetas, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para carregar as retas.\n", ArquivoRetas);
        return;
    }

    // Lê a quantidade de retas armazenadas no arquivo
    if (fscanf(arquivo, "%d", &L_Retas->QtdRetas) != 1) {
        printf("Erro ao ler a quantidade de retas do arquivo.\n");
        L_Retas->QtdRetas = 0; // Reseta a lista de retas
        fclose(arquivo);
        return;
    }

    // Verifica se o número de retas é válido
    if (L_Retas->QtdRetas < 0 || L_Retas->QtdRetas > MAXIMO) {
        printf("Número de retas inválido no arquivo.\n");
        L_Retas->QtdRetas = 0; // Reseta a lista de retas
        fclose(arquivo);
        return;
    }

    // Lê cada reta do arquivo
    for (int i = 0; i < L_Retas->QtdRetas; i++) {
        Reta *retaAtual = &L_Retas->retas[i];

        // Lê os pontos da reta (inicial, central e final)
        if (fscanf(arquivo, "%f %f %f %f %f",
                   &retaAtual->inicial.x,
                   &retaAtual->inicial.y,
                   &retaAtual->inicial.cor.Red,
                   &retaAtual->inicial.cor.Green,
                   &retaAtual->inicial.cor.Blue) != 5) {
            printf("Erro ao ler o ponto inicial da reta %d do arquivo.\n", i + 1);
            L_Retas->QtdRetas = i; // Ajusta o número de retas lidas corretamente
            break;
        }

        if (fscanf(arquivo, "%f %f %f %f %f",
                   &retaAtual->central.x,
                   &retaAtual->central.y,
                   &retaAtual->central.cor.Red,
                   &retaAtual->central.cor.Green,
                   &retaAtual->central.cor.Blue) != 5) {
            printf("Erro ao ler o ponto central da reta %d do arquivo.\n", i + 1);
            L_Retas->QtdRetas = i; // Ajusta o número de retas lidas corretamente
            break;
        }

        if (fscanf(arquivo, "%f %f %f %f %f",
                   &retaAtual->final.x,
                   &retaAtual->final.y,
                   &retaAtual->final.cor.Red,
                   &retaAtual->final.cor.Green,
                   &retaAtual->final.cor.Blue) != 5) {
            printf("Erro ao ler o ponto final da reta %d do arquivo.\n", i + 1);
            L_Retas->QtdRetas = i; // Ajusta o número de retas lidas corretamente
            break;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Retas carregadas com sucesso do arquivo %s.\n", ArquivoRetas);
}

int Add_Retas(float mouseX, float mouseY, int statusObjeto, Retas * L_Retas)
{
	// Se a lista de retas não foi criada ou está cheia não é possível adicionar mais retas
	if (L_Retas == NULL || L_Retas->QtdRetas == MAXIMO) {
		printf("Lista de retas nao foi criada ou esta cheia! Nao e possivel adicionar a reta!\n");
		return 0;
	}
	// Adicionar a reta
	else {
		// Se a reta tem somente o ponto inicial (está sendo desenhada ainda)
		if (statusObjeto == -1) {
			// Adicionar o ponto inicial da reta com as posições x e y, e a cor azul fixa
			L_Retas->retas[L_Retas->QtdRetas].inicial.x = mouseX;
			L_Retas->retas[L_Retas->QtdRetas].inicial.y = mouseY;
			L_Retas->retas[L_Retas->QtdRetas].inicial.cor = azul;
			return 1;
		}
		// Se o ponto final da reta foi informado (finalizando o desenho da reta)
		else {
			// Adicionar o ponto final da reta com as posições x e y, e a cor azul fixa
			L_Retas->retas[L_Retas->QtdRetas].final.x = mouseX;
			L_Retas->retas[L_Retas->QtdRetas].final.y = mouseY;
			L_Retas->retas[L_Retas->QtdRetas].final.cor = azul;

			// Calcular o ponto central da reta e adiciona a lista com as posições x e y, e a cor preta fixa
			L_Retas->retas[L_Retas->QtdRetas].central.x = (L_Retas->retas[L_Retas->QtdRetas].inicial.x + L_Retas->retas[L_Retas->QtdRetas].final.x) / 2;
			L_Retas->retas[L_Retas->QtdRetas].central.y = (L_Retas->retas[L_Retas->QtdRetas].inicial.y + L_Retas->retas[L_Retas->QtdRetas].final.y) / 2;
			L_Retas->retas[L_Retas->QtdRetas].central.cor = preta;

			// Acrescentando uma reta a lista
			L_Retas->QtdRetas++;

			printf("Reta adicionada com sucesso!\n");

			// Retorna ao status inicial do objeto
			return -1;
		}
	}
}


int RemoveReta(int chave, Retas * listaRetas)
{
	// Se a lista de retas não foi criada ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->QtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel excluir a reta!\n");
		return 0;
	}
	// Remover uma reta
	else {
		// Laço para percorrer a lista de retas a partir da chave da reta até o final da lista
        // Para não quebrar a integridade da lista
		for (int i = chave; i < listaRetas->QtdRetas; i++) {
			listaRetas->retas[i] = listaRetas->retas[i + 1];
		}

		// Diminuir uma unidade da quantidade de retas
		listaRetas->QtdRetas--;

		printf("Reta excluida com sucesso!\n");
		return 1;
	}
}


int Seleciona_Reta(float mouseX, float mouseY, Retas * listaRetas)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->QtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel selecionar a reta!\n");
		return 0;
	}
	// Selecionar reta
	else {
		for (int i = 0; i < listaRetas->QtdRetas; i++) {
			// Calcular formula da reta para saber se um ponto pertence a ela
			// Pegando o ponto inicial da reta
			float x1 = listaRetas->retas[i].inicial.x;
			float y1 = listaRetas->retas[i].inicial.y;

			// Pegando o ponto final da reta
			float x2 = listaRetas->retas[i].final.x;
			float y2 = listaRetas->retas[i].final.y;

			// Verificando se o ponto do mouse quando clicado pertence a reta
			if (VerificaPontoReta(mouseX, mouseY, x1, y1, x2, y2)) {
				printf("Reta selecionada com sucesso!\n");
				return i;
			}
		}

		printf("Ponto nao encontrado na lista de retas!\n");
		return -1;
	}
}

int VerificaPontoReta(float mouseX, float mouseY, float x1, float y1, float x2, float y2)
{
	float m, b, aux;
	int tolerancia = 8; 

	// Baseado na equação da reta: y = mx + b
	// Pode ser encontrada tendo dois pontos que pertencem a reta, assim encontramos o valor de m
	m = (y2 - y1) / (x2 - x1);

	// Substituindo na equação por um dos pontos conhecidos, assim encontramos o valor de b
	b = y1 - (m * x1);

	// Realiza o cálculo para saber o valor da coordenada y
	aux = (mouseX * m) + b;
	float distance = fabs(m * mouseX - mouseY + b) / sqrt(m * m + 1);

	// Verificando se o ponto do mouse quando clicado pertence a reta
	// Como existe a tolerância, tem que contar a área da reta
	// Se o valor estiver entre o valor da área da reta no ponto onde o mouse foi clicado
	if ((mouseY <= aux + tolerancia) && (mouseY >= aux - tolerancia)) {
		printf("O ponto selecionado pertence a reta!\n");
		return 1;
	} else {
		printf("O ponto selecionado nao pertence a reta!\n");
		return 0;
	}
}

void desenharRetas(Retas * listaRetas)
{
    glLineWidth(6.0);
    glBegin(GL_LINES);

    for (int i = 0; i < listaRetas->QtdRetas; i++) {
    	// Imprimindo os valores e intensidades de cores RGB
	glColor3f(listaRetas->retas[i].inicial.cor.Red, listaRetas->retas[i].inicial.cor.Green, listaRetas->retas[i].inicial.cor.Blue);
	// Posicionando o ponto inicial na largura e altura corretas do mouse
	glVertex2f(listaRetas->retas[i].inicial.x, listaRetas->retas[i].inicial.y);

	// Imprimindo os valores e intensidades de cores RGB
	glColor3f(listaRetas->retas[i].final.cor.Red, listaRetas->retas[i].final.cor.Green, listaRetas->retas[i].final.cor.Blue);
	// Posicionando o ponto final na largura e altura corretas do mouse
	glVertex2f(listaRetas->retas[i].final.x, listaRetas->retas[i].final.y);
    }

    glEnd();
}
