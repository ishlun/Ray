#include <cstring>
#include <iostream>
#include <cmath>

#include "functions.h"
#include "input.h"
#include "ball.h"
#include "camera.h"

using namespace std;

// screen dimensions
#define WIDTH 800
#define HEIGHT 600

// width and height of each character in pixels
const int dW = 4, dH = 8;

char palette[] = " .:;~=#OB8%&";

void init_screen();

int main() {
    //input setup(for linux and mac)
    changemode(RAW);

    // ball declaration:
    ball balls[4];
    balls[0].center[0] = 0;
    balls[0].center[1] = 0;
    balls[0].center[2] = 0;
    balls[0].radius = 1;
    balls[0].color = 1;
    balls[0].coeff = 0.5;

    balls[1].center[0] = 2;
    balls[1].center[1] = 0;
    balls[1].center[2] = 0;
    balls[1].radius = 0.8;
    balls[1].color = 1;
    balls[1].coeff = 0.7;

    balls[2].center[0] = 4;
    balls[2].center[1] = 0;
    balls[2].center[2] = 0;
    balls[2].radius = 0.5;
    balls[2].color = 1;
    balls[2].coeff = 0.7;
    //it is moon
    balls[3].center[0] = 0;
    balls[3].center[1] = 0;
    balls[3].center[2] = 80;
    balls[3].radius = 5;
    balls[3].color = 1;
    balls[3].coeff = 0;

    double alfa = 0, beta = 0, r = 0;
    double x = 0, y = 0, z = 0;

    // starting screen
    init_screen();

    bool exit = false,
            rotate_right = false, rotate_left = false,
            rotate_up = false, rotate_down = false,
            run = false, back = false,
            strafe_left = false, strafe_right = false;

    while (!exit) {

        char platno[HEIGHT / dH * (WIDTH / dW + 1) + 1];
        camera cam(r, alfa, beta, x, y, z);

        int p = 0;
        for (int i = 0; i < HEIGHT / dH; i++) {
            for (int j = 0; j < WIDTH / dW; j++) {
                double origin[3] = {cam.x, cam.y, cam.z};

                double unit[3] = {
                    -((double)(j - WIDTH / dW / 2) + 0.5) / (double)(WIDTH / dW / 2),
                    ((double)(i - HEIGHT / dH / 2) + 0.5) / (double)(WIDTH / dH / 2),
                    -1};
                transformVector(unit, cam.matrix);
                unit[0] -= cam.x;
                unit[1] -= cam.y;
                unit[2] -= cam.z;
                normalize(unit);
                double luminance = cam.rayTrace(origin, unit, balls, 4, 2, 0.3, 5);
                int color = (int)((strlen(palette) - 1) * luminance);
                platno[p++] = palette[color];
            }
            platno[p++] = '\n';
        }
        platno[p] = 0;

        // display:
        // puts is very fast
        puts(platno);

        ray_sleep(5);
        gotoxy(0, 0);

        /*moving and rotation*/
        if (rotate_up && beta >= -M_PI_2)
            beta -= 0.0006 * M_PI;

        if (rotate_down && beta <= M_PI_2)
            beta += 0.0006 * M_PI;

        if (rotate_right)
            alfa += 0.0006 * M_PI;
        if (rotate_left)
            alfa -= 0.0006 * M_PI;

        if (run)
        {
            x -= 0.012 * cos(alfa);
            y -= 0.012 * sin(alfa);
            z -= 0.012 * sin(beta);
        }
        if (back)
        {
            x += 0.012 * cos(alfa);
            y += 0.012 * sin(alfa);
            z += 0.012 * sin(beta);
        }

        /*input handling*/
        if (kbhit()){
            char key = ray_getch();
            if (key == '`') exit = true;
            if (key == 'e') {
                rotate_right = !rotate_right;
                rotate_left = false;
            }
            if (key == 'q'){
                rotate_left = !rotate_left;
                rotate_right = false;
            }
            if (key == 'w'){
                run = !run;
                back = false;
            }
            if (key == 's'){
                back = !back;
                run = false;
            }
            if (key == 'r'){
                rotate_up = !rotate_up;
                rotate_down = false;
            }
            if (key == 'f'){
                rotate_down = !rotate_down;
                rotate_up = false;
            }
        }
    }

    changemode(COOKED);
    return 0;
}

void init_screen(){
    for (int i = 0; i < HEIGHT / dH - 4; i++) {
        for (int j = 0; j < WIDTH / dW; j++) {
            putchar(' ');
        }
        putchar('\n');
    }

    gotoxy(55, 0);
    printf("RAY 1.0");
    gotoxy(50, 3);
    printf("` - exit, w - run, s - back");
    gotoxy(50, 4);
    printf("q - rotate left, e - rotate right");
    gotoxy(50, 5);
    printf("r - rotate up, f - rotate down");
    gotoxy(45, 7);
    printf("press any key(except pover and reset xD) to start");

    gotoxy(0, 0);

    ray_getch();

}
