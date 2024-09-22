#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

// Variaveis de Tela
static int tela;
static int Principal;
static int CriacaoDeObjeto;
static int SelecionarObjetos;
static int SalvaObjeto;
static int CarregaObjeto;
static int menu = 0;

//VARIÁVEIS PARA PONTO, RETA E POLIGONO

int key = -1;        // Guarda a chave da lista para manipulação dos objetos (desenhando: > -1; finalizado: -1)
int EstadoDoObjeto = -1; // Indica se o objeto ainda está sendo desenhado (desenhando: 1; finalizado: -1)

//DIMENSÕES DA TELA
float largura = 400;   // Largura fixa da tela (metade dos pixels que formam a tela: eixo x)
float altura = 300;    // Altura fixa da tela (metade dos pixels que formam a tela: eixo y)

// VARIÁVEIS DO MOUSE
float mouseX;          // Posição do mouse no eixo x
float mouseY;          // Posição do mouse no eixo y
int EstadoDoMouse = 0;   // Indica se o mouse foi clicado ou não (não foi clicado: 0; clicado: 1)

//VARIÁVEIS DAS LISTAS DE OBJETOS PARA SEREM MANIPULADOS
Pontos * L_Pontos = NULL;
Retas * L_Retas = NULL;
Poligonos * L_Poligonos = NULL;

// LISTA DE FUNÇÕES
int main(int argc, char ** argv);
void telaInicial();
void Criamenu();
void selecionarOpcao(int opcaoSelecionada);

void funcoesMouse(int botaoMouse, int statusMouse, int x, int y);
void Movimentacao(int x, int y);
void Teclado(unsigned char key, int x, int y);   



//TELA INICIAL
void telaInicial()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenhar elementos na tela
    DesenhaPonto(L_Pontos);
    desenharRetas(L_Retas);
    DesenhaPoligono(L_Poligonos);

    glutSwapBuffers();
}

//FUNÇÃO PARA DEFINIR AS OPÇÕES DO MENU
void Criamenu()
{
    // Opção de criar ponto, segmento de reta ou poligono
    CriacaoDeObjeto = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Segmento de Reta", 2);
    glutAddMenuEntry("Poligono", 3);

    // Opção de selecionar um ponto, segmento de reta ou poligono
    SelecionarObjetos = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Ponto", 4);
    glutAddMenuEntry("Segmento de Reta", 5);
    glutAddMenuEntry("Poligono", 6);

    // Opção de salvar os pontos, segmentos de reta ou poligonos
    SalvaObjeto = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Pontos", 7);
    glutAddMenuEntry("Segmentos de Reta", 8);
    glutAddMenuEntry("Poligonos", 9);

    // Opção de carregar os pontos, segmentos de reta ou poligonos
    CarregaObjeto = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Pontos", 10);
    glutAddMenuEntry("Segmentos de Reta", 11);
    glutAddMenuEntry("Poligonos", 12);

    // Menu principal para mostrar opções
    Principal = glutCreateMenu(selecionarOpcao);
    glutAddSubMenu("Criar", CriacaoDeObjeto);
    glutAddSubMenu("Selecionar", SelecionarObjetos);
    glutAddMenuEntry("Salvar Objetos", 7);
    glutAddMenuEntry("Carregar objetos", 8);
    glutAddMenuEntry("Cancelar", 0);
    glutAddMenuEntry("Sair", -1);

    // Utilizar o botão direito do mouse para acionar o menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void selecionarOpcao(int opcaoSelecionada)
{
    // Se o usuário escolheu "Sair" encerra e finaliza a tela
    if (opcaoSelecionada == -1) {
        glutDestroyWindow(tela);
        exit(0);
    }
    // Caso o usuário tenha selecionado alguma outra opção
    else {
        // Reinicializa todas as variáveis para o valor inicial (valor que tem enquanto não estão sendo manipuladas)
        key = -1;
        EstadoDoMouse = 0;
        EstadoDoObjeto = -1;
        menu = opcaoSelecionada;
        printf("Opcao selecionada: %d\n", menu);
    }

    glutPostRedisplay();
}

// FUNÇÃO PARA DEFINIR O USO DO MOUSE PELO USUÁRIO

void funcoesMouse(int botaoMouse, int statusMouse, int x, int y)
{
    // Variáveis para auxiliar o salvamento e o carregamento dos objetos na tela
    const char * ArquivoPontos = "arquivos/pontos/pontos.txt";
    const char * ArquivoRetas = "arquivos/retas/retas.txt";
    const char * ArquivoPoligonos = "arquivos/poligonos/poligonos.txt";

    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    // Transladar objetos selecionados da tela
    if (botaoMouse == GLUT_LEFT_BUTTON && statusMouse == GLUT_DOWN) {
        printf("mouseX: %.1f, mouseY: %.1f\n", mouseX, mouseY);

        ////////// Opções: Criar
        // Se a opção for 1 (Criar ponto)
        if (menu == 1) {
            // Adicionar ponto a lista
            AddPonto(mouseX, mouseY, L_Pontos);
            ImprimePontos(L_Pontos);
        }
        // Se a opção for 2 (Criar segmento de reta)
        else if (menu == 2) {
            // Adicionar reta a lista
            EstadoDoObjeto = Add_Retas(mouseX, mouseY, EstadoDoObjeto, L_Retas);
            ImprimeL_Retas(L_Retas);
        }
        // Se a opção for 3 (Criar polígono)
        else if (menu == 3) {
            // Adicionar polígono a lista
            EstadoDoObjeto = AddPoligono(mouseX, mouseY, EstadoDoObjeto, L_Poligonos);
            ImprimeL_Poligonos(L_Poligonos);
        }

        ////////// Opção: Selecionar
        // Se a opção for 4 (Selecionar ponto)
        else if (menu == 4) {
            // Retorna a chave da lista onde o ponto que foi selecionado com o mouse está
            key = SelecionaPonto(mouseX, mouseY, L_Pontos);
            printf("Chave selecionada: %d\n", key);
        }
        // Se a opção for 5 (Selecionar segmento de reta)
        else if (menu == 5) {
            // Retorna a chave da lista onde a reta que foi selecionada com o mouse está
            key = Seleciona_Reta(mouseX, mouseY, L_Retas);
            printf("Chave selecionada: %d\n", key);
        }
        // Se a opção for 6 (Selecionar polígono)
        else if (menu == 6) {
            // Retorna a chave da lista onde o polígono que foi selecionado com o mouse está
            key = SelecionaPoligono(mouseX, mouseY, L_Poligonos);
            printf("Chave selecionada: %d\n", key);
        }

        ////////// Opção: Salvar objetos
        // Se a opção for 7 (Salvar pontos)
        else if (menu == 7) {
            // Salvar objetos
            SalvaPontos("pontos.txt", L_Pontos);
            ImprimePontos(L_Pontos);
            SalvaL_Retas("retas.txt", L_Retas);
            ImprimeL_Retas(L_Retas);
            SalvaPoligonos("poligonos.txt", L_Poligonos);
            ImprimeL_Poligonos(L_Poligonos);
        }
        // Se a opção for 8 (Salvar retas)
        else if (menu == 8) {  
            // Carrega Objetos        
            Pontos listaPontosArquivo;                                // Variável para auxiliar o carregamento dos objetos na tela
            CarregaPontos("pontos.txt", &listaPontosArquivo);   // Carregar as variáveis com os dados do arquivo
            L_Pontos = &listaPontosArquivo;                             // Passar os dados das variáveis para a lista
            ImprimePontos(L_Pontos);                              // Imprimir a lista de pontos
            Retas listaRetasArquivo;                               // Variável para auxiliar o carregamento dos objetos na tela
            CarregaL_Retas("retas.txt", &listaRetasArquivo);   // Carregar as variáveis com os dados do arquivo
            L_Retas = &listaRetasArquivo;                            // Passar os dados das variáveis para a lista
            ImprimeL_Retas(L_Retas);                             // Imprimir a lista de retas 
            Poligonos listaPoligonosArquivo;                                   // Variáveis para auxiliar o carregamento dos objetos na tela
            CarregaPoligonos("poligonos.txt", &listaPoligonosArquivo);   // Carregar as variáveis com os dados do arquivo
            L_Poligonos = &listaPoligonosArquivo;                                // Passar os dados das variáveis para a lista
            ImprimeL_Poligonos(L_Poligonos);                                 // Imprimir a lista de polígonos
   
        }
        // Se a opção for 9 (Salvar polígonos)
        else if (menu == 9) {
            // Salvar no arquivo os polígonos desenhados da tela
            SalvaPoligonos(ArquivoPoligonos, L_Poligonos);
            ImprimeL_Poligonos(L_Poligonos);
        }

        ////////// Opção: Carregar objetos
        // Se a opção for 10 (Carregar pontos)
        else if (menu == 10) {

        }
        // Se a opção for 11 (Carregar retas)
        else if (menu == 11) {
            Retas listaRetasArquivo;                               // Variável para auxiliar o carregamento dos objetos na tela
            CarregaL_Retas("retas.txt", &listaRetasArquivo);   // Carregar as variáveis com os dados do arquivo
            L_Retas = &listaRetasArquivo;                            // Passar os dados das variáveis para a lista
            ImprimeL_Retas(L_Retas);                             // Imprimir a lista de retas
        }
        // Se a opção for 12 (Carregar polígonos)
        else if (menu == 12) {
            Poligonos listaPoligonosArquivo;                                   // Variáveis para auxiliar o carregamento dos objetos na tela
            CarregaPoligonos(ArquivoPoligonos, &listaPoligonosArquivo);   // Carregar as variáveis com os dados do arquivo
            L_Poligonos = &listaPoligonosArquivo;                                // Passar os dados das variáveis para a lista
            ImprimeL_Poligonos(L_Poligonos);                                 // Imprimir a lista de polígonos
        }

        ////////// Opção: Sair
        else if (menu == -1) {
            // Liberando espaço da memória antes de sair do programa
            ExcluiPontos(L_Pontos);
            ExcluiL_Retas(L_Retas);
            ExcluiPoligonos(L_Poligonos);
        }
    }

    glutPostRedisplay();
}

void Teclado(unsigned char key, int x, int y)
{
    float corte = 0.5;
    float angulo = 45.0;
    float escala = 1.05;

    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    switch (key) {

        // Excluir objetos selecionados da tela (D - Delete)
        case 'D':
        case 'd':
            ////////// Excluir ponto
            // Se um ponto está na opção "Selecionar" e a chave contém um valor diferente de -1
            if (menu == 4 && key != -1) {
                key = SelecionaPonto(mouseX, mouseY, L_Pontos);
                if (RemovePonto(key, L_Pontos)) {
                    ImprimePontos(L_Pontos);
                    key = -1;
                }
            }

            ////////// Excluir reta
            // Se uma reta está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (menu == 5 && key != -1) {
                key = Seleciona_Reta(mouseX, mouseY, L_Retas);
                if (RemoveReta(key, L_Retas)) {
                    ImprimeL_Retas(L_Retas);
                    key = -1;
                }
            }

            ////////// Excluir polígono
            // Se um polígono está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (menu == 6 && key != -1) {
                if (RemovePoligono(key, L_Poligonos)) {
                    ImprimeL_Poligonos(L_Poligonos);
                    key = -1;
                }
            }

            break;

        // Finalizar o polígono (F - Finish)
        case 'F':
        case 'f':
            if (menu == 3 && EstadoDoObjeto == 1) {
                // Finalizar o desenho do polígono
                FinalizaPoligono(EstadoDoObjeto, L_Poligonos);

                // finalizarPoligono(statusObjeto, listaPoligonos);
                ImprimeL_Poligonos(L_Poligonos);

                // Mudar status do objeto para ele ser finalizado
                EstadoDoObjeto = -1;
            }

            break;        
    }

    glutPostRedisplay();
}


//INICIAR O SISTEMA
int main (int argc, char ** argv)
{
    // Inicializando o OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    tela = glutCreateWindow("Paint - Computacao Grafica");

    // Mostrar menu
    Criamenu();

    // Inicialização das variáveis das listas de objetos manipulados
    L_Pontos = CriaL_Pontos();
    L_Retas = CriaL_Retas();
    L_Poligonos = CriaL_Poligonos();

    glClearColor(1.0, 1.0, 1.0, 0.0); // Cor do background
    glMatrixMode(GL_PROJECTION);
    glOrtho(-largura, largura, -altura, altura, -1.0f, 1.0f);

    glutMouseFunc(funcoesMouse);         // Chamadas quando um botão do mouse é acionado
    glutDisplayFunc(telaInicial);        // Para mostrar elementos na tela rederizando os objetos
    glutKeyboardFunc(Teclado); 
    glutMainLoop();

    return 0;
}