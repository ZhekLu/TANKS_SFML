#ifndef DEFINECELLS_H
#define DEFINECELLS_H

#define CELL 10                     //#define CELL 20
#define WIDTH CELL * 14 * 2 * 2     // 600 #define WIDTH CELL * 15 * 2
#define HEIGHT CELL * 13 * 2 * 2    // 560 #define HEIGHT CELL * 14 * 2
enum Rotation
{
    LEFT, UP, RIGHT, DOWN, STOP
};

#endif // DEFINECELLS_H
