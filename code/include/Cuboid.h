#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

class Cuboid {
private:
    float xTrans, yTrans, zTrans; ///< the translation parameters
    float xScale, yScale, zScale; ///< the scaling parameters
    float red, green, blue; ///< RGB color
public:
    /// Constructor
    Cuboid();

    /// Generates a cuboid at #height distance from the base
    void generateCuboid();

    /// setter for translation parameters
    void setTranslation(float xt, float yt, float zt);

    /// setter for scaling params
    void setScale(float xs, float ys, float zs);

    /// setter for color params
    void setColor(float r, float g, float b);

    /// getter for translation x
    float getXT();

    /// getter for translation y
    float getYT();

    /// getter for translation z
    float getZT();

    /// getter for scaling x
    float getXS();

    /// getter for scaling y
    float getYS();

    /// getter for scaling z
    float getZS();

    /// getter for color r
    float getRed();

    /// getter for color g
    float getGreen();

    /// getter for color b
    float getBlue();
};



