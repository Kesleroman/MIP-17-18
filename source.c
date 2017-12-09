#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Bod{
  double x;
  double y;
};

int je_hore(int a,
            int b,
            int c,
            struct Bod bod)
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

double determinant(struct Bod A, struct Bod B, struct Bod C)
{
  return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

double vzdialenost(struct Bod A, struct Bod B)
{
  double num = pow( (B.x-A.x) , 2.0) + pow( (B.y-A.y) , 2.0);
  return num;
}

void usporiadaj(struct Bod *body, int pocet_bodov)
{
  struct Bod pmc;
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

int main()
{
  int i, pocet_stromov, max_lavy, max_pravy;
  scanf("%d", &pocet_stromov);

  struct Bod *body = malloc(pocet_stromov * sizeof(struct Bod));
  struct Bod *dolny_obal = malloc(pocet_stromov * sizeof(struct Bod));
  struct Bod *horny_obal = malloc(pocet_stromov * sizeof(struct Bod));

  for(i = 0; i < pocet_stromov; ++i)
  {
    scanf("%lf %lf", &body[i].x, &body[i].y);
  }
  usporiadaj(body, pocet_stromov);
  for(i = 0; i < pocet_stromov; ++i)
  {

  }
  max_pravy = pocet_stromov - 1;
  max_lavy = 0;

  dolny_obal[0] = body[max_lavy];
  horny_obal[0] = body[max_pravy];
  int a = body[max_lavy].y - body[max_pravy].y, // ax + by + c = 0
      b = body[max_pravy].x - body[max_lavy].x,
      c = body[max_lavy].x * body[max_pravy].y - body[max_lavy].y * body[max_pravy].x,
      pocet_d_vrcholov = 1,
      pocet_h_vrcholov = 1;

  for(i = 1; i < pocet_stromov; ++i)
  {
    if( je_hore(a, b, c, body[i] ) <= 0)
    {
      while(1)
      {
        if(pocet_d_vrcholov == 1)
        {
          dolny_obal[pocet_d_vrcholov++] = body[i];
          break;
        }
        if( determinant(dolny_obal[pocet_d_vrcholov - 2],
                        dolny_obal[pocet_d_vrcholov - 1],
                        body[i]) >= 0)
        {
            dolny_obal[pocet_d_vrcholov++] = body[i];
            break;
        }
        else
        {
          pocet_d_vrcholov--;
        }
      }
    }
  }

  for(i = pocet_stromov - 2; i >= 0; --i)
  {
    if(je_hore(a, b, c, body[i]) >= 0)
    {
      while(1)
        {
          if(pocet_h_vrcholov == 1)
          {
            horny_obal[pocet_h_vrcholov++] = body[i];
            break;
          }
          if( determinant(horny_obal[pocet_h_vrcholov - 2],
                          horny_obal[pocet_h_vrcholov - 1],
                          body[i]) >= 0)
          {
              horny_obal[pocet_h_vrcholov++] = body[i];
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

  for(i = 0; i < pocet_d_vrcholov - 1; ++i)
  {
    medzi = vzdialenost(dolny_obal[i], dolny_obal[i+1]);
    obvod += sqrt(medzi);
  }

  for(i = 0; i < pocet_h_vrcholov - 1; ++i)
  {
    medzi = vzdialenost(horny_obal[i], horny_obal[i+1]);
    obvod += sqrt(medzi);
  }
  printf("%.3lf\n", obvod);

  return 0;
}
