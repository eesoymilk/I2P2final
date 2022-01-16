#include "Object.h"

std::pair<int, int>
Object::Transform(){
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

std::pair<double, double>
Object::UnitVector(double X, double Y)
{
    double length = sqrt(X * X + Y * Y);
    return { X / length, Y / length };
}