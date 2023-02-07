#ifndef BACKGROUND_H
#define BACKGROUND//

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf; 
using namespace std;

// This class' purpose is to display the background of our yahtzee game

class Background : public Drawable{

    public:

        Background();
        Background(string filename);

    private:

        Texture _backgroundTexture;
        Sprite _backgroundSprite;
        virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif