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

bool bogyo_ellenorzes(hely akt_bogyo, hely akt_fej, kigyo_lista *akt_test, hely akt_farka, int akt_pont){
    if(akt_bogyo.x == akt_fej.x && akt_bogyo.y == akt_fej.y)
        return false;
    if(akt_bogyo.x == akt_farka.x && akt_bogyo.y == akt_farka.y)
        return false;
    int i;
    for(i=0; i<akt_pont; i++){
        if(akt_bogyo.x == akt_test->pozicio.x && akt_bogyo.y == akt_test->pozicio.y){
            return false;
        }
        akt_test = akt_test->kov;
    }
    return true;
}

hely bogyo_koord_egyjatekos(hely atad_fej, kigyo_lista *atad_test, hely atad_farka, int atad_pont){
    hely bogyo_hely;
    bool mas =false;
    while(!mas){
        bogyo_hely.x = (rand()%46)*20+40;
        bogyo_hely.y = (rand()%30)*20+60;
        if(bogyo_ellenorzes(bogyo_hely, atad_fej, atad_test, atad_farka, atad_pont)){
                mas = true;
           }
    }
    return bogyo_hely;
}

hely bogyo_koord_ketjatekos(hely atad_fej_A, kigyo_lista *atad_test_A, hely atad_farka_A, int atad_pont_A, hely atad_fej_B, kigyo_lista *atad_test_B, hely atad_farka_B, int atad_pont_B){
    hely bogyo_hely;
    bool mas =false;
    while(!mas){
        bogyo_hely.x = (rand()%46)*20+40;
        bogyo_hely.y = (rand()%30)*20+60;
        if(bogyo_ellenorzes(bogyo_hely, atad_fej_A, atad_test_A, atad_farka_A, atad_pont_A) && bogyo_ellenorzes(bogyo_hely, atad_fej_B, atad_test_B, atad_farka_B, atad_pont_B)){
                mas = true;
           }
    }
    return bogyo_hely;
}

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}
