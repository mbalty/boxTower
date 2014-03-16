#include "Game.h"
#include <time.h>

Game::Game(float e, float h)
{
    baseEdge = e;
    globalHeight = h;
    setCuboids();
}

void Game::setCuboids()
{

    srand((unsigned int) time(NULL));
    float localHeight = 0; // intermediate height to which the cube tower reached
    float maxEdge = baseEdge / 3; // maximum length of a cuboid edge
    float maxOrizontal = baseEdge / 2; // the maximum range of coordinates for where to draw a cuboid


    Cuboid C;

    while (localHeight < globalHeight)
    {
        float xs, ys, zs, xt, yt, zt;
        xs = ((float) rand() / (float) (RAND_MAX)) * (float) (maxEdge - 1.0) + 1.0;
        ys = ((float) rand() / (float) (RAND_MAX)) * (float) (maxEdge - 1.0) + 1.0;
        zs = ((float) rand() / (float) (RAND_MAX)) * (float) (maxEdge - 1.0) + 1.0;
        xt = ((float) rand() / (float) (RAND_MAX)) * (float) baseEdge - (float) maxOrizontal;
        zt = ((float) rand() / (float) (RAND_MAX)) * (float) baseEdge - (float) maxOrizontal;
        yt = globalHeight; 
        localHeight += ys;
        C.setScale(xs, ys, zs);
        C.setTranslation(xt, yt, zt);
        C.setColor(0.0, 0.8, 0.0);

        cuboids.push_back(C);
    }
}




