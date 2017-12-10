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

double determinant(BOD A, BOD B, BOD C)
{
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

double vzdialenost(BOD A, BOD B)
{
  double num = pow( (B.x-A.x), 2.0) + pow( (B.y-A.y), 2.0);
  return num;
}

void vymen_prvky(BOD *bod1, BOD *bod2)
{
  BOD pomocny;
  pomocny = *bod1;
  *bod1 = *bod2;
  *bod2 = pomocny;
}

void usporiadaj(BOD *body, int pocet_bodov)
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

void nacitaj_suradnice(struct Bod *body, int pocet_bodov)
{
  int index;
  for(index = 0; index < pocet_bodov; ++index)
  {
    scanf("%lf %lf", &body[index].x, &body[index].y);
  }
}

PRIAMKA vypocitaj_priamku(BOD A, BOD B)
{
  PRIAMKA p;
  p.a = A.y - B.y;
  p.b = B.x - A.x;
  p.c = A.x * B.y - A.y * B.x;
  return p;
}
double vypocitaj_obvod(BOD *obal, int pocet_prvkov)
{
  int index;
  double obvod = 0.0, medzivysledok;

  for(index = 0; index < pocet_prvkov - 1; ++index)
  {
    medzivysledok = vzdialenost(obal[index], obal[index+1]);
    obvod += sqrt(medzi);
  }

  return obvod;
}

int main()
{
  int index, pocet_bodov, max_lavy, max_pravy;
  scanf("%d", &pocet_bodov);

  BOD *body = malloc(pocet_bodov * sizeof(BOD));
  BOD *dolny_obal = malloc(pocet_bodov * sizeof(BOD));
  BOD *horny_obal = malloc(pocet_bodov * sizeof(BOD));

  nacitaj_suradnice(body, pocet_bodov);
  usporiadaj(body, pocet_bodov);
  max_pravy = pocet_bodov - 1;
  max_lavy = 0;
  dolny_obal[0] = body[max_lavy];
  horny_obal[0] = body[max_pravy];
  int pocet_d_vrcholov = 1,
      pocet_h_vrcholov = 1;

  PRIAMKA priamka;
  priamka = vypocitaj_priamku(body[max_lavy], body[max_pravy]);

  for(index = 1; index < pocet_bodov; ++index)
  {
    if( je_hore(priamka, body[index] ) <= 0)
    {
      while(1)
      {
        if(pocet_d_vrcholov == 1)
        {
          dolny_obal[pocet_d_vrcholov++] = body[index];
          break;
        }
        if( determinant(dolny_obal[pocet_d_vrcholov - 2],
                        dolny_obal[pocet_d_vrcholov - 1],
                        body[index]) >= 0)
        {
            dolny_obal[pocet_d_vrcholov++] = body[index];
            break;
        }
        else
        {
          pocet_d_vrcholov--;
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
          if(pocet_h_vrcholov == 1)
          {
            horny_obal[pocet_h_vrcholov++] = body[index];
            break;
          }
          if( determinant(horny_obal[pocet_h_vrcholov - 2],
                          horny_obal[pocet_h_vrcholov - 1],
                          body[index]) >= 0)
          {
              horny_obal[pocet_h_vrcholov++] = body[index];
              break;
          }
          else
          {
            pocet_h_vrcholov--;
          }
        }
    }
  }

  double obvod;
  obvod = vypocitaj_obvod(horny_obal, pocet_h_vrcholov);
  obvod += vypocitaj_obvod(dolny_obal, pocet_d_vrcholov);
  printf("%.3lf", obvod);

  return 0;
}
