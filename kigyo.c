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


void felszabadit(kigyo_lista *torol){
    while (torol != NULL) {
        kigyo_lista *temp = torol->kov;
        free(torol);
        torol = temp;
    }
}

bool magaba_harap(hely fejecske, kigyo_lista *testecske, hely farkacska){
    if(fejecske.x == farkacska.x && fejecske.y == farkacska.y)
        return true;
    while(testecske->kov != NULL){
        if(fejecske.x == testecske->pozicio.x && fejecske.y == testecske->pozicio.y)
            return true;
        testecske = testecske->kov;
    }
    return false;
}

bool egymasba_harap(hely egyik_kigyo_feje, kigyo_lista *egyik_test, hely egyik_kigyo_farka, hely masik_kigyo_feje, kigyo_lista *masik_test, hely masik_kigyo_farka){
    if(egyik_kigyo_feje.x == masik_kigyo_feje.x && egyik_kigyo_feje.y == masik_kigyo_feje.y)
        return true;
    if(egyik_kigyo_feje.x == masik_kigyo_farka.x && egyik_kigyo_feje.y == masik_kigyo_farka.y)
        return true;
    if(masik_kigyo_feje.x == egyik_kigyo_farka.x && masik_kigyo_feje.y == egyik_kigyo_farka.y)
        return true;
    while(egyik_test->kov != NULL){
        if(masik_kigyo_feje.x == egyik_test->pozicio.x && masik_kigyo_feje.y == egyik_test->pozicio.y)
            return true;
        egyik_test = egyik_test->kov;
    }
    while(masik_test->kov != NULL){
        if(egyik_kigyo_feje.x == masik_test->pozicio.x && egyik_kigyo_feje.y == masik_test->pozicio.y)
            return true;
        masik_test = masik_test->kov;
    }
    return false;
}

int dir_converter(int regi, hely regi_farok, hely farok_elotti){
    if(regi_farok.x == farok_elotti.x){
        if(regi_farok.y > farok_elotti.y){
            return fel;
        } else if(regi_farok.y < farok_elotti.y){
            return le;
        }
    }
    if(regi_farok.y == farok_elotti.y){
        if(regi_farok.x > farok_elotti.x){
            return balra;
        } else if(regi_farok.x < farok_elotti.x){
            return jobbra;
        }
    }
    return regi;
}

hely farok_szamitas(int pontok_szamit, hely farok_szamit, hely fejbol_szamol, kigyo_lista *testbol_szamol){
    if(pontok_szamit == 0){
        farok_szamit.x = fejbol_szamol.x;
        farok_szamit.y = fejbol_szamol.y;
    } else {
        farok_szamit.x = testbol_szamol->pozicio.x;
        farok_szamit.y = testbol_szamol->pozicio.y;
    }
    return farok_szamit;
}

hely fej_szamitas(int irany, hely fej){
    if(irany==fel){
        fej.y -=egyseg;
    } else if(irany ==jobbra){
        fej.x +=egyseg;
    } else if(irany ==le){
        fej.y +=egyseg;
    } else if(irany ==balra){
        fej.x -=egyseg;
    }
    return fej;
}

void kigyo_helye(kigyo_lista *p, int h, hely fej){
    if(h==1){
        return;
    }
    kigyo_lista *seged = (kigyo_lista*) malloc(sizeof(kigyo_lista));
    kigyo_lista *mozgo;
    mozgo = p;
    while (mozgo->kov != NULL){
        mozgo = mozgo->kov;
    }
    seged->pozicio.x = fej.x;
    seged->pozicio.y = fej.y;
    mozgo->kov = seged;
    seged->kov = NULL;
}

void kigyo_maszik(kigyo_lista *p, hely kigyo_fej){
    while(p->kov!=NULL){
        p->pozicio.x = p->kov->pozicio.x;
        p->pozicio.y = p->kov->pozicio.y;
        p = p->kov;
    }
    p->pozicio.x = kigyo_fej.x;
    p->pozicio.y = kigyo_fej.y;
}
