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

void magyarazatok(SDL_Surface *screen, int helyzet){
    if(helyzet == 1){
        stringColor(screen, menu.x+300, menu.y+100+1*egyseg, "Egyjatekos mod:", feher);
        stringColor(screen, menu.x+300, menu.y+100+2*egyseg, "Ebben a modban az a cel, hogy minel tobb pontot elerj.", feher);
        stringColor(screen, menu.x+300, menu.y+100+3*egyseg, "A pontokat ugy lehet gyujteni, hogy a kigyoval megeszed", feher);
        stringColor(screen, menu.x+300, menu.y+100+4*egyseg, "az aranyat. A kigyo iranyitasa a nyilakkal tortenik.", feher);
        stringColor(screen, menu.x+300, menu.y+100+5*egyseg, "Ha eleg ugyes vagy, felkerulsz a ranglistara.", feher);
        stringColor(screen, menu.x+300, menu.y+100+6*egyseg, "Sok sikert.", feher);
    } else if (helyzet == 2){
        stringColor(screen, menu.x+300, menu.y+100+1*egyseg, "Ketjatekos mod:", feher);
        stringColor(screen, menu.x+300, menu.y+100+2*egyseg, "Az egyjatekos modhoz hasonloan itt is pontokat kell", feher);
        stringColor(screen, menu.x+300, menu.y+100+3*egyseg, "gyujteni, csak itt egy baratod ellen jatszhatsz. Az", feher);
        stringColor(screen, menu.x+300, menu.y+100+4*egyseg, "iranyitas az egyik igyo eseteben a nyilakkal, a masik", feher);
        stringColor(screen, menu.x+300, menu.y+100+5*egyseg, "eseteben a WASD billentyukkel tortenik.", feher);
        stringColor(screen, menu.x+300, menu.y+100+6*egyseg, "Gyozzon a jobbik.", feher);
    } else if (helyzet == 3){
        stringColor(screen, menu.x+300, menu.y+100+1*egyseg, "Ranglista:", feher);
        stringColor(screen, menu.x+300, menu.y+100+2*egyseg, "Itt szerepelnek a legjobb jatekosok nevei. Ha szor-", feher);
        stringColor(screen, menu.x+300, menu.y+100+3*egyseg, "galmasan gyakorolsz egyszer te lehetsz az elso.", feher);
    } else if (helyzet ==4){
        stringColor(screen, menu.x+300, menu.y+100+1*egyseg, "Tenyleg ki akarsz lepni? :(", feher);
    }
    stringColor(screen, ablak_szelesseg-100, ablak_magassag-20, "Made by ktg", feher);
}

void kigyo_rajzol(SDL_Surface *screen, kigyo_lista *testet_rajzol, hely fejet_rajzol, hely farkat_rajzol, int fej_irany, int farok_irany, int osszeg, int szin_fo, int szin_mas){
    filledCircleColor(screen, fejet_rajzol.x, fejet_rajzol.y, 2*egyseg/3, szin_fo);
    kigyo_lista *mozgo_test;
    mozgo_test=testet_rajzol;
    while(mozgo_test != NULL && osszeg != 0){
        boxColor(screen, mozgo_test->pozicio.x-egyseg/2, mozgo_test->pozicio.y-egyseg/2, mozgo_test->pozicio.x+egyseg/2, mozgo_test->pozicio.y+egyseg/2, szin_fo);
        filledTrigonColor(screen, mozgo_test->pozicio.x-egyseg/2, mozgo_test->pozicio.y-egyseg/2+10, mozgo_test->pozicio.x-egyseg/2+10, mozgo_test->pozicio.y-egyseg/2, mozgo_test->pozicio.x+egyseg/2-10, mozgo_test->pozicio.y+egyseg/2, szin_mas);
        filledTrigonColor(screen, mozgo_test->pozicio.x-egyseg/2+10, mozgo_test->pozicio.y-egyseg/2, mozgo_test->pozicio.x+egyseg/2, mozgo_test->pozicio.y+egyseg/2-10, mozgo_test->pozicio.x+egyseg/2-10, mozgo_test->pozicio.y+egyseg/2, szin_mas);
        mozgo_test = mozgo_test->kov;
    }
    if(osszeg == 0){
            farok_irany = fej_irany;
            if(farok_irany==fel){
                filledTrigonColor(screen, farkat_rajzol.x, farkat_rajzol.y+3*egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y+egyseg/2, szin_fo);
            } else if(farok_irany==jobbra){
                filledTrigonColor(screen, farkat_rajzol.x-3*egyseg/2, farkat_rajzol.y, farkat_rajzol.x-egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            } else if(farok_irany==le){
                filledTrigonColor(screen, farkat_rajzol.x, farkat_rajzol.y-3*egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y-egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            } else if(farok_irany==balra){
                filledTrigonColor(screen, farkat_rajzol.x+3*egyseg/2, farkat_rajzol.y, farkat_rajzol.x+egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            }
        } else {
            if(farok_irany==fel){
                filledTrigonColor(screen, farkat_rajzol.x, farkat_rajzol.y+3*egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y+egyseg/2, szin_fo);
            } else if(farok_irany==jobbra){
                filledTrigonColor(screen, farkat_rajzol.x-3*egyseg/2, farkat_rajzol.y, farkat_rajzol.x-egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            } else if(farok_irany==le){
                filledTrigonColor(screen, farkat_rajzol.x, farkat_rajzol.y-3*egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y-egyseg/2, farkat_rajzol.x-egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            } else if(farok_irany==balra){
                filledTrigonColor(screen, farkat_rajzol.x+3*egyseg/2, farkat_rajzol.y, farkat_rajzol.x+egyseg/2, farkat_rajzol.y+egyseg/2, farkat_rajzol.x+egyseg/2, farkat_rajzol.y-egyseg/2, szin_fo);
            }
        }
}

void palya_rajzol(SDL_Surface *screen, hely bogyo_rajz){
    boxColor(screen, 0, 0, ablak_szelesseg, ablak_magassag, fekete);
    boxColor(screen, alap.x, alap.y, szelesseg+alap.x, magassag+alap.y, feher);
    filledCircleColor(screen, bogyo_rajz.x, bogyo_rajz.y, egyseg/2, arany);
}

void pontok_kiirasa(SDL_Surface *screen, char *pont_beir, int pontszam, int szine, int a, int b){
    stringColor(screen, menu.x+a, menu.y+b, "Pontok:", szine);
    sprintf(pont_beir, "%d", pontszam);
    stringColor(screen, menu.x+a+3*egyseg, menu.y+b, pont_beir, szine);
}

void menu_rajzol(SDL_Surface *screen, int kivalasztott_atadva ){
    boxColor(screen, 0, 0, ablak_szelesseg, ablak_magassag, fekete);
    stringColor(screen, menu.x, menu.y, "Menu:", feher);
    stringColor(screen, menu.x, menu.y+egyseg, "Egyjatekos mod", feher);
    stringColor(screen, menu.x, menu.y+2*egyseg, "Ketjatekos mod", feher);
    stringColor(screen, menu.x, menu.y+3*egyseg, "Ranglista", feher);
    stringColor(screen, menu.x, menu.y+4*egyseg, "Kilepes", feher);
    filledCircleColor(screen, menu.x-egyseg+igazitas, menu.y+kivalasztott_atadva*egyseg+igazitas, sugar, piros);
}

void kitolt(FILE *p){
    fprintf(p, "Koreai_kisgyerek_aki_mindenkinel_jobb\n");
    fprintf(p, "%d\n", 210);
    fprintf(p, "Orosz_Laszlo\n");
    fprintf(p, "%d\n", 200);
    fprintf(p, "A_legjobb\n");
    fprintf(p, "%d\n", 175);
    fprintf(p, "Csalo\n");
    fprintf(p, "%d\n", 150);
    fprintf(p, "Egy_piros_alma\n");
    fprintf(p, "%d\n", 125);
    fprintf(p, "Unikornis\n");
    fprintf(p, "%d\n", 100);
    fprintf(p, "Fehervari_uti_vasarcsarnok_langososa\n");
    fprintf(p, "%d\n", 75);
    fprintf(p, "Egy_fellabu_mosomedve\n");
    fprintf(p, "%d\n", 50);
    fprintf(p, "Kezdo\n");
    fprintf(p, "%d\n", 25);
    fprintf(p, "Bemelegites\n");
    fprintf(p, "%d\n", 10);
}


void ranglista_rajzol(SDL_Surface *screen){
    int i;
    boxColor(screen, 0, 0, ablak_szelesseg, ablak_magassag, fekete);
    stringColor(screen, ranglista_sorok.x, ranglista_sorok.y, "Ranglista", feher);
    char helyezes[5];
    for(i=1; i<11; i++){
        sprintf(helyezes, "%d", i);
        stringColor(screen, ranglista_sorok.x, ranglista_sorok.y+i*egyseg, helyezes, feher);
    }
    filledCircleColor(screen, ranglista_sorok.x+19*egyseg+igazitas, ranglista_sorok.y+14*egyseg+2*igazitas/3, sugar, piros);
    stringColor(screen, ranglista_sorok.x+20*egyseg, ranglista_sorok.y+14*egyseg, "Vissza", feher);
}

