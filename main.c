#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "konstansok.h"
#include "egyjatekosmod.h"
#include "ketjatekosmod.h"
#include "ranglista.h"
#include "bogyo_es_idozit.h"
#include "kigyo.h"
#include "rajzol.h"


int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Surface *screen;
    srand(time(0));
    bool quit=false;
    int kivalasztott = 1;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(ablak_szelesseg, ablak_magassag, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    FILE* letrehoz;
    if((letrehoz = fopen("lista.txt", "rt")) == NULL){
        letrehoz = fopen("lista.txt", "wt");
        kitolt(letrehoz);
    }
    fclose(letrehoz);
    SDL_WM_SetCaption("Snake", "Snake");
    while (!quit) {
            SDL_WaitEvent(&event);
            menu_rajzol(screen, kivalasztott);
            magyarazatok(screen, kivalasztott);
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            if(kivalasztott != 1){
                                kivalasztott-=1;
                            }
                            break;
                        case SDLK_DOWN:
                            if(kivalasztott != 4){
                                kivalasztott+=1;
                            }
                            break;
                        case SDLK_ESCAPE:
                            quit=true;
                            break;
                        case SDLK_RETURN:
                            if(kivalasztott==1){
                                if(egyjatekos(screen)){
                                    quit = true;
                                };
                            } else if(kivalasztott==2){
                                if(ketjatekos(screen)){
                                    quit = true;
                                };
                            } else if(kivalasztott==3){
                                if(ranglista_olvas(screen)){
                                    quit = true;
                                };
                            } else if(kivalasztott==4){
                                quit=true;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit=true;
                    break;
            }
        SDL_Flip(screen);
    }
    SDL_Quit();
    return 0;
}
