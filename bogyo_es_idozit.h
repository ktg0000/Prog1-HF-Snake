#ifndef BOGYO_ES_IDOZIT_H_INCLUDED
#define BOGYO_ES_IDOZIT_H_INCLUDED

bool bogyo_ellenorzes(hely akt_bogyo, hely akt_fej, kigyo_lista *akt_test, hely akt_farka, int akt_pont);
hely bogyo_koord_egyjatekos(hely atad_fej, kigyo_lista *atad_test, hely atad_farka, int atad_pont);
Uint32 idozit(Uint32 ms, void *param);
hely bogyo_koord_ketjatekos(hely atad_fej_A, kigyo_lista *atad_test_A, hely atad_farka_A, int atad_pont_A, hely atad_fej_B, kigyo_lista *atad_test_B, hely atad_farka_B, int atad_pont_B);

#endif // BOGYO_ES_IDOZIT_H_INCLUDED
