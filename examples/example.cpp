
/* Funcoes da consola. Dez 2010 */

/* Pequenas correcoes + função main nova. Nov. 2013 */



#include <iostream>
#include "example.h"

#include "Consola.h"  // Isto é uma bibilioteca desenvolvida para POO
                      // Não é standard e não pretende ser


using namespace std;

// exemplo. serve de explicacao
int example() {
	Consola c;  // Este objecto dá acesso à funcionalidade da consola. Basta um por programa
	
	c.setTextColor(c.VERDE_CLARO);
	c.gotoxy(10,10);
	cout << "Este programa serve para demonstrar o que se pode fazer com";
	c.gotoxy(10,11);
	cout << "a biblioteca \"consola\" de POO";
	c.gotoxy(10,13);
	cout << "Convem ver o codigo disto antes de colocar questoes";
	c.gotoxy(10,15);
	cout << "Primeiro passo: redimensionar o ecran";
	c.gotoxy(10,17);
	cout << "Carrega numa tecla para continuar";

	c.getch();

	c.setTextSize(8,8);
	c.setScreenSize(50,80);  // linhas colunas. valores grandes pode nao dar
	c.setBackgroundColor(c.AZUL);  // favor consultar o .h para ver as constantes
	c.setTextColor(c.AMARELO_CLARO);
	c.clrscr();  // reparar no c.   trata-se de funções da biblioteca de COnsolda (para POO)
	             // e não das funções com o mesmo nome da cionio.h do antigo turbo-c

	cout << "\n\n\nEsta parte do programa demostra que se pode ler uma tecla sem esperar pelo enter\n";
	cout << "Cada tecla tem um codigo associado.\n";
	cout << "Teclas especiais (Fxx) tem uma sequencia de dois codigos\n";
	cout << "Carrega em teclas. \"Espaco\" para sair\n";

	char tecla;

	while (1) {
		tecla = c.getch();  // reparar em c. -> getch da biblioteca de POO, não é a do conio.h
		cout << (char) tecla << " = " << (int) tecla << "\n";
		if (tecla == ' ')
			break;
	}

	c.setTextColor(c.BRANCO_CLARO);
	cout << "\nAgora experimenta teclas de direccao.";
	cout << "\nRepara no asterisco no centro do ecran.";
	cout << "\n\"escape\" para sair";

	int x = 39, y = 24;
	c.gotoxy(x,y);
	cout << '*';
	while (1) {
		tecla = c.getch();
		if (tecla == c.ESCAPE) break;
		if ( (tecla != c.ESQUERDA) && (tecla != c.DIREITA) &&
		     (tecla != c.CIMA)     && (tecla != c.BAIXO) ) continue;

		//c.setTextColor(c.AZUL);
		c.gotoxy(x,y);
		cout << ' ';

		if (tecla == c.ESQUERDA) x--;
		if (tecla == c.DIREITA) x++;
		if (tecla == c.CIMA) y--;
		if (tecla == c.BAIXO) y++;
		c.gotoxy(x,y);
		cout << '*';
		// TPC: validar os limites da consola
	}
	// RGB -> macro. valores entre 0 e 255 
	c.drawLine(0, 0, 300, 200, RGB (255,0,0));
	c.drawCircle(150, 130, 105, RGB (0,0,255),1);
	c.drawCircle(200, 130, 75, RGB (50,255,50),0);
	
	c.gotoxy(0,34);
	c.setTextColor(c.AMARELO_CLARO);
	cout << "Desenho de pixels e possivel mas nao e suportado\n";
	cout << "Sao disponibilizadas algumas funcoes para esse efeito";
	cout << "\nmas o resultado nao fica \"memorizado\" na janela\n";
	cout << "(depois em SO2 resove-se isso)\n";
	cout << "\n\nEscolhendo com cuidado as coordenadas pode-se fazer os desenhos coincidir\n";
	cout << "com os limites dos caracteres\n";
	cout << "\nCaracteres com a mesma altura que a largura melhoram a apresentacao\n";
	cout << "\n\ncarrega numa tecla qualquer";
	c.getch();

	c.setBackgroundColor(c.CINZENTO);
	c.setTextColor(c.BRANCO_CLARO);
	c.clrscr();  // reparar no c.   trata-se de funções da biblioteca de Consolda (para POO)
	c.gotoxy(10,4);
	cout << "Tabela com caracteres.";
	c.gotoxy(10,5);
	cout <<	"Reparar que muitos podem ser usados para desenhar molduras e afins";
	c.gotoxy(10,6);
	cout <<	"Outros podem ser como tonalidades";

	for (int i=0; i< 16; i++) {
		for (int j=0; j<16; j++) {
			c.gotoxy(20+j*3, 9+i*2);
			cout << (char) (i*16+j);
		}
	}

	c.setTextColor(c.VERMELHO);
	c.gotoxy(10, 40);
	cout << "\n\tNotar os seguintes\n\n";
	cout << "\t" << (char) 176 << ' ' << (char) 177 << ' ' << (char) 178 << '\n';
	cout << "\n\t";
	cout << (char) 179 << ' ' << (char) 180 << ' ';
	for (int i=192; i<198; i++) cout << (char) i << ' ';
	for (int i=200; i<207; i++) cout << (char) i << ' ';
	cout << "\n\n\tcarrega numa tecla qualquer para ver exemplos";
	c.getch();
	
	c.setTextColor(c.PRETO);
	c.setBackgroundColor(c.BRANCO_CLARO);
	c.clrscr();

	c.gotoxy(20,20);
	cout << (char) 218 << (char) 196 << (char) 196 << (char) 196 << (char) 191 << '\n';
	c.gotoxy(20,21);
	cout << (char) 179 << (char) 176 << (char) 176 << (char) 176 << (char) 179 << '\n';
	c.gotoxy(20,22);
	cout << (char) 179 << (char) 176 << (char) 176 << (char) 176 << (char) 179 << '\n';
	c.gotoxy(20,23);
	cout << (char) 179 << (char) 176 << (char) 176 << (char) 176 << (char) 179 << '\n';
	c.gotoxy(20,24);
	cout << (char) 192 << (char) 196 << (char) 196 << (char) 196 << (char) 217 << '\n';


	c.gotoxy(25,20);
	cout << (char) 218 << (char) 196 << (char) 196 << (char) 196 << (char) 191 << '\n';
	c.gotoxy(25,21);
	cout << (char) 179 << (char) 177 << (char) 177 << (char) 177 << (char) 179 << '\n';
	c.gotoxy(25,22);
	cout << (char) 179 << (char) 177 << (char) 177 << (char) 177 << (char) 179 << '\n';
	c.gotoxy(25,23);
	cout << (char) 179 << (char) 177 << (char) 177 << (char) 177 << (char) 179 << '\n';
	c.gotoxy(25,24);
	cout << (char) 192 << (char) 196 << (char) 196 << (char) 196 << (char) 217 << '\n';


	c.gotoxy(30,20);
	cout << (char) 218 << (char) 196 << (char) 196 << (char) 196 << (char) 191 << '\n';
	c.gotoxy(30,21);
	cout << (char) 179 << (char) 178 << (char) 178 << (char) 178 << (char) 179 << '\n';
	c.gotoxy(30,22);
	cout << (char) 179 << (char) 178 << (char) 178 << (char) 178 << (char) 179 << '\n';
	c.gotoxy(30,23);
	cout << (char) 179 << (char) 178 << (char) 178 << (char) 178 << (char) 179 << '\n';
	c.gotoxy(30,24);
	cout << (char) 192 << (char) 196 << (char) 196 << (char) 196 << (char) 217 << '\n';

	c.gotoxy(35,20);
	cout << (char) 218 << (char) 196 << (char) 196 << (char) 196 << (char) 191 << '\n';
	c.gotoxy(35,21);
	cout << (char) 179 << (char) 219 << (char) 219 << (char) 219 << (char) 179 << '\n';
	c.gotoxy(35,22);
	cout << (char) 179 << (char) 219 << (char) 219 << (char) 219 << (char) 179 << '\n';
	c.gotoxy(35,23);
	cout << (char) 179 << (char) 219 << (char) 219 << (char) 219 << (char) 179 << '\n';
	c.gotoxy(35,24);
	cout << (char) 192 << (char) 196 << (char) 196 << (char) 196 << (char) 217 << '\n';

	c.setTextColor(c.VERDE);
	cout << "\n\n\t\tAgora e uma questao de criatividade";
	c.setTextColor(c.PRETO);
	cout << "\n\n\t\tCarrega numa tecla qualquer";
	c.getch();
	return 0;
}

