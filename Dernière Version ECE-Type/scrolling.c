#include "header.h"

void scrolling(BITMAP *decor, int niveau)
{
    int couleur;
    couleur = makecol(255,255,255);

    // ON DECALE SCREEN (L'ECRAN VISIBLE) SUR LE DECOR
    if ((niveau==1)&&(screenx<400))screenx++;
    if ((niveau==2)&&(screenx<100))screenx++;
    else screenx+=3;
    //else screenx+=5; //pour faire un speedrun ou des tests de fin de niveau

    // ON BLOQUE LE SCROLLING SI LA FIN DU DECOR EST ATTEINTE
    if ( screenx < 0 ) screenx=0;
    if ( screenx > decor->w - SCREEN_W ) screenx = decor->w - SCREEN_W;
    if ( screeny < 0 ) screeny=0;
    if ( screeny > decor->h - SCREEN_H ) screeny = decor->h - SCREEN_H;

    // ON EFFACE LE BUFFER EN APPLIQUANT UNE PARTIE DU DECOR (TAILLE DE L'ECRAN)
    blit(decor,page,screenx,screeny,0,0,SCREEN_W,SCREEN_H);
}
