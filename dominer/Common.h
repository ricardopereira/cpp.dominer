#include <string>

#ifndef __COMMON_H__
#define __COMMON_H__

#define BLOCKSIZE 5
#define TEXTSIZE 8
#define SCREENBUFFERSIZE 7
#define SCREENCOLUMNS 80
#define SCREENROWS 50
#define MESSAGETIME 2000
#define MODEDEBUG 0

#define GAMEEASY 21
#define GAMENORMAL 41
#define GAMEHARD 61
#define MENULAST 5

#define MINERENERGY 50
#define MINERMONEY 50
#define MINERLIFES 2
#define MINERLADDERS 10
#define MINERBEAMS 5
#define MINERPARACHUTES 2
#define MINERDINAMITES 0
#define MINERSUPER 0

#define BAGNORMAL 15
#define BAGPRO 25
#define BAGMASTER 35

#define LIGHTNORMAL 3
#define LIGHTPRO 5
#define LIGHTMASTER 7

#define PICKERNORMAL 1
#define PICKERPRO 2
#define PICKERMASTER 4

#define LADDERPACK 15
#define BEAMPACK 15
#define FALLTICK 3

#define PRETO 0
#define AZUL 1
#define VERDE 2
#define CYAN 3
#define VERMELHO 4
#define ROXO 5
#define AMARELO 6
#define BRANCO 7
#define CINZENTO 8
#define AZUL_CLARO 9
#define VERDE_CLARO 10
#define CYAN_CLARO 11
#define VERMELHO_CLARO 12
#define COR_DE_ROSA 13
#define AMARELO_CLARO 14
#define BRANCO_CLARO 15

#define ESQUERDA 1
#define DIREITA 2
#define CIMA 3
#define BAIXO 4
#define ENTER 13
#define ESCAPE 27
#define ESPACO 32

#define DEFAULTCOLOR BRANCO


// Utils

int isEqual(const std::string& a, const std::string& b);

#endif