#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Bod{
  double x;
  double y;
} BOD;

int je_hore(int a,
            int b,
            int c,
            BOD bod)
{
  if( (a * bod.x + b * bod.y + c) > 0)
  {
    return 1;
  }
  else if( (a * bod.x + b * bod.y + c) == 0)
    return 0;
    else
    {
      return -1;
    }
}

double determinant(BOD A, BOD B, BOD C)
{
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

double vzdialenost(BOD A, BOD B)
{
  double num = pow( (B.x-A.x) , 2.0) + pow( (B.y-A.y) , 2.0);
  return num;
}

void usporiadaj(BOD *body, int pocet_bodov)
{
  BOD pmc;
  int i, j, min;
  for(i = 0; i < pocet_bodov; ++i)
  {
    for(j = i, min = i; j < pocet_bodov; ++j)
    {
      if(body[min].x > body[j].x)
      {
        min = j;
      }
      if(body[min].x == body[j].x)
      {
        if(body[min].y > body[j].y)
        {
          min = j;
        }
      }
    }
    pmc = body[min];
    body[min] = body[i];
    body[i] = pmc;
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
  int a = body[max_lavy].y - body[max_pravy].y, // ax + by + c = 0
      b = body[max_pravy].x - body[max_lavy].x,
      c = body[max_lavy].x * body[max_pravy].y - body[max_lavy].y * body[max_pravy].x,
      pocet_d_vrcholov = 1,
      pocet_h_vrcholov = 1;

  for(index = 1; index < pocet_bodov; ++index)
  {
    if( je_hore(a, b, c, body[index] ) <= 0)
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
    if(je_hore(a, b, c, body[index]) >= 0)
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

  double obvod = 0.0, medzi;

  for(index = 0; index < pocet_d_vrcholov - 1; ++index)
  {
    medzi = vzdialenost(dolny_obal[index], dolny_obal[index+1]);
    obvod += sqrt(medzi);
  }

  for(index = 0; index < pocet_h_vrcholov - 1; ++index)
  {
    medzi = vzdialenost(horny_obal[index], horny_obal[index+1]);
    obvod += sqrt(medzi);
  }
  printf("%.3lf\n", obvod);

  return 0;
}
