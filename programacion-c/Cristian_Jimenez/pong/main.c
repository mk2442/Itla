#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define V 21
#define H 75

void inicio(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia);
void borde(char campo [V][H]);
void raqjug(char campo[V][H], int inijug, int finjug);
void raqia(char campo[V][H], int iniia, int finia);
void pel(char campo[V][H], int pelx, int pely);
void leercamp(char campo[V][H]);
void gameloop(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia, int modx, int mody, int modia);
void draw(char campo[V][H]);
void input(char campo[V][H], int *pelx, int *pely, int *inijug, int *finjug, int *iniia, int *finia, int *modx, int *mody, int *modia, int * gol);
void update(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia);

int main()
{
    int pelx, pely, inijug, finjug, iniia, finia;
    int modx, mody, modia;
    char campo[V][H];

    pelx = 37;
    pely = 10;

    inijug = 8;
    finjug = 12;

    iniia = 8;
    finia = 12;

    srand(time(NULL));

    do
    {
        modx = (rand() %2)*2 - 1;
        mody = (rand() %2)*2 - 1;
    }while((modx == 0) && (mody == 0));

    modia = -1;

    inicio(campo, pelx, pely, inijug, finjug, iniia, finia);
    gameloop(campo, pelx, pely, inijug, finjug, iniia, finia, modx, mody, modia);
    system("pause");
    return 0;
}

void inicio(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia)
{
    borde(campo);
    raqjug(campo, inijug, finjug);
    raqia(campo, iniia, finia);
    pel(campo, pelx, pely);
}

void borde(char campo [V][H])
{
    int i, j;

    for(i=0; i<V; i++)
    {
        for(j=0; j<H; j++)
        {
            if(i == 0 || i == V-1)
            {
                campo[i][j] = '-';
            }
            else if(j == 0 || j == H-1)
            {
                campo[i][j] = '|';
            }
            else
            {
                campo[i][j] = ' ';
            }
        }
    }
}

void raqjug(char campo[V][H], int inijug, int finjug)
{
    int i, j;

    for(i = inijug; i<= finjug; i++)
    {
        for(j = 2; j<= 3; j++)
        {
            campo[i][j] = 'X';
        }
    }
}

void raqia(char campo[V][H], int iniia, int finia)
{
    int i, j;

    for(i = iniia; i<= finia; i++)
    {
        for(j = H-4; j <= H-3; j++)
        {
            campo[i][j] = 'X';
        }
    }
}

void pel(char campo[V][H], int pelx, int pely)
{
    campo[pely][pelx] = 'O';
}

void leercamp(char campo[V][H])
{
    int i, j;

    for(i=0; i<V; i++)
    {
        for(j=0;j<H; j++)
        {
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }
}

void gameloop(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia, int modx, int mody, int modia)
{
    int gol = 0;

    do
    {
        draw(campo);
        input(campo, &pelx, &pely, &inijug, &finjug, &iniia, &finia, &modx, &mody, &modia, &gol);
        update(campo, pelx, pely, inijug, finjug, iniia, finia);
    }while(gol == 0);
}

void draw(char campo[V][H])
{
    system("cls");
    leercamp(campo);
}

void input(char campo[V][H], int *pelx, int *pely, int *inijug, int *finjug, int *iniia, int *finia, int *modx, int *mody, int *modia, int * gol)
{
    char key;
    int i;

    if(*pely == 1 || *pely == (V-2))
    {
        *mody *= -1;
    }

    if(*pelx == 1 || *pelx == (H-2))
    {
        *gol = 1;
    }

    if(*pelx == 4)
    {
        for(i = (*inijug); i<= (*finjug); i++)
        {
            if(i == (*pely))
            {
                *modx *= -1;
            }
        }
    }
    if(*pelx == (H-5))
    {
        for(i = (*iniia); i<= (*finia); i++)
        {
            if(i == (*pely))
            {
                *modx *= -1;
            }
        }
    }
    if(*iniia == 1 || *finia == (V-1))
    {
        *modia *= -1;
    }

    if(*gol == 0)
    {
        *pelx += (*modx);
        *pely += (*mody);

        *iniia += (*modia);
        *finia += (*modia);
    }

    if(kbhit() == 1)
    {
        key = getch();

        if(key == 'w')
        {
            if(*inijug != 1)
            {
                *inijug -= 1;
                *finjug -= 1;
            }
        }

        if(key == 's')
        {
            if(*finjug != (V-2))
            {
                *inijug +=1;
                *finjug +=1;
            }
        }
    }
}

void update(char campo[V][H], int pelx, int pely, int inijug, int finjug, int iniia, int finia)
{
    borde(campo);
    raqjug(campo, inijug, finjug);
    raqia(campo, iniia, finia);
    pel(campo, pelx, pely);
}
