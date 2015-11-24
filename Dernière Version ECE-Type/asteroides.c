/*#include "header.h"

#define NASTEROIDES 10
#define NEXEMPLES 8


t_asteroide *creerAsteroide();

void asteroides()
{
    printf("yolo");
    t_asteroide *creerAsteroide();
    printf("yoloswag");
    BITMAP *imgAs;
    float phase=0,alpha=2.0*M_PI/NEXEMPLES,radius=250.0;

    clear_bitmap(page);
    imgAs=charger_image("images/vaisseau/asteroide.bmp");
    //blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    t_asteroide * asteroide[NASTEROIDES];
    remplirTabAsteroide(asteroide);
    //while ((screenx>3000)&&(screenx<8000))
        //{
            phase+=M_PI/1000;
            // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
            //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)
            clear_bitmap(page);

            // 2) DETERMINER NOUVELLEs POSITIONs
            actualiserTabAsteroide(asteroide);

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            dessinerTabAsteroide(page, asteroide, imgAs, page, phase, alpha);

            // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

            // 5) TEMPORISATION
           // rest(20);
        //}
}

t_asteroide *creerAsteroide()
{
    t_asteroide *asteroide;
    asteroide = (t_asteroide *)malloc(1*sizeof(t_asteroide));

    asteroide->posax = rand()%(1100-1024)+1024;
    asteroide->posay = rand()%(SCREEN_H - asteroide->tay);

    asteroide->tax=150;
    asteroide->tay=141;

    asteroide->depax=rand()%(6-3)+3;
    asteroide->depay=rand()%(5-1)+1;

    asteroide->etat=0;
    asteroide->rota=rand()%(3000-200)+200;
    asteroide->coll=0;

    return asteroide;
}


// Remplir un tableau avec des (pointeurs sur) asteroides créés
void remplirTabAsteroide(t_asteroide * tab[NASTEROIDES])
{
    int i;
    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<NASTEROIDES;i++)
        tab[i]=creerAsteroide();

    for (i=0; i<20;i++)
        tab[i]->etat=1;
}


// Actualiser un astéroide (bouger ...)
void actualiserAsteroide(t_asteroide *asteroide)
{
    // contrôle des bords : l'astéroide rebondit sur les bords
    if (asteroide->posax < 0-asteroide->tax)        //50 est la longueur de l'image
    {
        asteroide->posax=rand()%(1200-1024)+1024; //<=====================================
        asteroide->posay=rand()%(SCREEN_H-asteroide->tay);
        asteroide->rota=rand()%(3000-200)+200;
        asteroide->depay=rand()%(5-1)+1;
    }
    if  (  ( asteroide->posay < 0 && asteroide->depay < 0 ) ||
           ( asteroide->posay + asteroide->tay > SCREEN_H && asteroide->depay > 0) )
        asteroide->depay = -asteroide->depay;

    asteroide->posax=asteroide->posax-asteroide->depax;
    asteroide->posay=asteroide->posay+asteroide->depay;
}


// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabAsteroide(t_asteroide * tab[NASTEROIDES])
{
    int i, j, x, y;
    //tentative de blindage du spawn des vaisseaux
    /*for (i=0;i<NASTEROIDES;i++)
    {
        for (j=i+1;j<NASTEROIDES;j++)
        {
            if (tab[i]->posay>tab[j]->posay && tab[i]->etat==1 && tab[j]->etat==1)
            {
                x=tab[i]->posay - tab[j]->posay;
                if (tab[i]->posax<tab[j]->posax)
                {
                    y=tab[j]->posax-tab[i]->posax-tab[i]->tax;
                    tab[j]->depay=-rand()%(5-2)+2;
                }
                if (tab[i]->posax>tab[j]->posax)
                {
                    y=tab[i]->posax-tab[j]->posax-tab[i]->tax;
                    tab[i]->depay=rand()%(5-2)+2;
                }
                if (x<tab[i]->tay && y<10)
                {
                    tab[i]->coll=1;/*tab[i]->posay=tab[i]->posay+x+10;*//*
                    tab[j]->coll=1;
                }
            }
            else if(tab[i]->posay<tab[j]->posay && tab[i]->etat==1 && tab[j]->etat==1)
            {
                x=tab[j]->posay - tab[i]->posay;
                if (tab[i]->posax<tab[j]->posax)
                {
                    y=tab[j]->posax-tab[i]->posax-tab[i]->tax;
                    tab[j]->depay=5;
                }
                if (tab[i]->posax>tab[j]->posax)
                {
                    y=tab[i]->posax-tab[j]->posax-tab[i]->tax;
                    tab[i]->depay=-5;
                }
                if (x<tab[i]->tay && y<10)
                {
                    tab[i]->coll=1;/*tab[j]->posay=tab[j]->posay+x+10;*//*
                    tab[j]->coll=1;
                }
            }
        }
    }<===============================*//*

    for (i=0;i<NASTEROIDES;i++)
        actualiserAsteroide(tab[i]);

}

// Dessiner un acteur sur une bitmap bmp
void dessinerAsteroide(BITMAP *bmp, t_asteroide *asteroide, BITMAP *imgAs, BITMAP *page, float phase, float alpha)
{
    //draw_sprite(page, imgAs, asteroide->posax, asteroide->posay);
    rotate_sprite(page, imgAs, asteroide->posax, asteroide->posay, ftofix((phase-7*alpha)*asteroide->rota/M_PI));
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerTabAsteroide(BITMAP *bmp,t_asteroide * tab[NASTEROIDES], BITMAP *imgAs, BITMAP *page, float phase, float alpha)
{
    int i;
    for (i=0; i<NASTEROIDES; i++)
    {
        if (tab[i]->etat==1)
            dessinerAsteroide(bmp,tab[i], imgAs, page, phase, alpha);
    }
}
*/
