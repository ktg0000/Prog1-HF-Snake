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


bool ketjatekos(SDL_Surface *screen){
    SDL_TimerID id;
    SDL_Event esemeny;
    id = SDL_AddTimer(ido, idozit, NULL);
    bool kovetkezo = true, vissza=false, irany_engedelyezo_A = false, irany_engedelyezo_B = false, vege=false;
    int dir_feje_A=jobbra, dir_farka_A=jobbra, pontok_A = 0, dir_feje_B=balra, dir_farka_B=balra, pontok_B = 0;
    char pontok_atalakitasa[5];
    hely bogyo_hely, kigyo_farka_A, kigyo_feje_A = {100, 120}, kigyo_farka_B, kigyo_feje_B = {ablak_szelesseg-100, ablak_magassag-100};
    kigyo_lista *test_A=(kigyo_lista*) malloc (sizeof(kigyo_lista)), *test_B=(kigyo_lista*) malloc (sizeof(kigyo_lista));
    test_A->kov = NULL; test_B->kov = NULL;
    while(!vissza){
        SDL_WaitEvent(&esemeny);
        if(kovetkezo){
            bogyo_hely = bogyo_koord_ketjatekos(kigyo_feje_A, test_A, kigyo_farka_A, pontok_A, kigyo_feje_B, test_B, kigyo_farka_B, pontok_B);
            kovetkezo=false;
        }
        switch(esemeny.type){
            case SDL_USEREVENT:
                palya_rajzol(screen, bogyo_hely);
                pontok_kiirasa(screen, pontok_atalakitasa, pontok_A, kek, 0, 0);
                pontok_kiirasa(screen, pontok_atalakitasa, pontok_B, piros, 500, 0);
                kigyo_farka_A = farok_szamitas(pontok_A, kigyo_farka_A, kigyo_feje_A, test_A);
                kigyo_farka_B = farok_szamitas(pontok_B, kigyo_farka_B, kigyo_feje_B, test_B);
                kigyo_rajzol(screen, test_A, kigyo_feje_A, kigyo_farka_A, dir_feje_A, dir_farka_A, pontok_A, kek, sarga);
                kigyo_rajzol(screen, test_B, kigyo_feje_B, kigyo_farka_B, dir_feje_B, dir_farka_B, pontok_B, piros, narancs);
                if(pontok_A != 0){
                    kigyo_maszik(test_A, kigyo_feje_A);
                    dir_farka_A = dir_converter(dir_farka_A, kigyo_farka_A, test_A->pozicio);
                } else {dir_farka_A=dir_feje_A;}
                if(pontok_B != 0){
                    kigyo_maszik(test_B, kigyo_feje_B);
                    dir_farka_B = dir_converter(dir_farka_B, kigyo_farka_B, test_B->pozicio);
                } else {dir_farka_B=dir_feje_B;}
                kigyo_feje_A = fej_szamitas(dir_feje_A, kigyo_feje_A);
                kigyo_feje_B = fej_szamitas(dir_feje_B, kigyo_feje_B);
                if(bogyo_hely.x == kigyo_feje_A.x && bogyo_hely.y == kigyo_feje_A.y){
                    pontok_A +=1;
                    if(pontok_A == 1){test_A->pozicio.x = kigyo_feje_A.x; test_A->pozicio.y = kigyo_feje_A.y;}
                    kigyo_helye(test_A, pontok_A, kigyo_feje_A);
                    kovetkezo=true;
                }
                if(bogyo_hely.x == kigyo_feje_B.x && bogyo_hely.y == kigyo_feje_B.y){
                    pontok_B +=1;
                    if(pontok_B == 1){test_B->pozicio.x = kigyo_feje_B.x; test_B->pozicio.y = kigyo_feje_B.y;}
                    kigyo_helye(test_B, pontok_B, kigyo_feje_B);
                    kovetkezo=true;
                }
                if(kigyo_feje_A.x<alap.x+egyseg/2 || kigyo_feje_A.x>alap.x+szelesseg-egyseg/2 || kigyo_feje_A.y<alap.y+egyseg/2 || kigyo_feje_A.y>alap.y+magassag-egyseg/2 || magaba_harap(kigyo_feje_A, test_A, kigyo_farka_A) || kigyo_feje_B.x<alap.x+egyseg/2 || kigyo_feje_B.x>alap.x+szelesseg-egyseg/2 || kigyo_feje_B.y<alap.y+egyseg/2 || kigyo_feje_B.y>alap.y+magassag-egyseg/2 || magaba_harap(kigyo_feje_B, test_B, kigyo_farka_B) || egymasba_harap(kigyo_feje_A, test_A, kigyo_farka_A, kigyo_feje_B, test_B, kigyo_farka_B)){ //ez lehet igazából rövidebb is, de nekem tetszik, hogy ilyen hosszú lett :)
                    SDL_RemoveTimer(id);
                    vege=true;
                }
                break;
            case SDL_KEYDOWN:
                switch(esemeny.key.keysym.sym){
                    case SDLK_UP: if(!irany_engedelyezo_A){dir_feje_A=fel;irany_engedelyezo_A = true;} break;
                    case SDLK_RIGHT: if(irany_engedelyezo_A){dir_feje_A=jobbra;irany_engedelyezo_A = false;} break;
                    case SDLK_DOWN: if(!irany_engedelyezo_A){dir_feje_A=le; irany_engedelyezo_A = true;} break;
                    case SDLK_LEFT: if(irany_engedelyezo_A){dir_feje_A=balra; irany_engedelyezo_A = false;} break;
                    case SDLK_w: if(!irany_engedelyezo_B){dir_feje_B=fel; irany_engedelyezo_B = true;} break;
                    case SDLK_d: if(irany_engedelyezo_B){dir_feje_B=jobbra; irany_engedelyezo_B = false;} break;
                    case SDLK_s: if(!irany_engedelyezo_B){dir_feje_B=le; irany_engedelyezo_B = true;} break;
                    case SDLK_a: if(irany_engedelyezo_B){dir_feje_B=balra; irany_engedelyezo_B = false;} break;
                    case SDLK_ESCAPE: vissza = true; break;
                    default: break;
                }
                if(vege){vissza=true;}
                break;
            case SDL_QUIT:
                vissza=true;
                return true;
                break;
        }
        SDL_Flip(screen);
    }
    SDL_RemoveTimer(id);
    felszabadit(test_A);
    felszabadit(test_B);
    return false;
}

