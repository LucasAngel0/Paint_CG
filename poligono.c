#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

Cor laranja = { 1.0, 0.6, 0.0 };
Cor violeta = { 0.5, 0.0, 1.0 };

Poligonos * CriaL_Poligonos()
{
	Poligonos * L_Poligono = (Poligonos *)malloc(sizeof(Poligonos));
	L_Poligono->qtdPoligonos = 0;
	return L_Poligono;
}

void ImprimeL_Poligonos(Poligonos * L_Poligonos)
{
    // Se a lista de polígonos estiver vazia ou a quantidade de polígomos for zero
	if (L_Poligonos == NULL || L_Poligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou esta vazia! Nao e possivel imprimir poligonos!\n");
	}
	// Imprimir polígonos
	else {
		printf("Quantidade de poligonos: %d\n", L_Poligonos->qtdPoligonos);

		for (int i = 0; i < L_Poligonos->qtdPoligonos; i++) {
			printf("Poligono: %d\n", i + 1);
			printf("Quantidade de lados: %d\n", L_Poligonos->poligonos[i].qtdLados);
			printf("Centroide: (%.1f, %.1f)\n", L_Poligonos->poligonos[i].centroide.x, L_Poligonos->poligonos[i].centroide.y);
			imprimePontos(L_Poligonos->poligonos[i].inicial);
		}
	}
}


void ExcluiPoligonos(Poligonos * L_Poligonos)
{
	// Se a lista de polígonos não está vazia
    if (L_Poligonos != NULL) {
        // Liberar os polígonos
        free(L_Poligonos);
    }
}


void SalvaPoligonos(const char * nomeArquivoPoligonos, Poligonos * L_Poligono)
{
	// Se a lista de polígonos não está vazia
	if (L_Poligono != NULL) {
		// Variável para iterar a lista de polígonos
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));
		
		// Abrir o arquivo para salvar a lista
		FILE * arquivoPoligonos = fopen(nomeArquivoPoligonos, "w");

		// Checar se o arquivo foi aberto com sucesso
		if (arquivoPoligonos == NULL) {
			fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivoPoligonos);
			return;
		}

		// Escrever as dimensões da lista no arquivo
		fprintf(arquivoPoligonos, "%d\n\n", L_Poligono->qtdPoligonos);

		// Escrever os elementos da lista no arquivo
		// inicial.x, inicial.y,
		// ...,
		// final.x, final.y,
		// centroide.x, centroide.y, red, green, blue)
		for (int i = 0; i < L_Poligono->qtdPoligonos; i++) {
			// Escrever as dimensões da lista de pontos do polígono no arquivo
			fprintf(arquivoPoligonos, "%d\n", L_Poligono->poligonos[i].qtdLados);

			// Inicializando a variável com o primeiro ponto
			atualPontoPoligono = L_Poligono->poligonos[i].inicial;

			// Laço para iterar os pontos do polígono
			while (atualPontoPoligono != NULL) {
				////////// Ponto atual
				// Salvar posições do ponto atual
				fprintf(arquivoPoligonos, "%.1f ", atualPontoPoligono->ponto.x);
				fprintf(arquivoPoligonos, "%.1f", atualPontoPoligono->ponto.y);
				fprintf(arquivoPoligonos, "\n"); // Mover para a próxima linha do arquivo

				// Mover para o próximo ponto
				atualPontoPoligono = atualPontoPoligono->prox;
			}

			////////// Ponto centroide
			// Salvar posições do ponto centroide
			fprintf(arquivoPoligonos, "%.1f ", L_Poligono->poligonos[i].centroide.x);
			fprintf(arquivoPoligonos, "%.1f ", L_Poligono->poligonos[i].centroide.y);

			// Salvar os dados do RGB
			fprintf(arquivoPoligonos, "%.1f ", L_Poligono->poligonos[i].centroide.cor.Red);
			fprintf(arquivoPoligonos, "%.1f ", L_Poligono->poligonos[i].centroide.cor.Green);
			fprintf(arquivoPoligonos, "%.1f\n", L_Poligono->poligonos[i].centroide.cor.Blue);
			fprintf(arquivoPoligonos, "\n"); // Mover para a próxima linha do arquivo
		}

		// Fechar arquivo
		fclose(arquivoPoligonos);

		printf("Lista de poligonos salva com sucesso!\n");
	}
	// Se a lista de polígonos está vazia
	else {
		printf("A lista de poligonos esta vazia. Nada foi salvo no arquivo.\n");
		return;
	}
}


void CarregaPoligonos(const char * nomeArquivoPoligonos, Poligonos * listaPoligonosArquivo)
{
	float pontoX, pontoY;

	// Abrir o arquivo para carregar a lista
    FILE * arquivoPoligonos = fopen(nomeArquivoPoligonos, "r");

    // Checar se o arquivo foi aberto com sucesso
    if (arquivoPoligonos == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivoPoligonos);
        return;
    }

    // Ler as dimensões da lista no arquivo
    fscanf(arquivoPoligonos, "%d\n\n", &listaPoligonosArquivo->qtdPoligonos);

    // Ler os elementos da lista no arquivo
	// inicial.x, inicial.y,,
	// ...,
	// final.x, final.y,,
	// centroide.x, centroide.y, red, green, blue)
    for (int i = 0; i < listaPoligonosArquivo->qtdPoligonos; i++) {
    	// Ler as dimensões da lista de pontos do polígono no arquivo
		fscanf(arquivoPoligonos, "%d\n", &listaPoligonosArquivo->poligonos[i].qtdLados);

		// Laço para iterar os pontos do polígono
		for (int j = 0; j < listaPoligonosArquivo->poligonos[i].qtdLados; j++) {
			////////// Ponto atual
			// Ler posições do ponto atual
			fscanf(arquivoPoligonos, "%f ", &pontoX);
			fscanf(arquivoPoligonos, "%f", &pontoY);
			fscanf(arquivoPoligonos, "\n"); // Mover para a próxima linha do arquivo

			// Inserir o ponto do polígono no próximo ponteiro da lista
			AddPontoPoli(&listaPoligonosArquivo->poligonos[i].inicial, pontoX, pontoY);
		}	

		////////// Ponto centroide
		// Ler posições do ponto centroide
		fscanf(arquivoPoligonos, "%f ", &listaPoligonosArquivo->poligonos[i].centroide.x);
		fscanf(arquivoPoligonos, "%f ", &listaPoligonosArquivo->poligonos[i].centroide.y);

		// Ler os dados do RGB
		fscanf(arquivoPoligonos, "%f ", &listaPoligonosArquivo->poligonos[i].centroide.cor.Red);
		fscanf(arquivoPoligonos, "%f ", &listaPoligonosArquivo->poligonos[i].centroide.cor.Green);
		fscanf(arquivoPoligonos, "%f\n", &listaPoligonosArquivo->poligonos[i].centroide.cor.Blue);
		fscanf(arquivoPoligonos, "\n"); // Mover para a próxima linha do arquivo
    }

    // Fechar arquivo
    fclose(arquivoPoligonos);

    printf("Lista de poligonos carregada com sucesso!\n");
}


PontoPoligono * criarPontoPoligono(float mouseX, float mouseY)
{
	PontoPoligono * novoPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	// Checando se o novo ponto está vazio antes de inserir os dados
	if (novoPontoPoligono != NULL) {
		// Inicializando os valores do ponto do polígono
		novoPontoPoligono->ponto.x = mouseX;
		novoPontoPoligono->ponto.y = mouseY;
		novoPontoPoligono->ponto.cor = laranja;
		novoPontoPoligono->prox = NULL;
	}

	// Retornar ponto do polígono
	return novoPontoPoligono;
}


void AddPontoPoli(PontoPoligono ** pontoPoligonoInicial, float mouseX, float mouseY)
{
	// Criando o novo ponto
	PontoPoligono * novoPontoPoligono = criarPontoPoligono(mouseX, mouseY);

	// Se a lista estiver vazia, o novo ponto vira o ponto inicial da lista
	if (*pontoPoligonoInicial == NULL) {
		*pontoPoligonoInicial = novoPontoPoligono;
		return;
	}

	// Variável recebe o ponteiro para o último elemento da lista
	PontoPoligono * ultimoPontoPoligono = BuscaUltimoPonto(*pontoPoligonoInicial);

	// Inserir o novo ponto do polígono no último lugar da lista
	ultimoPontoPoligono->prox = novoPontoPoligono;
}

void imprimePontos(PontoPoligono * pontoPoligonoInicial)
{
	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoPoligonoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	int i = 0;
	while (pontoPoligonoInicial != NULL) {
		printf("Ponto %d: x: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
			i + 1,
			pontoPoligonoInicial->ponto.x,
			pontoPoligonoInicial->ponto.y,
            pontoPoligonoInicial->ponto.cor.Red,
            pontoPoligonoInicial->ponto.cor.Green,
            pontoPoligonoInicial->ponto.cor.Blue
		);

		pontoPoligonoInicial = pontoPoligonoInicial->prox;
		i++;
	}
}

/*
 * FUNÇÃO PARA BUSCAR O ÚLTIMO PONTO DO POLÍGONO
 */
PontoPoligono * BuscaUltimoPonto(PontoPoligono * pontoPoligonoInicial)
{
	// Checar se a variável para o ponto passada ainda é nula
	if (pontoPoligonoInicial == NULL) {
		return NULL;
	}

	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoPoligonoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	while (pontoPoligonoInicial->prox != NULL) {
		pontoPoligonoInicial = pontoPoligonoInicial->prox;
	}

	// Retorna o último elemento da lista de pontos do polígono
	return pontoPoligonoInicial;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UM POLÍGONO A TELA
 */
int AddPoligono(float mouseX, float mouseY, int statusObjeto, Poligonos * L_Poligono)
{
	// Se a lista de polígonos não foi criada ou está cheia, não é possível adicionar mais polígonos
	if (L_Poligono == NULL || L_Poligono->qtdPoligonos == MAX_POLIGONOS) {
		printf("Lista de poligonos nao foi criada ou esta cheia! Nao e possivel adicionar o poligono!\n");
		return 0;
	}
	// Adicionar polígono
	else {
		// Se o polígono está sendo inicializado (primeiro ponto do polígono)
		if (statusObjeto == -1) {
			// Inserir o ponto do polígono no próximo ponteiro da lista
			AddPontoPoli(&L_Poligono->poligonos[L_Poligono->qtdPoligonos].inicial, mouseX, mouseY);

			// Adicionando mais um quantidade de lados do polígono
			L_Poligono->poligonos[L_Poligono->qtdPoligonos].qtdLados = 1;

			// Retornar para continuar a adição de pontos ao polígono
			return 1;
		}
		// Se o polígono está sendo desenhando (adicionando outros pontos ao polígono)
		else if (statusObjeto == 1) {
			// Inserir o ponto do polígono no próximo ponteiro da lista
			AddPontoPoli(&L_Poligono->poligonos[L_Poligono->qtdPoligonos].inicial, mouseX, mouseY);

			// Adicionando mais um quantidade de lados do polígono
			L_Poligono->poligonos[L_Poligono->qtdPoligonos].qtdLados++;

			// Retornar o status que o objeto ainda terá mais pontos
			return 1;
		}

		// Se não tem lados o suficiente para montar um polígono
        printf("Nao ha lados suficientes para montar o poligono!\n");
        return 1;
	}
}

/*
 * FUNÇÃO PARA FINALIZAR O POLÍGONO SENDO DESENHADO
 */
void FinalizaPoligono(int statusObjeto, Poligonos * L_Poligono)
{
	// Se a lista de polígonos não foi criada ou está cheia, não é possível adicionar mais polígonos
	if (L_Poligono == NULL || L_Poligono->qtdPoligonos == MAX_POLIGONOS) {
		printf("Lista de poligonos nao foi criada ou esta cheia! Nao e possivel finalizar o poligono!\n");
	}
	// Finalizar polígono
	else {
		// Se for finalizar o polígono e ele tiver 3 ou mais lados
		if (statusObjeto == 1 && L_Poligono->poligonos[L_Poligono->qtdPoligonos].qtdLados >= 3) {
			// Calcular o centróide do polígono
			CentroidePoligono(L_Poligono->qtdPoligonos, L_Poligono);

			// Acrescentando um polígono a lista
			L_Poligono->qtdPoligonos++;
		}

		// Se não tem lados o suficiente para montar um polígono
        printf("Nao ha lados suficientes para montar o poligono!\n");
	}
}

/*
 * FUNÇÃO PARA CALCULAR O CENTRÓIDE DO POLÍGONO
 */
void CentroidePoligono(int chave, Poligonos * L_Poligono)
{
	float centroideX = 0.0, centroideY = 0.0, areaPoligono = 0.0, auxPoligono = 0.0;

	// Variáveis para iterar a lista de polígonos e fazer o cálculo do centroide do polígono
	PontoPoligono * inicialPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));
	PontoPoligono * finalPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	// Inicializando as variáveis com o primeiro ponto e com o próximo ponto, respectivamente inicialPontoPoligono e finalPontoPoligono
	inicialPontoPoligono = L_Poligono->poligonos[chave].inicial;
	finalPontoPoligono = L_Poligono->poligonos[chave].inicial->prox;

	// Se a quantidade de lados do polígono for 3
	if (L_Poligono->poligonos[chave].qtdLados == 3) {
		printf("entrou\n");
		// Laço para percorrer toda a lista de pontos do polígono
		// Utilizando também a fórmula do cálculo do centróide de um triângulo
		while (inicialPontoPoligono != NULL) {
			// Somatório para o cálculo do centróide
			// Sendo Cx = soma(xI)
			centroideX += inicialPontoPoligono->ponto.x;
			// Sendo Cy = soma(yI)
			centroideY += inicialPontoPoligono->ponto.y;

			// Passando para os próximos pontos da lista
			inicialPontoPoligono = inicialPontoPoligono->prox;
		}

		// Atribuindo o valor do cálculo do centróide a variável referente a ele na lista de polígonos
		L_Poligono->poligonos[chave].centroide.x = centroideX / 3;
		L_Poligono->poligonos[chave].centroide.y = centroideY / 3;
	}
	// Se a quantidade de lados do polígono for 4 ou mais
	else if (L_Poligono->poligonos[chave].qtdLados >= 4) {
		// Laço para percorrer toda a lista de pontos do polígono
		// Utilizando o finalPontoPoligono como condição de parada (já que ele está mais a frente na iteração)
		// Utilizando também a fórmula do cálculo do centróide de um polígono
		while (finalPontoPoligono != NULL) {
			// Variável auxiliar para o cálculo da área e do centróide do polígono
			// Realizando a subtração das variáveis que serão utilizadas nos cálculos necessários
			auxPoligono = (inicialPontoPoligono->ponto.x * finalPontoPoligono->ponto.y) - (finalPontoPoligono->ponto.x * inicialPontoPoligono->ponto.y);

			// Somatório para o cálculo do centróide
			// Sendo Cx = soma((xI + xImais1) * (xI * yImais1 - yI * xImais1)) / (6 * A)
			centroideX += (inicialPontoPoligono->ponto.x + finalPontoPoligono->ponto.x) * auxPoligono;
			// Sendo Cy = soma((yI + yImais1) * (xI * yImais1 - yI * xImais1)) / (6 * A)
			centroideY += (inicialPontoPoligono->ponto.y + finalPontoPoligono->ponto.y) * auxPoligono;

			// Sendo a área A = soma(xI * yImais1 - yI * xImais1) / 2, onde i é igual a quantidade de ponto de um polígono
			areaPoligono += auxPoligono;

			// Passando para os próximos pontos da lista
			inicialPontoPoligono = inicialPontoPoligono->prox;
			finalPontoPoligono = finalPontoPoligono->prox;
		}

		// Atribuindo a variável finalPontoPoligono com o último ponto que está na inicialPontoPoligono
		finalPontoPoligono = inicialPontoPoligono;
		inicialPontoPoligono = L_Poligono->poligonos[chave].inicial;

		// Atribuindo o valor para finalizar a soma do cálculo da área do polígono
		auxPoligono = (finalPontoPoligono->ponto.x * inicialPontoPoligono->ponto.y) - (inicialPontoPoligono->ponto.x * finalPontoPoligono->ponto.y);
		areaPoligono += auxPoligono;
		areaPoligono = areaPoligono / 2;

		// Atribuindo o valor para finalizar a soma do cálculo do centróide
		centroideX += (inicialPontoPoligono->ponto.x + finalPontoPoligono->ponto.x) * auxPoligono;
		centroideY += (inicialPontoPoligono->ponto.y + finalPontoPoligono->ponto.y) * auxPoligono;

		// Atribuindo o valor do cálculo do centróide a variável referente a ele na lista de polígonos
		L_Poligono->poligonos[chave].centroide.x = centroideX / (6 * areaPoligono);
		L_Poligono->poligonos[chave].centroide.y = centroideY / (6 * areaPoligono);
	}

	// Atribuindo a cor ao centróide
	L_Poligono->poligonos[chave].centroide.cor = violeta;

	printf("Centroide: (%.1f, %.1f)\n", L_Poligono->poligonos[chave].centroide.x, L_Poligono->poligonos[chave].centroide.y);
}

/*
 * FUNÇÃO PARA EXCLUIR UM POLÍGONO DA TELA
 */
int RemovePoligono(int chave, Poligonos * L_Poligono)
{
	// Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (L_Poligono == NULL || L_Poligono->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel excluir o poligono!\n");
		return 0;
	}
	// Remover um polígono
	else {
		// Laço para percorrer a lista de polígonos a partir da chave do polígono até o final da lista
        // Para não quebrar a integridade da lista
		for (int i = chave; i < L_Poligono->qtdPoligonos; i++) {
			L_Poligono->poligonos[i] = L_Poligono->poligonos[i + 1];
		}

		// Diminuir uma unidade da quantidade de polígonos
		L_Poligono->qtdPoligonos--;

		printf("Poligono excluido com sucesso!\n");
		return 1;
	}
}

/*
 * FUNÇÃO PARA SELECIONAR UM POLÍGONO DA TELA
 */
int SelecionaPoligono(float mouseX, float mouseY, Poligonos * L_Poligono)
{
    // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (L_Poligono == NULL || L_Poligono->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel selecionar o poligono!\n");
		return 0;
	}
	// Remover um polígono
	else {
		// Variável para manipular os dados da lista
		Poligono * poligonos = (Poligono *)malloc(sizeof(Poligono));

		// Laço para percorrer a lista de polígonos
		for (int i = 0; i < L_Poligono->qtdPoligonos; i++) {
			// Inicializar com os pontos do polígono sendo verificado
			poligonos[i] = L_Poligono->poligonos[i];

			// Se o ponto passado pertencer ao poligono, retornar a chave da lista de polígonos referente ao polígono
			if (VerificaPontoPoligono(mouseX, mouseY, &poligonos[i])) {
				return i;
			}
		}

		return 0;
	}
}

/*
 * FUNÇÃO PARA VERIFICAR SE O PONTO PERTENCE AO POLÍGONO
 */
bool VerificaPontoPoligono(float mouseX, float mouseY, Poligono * poligono)
{
	// Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (poligono == NULL) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel verificar o ponto no poligono!\n");
		return false;
	}
	// Verificar ponto no polígono
	else {
		// Variável para registrar caso o ponto faz parte do polígono
		bool dentroPoligono = false;

		// Variáveis para auxiliar a manipulação dos dados
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));
		PontoPoligono * anteriorPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

		// Inicializando as variáveis para manipulação
		atualPontoPoligono = poligono->inicial;
		anteriorPontoPoligono = NULL;

		// Laço para percorrer todos os pontos do polígono
		while (atualPontoPoligono != NULL) {
			// Conferindo se os pontos do polígono são maiores que os que foram passados
			// Os pontos do eixo Y devem estar em diferentes lados do eixo X (horizontal)
			// A expressão é usado para detectar se o raio horizontal se extende a partir do ponto passado com a
			// coordenada Y, intersectando com a borda definida pelos vertices (pontos) que compoem o polígono
			// E o ponto passado no eixo X for também menor que a coordenada X
			// Se ambas as condições forem verdadeiras, significa que o ponto está dentro do polígono

			// Checar se os raios se intersectam com a borda entre o ponto anterior e o atual
			if (anteriorPontoPoligono != NULL &&
				(anteriorPontoPoligono->ponto.y > mouseY) != (atualPontoPoligono->ponto.y > mouseY) &&
				(mouseX < (atualPontoPoligono->ponto.x - anteriorPontoPoligono->ponto.x) * (mouseY - anteriorPontoPoligono->ponto.y) / (atualPontoPoligono->ponto.y - anteriorPontoPoligono->ponto.y) + anteriorPontoPoligono->ponto.x)) {
				dentroPoligono = !dentroPoligono;
			}

			anteriorPontoPoligono = atualPontoPoligono;
			atualPontoPoligono = atualPontoPoligono->prox;
		}

		// Chechar se os raios intesectam com as bordas entre o último e primeiro pontos
		// Isso é necessário porque o laço não dá a volta para o início, então é necessa'rio pegar o último ponto e comparar com o primeiro
		if (poligono->qtdLados >= 2 &&
			(anteriorPontoPoligono->ponto.y > mouseY) != (poligono->inicial->ponto.y > mouseY) &&
			(mouseX < (poligono->inicial->ponto.x - anteriorPontoPoligono->ponto.x) * (mouseY - anteriorPontoPoligono->ponto.y) / (poligono->inicial->ponto.y - anteriorPontoPoligono->ponto.y) + anteriorPontoPoligono->ponto.x)) {
			dentroPoligono = !dentroPoligono;
		}

		return dentroPoligono;
	}
}

/*
 * FUNÇÃO PARA DESENHAR OS POLÍGONOS NA TELA
 */
void DesenhaPoligono(Poligonos * L_Poligono)
{
	// Criando uma variável ponto para auxílio na manipulação dos dados
	PontoPoligono * auxPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	glLineWidth(6.0);

	// Laço para percorrer toda a lista de polígonos
    	for (int i = 0; i < L_Poligono->qtdPoligonos; i++) {
		glBegin(GL_POLYGON);

		// Recebe os mesmos dados do ponto inicial para manipulação
		auxPontoPoligono = L_Poligono->poligonos[i].inicial;

		// Laço para percorrer toda a lista de pontos do polígono
		while (auxPontoPoligono != NULL) {
			// Imprimindo os valores e intensidades de cores RGB
			glColor3f(auxPontoPoligono->ponto.cor.Red, auxPontoPoligono->ponto.cor.Green, auxPontoPoligono->ponto.cor.Blue);
			// Posicionando o ponto na largura e altura corretas do mouse
			glVertex2f(auxPontoPoligono->ponto.x, auxPontoPoligono->ponto.y);

			// Iteração para o próximo ponto da lista
			auxPontoPoligono = auxPontoPoligono->prox;
		}

		glEnd();
    }
}
