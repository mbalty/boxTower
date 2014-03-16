#include "Cuboid.h"
#include <iostream>

Cuboid::Cuboid()
{
    xTrans = yTrans = zTrans = 0.0;
    xScale = yScale = zScale = 0.0;
    red = green = blue = 0.0;
}

void Cuboid::setTranslation(float xt, float yt, float zt)
{
    xTrans = xt;
    yTrans = yt;
    zTrans = zt;
}

void Cuboid::setScale(float xs, float ys, float zs)
{
    xScale = xs;
    yScale = ys;
    zScale = zs;
}

void Cuboid::setColor(float r, float g, float b)
{
    red = r;
    blue = b;
    green = g;
}

void Cuboid::generateCuboid()
{
    glColor3f(red, green, blue);
    glPushMatrix();

    glTranslatef(xTrans, yTrans, zTrans);
    glScalef(xScale, yScale, zScale);
    glutSolidCube(1.0);

    glColor3f(0.0, 0.0, 0.0); /// I wanted to have highlighted edges for the cubes and drawing a new wire cube seemed to be the simplest solution
    glutWireCube(1.0);

    glPopMatrix();
}

float Cuboid::getXT()
{
    return xTrans;
}

float Cuboid::getYT()
{
    return yTrans;
}

float Cuboid::getZT()
{
    return zTrans;
}

float Cuboid::getXS()
{
    return xScale;
}

float Cuboid::getYS()
{
    return yScale;
}

float Cuboid::getZS()
{
    return zScale;
}

float Cuboid::getRed()
{
    return red;
}

float Cuboid::getGreen()
{
    return green;
}

float Cuboid::getBlue()
{
    return blue;
}