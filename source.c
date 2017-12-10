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
  BOD *obal;
  int pocet_bodov;
} OBAL;

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
  {
    scanf("%lf %lf", &body[index].x, &body[index].y);
  }
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
    medzivysledok = vzdialenost(obal->obal[index], obal->obal[index+1]);
    obvod += sqrt(medzivysledok);
  }

  return obvod;
}

void najdi_horny_a_dolny_obal(BOD *body,
                              OBAL *horny_obal,
                              OBAL *dolny_obal,
                              int pocet_bodov)
{
  int max_lavy = 0,
      max_pravy = pocet_bodov - 1;
  dolny_obal->obal[0] = body[max_lavy];
  horny_obal->obal[0] = body[max_pravy];
  int *pocet_d_vrcholov = &dolny_obal->pocet_bodov,
      *pocet_h_vrcholov = &horny_obal->pocet_bodov;
  *pocet_d_vrcholov = 1;
  *pocet_h_vrcholov = 1;

  PRIAMKA priamka;
  priamka = vypocitaj_priamku(body[max_lavy], body[max_pravy]);

  int index;
  for(index = 1; index < pocet_bodov; ++index)
  {
    if( je_hore(priamka, body[index] ) <= 0)
    {
      while(1)
      {
        if(*pocet_d_vrcholov == 1)
        {
          dolny_obal->obal[*pocet_d_vrcholov] = body[index];
          (*pocet_d_vrcholov) += 1;
          break;
        }
        if( determinant(dolny_obal->obal[(*pocet_d_vrcholov) - 2],
                        dolny_obal->obal[(*pocet_d_vrcholov) - 1],
                        body[index]) >= 0)
        {
          dolny_obal->obal[*pocet_d_vrcholov] = body[index];
          (*pocet_d_vrcholov) += 1;
          break;
        }
        else
        {
          (*pocet_d_vrcholov) -= 1;
        }
      }
    }
  }

  for(index = pocet_bodov - 2; index >= 0; --index)
  {
    if(je_hore(priamka, body[index]) >= 0)
    {
      while(1)
        {
          if(*pocet_h_vrcholov == 1)
          {
            horny_obal->obal[*pocet_h_vrcholov] = body[index];
            (*pocet_h_vrcholov) += 1;
            break;
          }
          if( determinant(horny_obal->obal[(*pocet_h_vrcholov) - 2],
                          horny_obal->obal[(*pocet_h_vrcholov) - 1],
                          body[index]) >= 0)
          {
            horny_obal->obal[*pocet_h_vrcholov] = body[index];
            (*pocet_h_vrcholov) += 1;
            break;
          }
          else
          {
            (*pocet_h_vrcholov) -= 1;
          }
        }
    }
  }
}

int main()
{
  int index, pocet_bodov;
  scanf("%d", &pocet_bodov);

  BOD *body = malloc(pocet_bodov * sizeof(BOD));
  OBAL *dolny_obal = malloc(sizeof(OBAL));
       dolny_obal->obal = malloc(pocet_bodov * sizeof(BOD));
  OBAL *horny_obal = malloc(sizeof(OBAL));
       horny_obal->obal = malloc(pocet_bodov * sizeof(BOD));

  nacitaj_suradnice(body, pocet_bodov);
  usporiadaj(body, pocet_bodov);

  najdi_horny_a_dolny_obal(body, horny_obal, dolny_obal, pocet_bodov);

  double obvod;
  obvod = vypocitaj_obvod(horny_obal);
  obvod += vypocitaj_obvod(dolny_obal);
  printf("%.3lf", obvod);

  return 0;
}
