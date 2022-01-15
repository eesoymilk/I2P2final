#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <utility>
#include "Circle.h"
#include "global.h"

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;

    int getX() { return circle->x; }
    int getY() { return circle->y; }
    int getRadius() { return circle->r; }

    Circle* getCircle() const { return circle; }

    std::pair<int, int> Transform(){
        int rx = getX(); int ry = getY();
        //printf("%d %d %d %d\n", rx, ry, background_width, background_height);
        if(rx < window_width / 2 && ry < window_height / 2)
            return{rx, ry};
        else if(rx < window_width / 2 && ry > background_height - window_height / 2)
            return {rx, window_height + ry - background_height};
        else if(rx > background_width - window_width / 2 && ry > background_height - window_height / 2)
            return{window_width + rx - background_width, window_height + ry - background_height};
        else if(rx > background_width - window_width / 2 && ry < window_height / 2)
            return {window_width + rx - background_width, ry};
        else if(rx < window_width / 2)
            return {rx, window_height / 2};
        else if(rx > background_width - window_width / 2)
            return {window_width + rx - background_width, window_height / 2};
        else if(ry < window_height / 2)
            return {window_width / 2 , ry};
        else if(ry > background_height - window_height / 2)
            return {window_width / 2 , window_height + ry - background_height};
        else
            return {window_width / 2, window_height / 2};
    }

protected:
    Circle *circle;

};

#endif // OBJECT_H_INCLUDED
