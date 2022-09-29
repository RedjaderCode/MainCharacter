#ifndef MAIN_H_
#define MAIN_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <chrono>
#include <stdio.h>

class TEXTURE{

    private:

    int IMG_Width;
    int IMG_Height;

    SDL_Texture * cTexture;

    public:

    TEXTURE()
        :
            IMG_Height(NULL),
            IMG_Width(NULL)
            {}
    ~TEXTURE(){free();}

    class sGET_TIME{

        private:

        std::chrono::time_point<std::chrono::high_resolution_clock> nFirst;
        std::chrono::time_point<std::chrono::high_resolution_clock> nLast;
        std::chrono::duration<float> dDuration;

        public:

        sGET_TIME(){nFirst = std::chrono::high_resolution_clock::now();}
        ~sGET_TIME(){
            nLast = std::chrono::high_resolution_clock::now();
            dDuration = nLast - nFirst;
            printf("%f seconds to load assets\n", dDuration);
        }
    };

    void free();
    void LoadTexture(const char * PTH);
    void render(int x, int y, SDL_Rect * clip);

    int Width(){return IMG_Width;}
    int Height(){return IMG_Height;}
};

enum MapSprites{

    RIGHT_TREE,
    BULB_TREE,
    SLANT_TREE,
    TRI_TREE,

    GRASS_GROUND,
    GRASS_CYCLOPS,
    GRASS_SNAKEEYES,
    GRASS_GRASSBLOCK,

    NORMAL_DIRT,
    SEED_DIRT,

    NUM_OF_MAP_SPRITES
};

#endif