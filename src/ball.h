#ifndef BALL_H
#define BALL_H

typedef struct Ball {
  double center[3];
  double radius;
  double color; // on the interval from 0 (dark) to 1 (light)
  double coeff; // on the scale from 0 to 1 how much does the ball reflect light
                // (1 means it's the perfect mirror)

  struct Ball *next;
  struct Ball *prev;

  Ball() {}

} ball;

#endif // BALL_H
