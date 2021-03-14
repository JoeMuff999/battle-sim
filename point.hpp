/*
    wrapper for coordinates
*/
#ifndef POINT_HPP
#define POINT_HPP

struct point{
    int x;
    int y;
};

typedef struct point Point;

struct floatPoint{
    float x;
    float y;
};

typedef struct floatPoint FloatPoint;

Point point(int xx, int yy)
{
    Point p;
    p.x = xx;
    p.y = yy;
    return p;
}

#endif