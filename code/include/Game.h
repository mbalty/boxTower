/**
 * My idea here is that using a fixed height for the game space and a fixed edge for the base plane, 
 * to create the random cubids(only the info about these cuboids) beforehand into a vector, 
 * and then just iterate through the vetor and generate them in order on the screen .
 */



#include "Cuboid.h"
#include <cstdlib>
#include <vector>
#include <time.h>

class Game {
public:
    float globalHeight; ///< the height from where the cubes will be dropped
    float baseEdge; ///< length of the base's edge
    std::vector<Cuboid> cuboids; ///< the cubes that will be drawn on the screen

    /**
     * Game Constructor
     * @param e - edge 
     * @param h - height 
     */
    Game(float e, float h);

    /// Fills in the cuboids, vector ; called in constructor Game 
    void setCuboids();
};



