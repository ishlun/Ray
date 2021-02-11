#ifndef INPUT_H
#define INPUT_H

//crossplatform getch
#ifndef _WIN32 //must work on linux and mac
#include<cstdlib>
#include<cstdio>

char ray_getch(){
    system("/bin/stty raw");
    char c = getchar();
    system("/bin/stty cooked");

    return  c;
}

#else
#include <conio.h>
#define ray_getch() getch()
#endif // ifndef _WIN32


// set cursor at start to avoid flickering
void gotoxy(short x, short y) {
#ifdef _WIN32
  COORD coord = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
  printf("%c[%d;%df", 0x1B, y, x);
#endif
}

#endif // INPUT_H
