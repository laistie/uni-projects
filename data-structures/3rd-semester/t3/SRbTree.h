#ifndef _SRB_Tree_H
#define _SRB_Tree_H

#include "List.h"

/* Uma árvore RubroNegra espacial (SRbTree) é uma árvore Rubro-Negra que associa uma coordenada no plano (âncora) a uma dada informação e também define o menor retângulo envolvente (minimum bounding box -- MBB) que delimita tal informação. Tipicamente a âncora está dentro (incluindo fronteira) da MBB. O MBB é definido por 2 pontos (x1,y1) e (x2,y2), diagonal que determina o retângulo envolvente: x1 <= x2 e y1 <= y2.
A chave de busca é a coordenada da âncora.
A ordem da chave de busca é definido como a seguir: sejam ch1 e ch2 duas chaves de busca, define-se que ch1 < ch2, se:
    ch1.x < ch2.x 
    OU
    ch1.x == ch2.x  AND ch1.y < ch2.y
caso contrário, ch1 == ch2

Associa-se uma precisão epsilon à árvore. Esta precisão é usada para determinar quando dois números reais da chave de busca devem ser considerados como iguais. Assim v == w, se |v - w| <= epsilon.

Algumas operações de busca retornam o nó da árvore onde uma determinada informação está armazenada. Os dados referentes a este nó podem ser obtidos por outras operações, desde que estes nós continuem válidos. Qualquer remoção posterior faz com que nós retornados previamente devam ser considerados inválidos. */

typedef void* SRbTree; 
typedef void* Info;
typedef void* Node;

typedef void (*FvisitaNo) (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);
/* Processa a informacao i associada a um nó da árvore, cuja âncora é o ponto (x,y), bounding box (mbbX1,mbbY1) -- (mbbX2,mbbY2). O parâmetro aux aponta para conjunto de dados (provavelmente um registro) que são compartilhados entre as sucessivas invocações a esta função. */

SRbTree createSRb(double epsilon);
/* Retorna uma árvore vazia, com precisão epsilon. Retorna NULL caso não tenha conseguido criar a árvore. */

Node insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info);
/* Insere a informação info na árvore t, associada a coordenada (x,y), sendo delimitada pelo retângulo definido pela diagonal (mbbX1,mbbY1) -- (mbbX2,mbbY2). Retorna o nó onde foi inserida a informação; NULL, caso já exista informação com a mesma chave (veja acima) inserida. */

Node insertBbSRb(SRbTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info);
/* Equivalente à insertSRb(t, mbbX1, mbbY1,  mbbX1, mbbY1,  mbbX2, mbbY2,  info) */

void getBbPartSRb(SRbTree t, double x, double y, double w, double h, Lista resultado);
/* Insere na lista resultado os nós da árvore (Node) que seu retângulo envolvente possua alguma intersecção com a região retangular de âncora (x,y), largura w e altura h. */

void getBbSRb(SRbTree t, double x, double y, double w, double h, Lista resultado);
/* Similar à getBbPartSRb, porém seleciona apenas os nós cujos retângulos envolventes estejam inteiramente dentro da região. */

Info getInfoSRb(SRbTree t, Node n, double* xa, double* ya, double* mbbX1, double* mbbY1, double* mbbX2, double* mbbY2);
/* Retorna a informação associada ao nó n, sua âncora (xa,ya) e o retângulo envolvente (mbbX1,mbbY1) -- (mbbX2,mbbY2). Este nó deve ser um nó válido (veja acima). */

Node getNodeSRb(SRbTree t, double xa, double ya, double* mbbX1, double* mbbY1, double* mbbX2, double* mbbY2);
/* Retorna o nó da árvore associado à âncora (xa,ya) e o retângulo envolvente; NULL, se tal âncora nao existir. */

void updateInfoSRb(SRbTree t, Node n, Info i);
/* Altera a informação associada ao nó n que deve ser existente e válido. A âncora e o MBB deste no não são alterados, portanto, a informação deve permanecer compatível a estes dois valores. */

Info removeSRb(SRbTree t,double xa, double ya, double* mbbX1, double* mbbY1, double* mbbX2, double* mbbY2);
/* Remove o nó da árvore cuja chave é a coordenada (xa,ya). Qualquer nó da árvore retornado por operações anteriores deve ser considerado inválido. Retorna a informação que estava associada a tal nó (ou NULL, se não encontrado), bem como o seu retângulo envolvente. */

void printSRb(SRbTree t, char* nomeArq);
/* "Desenha" (no formato dot) a árvore no arquivo nomeArq. Veja: https://graphviz.org/ */


/* As próximas operações percorrem a árvore em largura/profundidade/simetrico. Invoca a função fVisita (veja descrição acima) em cada nó visitado. */

void percursoLargura(SRbTree t, FvisitaNo fVisita, void* aux);

void percursoSimetrico(SRbTree t, FvisitaNo fVisita, void* aux);

void percursoProfundidade(SRbTree t, FvisitaNo fVisita, void* aux);


void killSRb(SRbTree t);
/* Desaloca todos os recursos usados pela arvore t. */

#endif