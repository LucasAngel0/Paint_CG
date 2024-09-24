# Construção do Paint ultilizando OpenGL e Glut para a cadeira de Computação Gráfica

Este projeto é um programa em C que permite a criação, manipulação e visualização de objetos geométricos, incluindo pontos, segmentos de reta e polígonos, utilizando a biblioteca OpenGL e GLUT para renderização gráfica.

## Funcionalidades
  - Criar Objetos: Permite criar pontos, segmentos de reta e polígonos na tela utilizando o mouse.
  - Selecionar Objetos: Seleciona objetos criados para manipulação.
  - Salvar e Carregar Objetos: Os objetos podem ser salvos em arquivos de texto 
   e carregados posteriormente.

## Manipulação de Objetos:
  - Escalar objetos (aumentar ou diminuir)
  - Rotacionar objetos
  - Deletar objetos
  - Finalizar a criação de polígonos
  - Refletir o Objeto em y e em relação a origem.
  - Cisalhar Poligono

- Criar e manipular pontos, segmentos de reta e polígonos.
- Salvar e carregar objetos de arquivos.
- Selecionar objetos com o mouse.
- Manipulação básica de objetos (exclusão, escalonamento e rotação) através do teclado.

## Instruções para Execução do Projeto
Este Projeto foi Criado utilizando o Ubuntu 24.02 lts então para iniciar o Projeto, deverá abrir um terminal dentro da pasta do Arquivo e colocar o seguinte comando:
```bash
g++ main.c  ponto.c reta.c poligono.c matriz.c -o main -lglut -lGLU -lGL
```
Para roda o programa basta inicializar o Arquivo Main gerado na pasta do arquivo do Projeto

## Instrução Para Uso
### Menu de Contexto

  #### Acesse o menu principal clicando com o botão direito do mouse.
  - O menu permite criar, selecionar, salvar, carregar objetos e sair do programa.
  #### Interação com o Mouse
  - Clique com o botão esquerdo para adicionar ou selecionar objetos.
   Os objetos são criados ou selecionados dependendo da opção ativa no menu.

### Controles 
Com o objeto selecionado de acordo com o menu de contexto aperte as seguintes teclas(maiusculas ou minusculas)  para executar a funcionalidade requerida 
- F: Finaliza o desenho do polígono.
- D: Deleta o objeto selecionado.
- L: Aumenta o objeto selecionado.(exceto o Ponto)
- K: Diminui o objeto selecionado para baixo.
- R: Rotaciona o objeto selecionado em sentido horário.(o Ponto é rotacionado  ao redor da origem)
- E: Rotaciona o objeto selecionado em sentido horário.(o Ponto é rotacionado  ao redor da origem)
- M: Reflete o objeto como base na horigem
- N: Reflete o objeto com base o Eixo Y
- C: Cisalha o poligono em x
- X :
  


