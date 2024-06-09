#ifndef KIGYO_H_INCLUDED
#define KIGYO_H_INCLUDED

void felszabadit(kigyo_lista *torol);
bool magaba_harap(hely fejecske, kigyo_lista *testecske, hely farkacska);
bool egymasba_harap(hely egyik_kigyo_feje, kigyo_lista *egyik_test, hely egyik_kigyo_farka, hely masik_kigyo_feje, kigyo_lista *masik_test, hely masik_kigyo_farka);
int dir_converter(int regi, hely regi_farok, hely farok_elotti);
hely farok_szamitas(int pontok_szamit, hely farok_szamit, hely fejbol_szamol, kigyo_lista *testbol_szamol);
hely fej_szamitas(int irany, hely fej);
void kigyo_helye(kigyo_lista *p, int h, hely fej);
void kigyo_maszik(kigyo_lista *p, hely kigyo_fej);


#endif // KIGYO_H_INCLUDED
