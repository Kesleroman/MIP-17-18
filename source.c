#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Bod{
  double x;
  double y;
} BOD;

typedef struct {
  // ax + by + c = 0
  int a;
  int b;
  int c;
} PRIAMKA;

typedef struct{
  BOD *body;
  int pocet_bodov;
} OBAL;

/*
    Funkcia setri, ci je bod nad priamkou alebo pod nej.
    Ak bod je vyssie funkcia vrati 1.
    Ak bod patri do priamky funkcia vrati 0.
    Inak vrati -1;
*/
int je_hore(PRIAMKA priamka,
            BOD bod)
{
  int hodnota = priamka.a * bod.x + priamka.b * bod.y + priamka.c;

  if(hodnota > 0)
    return 1;
  else
  {
    if(hodnota == 0)
      return 0;
    else
      return -1;
  }
}

double determinant(BOD A,
                   BOD B,
                   BOD C)
{
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

double vzdialenost(BOD A,
                   BOD B)
{
  double num = pow( (B.x-A.x), 2.0) + pow( (B.y-A.y), 2.0);
  return num;
}

void vymen_prvky(BOD *bod1,
                 BOD *bod2)
{
  BOD pomocny;
  pomocny = *bod1;
  *bod1 = *bod2;
  *bod2 = pomocny;
}

/*
    Funkcia usporiada body vzostupne podla x-ej suradnice.
    Ak dva body maju rovnak x-u suradnicu, funkcia usporiada podla y.
*/
void usporiadaj(BOD *body,
                int pocet_bodov)
{
  int usporiadane_body, index, min;
  for(usporiadane_body = 0; usporiadane_body < pocet_bodov; ++usporiadane_body)
  {
    for(index = usporiadane_body, min = usporiadane_body; index < pocet_bodov; ++index)
    {
      if(body[min].x > body[index].x)
        min = index;

      if(body[min].x == body[index].x)
      {
        if(body[min].y > body[index].y)
          min = index;
      }
    }
    vymen_prvky( &body[min], &body[usporiadane_body]);
  }
}

void nacitaj_suradnice(struct Bod *body,
                       int pocet_bodov)
{
  int index;
  for(index = 0; index < pocet_bodov; ++index)
    scanf("%lf %lf", &body[index].x, &body[index].y);
}

PRIAMKA vypocitaj_priamku(BOD A,
                          BOD B)
{
  PRIAMKA p;
  p.a = A.y - B.y;
  p.b = B.x - A.x;
  p.c = A.x * B.y - A.y * B.x;
  return p;
}

double vypocitaj_obvod(OBAL *obal)
{
  int index;
  double obvod = 0.0, medzivysledok;

  for(index = 0; index < obal->pocet_bodov - 1; ++index)
  {
    medzivysledok = vzdialenost(obal->body[index], obal->body[index+1]);
    obvod += sqrt(medzivysledok);
  }

  return obvod;
}

void pridaj_bod(OBAL *obal, BOD bod)
{
  obal->body[obal->pocet_bodov] = bod;
  obal->pocet_bodov++;
}

void pridaj_alebo_odstran_bod(OBAL *obal, BOD bod)
{
  int *pocet_vrcholov = &obal->pocet_bodov;
  BOD predposleny_b = obal->body[(*pocet_vrcholov) - 2],
      posledny_b = obal->body[(*pocet_vrcholov) - 1];

  while(1)
      {
        if(*pocet_vrcholov == 1)
        {
          pridaj_bod(obal, bod);
          break;
        }

        if( determinant(predposleny_b, posledny_b, bod) >= 0)
        {
          pridaj_bod(obal, bod);
          break;
        }
        else
          (*pocet_vrcholov) -= 1;
      }
}

void najdi_horny_a_dolny_obal(BOD *body,
                              OBAL *horny_obal,
                              OBAL *dolny_obal,
                              int pocet_bodov)
{
  int max_lavy = 0,
      max_pravy = pocet_bodov - 1;
  dolny_obal->body[0] = body[max_lavy];
  horny_obal->body[0] = body[max_pravy];
  dolny_obal->pocet_bodov = horny_obal->pocet_bodov = 1;

  PRIAMKA priamka;
  priamka = vypocitaj_priamku(body[max_lavy], body[max_pravy]);

  int index;
  for(index = 1; index < pocet_bodov; ++index)
  {
    if( je_hore(priamka, body[index] ) <= 0)
      pridaj_alebo_odstran_bod(dolny_obal, body[index]);
  }

  for(index = pocet_bodov - 2; index >= 0; --index)
  {
    if(je_hore(priamka, body[index]) >= 0)
      pridaj_alebo_odstran_bod(horny_obal, body[index]);
  }
}

int main()
{
  int pocet_bodov;
  scanf("%d", &pocet_bodov);

  BOD *body = malloc(pocet_bodov * sizeof(BOD));
  OBAL *dolny_obal = malloc(sizeof(OBAL));
       dolny_obal->body = malloc(pocet_bodov * sizeof(BOD));
  OBAL *horny_obal = malloc(sizeof(OBAL));
       horny_obal->body = malloc(pocet_bodov * sizeof(BOD));

  nacitaj_suradnice(body, pocet_bodov);
  usporiadaj(body, pocet_bodov);
  najdi_horny_a_dolny_obal(body, horny_obal, dolny_obal, pocet_bodov);

  double obvod;
  obvod = vypocitaj_obvod(horny_obal);
  obvod += vypocitaj_obvod(dolny_obal);
  printf("%.3lf", obvod);

  return 0;
}
