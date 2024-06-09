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


bool ranglista_olvas(SDL_Surface *screen){
    FILE *fp;
    SDL_Event ev;
    int i=0;
    char pont_str[5];
    bool enter = false;
    helyezett top_olv[10];
    fp = fopen("lista.txt", "rt");
    for(i=0; i<10; i++){
        fscanf(fp, "%s", top_olv[i].nev);
        fscanf(fp, "%d", &top_olv[i].rekord);
    }
    fclose(fp);
    while(!enter){
        SDL_WaitEvent(&ev);
        ranglista_rajzol(screen);
        i=0;
        while(i<10){
            stringColor(screen, ranglista_sorok.x+2*egyseg, ranglista_sorok.y+(i+1)*egyseg, top_olv[i].nev, feher);
            sprintf(pont_str, "%d", top_olv[i].rekord);
            stringColor(screen, ranglista_sorok.x+20*egyseg, ranglista_sorok.y+(i+1)*egyseg, pont_str, feher);
            i++;
        }
        switch(ev.type){
            case SDL_KEYDOWN:
                switch(ev.key.keysym.sym){
                    case SDLK_RETURN:
                            enter = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return true;
                break;
            default:
                break;
        }
        SDL_Flip(screen);
    }
    return false;
}


bool rekord_lett(int akt_pont){
    FILE *fp;
    helyezett top_ellenoriz[10];
    int i=0;
    fp = fopen("lista.txt", "rt");
    for(i=0; i<10; i++){
        fscanf(fp, "%s", top_ellenoriz[i].nev);
        fscanf(fp, "%d", &top_ellenoriz[i].rekord);
    }
    i=0;
    while(i<10){
        if(akt_pont > top_ellenoriz[i].rekord){
            fclose(fp);
            return true;
        }
        i++;
    }
    fclose(fp);
    return false;
}

bool ranglista_ir(SDL_Surface *screen, int uj_rekord){
    helyezett top_ir[10];
    helyezett uj;
    uj.rekord=uj_rekord;
    SDL_Event beolvas;
    bool enter_volt = false;
    FILE *fp;
    int i=0, pozicio = 0;
    uj.nev[0]='\0';
    fp = fopen("lista.txt", "rt");
    while(i<10){
        fscanf(fp, "%s", top_ir[i].nev);
        fscanf(fp, "%d", &top_ir[i].rekord);
        i++;
    }
    i=0;
    fclose(fp);
    SDL_EnableUNICODE(1);
    while (!enter_volt){
        SDL_WaitEvent(&beolvas);
        boxColor(screen, ablak_szelesseg/2-150, ablak_magassag/2-30, ablak_szelesseg/2+150, ablak_magassag/2+20, szurke);
        stringColor(screen, ablak_szelesseg/2-100-35, ablak_magassag/2-20, "Ird be a neved (utana uss entert):", feher);
        stringColor(screen, ablak_szelesseg/2-100, ablak_magassag/2, uj.nev, feher);
        switch(beolvas.type){
            case SDL_KEYDOWN:
                switch(beolvas.key.keysym.unicode){
                    case ' ':
                    case 0x0000:
                        break;
                    case '\r':
                    case '\n':
                        enter_volt = true;
                        break;
                    case '\b':
                        if (pozicio > 0)
                            uj.nev[--pozicio] = 0x0000;
                        break;
                        break;
                    default:
                        if(pozicio <51){
                            uj.nev[pozicio++] = beolvas.key.keysym.unicode;
                            uj.nev[pozicio] = 0x0000;
                        }
                        break;
                }
                break;
            case SDL_QUIT:
                return true;
                break;
        }
        SDL_Flip(screen);
    }

    if(uj.nev[0] == '\0' || uj.rekord > 9999){
        return false;
    }
    fp = fopen("lista.txt", "wt");
    bool volt_mar = false;
    while(i<10){
        if(!volt_mar && top_ir[i].rekord < uj.rekord){
            fprintf(fp, "%s\n", uj.nev);
            fprintf(fp, "%d\n", uj.rekord);
            volt_mar=true;

        } else {
            fprintf(fp, "%s\n", top_ir[i].nev);
            fprintf(fp, "%d\n", top_ir[i].rekord);
            i++;
        }
    }
    fclose(fp);
    return false;
}
