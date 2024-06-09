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


bool egyjatekos(SDL_Surface *screen){
    SDL_TimerID id;
    SDL_Event esemeny;
    id = SDL_AddTimer(ido, idozit, NULL);
    bool kovetkezo = true, vissza=false, irany_engedelyezo = false, megallit = true, vege=false;
    int dir_feje=jobbra, dir_farka=jobbra, pontok = 0;
    char pontok_atalakitasa[5];
    hely bogyo_hely, kigyo_farka, kigyo_feje = {100, 100};
    kigyo_lista *test=(kigyo_lista*) malloc (sizeof(kigyo_lista));
    test->kov = NULL;
    while(!vissza){
        SDL_WaitEvent(&esemeny);
        if(kovetkezo){
            bogyo_hely = bogyo_koord_egyjatekos(kigyo_feje, test, kigyo_farka, pontok);
            kovetkezo=false;
        }
        switch(esemeny.type){
            case SDL_USEREVENT:
                palya_rajzol(screen, bogyo_hely);
                pontok_kiirasa(screen, pontok_atalakitasa, pontok, feher, 0, 0);
                kigyo_farka = farok_szamitas(pontok, kigyo_farka, kigyo_feje, test);
                kigyo_rajzol(screen, test, kigyo_feje, kigyo_farka, dir_feje, dir_farka, pontok, barna, zold);
                if(pontok != 0){
                    kigyo_maszik(test, kigyo_feje);
                    dir_farka = dir_converter(dir_farka, kigyo_farka, test->pozicio);
                } else {dir_farka=dir_feje;}
                kigyo_feje = fej_szamitas(dir_feje, kigyo_feje);
                if(bogyo_hely.x == kigyo_feje.x && bogyo_hely.y == kigyo_feje.y){
                    pontok +=1;
                    if(pontok == 1){
                        test->pozicio.x = kigyo_feje.x;
                        test->pozicio.y = kigyo_feje.y;
                    }
                    kigyo_helye(test, pontok, kigyo_feje);
                    kovetkezo=true;
                }
                if(kigyo_feje.x<alap.x+egyseg/2||kigyo_feje.x>alap.x+szelesseg-egyseg/2||kigyo_feje.y<alap.y+egyseg/2||kigyo_feje.y>alap.y+magassag-egyseg/2 || magaba_harap(kigyo_feje, test, kigyo_farka)){
                    SDL_RemoveTimer(id);
                    vege=true;
                }
                break;
            case SDL_KEYDOWN:
                switch(esemeny.key.keysym.sym){
                    case SDLK_UP:
                        if(!irany_engedelyezo){ dir_feje=fel; irany_engedelyezo = true; }
                        break;
                    case SDLK_RIGHT:
                        if(irany_engedelyezo){ dir_feje=jobbra; irany_engedelyezo = false;}
                        break;
                    case SDLK_DOWN:
                        if(!irany_engedelyezo){ dir_feje=le; irany_engedelyezo = true;}
                        break;
                    case SDLK_LEFT:
                        if(irany_engedelyezo){ dir_feje=balra; irany_engedelyezo = false;}
                        break;
                    case SDLK_ESCAPE: vissza = true; break;
                    default: break;
                }
                if(vege){vissza=true;}
                break;
            case SDL_QUIT: vissza=true; return true; break;
        }
        SDL_Flip(screen);
    }
    if(rekord_lett(pontok)){ if(ranglista_ir(screen, pontok)){vissza=true;}}
    felszabadit(test);
    return false;
}

