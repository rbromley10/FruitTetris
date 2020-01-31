#ifndef _SHAPE_H_
#define _SHAPE_H_

enum types {I, S, S_inverted, L, L_inverted, T};
enum fruits {APPLE, PEAR, BANANA, GRAPE, ORANGE, FRUITS_TOTAL};

class Shape {
    public:
        int getShape(int type, int rotation, int x, int y);
        int getXMinPos(int type, int rotation);
        int getXMaxPos(int type, int rotation);
        int getYInitPos(int type, int rotation);
};

#endif