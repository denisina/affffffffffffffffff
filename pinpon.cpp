#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <conio.h>



#define ARRIBA     72qq
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13


#define AZUL     0x009
#define AMARILLO 0x00E
#define ROJO     0x00C
#define VERDE    0x002
#define VERDE2   0x00B
#define MORADO   0x005
#define PLATA    0x00F


void inicia_libgame();
void gotoxy(int x, int y);
void OcultaCursor();
void pintar_marco();
void Color(int color);
void pausa(int x);
void pausa();
void gotoxy(int x, int y)  // funcion que posiciona el cursos en la coordenada (x,y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void OcultaCursor() {
    CONSOLE_CURSOR_INFO cci = {100, FALSE}; // El segundo miembro de la estructura indica si se muestra el cursor o no.

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Color(int color){
	static HANDLE hConsole;
    hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hConsole, color | (0 * 0x10 + 0x100) );
}

void pintar_marco()       // funcion que pinta los limites del escenario
{
     // Lineas horizontals
     for(int i=2; i < 78; i++){
        gotoxy (i, 3); printw ("%c", 205);
        gotoxy(i, 23); printw ("%c", 205);
     }
     //Lineas verticales
     for(int v=4; v < 23; v++){
        gotoxy (2,v);  printw ("%c", 186);
        gotoxy(77,v);  printw ("%c", 186);
     }
     // Esquinas
     gotoxy  (2,3);    printw ("%c", 201);
     gotoxy (2,23);    printw ("%c", 200);
     gotoxy (77,3);    printw ("%c", 187);
     gotoxy(77,23);    printw ("%c", 188);
}

void pausa(int x){
    Sleep(x);

}

class JUGADOR{
      int x,y;
public:
      JUGADOR (int _x , int _y); //constructor
      void pintar() const;
      void borrar() const;
      void mover_cpu(int _x, int _y, int _dx); //para poder jugar vs computadora
      void Y(int _y){y = y+_y; }
      int RY() {return y; }
      int RX() {return x; }
};

JUGADOR::JUGADOR(int _x , int _y) : x(_x), y(_y){} //asignar parametros
      void JUGADOR::pintar() const{
        gotoxy(x , y-1); printw("%c",219);
        gotoxy(x , y  ); printw("%c",219);
        gotoxy(x , y+1); printw("%c",219);
}

      void JUGADOR::borrar() const{
        gotoxy(x , y-1); printw(" ");
        gotoxy(x , y  ); printw(" ");
        gotoxy(x , y+1); printw(" ");
 }

 void JUGADOR::mover_cpu(int _x, int _y, int _dx){
     if( _x > 65 && _dx > 0){
         borrar();
         if(_y > y && y+1 < 22)
            y++;
         if(_y < y && y-1 > 4)
            y--;
         pintar();
     }
 }

class PELOTA{
      int x,y;
      int dx,dy;
public:
       PELOTA(int _x, int _y, int _dx, int _dy);
       void pintar () const;
       void borrar () const;
       void mover(JUGADOR A , JUGADOR B);
       void asign (int _x , int _y) { x=_x; y=_y; }
       int PX() {return x;}
       int PY() {return y;}
       int DX() {return dx;}
};

class MENU{
public:
     void pintar_portada(int &a);
};
PELOTA::PELOTA(int _x, int _y, int _dx, int _dy) : x(_x),y(_y), dx(_dx), dy(_dy) {}

  void PELOTA::pintar() const{
      gotoxy(x,y); printw("%c",234);
  }
  void PELOTA::borrar() const{
      gotoxy(x,y); printw(" ");

}

  void PELOTA::mover(JUGADOR A, JUGADOR B){
      borrar();
      x=x+dx; y=y+dy;
      pintar();
      if (x + dx == 3 || x + dx == 76){ //haciendo rebotar la pelota con el mapa
          borrar();
          asign(38,14);
          dx = -dx;
      }
      if (y + dy == 3 || y + dy == 23)
          dy = -dy;

      if(x + dx == A.RX() && y > A.RY() - 2 && y <= A.RY() + 2) {dx = - dx;} //para que rebote con los jugadores
      if(x + dx == B.RX() && y > B.RY() - 2 && y <= B.RY() + 2) {dx = - dx;}
  }

  void MENU::pintar_portada(int &a){
  char portada[18][71] =
    {
    "                        OO   OO                                       ",
    "     aaaaaaaas          OOO OOO                                       ",
    "   aaaaaaaaaaass         OOOOO                1. MULTIJUGADOR         ",
    "   aa       aass          OOO                 2. UN SOLO JUGADOR      ",
    "   aa       aass           O                                          ",
    "   aa       aass                                                      ",
    "   aaaaaaaaaass                                                       ",
    "   aaaaaaaaas               aaasaaas                                  ",
    "   aass                     aaasaaaasa                                ",
    "   aass   aaas  aaas   aas  aaas    aas    aaas     aaas   aas        ",
    "   aass   aaas  aasas  aas  aaas    aas  aa    as   aasas  aas        ",
    "   aass   aaas  aas as aas  aaas    aas aaa    aas  aas as aas        ",
    "   aass   aaas  aas  asaas  aaasaaaaas  aaa    aas  aas  asaas        ",
    "   aass   aaas  aas   aaas  aaas        aaa    aas  aas   aaas        ",
    "   aass   aaas  aas    aas  aaas         aa    as   aas    aas        ",
    "   aass   aaas  aas    aas  aaas           aaas     aas    aas        ",

    };

  for (int i=0;i<16;i++){
      for(int j=0;j<70;j++){
           gotoxy(j+5,i+5);   //para centrarlo en pantalla
           printw("%c",portada[i][j]);
      }
  }
     a = getch();

  for (int i=0;i<16;i++){
      for(int j=0;j<70;j++){
           gotoxy(j+5,i+5);   //para centrarlo en pantalla
           printw(" ");
      }
  }


}
int main(){
    int cont = 0, op_juego;
    OcultaCursor();
    pintar_marco();

    MENU M; M.pintar_portada(op_juego);
    JUGADOR A(6,15); A.pintar();
    JUGADOR B(74,15); B.pintar();

    PELOTA P(38,14,1,1);

    char tecla;

    while(1){

        if(kbhit()){
        A.borrar(); B.borrar();
            tecla = getch();
            if(tecla == 'q' && A.RY()>5) A.Y(-1);

                 else if(tecla == 'a' && A.RY()<21) A.Y(1);

            if(op_juego == '1'){

                 if(tecla == 'o' && A.RY()>5) B.Y(-1);

                 else if(tecla == 'l' && A.RY()<21) B.Y(1);
            }
        A.pintar(); B.pintar();
        }
        if(op_juego == '2' && !cont) B.mover_cpu(P.PX(),P.PY(),P.DX());
        if(!cont++) P.mover(A,B); //para mover la pelota mas lento
        if(cont > 5) cont =0;
        pausa(10);

    }
    return 0;

}
