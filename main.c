/**
 * Author: Zakaria HAMMAL
 * email: hammalzakaria06@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#define PI 3.14159265

void drawCube(SDL_Window* w, SDL_Renderer* r, SDL_Point* cube, int a)
{
    SDL_Point center = {500, 500};

    double ratio = a * PI / 180;

    int newX, newY;

    for(int i = 0; i < 7; i++) 
    {
        newX = (cube[i].x - center.x) * cos(ratio) - (cube[i].y - center.y) * sin(ratio) + center.x;
        newY = (cube[i].x - center.x) * sin(ratio) + (cube[i].y - center.y) * cos(ratio) + center.y;
        
        cube[i].x = newX;
        cube[i].y = newY;
    }
    

    SDL_RenderDrawLine(r, cube[0].x, cube[0].y, cube[1].x, cube[1].y);
    SDL_RenderDrawLine(r, cube[0].x, cube[0].y, cube[2].x, cube[2].y);
    SDL_RenderDrawLine(r, cube[1].x, cube[1].y, cube[3].x, cube[3].y);
    SDL_RenderDrawLine(r, cube[2].x, cube[2].y, cube[3].x, cube[3].y);
    SDL_RenderDrawLine(r, cube[0].x, cube[0].y, cube[4].x, cube[4].y);
    SDL_RenderDrawLine(r, cube[2].x, cube[2].y, cube[5].x, cube[5].y);
    SDL_RenderDrawLine(r, cube[4].x, cube[4].y, cube[5].x, cube[5].y);
    SDL_RenderDrawLine(r, cube[3].x, cube[3].y, cube[6].x, cube[6].y);
    SDL_RenderDrawLine(r, cube[5].x, cube[5].y, cube[6].x, cube[6].y);

}

// ---------------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Point c[] = {
        {400, 400}, {400, 600}, {600, 400}, {600, 600}, {450, 350}, {650, 350}, {650, 550}
    };

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur de SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;    
    }

    window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_SHOWN);

    if(window == NULL) 
    {
        fprintf(stderr, "Erreur de SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
    {
        fprintf(stderr, "Erreur de SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    int quit = 0;
    int g = 0;

    SDL_Event e;
    
    printf("Tutoriel :\nClick on :\n'a' to rotate to the right\n'b' to rotate to the left\n'c' to  stop the rotaion\n");

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {

            if(e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.key.keysym.sym == SDLK_a)
            {
                g = 30;

            }
            else if (e.key.keysym.sym == SDLK_b)
            {
                g = -30;
            }
            else if (e.key.keysym.sym == SDLK_c)
            {
                g = 0;
            }
            
        }    

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        drawCube(window, renderer, c, g); 

        SDL_RenderPresent(renderer);

        SDL_Delay(300);
    }
        
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return EXIT_SUCCESS;
}
