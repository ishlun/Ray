#ifndef INPUT_H
#define INPUT_H


#define RAW 1
#define COOKED 0

#ifndef _WIN32 //must work on linux and mac

#include <cstdlib>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define ray_getch() getchar()

void changemode(int dir)
{
  static struct termios oldt, newt;

  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);

  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);

}


#else
#include <conio.h>
#define ray_getch() getch()

#define disable_raw_mode(x) /*nop*/
#define enable_raw_mode(x)  /*nop*/
#endif // ifndef _WIN32


// set cursor at start to avoid flickering
void gotoxy(short x, short y) {
#ifdef _WIN32
  #include <windows.h>
  COORD coord = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
  printf("%c[%d;%df", 0x1B, y, x);
#endif
}

#endif // INPUT_H
