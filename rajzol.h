#ifndef RAJZOL_H_INCLUDED
#define RAJZOL_H_INCLUDED

void magyarazatok(SDL_Surface *screen, int helyzet);
void kigyo_rajzol(SDL_Surface *screen, kigyo_lista *testet_rajzol, hely fejet_rajzol, hely farkat_rajzol, int fej_irany, int farok_irany, int osszeg, int szin_fo, int szin_mas);
void palya_rajzol(SDL_Surface *screen, hely bogyo_rajz);
void pontok_kiirasa(SDL_Surface *screen, char *pont_beir, int pontszam, int szine, int a, int b);
void menu_rajzol(SDL_Surface *screen, int kivalasztott_atadva );
void kitolt(FILE *p);
void ranglista_rajzol(SDL_Surface *screen);

#endif // RAJZOL_H_INCLUDED
