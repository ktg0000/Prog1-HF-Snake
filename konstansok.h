#ifndef KONSTANSOK_H_INCLUDED
#define KONSTANSOK_H_INCLUDED

static int const ablak_magassag = 700;
static int const ablak_szelesseg = 1000;
static int const magassag = 620;
static int const szelesseg = 940;
static int const egyseg = 20;
static int const sugar = 10;
static int const igazitas = 5;
static int const ido = 50;

static int const fekete = 0x000000FF;
static int const feher = 0xFFFFFFFF;
static int const piros = 0xFF0000FF;
static int const zold = 0x32CD32FF;
static int const kek = 0x0000FFFF;
static int const halvany_fekete = 0x00000080;
static int const halvany_kek = 0x0000FF80;
static int const szurke = 0xA77280FF;
static int const arany = 0xFFD700FF;
static int const narancs = 0xFFA500FF;
static int const sarga = 0xFFFF00FF;
static int const barna = 0xA52A2AFF;

static int const fel = 1;
static int const jobbra = 2;
static int const le = 3;
static int const balra = 4;

typedef struct hely {int x; int y;} hely;
typedef struct kigyo_lista{hely pozicio; struct kigyo_lista *kov;} kigyo_lista;
typedef struct helyezett{char nev[51]; int rekord;} helyezett;

static hely const alap = {30, 50};
static hely const menu = {100, 20};
static hely const ranglista_sorok = {200, 100};

#endif
