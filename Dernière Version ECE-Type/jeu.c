#include "header.h"

void jeu(int niveau)
{
    /************************************************/
    /**       INITIALISATIONS ET CHARGEMENTS        */
    /************************************************/

    // Il y aura du hasard
    srand(time(NULL));

    // Image de fond
    BITMAP *decor;

    // La collection des armes (les tirs)
    t_listearmes *armes;

    // Le vaisseau manipulé par le joueur
    t_joueur *joueur;

    //boss
    t_ennemi *boss;

    //pour le AT-AT
    t_ATAT *ATAT;
    char nomfichier[256];
    ATAT=creerATAT(nomfichier);

    // La cible qui se déplace automatiquement
    t_ennemi *cible;
    t_ennemi *ennemi2[NENNEMIS];

    //on initialise la position initiale de l'écran sur le décor et les booleens
    screenx=0;
    screeny=0;
    gagne=0;
    int sortie = 0;
    int invincibiliteAstero=0;
    int invincibiliteTotale=0;
    float phase=0,alpha=2.0*M_PI/NEXEMPLES,radius=250.0;


    //chargement de l'image utilisée pour les conseils/didacticiels,
    // à terme à mettre ds un SP de chargement d'image car rien à foutre là (David)
    // mais important de ne pas le laisser ds le scrolling (chargement img = ralentissement)
    //BITMAP *yoda;
    //yoda=charger_image("images/yoda2.bmp");

    BITMAP *hangar;
    BITMAP *perdu;
    perdu=charger_image("images/menu/quitter.bmp");
    BITMAP *gagne_1;
    BITMAP *gagne_2;
    BITMAP *gagne_3;
    gagne_1=charger_image("images/menu/gagne_1.bmp");
    gagne_2=charger_image("images/menu/gagne_2.bmp");
    gagne_3=charger_image("images/menu/gagne_3.bmp");
    BITMAP *carteCollision;
    BITMAP *joueurCollision;
    BITMAP *imgAs;

    BITMAP *yoda_lvl_1_1;
    BITMAP *yoda_lvl_2_1;
    BITMAP *yoda_lvl_3_1;
    BITMAP *yoda_lvl_3_2;
    BITMAP *yoda_lvl_3_3;
    BITMAP *vador_lvl_3;
    yoda_lvl_1_1=charger_image("images/bonus/yoda_lvl_1_1.bmp");
    yoda_lvl_2_1=charger_image("images/bonus/yoda_lvl_2_1.bmp");
    yoda_lvl_3_1=charger_image("images/bonus/yoda_lvl_3_1.bmp");
    yoda_lvl_3_2=charger_image("images/bonus/yoda_lvl_3_2.bmp");
    yoda_lvl_3_3=charger_image("images/bonus/yoda_lvl_3_3.bmp");
    vador_lvl_3=charger_image("images/bonus/vador_lvl_3.bmp");

    BITMAP *bosshitimg;
    bosshitimg=charger_image("images/vaisseau/bosshit.bmp");

    if (niveau == 1)
    {
        joueur=creerJoueur("images/vaisseau/niveau1.bmp");
        decor=charger_image("images/fond/niveau_1.bmp");
       // decor=charger_image("images/fond/niveau_1_collision.bmp"); //pour tests rapide si collision déconne ou visualiser bonus
        carteCollision=charger_image("images/fond/niveau_1_collision.bmp");
        joueurCollision=charger_image("images/vaisseau/niveau1_collision.bmp");
        hangar=charger_image("images/fond/hangar.bmp");
    }

    if (niveau == 2)
    {
        joueur=creerJoueur("images/vaisseau/faucon_millenium.bmp");
        decor=charger_image("images/fond/niveau_2.bmp");
        //decor=charger_image("images/fond/niveau_2_collision.bmp");//pour tests rapide si collision déconne ou visualiser bonus
        carteCollision=charger_image("images/fond/niveau_2_collision.bmp");
        joueurCollision=charger_image("images/vaisseau/faucon_millenium_collision.bmp");
    }


    if (niveau == 3)
    {
        boss=creerBoss("images/vaisseau/boss24.bmp");
        joueur=creerJoueur("images/vaisseau/x_wing.bmp");
        decor=charger_image("images/fond/niveau_3.bmp");
        //decor=charger_image("images/fond/niveau_3_collision.bmp");////pour tests rapide si collision déconne ou visualiser bonus
        carteCollision=charger_image("images/fond/niveau_3_collision.bmp");
        joueurCollision=charger_image("images/vaisseau/x_wing_collision.bmp");
        imgAs=charger_image("images/vaisseau/asteroide.bmp");
    }

    // on crée le buffer
    page=create_bitmap(SCREEN_W,SCREEN_H);

    //créer le vaisseau et la cible
    //ennemi=creerEnnemi2("vennemi.bmp");
    remplirTabEnnemi(ennemi2, niveau);
    //cible=creerEnnemi("deathstar.bmp");

    // préparer la liste des armes (100 maxi)
    // mais vide initialement
    armes=creerListearmes(200);
    t_asteroide * asteroide[NASTEROIDES];
    remplirTabAsteroide(asteroide);

    //Pour les bonus
    t_bonus *bonus[NBONUS];
    remplirTabBonus(bonus, niveau);


/************************************************/
/*               BOUCLE DE JEU                  */
/************************************************/

    // BOUCLE DE JEU
    while (sortie!=1)
    {
        sortie = 0;
        if(key[KEY_ESC])sortie = 1;
        if (key[KEY_P])
        {
            printf("pause activee\n");
            do{
                rest(50);
            }while(!key[KEY_P]);
            printf("pause desactivee\n");
        }
        if (key[KEY_N] && invincibiliteAstero==1)
        {
            printf("invincibilite asteroides desactivee\n");
            invincibiliteAstero=0;
        }
        if (key[KEY_B] && invincibiliteAstero==0)
        {
            printf("invincibilite asteroides activee\n");
            invincibiliteAstero=1;
        }
        if (key[KEY_I] && invincibiliteTotale==1)
        {
            printf("invincibilite totale desactivee\n");
            invincibiliteTotale=0;
        }
        if (key[KEY_I] && invincibiliteTotale==0)
        {
            printf("invincibilite totale activee\n");
            invincibiliteTotale=1;
        }

        //effacer le buffer avant de remettre des choses dessus
        clear_bitmap(page);

        // bouger tout le monde
        actualiserJoueur(joueur,armes, niveau, bonus);
        actualiserTabBonus(bonus, joueur, niveau);

        //présence d'ennemis selon les niveaux
        if ((niveau==1)&&(screenx>700))actualiserTabEnnemi(ennemi2, armes, niveau);
        if ((niveau==2)&&(screenx <decor->w - SCREEN_W-100))actualiserTabEnnemi(ennemi2, armes, niveau);
        if ((niveau==1)&&(screenx <decor->w - SCREEN_W-100))    dessinerTabEnnemi(page,ennemi2);
        if (niveau==2)actualiserATAT(ATAT, armes);
        if ((niveau==3)&&(((screenx>1000)&&(screenx<3000))||((screenx>6000)&&(screenx<9000))))actualiserTabEnnemi(ennemi2, armes, niveau);
        if ((niveau==3)&&(screenx>1500)&&(screenx<10000))
        {
            phase+=M_PI/1000;
            clear_bitmap(page);
            actualiserTabAsteroide(asteroide);
        }
        if ((niveau==3)&&(screenx>10820-SCREEN_W)&&(screenx<10820))
        {
            clear_bitmap(page);
            actualiserBoss(boss, armes);
            collisionBoss(joueur, boss, bonus, invincibiliteTotale);
        }
        //actualiserEnnemi(cible);
        actualiserListearmes(armes, joueur, ATAT, boss);

        //scrolling décor
        scrolling(decor, niveau);

        if ((niveau==1)&&(screenx<700))draw_sprite(page, yoda_lvl_1_1, 300, 490);
        if ((niveau==2)&&(screenx<700))draw_sprite(page, yoda_lvl_2_1, 300, 490);
        if ((niveau==3)&&(screenx<700))draw_sprite(page, yoda_lvl_3_1, 300, 490);
        if ((niveau==3)&&(screenx>1000)&&(screenx<2000))draw_sprite(page, yoda_lvl_3_2, 300, 490);
        if ((niveau==3)&&(screenx>8000)&&(screenx<8500))draw_sprite(page, yoda_lvl_3_3, 300, 490);
        if ((niveau==3)&&(screenx>8400)&&(screenx<9500))draw_sprite(page, vador_lvl_3, 300, 490);

        // gérer les collisions
        collisionListearmes(cible,armes,ennemi2,joueur,ATAT, bonus, boss, invincibiliteTotale, niveau);
        collisionDecor(joueur, joueurCollision, niveau, carteCollision);
        niveauReussi(joueur, joueurCollision, niveau, carteCollision);
        collisionTabAsteroide(joueur,asteroide, bonus, invincibiliteAstero);
        // afficher tout le monde
        if ((niveau==3)&&(screenx>1500)&&(screenx<90000)) dessinerTabAsteroide(page, asteroide, imgAs, page, phase, alpha);
        if((niveau==3) && screenx>10820-SCREEN_W) dessinerBoss(page, boss, bosshitimg);

        dessinerJoueur(page,joueur,bonus,niveau);
        dessinerTabEnnemi(page,ennemi2);

        dessinerListearmes(page,armes);
        dessinerATAT(page, ATAT);
        dessinerTabBonus(page, bonus);

        //blit special pour avoir l'effet de sortie du hangar ds le niveau 1
        if ((niveau == 1)&&(screenx<207)) blit(hangar,page,0,0,-screenx,0,SCREEN_W,SCREEN_H);

        // afficher tout ça à l'écran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if ((joueur->collisionDecor==1)||(joueur->vivant==0)){
            clear_bitmap(page);
            clear_bitmap(screen);
            draw_sprite(screen, perdu, 0, 0);
            rest(2000);
            sortie = 1;
        }

        if (gagne==1){
            clear_bitmap(page);
            clear_bitmap(screen);
            if (niveau==1) draw_sprite(screen, gagne_1, 0, 0);
            if (niveau==2) draw_sprite(screen, gagne_2, 0, 0);
            if (niveau==3) draw_sprite(screen, gagne_3, 0, 0);
            rest(8000);
            sortie = 1;
        }
        //temporisation
        rest(20);
    }
}

/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/************************************************/


// Allouer et initialiser une arme
t_arme * creerarme(int x,int y,int type){
    t_arme *nouv;

    // Allouer
    nouv=(t_arme *)malloc(1*sizeof(t_arme));

    // Initialiser ...

    // ici ce qui est commun aux armes
    nouv->x=x;
    nouv->y=y;
    nouv->type=type;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explosé mais on initialise par sécurité
    nouv->vivant=1;

    // ici ce qui est spécifique aux types
    switch (type)
    {
        // laser
        case 0:
            nouv->tx=40;
            nouv->ty=4;
            nouv->dx=10;
            nouv->dy=0;
            nouv->img=charger_image("images/vaisseau/laser.bmp");
            nouv->couleur=makecol(255,255,0);
            break;

        // missile
        case 1:
            nouv->tx=50;
            nouv->ty=16;
            nouv->dx=2;
            // petite dispersion dans la trajectoire des missiles :
            nouv->img=charger_image("images/vaisseau/missile.bmp");
            nouv->dy=rand()%5-2;
            nouv->couleur=makecol(240,220,220);
            break;

        case 2:
            nouv->tx=40;
            nouv->ty=4;
            nouv->dx=-10;
            nouv->dy=0;
            nouv->img=charger_image("images/vaisseau/laser.bmp");
            nouv->couleur=makecol(255,255,0);
            break;

        case 3:
            nouv->tx=24;
            nouv->ty=24;
            nouv->dx=0;
            nouv->dy=0;
            nouv->img=charger_image("images/vaisseau/laseratat.bmp");
            break;

        case 4:
            nouv->tx=40;
            nouv->ty=9;
            nouv->dx=0;
            nouv->dy=0;
            nouv->img=charger_image("images/vaisseau/laserboss.bmp");
            break;
    }

    return nouv;
}

// Actualiser une arme (bouger, sortie écran, fin explosion ...)
void actualiserarme(t_arme *arme, t_joueur *joueur, t_ATAT *ATAT, t_ennemi *boss){

    int diffx, diffy;
    float coeff;
    // deplacement
    arme->x=arme->x+arme->dx;
    arme->y=arme->y+arme->dy;

    // type missile : accélère en dx mais pas au dela d'une limite
    if (arme->type==1 && arme->dx<12)
        arme->dx++;

    if (arme->type==2)
        arme->dx--;

    if (arme->type==4 && arme->dx<12)
        arme->dx--;

    if (arme->type==3 && ATAT->vivant==1)
    {
        if(joueur->x+joueur->tx/2<=ATAT->x)
        {
            if(arme->dx<1) arme->dx-=1;
            diffx=ATAT->x-500-joueur->x-joueur->tx;
            diffy=ATAT->y-joueur->y-joueur->ty;
            coeff=(float)diffy/(float)diffx;
            if (coeff<0)
                coeff*=-1;
            arme->dy-=coeff;
        }
        else //if(joueur->x>ATAT->x+ATAT->tx)
        {
            if(arme->dx>-1) arme->dx+=1;
            diffx=joueur->x-500-ATAT->x-ATAT->tx;
            diffy=ATAT->y-joueur->y-joueur->ty;
            coeff=(float)diffy/(float)diffx;
            if (coeff<0)    coeff*=-1;
            arme->dy-=coeff;
        }
    }

    // si dépasse le bord alors disparait
    if (arme->x+arme->tx<0 || arme->x>SCREEN_W || arme->y+arme->ty<0 || arme->y>SCREEN_H )
        arme->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (arme->comportement==1)
    {
        arme->cptexplo++;
        if (arme->cptexplo > 7)
            arme->vivant=0;
    }
}

// Dessiner une arme sur la bitmap bmp
void dessinerarme(BITMAP *bmp,t_arme *arme){
    // Si pas d'explosion
    if (arme->comportement==0){
        switch(arme->type)
        {
            case 0:
                //rectfill(bmp,arme->x,arme->y,arme->x+arme->tx,arme->y+arme->ty,arme->couleur);
                draw_sprite(bmp, arme->img, arme->x, arme->y);
                break;
            case 1:
                draw_sprite(bmp, arme->img, arme->x, arme->y);
                //ellipsefill(bmp,arme->x,arme->y+arme->ty/2,2*arme->tx/3,arme->ty/2,makecol(255,100,25));
                //ellipsefill(bmp,arme->x,arme->y+arme->ty/2,arme->tx/3,arme->ty/3,makecol(255,200,50));
                //triangle(bmp,arme->x,arme->y,arme->x,arme->y+arme->ty,arme->x+arme->tx,arme->y+arme->ty/2,arme->couleur);
                break;
            case 2:
                draw_sprite(bmp, arme->img, arme->x-50, arme->y);
                //rectfill(bmp,arme->x-70,arme->y,arme->x-arme->tx-70,arme->y+arme->ty,arme->couleur);
                break;

            case 3:
                draw_sprite(bmp, arme->img, arme->x-200, arme->y-55);
                //rectfill(bmp,arme->x-160,arme->y-55,arme->x-arme->tx-160,arme->y+arme->ty-55,arme->couleur);
                break;
            case 4:
                draw_sprite(bmp, arme->img, arme->x-160, arme->y);
                break;
        }
    }
    // sinon on dessine l'explosion
    // d'un diamètre décroissant et d'une couleur rougissante
    else {
        switch(arme->type)
        {
            case 0:
                circlefill(bmp,arme->x+arme->tx/2,arme->y+arme->ty/2,30-4*arme->cptexplo,makecol(255,255-15*arme->cptexplo,255-30*arme->cptexplo));
                break;
            case 1:
                circlefill(bmp,arme->x+arme->tx/2,arme->y+arme->ty/2,20-6*arme->cptexplo,makecol(255-15*arme->cptexplo,128-15*arme->cptexplo,0));
                break;
        }
    }
}

// Allouer et initialiser une liste (vide) d'armes
t_listearmes * creerListearmes(int maxarmes){
    t_listearmes *nouv;
    int i;

    nouv=(t_listearmes *)malloc(1*sizeof(t_listearmes));

    nouv->max=maxarmes;
    nouv->n=0;
    nouv->tab=(t_arme **)malloc(maxarmes*sizeof(t_arme*));

    for (i=0;i<maxarmes;i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un booléen vrai s'il reste de la place dans la liste, faux sinon
int libreListearmes(t_listearmes *la){
    return la->n < la->max;
}

// Allouer et ajouter une arme à la liste
t_arme * ajouterarme(t_listearmes *la,int x,int y,int type){
    int i;
    t_arme *arme;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un arme initialisé
    arme=creerarme(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouvé ...
    // (normalement oui car on a vérifié n<max)
    if (i<la->max){
        // Accrocher le arme à l'emplacement trouvé
        la->tab[i]=arme;
        la->n++;
    }
    // Sinon c'est qu'il y a un problème de cohérence
    else
        allegro_message("Anomalie gestion ajouterarme : liste corrompue");

    return arme;
}

// Enlever et libèrer une arme qui était dans la liste en indice i
void enleverarme(t_listearmes *la,int i){

    // Vérifier qu'il y a bien une arme accroché en indice i
    if (la->tab[i]!=NULL)
    {
        // libérer la mémoire de l'arme
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// Gérer l'évolution de l'ensemble des armes
void actualiserListearmes(t_listearmes *la, t_joueur *joueur, t_ATAT *ATAT,t_ennemi *boss){
    int i;

    // actualiser chaque arme
    // si une arme n'est plus vivante, l'enlever de la liste
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserarme(la->tab[i], joueur, ATAT, boss);
            if (!la->tab[i]->vivant){
                enleverarme(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des armes
void dessinerListearmes(BITMAP *bmp,t_listearmes *la){

    int i;
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            dessinerarme(bmp,la->tab[i]);
}

// Une arme touche un objet : elle explose (comportement 1)
void destinarme(t_arme *arme){
    arme->dx/=2;
    arme->dy/=2;
    arme->comportement=1;
    arme->cptexplo=0;
}

void destinJoueur(t_joueur *joueur){

    joueur->comportement=1;
}

void destinEnnemi2(t_ennemi *ennemi2){

    ennemi2->comportement=1;
}

// Gérer collision (éventuelle) entre une arme (un tir) et un ennemi
void collisionarme(t_ennemi *ennemi,t_arme *arme, t_ennemi *ennemi2, t_joueur *joueur, t_ATAT *ATAT, t_ennemi *boss, t_bonus *bonus[NBONUS], int invincibiliteTotale, int niveau){
    int x1g, x2d,x2g,x1d,y1h,y2b,y2h,y1b;
    int x1g2, x2d2,x2g2,x1d2,y1h2,y2b2,y2h2,y1b2;
    int collx,colly, collmx, collmy, collex, colley, collbx, collby, colltx, collty, collax, collay;
    int i, j, couleur, couleur2;

    x1g=joueur->x;
    x2d=ennemi2->x+ennemi2->tx;
    x2g=ennemi2->x;
    x1d=joueur->x+joueur->tx;
    y1h=joueur->y;
    y2b=ennemi2->y+ennemi2->ty;
    y2h=ennemi2->y;
    y1b=joueur->y+joueur->ty;

    x1g2=joueur->x;
    x2d2=ATAT->x+ATAT->tx;
    x2g2=ATAT->x;
    x1d2=joueur->x+joueur->tx;
    y1h2=joueur->y;
    y2b2=ATAT->y+ATAT->ty;
    y2h2=ATAT->y;
    y1b2=joueur->y+joueur->ty;

    int ok;
    if(invincibiliteTotale==0)  ok=0;
    if(invincibiliteTotale==1)  ok=1;
    //regarde si un bonus de bouclier actif
    for(j=0; j<NBONUS; j++)
    {
        if(bonus[j]->actif==1 && bonus[j]->bouclier==1)
        {
            ok=1;
            bonus[j]->compteur++;
            //le decompte du compteur pour le bouclier
            if(bonus[j]->compteur>500)
            {
                bonus[j]->actif=0;
                bonus[j]->compteur=0;
            }
        }
    }
    // s'il n'explose déjà pas !
    if ( arme->comportement==0 )
    {
        // si il est dans la cible alors appeler destinarme (explosion)
        //printf("vaisseau posx:%d\n", joueur->x);
        // calcul du vecteur entre arme et centre cible
        //vx = arme->x+arme->tx/2 - (ennemi->x+ennemi->tx/2);
        //vy = arme->y+arme->ty/2 - (ennemi->y+ennemi->ty/2);

        //collision missile vaisseau/vaisseau ennemi
        if (ennemi2->vivant==1 && ennemi2->comportement==0 && (arme->type==0 || arme->type==1))
        {
            collmx=ennemi2->x-arme->x-arme->tx;
            if(arme->y<=(ennemi2->y+ennemi2->ty))
                collmy=ennemi2->y-arme->y-arme->ty;

            if(collmx<=0 && (collmy<=0 && collmy>=-(ennemi2->ty+arme->ty)))
                destinEnnemi2(ennemi2);
        }
        //collision tir ennemi/vaisseau joueur
        if(ennemi2->vivant==1 && arme->type==2 && ok!=1 && arme->etat==1)
        {
            collex=arme->x-joueur->x-joueur->tx;
            colley=joueur->y-arme->y-arme->ty;
            if(collex<=0 && (colley<=0 && colley>=-(joueur->ty+arme->ty)))
                destinJoueur(joueur);
        }

        //collision joueur/vaisseau ennemi
        if ( x1g<=x2d && x2g<=x1d && y1h<=y2b && y2h<=y1b && ennemi2->vivant==1 && ok!=1)
            destinJoueur(joueur);

        //collision missile ATAT/joueur
        if (ATAT->vivant==1 && arme->type==3 && ok!=1)
        {
            if(arme->x>joueur->x+joueur->tx)
            {
                collx=arme->x-joueur->x-joueur->tx;
                colly=arme->y-joueur->y-joueur->ty;
                if(collx<0 && colly<0)
                    destinJoueur(joueur);
            }
            else
            {
                collx=joueur->x-arme->x-arme->tx;
                colly=arme->y-joueur->y-joueur->ty;
                if(collx<0 && colly<0)
                    destinJoueur(joueur);
            }
        }

        //collision joueur contre ATAT
        if ( x1g2<=x2d2 && x2g2<=x1d2 && y1h2<=y2b2 && y2h2<=y1b2 && ATAT->vivant==1 && ok!=1)
            destinJoueur(joueur);

        //collision missile boss/joueur
        if(arme->type==4 && ok!=1)
        {
            collbx=arme->x-joueur->x-joueur->tx;
            collby=joueur->y-arme->y-arme->ty;
            if(collbx<=0 && (collby<=0 && collby>=-(joueur->ty)))
                destinJoueur(joueur);

        }
        //collision missile vaisseau contre boss
        if (/*boss->vivant==1 && */niveau==3 && (arme->type==0 || arme->type==1))
        {
            colltx=boss->x-arme->x-arme->tx;
            if(arme->y<=(boss->y+boss->ty))
                collty=boss->y-arme->y-arme->ty;

            if(colltx<=0 && (collty<=0 && collty>=-(boss->ty+arme->ty)))//<---------finir de blinder
            {
                boss->touche=1;
                boss->vie--;
            }
            if(boss->vie==0)
            {
                boss->vivant==0;
                destinEnnemi2(boss);
            }

        }
    }
}

// Gérer les collisions entre les armes (tous les tirs) et un ennemi
void collisionListearmes(t_ennemi *ennemi,t_listearmes *la,t_ennemi *tab2[NENNEMIS],t_joueur *joueur, t_ATAT *ATAT, t_bonus *bonus[NBONUS], t_ennemi *boss, int invincibiliteTotale, int niveau){

    int i;
    // regarder pour chaque arme...
    for (i=0;i<la->max;i++)
    {
        if (la->tab[i]!=NULL)
        {
            collisionarme(ennemi,la->tab[i], tab2[i],joueur, ATAT, boss, bonus, invincibiliteTotale, niveau);
        }
    }
}

//detecte les collisions entre vaisseau et asteroides
void collisionAsteroide(t_joueur *joueur, t_asteroide * asteroide)
{
    int x1g3, x2d3,x2g3,x1d3,y1h3,y2b3,y2h3,y1b3;

    x1g3=joueur->x;
    x2d3=asteroide->posax+50;
    x2g3=asteroide->posax;
    x1d3=joueur->x+joueur->tx;
    y1h3=joueur->y;
    y2b3=asteroide->posay+50;
    y2h3=asteroide->posay;
    y1b3=joueur->y+joueur->ty;

    if ( x1g3<=x2d3 && x2g3<=x1d3 && y1h3<=y2b3 && y2h3<=y1b3 && asteroide->etat==1)
            destinJoueur(joueur);
}

void collisionTabAsteroide(t_joueur *joueur, t_asteroide * asteroide[NASTEROIDES], t_bonus *bonus[NBONUS], int invincibiliteAstero)
{
    int i, j, ok;
    if (invincibiliteAstero==1)
        ok=1;
    if (invincibiliteAstero==0)
        ok=0;
    for(j=0; j<NBONUS; j++)
    {
        if(bonus[j]->actif==1 && bonus[j]->bouclier==1)
        {
            ok=1;
            bonus[j]->compteur++;
            //le decompte du compteur pour le bouclier
            if(bonus[j]->compteur>500)
                bonus[j]->actif=0;
                bonus[j]->compteur=0;
        }
    }

    for(i=0; i<NASTEROIDES;i++)
    {
        if(ok!=1 && asteroide[i]->etat==1)
            collisionAsteroide(joueur, asteroide[i]);
    }

}

// Allouer et initialiser un joueur
t_joueur * creerJoueur(char *nomimage){
    t_joueur *nouv;

    // Allouer
    nouv = (t_joueur *)malloc(1*sizeof(t_joueur));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = 0;
    nouv->y = SCREEN_H/2-nouv->ty/2;
    nouv->vit = 5;
    nouv->vivant=1;
    nouv->comportement=0;
    nouv->cptexplo=0;
    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;
    nouv->niveauReussi = 0;
    nouv->collisionDecor = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur *joueur,t_listearmes *la, int niveau, t_bonus *bonus[NBONUS]){

    int i, cad=10 ;
    int coefficientVitesse = 2;//but on pourra eventuellement modifier la vitesse de déplacement grâce à un bonus/malus, ou via options

    for(i=0; i<NBONUS; i++)
    {
        if(bonus[i]->actif==1 && bonus[i]->accel==1)
        {
            coefficientVitesse=4;
            bonus[i]->compteur++;
            if(bonus[i]->compteur>200)
            {
                bonus[i]->actif=0;
                bonus[i]->compteur=0;
            }
        }

        if(bonus[i]->actif==1 && bonus[i]->cadence==1)
        {
            cad=5;
            bonus[i]->compteur++;
            if(bonus[i]->compteur>200)
            {
                bonus[i]->actif=0;
                bonus[i]->compteur=0;
            }
        }

    }

    //verrouiller le déplacement au début du niveau 1(la sortie du hangar)
    if ((niveau ==1)&&(screenx<500))
        joueur->y = 420;

     else{

    if (clavier==0){
        //si on utilise la souris
        joueur->dx = coefficientVitesse/2*(mouse_x - (joueur->x + joueur->tx/2));
        joueur->dy = coefficientVitesse/2*(mouse_y - (joueur->y + joueur->ty/2));
        // mais il faut limiter la vitesse : borner les valeurs obtenues
        if (joueur->dx>10 ) joueur->dx= 10;
        if (joueur->dx<-10) joueur->dx=-10;
        if (joueur->dy>10 ) joueur->dy= 10;
        if (joueur->dy<-10) joueur->dy=-10;

        joueur->precx = joueur->x;
        joueur->precy = joueur->y;

        joueur->x += joueur->dx;
        joueur->y += joueur->dy;

        joueur->vit = sqrt((joueur->dx*joueur->dx)+(joueur->dy*joueur->dy));


        // espace = laser
        if ( mouse_b&1 && (joueur->cpttir0>=cad)){
            ajouterarme(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
            joueur->cpttir0 = 0;
        }


        // entrée = missile
       if ( mouse_b&2 && (joueur->cpttir1>=5*cad)){
            ajouterarme(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,1);
            joueur->cpttir1 = 0;
        }

    }

    if(clavier==1){
        // Si on utilise le clavier
        //Déplacements instantanés (pas d'inertie)
        if (key[KEY_LEFT]){
            joueur->x -= coefficientVitesse*joueur->vit;
            if (joueur->x<0)
                joueur->x=0;
        }

        if (key[KEY_RIGHT]){
            joueur->x += coefficientVitesse*joueur->vit;
            if (joueur->x+joueur->tx > SCREEN_W)
                joueur->x=SCREEN_W-joueur->tx;
        }

        if (key[KEY_UP]){
            joueur->y -= coefficientVitesse*joueur->vit;
            if (joueur->y<0)
                joueur->y=0;
        }

        if (key[KEY_DOWN]){
            joueur->y += coefficientVitesse*joueur->vit;
            if (joueur->y+joueur->ty > SCREEN_H)
                joueur->y=SCREEN_H-joueur->ty;
        }

        // Gestion du tir...

        // incrémenter la tempo des tirs
        joueur->cpttir0++;
        joueur->cpttir1++;

        // si le joueur appuie sur la gachette et arme ok...
        // espace = laser
        if (key[KEY_SPACE] && joueur->cpttir0>=cad){
            ajouterarme(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
            joueur->cpttir0 = 0;
        }
        // entrée = missile
        if (key[KEY_ENTER] && joueur->cpttir1>=5*cad){
            ajouterarme(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,1);
            joueur->cpttir1 = 0;
        }
    }
     }
    if (joueur->comportement==1)
    {
        joueur->cptexplo++;
        if (joueur->cptexplo > 7)
            joueur->vivant=0;
    }
}

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur *joueur, t_bonus *bonus[NBONUS], int niveau){
    int i, x;
    if (joueur->vivant==1)
    {
        draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
        //si bonus de bouclier actif on dessine un cercle vide bleu autour
        for(i=0; i<NBONUS; i++)
        {
            if(bonus[i]->actif==1 && bonus[i]->bouclier==1)
            {
                if (niveau=3)   x=500;
                else    x=200;
                if(bonus[i]->compteur<x)
                    circle(bmp, joueur->x+joueur->tx/2, joueur->y+joueur->ty/2, 100, makecol(0,0,255));
            }
        }
    }

    if (joueur->comportement==1) //on dessine l'explosion (ici, simple rond qui diminue en taille et change de couleur. Mettre une vraie animation ?
        circlefill(bmp,joueur->x+joueur->tx/2,joueur->y+joueur->ty/2,70-4*joueur->cptexplo,makecol(255,255-15*joueur->cptexplo,255-30*joueur->cptexplo));
}

t_ennemi * creerEnnemi2(char *nomimage, int niveau){

    // Allouer
    t_ennemi *nouv;
    nouv = (t_ennemi *)malloc(1*sizeof(t_ennemi));

    // Initialiser
    nouv->img=charger_image(nomimage);

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;
    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;
    nouv->comportement=0;
    nouv->cptexplo=0;
    nouv->x = 1000;
    nouv->dx=rand()%(6-2)+2;
    nouv->dy=0;
    nouv->vivant=0;

    switch(niveau)
    {
        case'1':	nouv->y = rand()%(SCREEN_H - nouv->ty);
        break;

        case'2':	nouv->y = rand()%(SCREEN_H - nouv->ty - 350);
        break;
    }

    return nouv;
}

void remplirTabEnnemi(t_ennemi * tab2[NENNEMIS], int niveau){

    int i;

    // On "accroche" Narme nouveaux armes
    // à chaque case du tableau
    for (i=0;i<NENNEMIS;i++)
        tab2[i]=creerEnnemi2("images/vaisseau/TIE.bmp", niveau);

    if (niveau==1)
    {
        for (i=0; i<4;i++)
            tab2[i]->vivant=1;
    }

    //idem pour l'instant, on pourra augmenter le nb d'ennemis
    if (niveau==2)
    {
        for (i=0; i<3;i++)
            tab2[i]->vivant=1;
    }
}

// Actualiser un ennemi (bouger ...)
void actualiserEnnemi2(t_ennemi *ennemi2, t_listearmes *la, int niveau){

    if (ennemi2->x < 0-ennemi2->tx && ennemi2->vivant==1)
    {
        ennemi2->x=rand()%(1100-1024)+1024;
        if(niveau==1)	ennemi2->y=rand()%(SCREEN_H-ennemi2->ty);
        if(niveau==2)	ennemi2->y=rand()%(SCREEN_H-ennemi2->ty-350);
        ennemi2->dx=rand()%(6-2)+2;
        //ennemi->tir=0;
    }

    // incrémenter la tempo des tirs
    ennemi2->cpttir0++;
    ennemi2->cpttir1++;

    //le vaisseau tire tout les 100 atteint
    //laser
    if (ennemi2->cpttir0>=50 && ennemi2->vivant==1){
        ajouterarme(la,ennemi2->x+ennemi2->tx,ennemi2->y+ennemi2->ty/2,2);
        ennemi2->cpttir0 = 0;
    }
    // entrée = missile

    //POUR UNE TRAJECTOIRE SINUSOIDALE
    /*if (x>=360)
    {
        x=0;
    }
    a=sin(x);
    arme->posy=arme->posy+a*30;
    //arme->posy=arme->posy+arme->depy;
    arme->i=x+1;*/

    if (ennemi2->comportement==1)
    {
        ennemi2->cptexplo++;
        if (ennemi2->cptexplo > 7)
            ennemi2->vivant=0;
    }

    ennemi2->x=ennemi2->x-ennemi2->dx;
    ennemi2->y=ennemi2->y+ennemi2->dy;
}

void enleverEnnemi2(t_ennemi *tab2[NENNEMIS], int i){
int compteurmorts;
    // Vérifier qu'il y a bien un arme accroché en indice i
    if (tab2[i]!=NULL)
    {
        // libérer la mémoire du arme
        free(tab2[i]);
        // marquer l'emplacement comme libre
        tab2[i]=NULL;
    }
    compteurmorts++;
   int* pcompteurmorts=&compteurmorts;
}

// Gérer l'évolution de l'ensemble des armes
void actualiserTabEnnemi(t_ennemi * tab2[NENNEMIS], t_listearmes *la, int niveau){

    int i;
    for (i=0;i<NENNEMIS;i++)
        if (tab2[i]!=NULL)
        {
            actualiserEnnemi2(tab2[i], la, niveau);
            if(tab2[i]->vivant==0 && tab2[i]->comportement==1)
            {
                enleverEnnemi2(tab2[i], i);
                //fait reapparaitre un ennemi
                tab2[i]=creerEnnemi2("images/vaisseau/TIE.bmp", niveau);
                tab2[i]->vivant=1;
                tab2[i]->x=rand()%(1500-1200)+1200;
            }
        }

}

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi2){
    draw_sprite(bmp,ennemi2->img,ennemi2->x,ennemi2->y);
    if (ennemi2->comportement==1)
        circlefill(bmp,ennemi2->x+ennemi2->tx/2,ennemi2->y+ennemi2->ty/2,50-4*ennemi2->cptexplo,makecol(255,255-15*ennemi2->cptexplo,255-30*ennemi2->cptexplo));
}

void dessinerTabEnnemi(BITMAP *bmp, t_ennemi *tab2[NENNEMIS]){

    int i;
    for (i=0; i<NENNEMIS; i++)
    {
        if (tab2[i]->vivant==1)
            dessinerEnnemi(bmp,tab2[i]);
    }
}

void collisionDecor(t_joueur *joueur, BITMAP *joueurCollision, int niveau, BITMAP *carteCollision){

    //TEST DE COLLISION : On balaie l'ensemble des positions occupées par le vaisseau. Pour chaque pixel, on regarde la couleur
    //de la carte de collision. Si elle correspond à la valeur interdite, alors on fait passer le booléen collision à 1 => explosion
    //pour réduire le nombre de tests à chaque clock  nombre de pixels du vaisseau), on charge une image de collision du vaisseau, qui
    //ne sera pas affichée à l'écran. Les seules parties interessantes sont certains points aux contours du vaisseau. (un point sur 2 par exemple)
    //on y pose des repères (pixels d'une certaine couleur). On ne fera le test de carte de collision que quand on atteint ces pixels
    int x, y;

    for(x = screenx + joueur->x; x < screenx + joueur->x + joueur->tx; x++){
        for(y = joueur->y; y < joueur->y + joueur->ty; y++){
            if((getpixel(joueurCollision, x - screenx - joueur->x, y-joueur->y)== makecol(255,0,0))){
                if((getpixel(carteCollision,x,y)==makecol(255,0,0))) joueur->collisionDecor=1;
            }
        }
    }
}

void niveauReussi(t_joueur *joueur, BITMAP *joueurCollision, int niveau, BITMAP *carteCollision){

    //TEST DE COLLISION : même principe que le sous programme collisionDecor. Cette fois, on détecte une autre couleur (jaune) qui signifie la fin du niveau
    int x, y;

    for(x = screenx + joueur->x; x < screenx + joueur->x + joueur->tx; x++){
        for(y = joueur->y; y < joueur->y + joueur->ty; y++){
            if((getpixel(joueurCollision, x - screenx - joueur->x, y-joueur->y)== makecol(255,0,0))){
                if((getpixel(carteCollision,x,y)==makecol(255,255, 0))) gagne = 1;
            }
        }
    }
}

t_ATAT *creerATAT(char nomfichier[256]){

    int i;

    // Allouer
    t_ATAT *nouv;
    nouv = (t_ATAT *)malloc(1*sizeof(t_ATAT));
    for (i=0;i<NIMAGE;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"images/AT-AT/%d.bmp",i);
        nouv->img[i] = charger_image(nomfichier);
    }
    nouv->tx = nouv->img[0]->w; // pour la taille on se base sur la 1ère image de la séquence
    nouv->ty = nouv->img[0]->h;
    nouv->x =rand()%(1100-1024)+1024;
    nouv->y = SCREEN_H - nouv->ty - 20;
    nouv->dx = -4;

    nouv->cptdx=0;
    nouv->tmpdx=1;
    nouv->cpttir0++;
    nouv->imgcourante=0;
    nouv->cptimg=0;
    nouv->tmpimg=5;
    nouv->vivant=1;

    return nouv;
}

void dessinerATAT(BITMAP *bmp, t_ATAT *ATAT){

    draw_sprite(bmp,ATAT->img[ATAT->imgcourante],ATAT->x,ATAT->y);
}

void actualiserATAT(t_ATAT *ATAT, t_listearmes *la){

    ATAT->cptdx++;
    ATAT->cpttir0++;
    if (ATAT->cpttir0>=50 && ATAT->vivant==1){
        ajouterarme(la,ATAT->x+ATAT->tx,ATAT->y+ATAT->ty/2,3);
        ATAT->cpttir0 = 0;
    }
    if (ATAT->cptdx>=ATAT->tmpdx){
        ATAT->cptdx=0;
        ATAT->x+=ATAT->dx;
    }
    if (ATAT->x+ATAT->tx<0)
    {
        ATAT->x=rand()%(1500-1100)+1100;
        ATAT->vivant=0;
    }
    if (ATAT->x>0 && ATAT->x<1024)
    {
        ATAT->vivant=1;
    }
    // gestion enchainement des images
    // incrémenter imgcourante une fois sur tmpimg
    ATAT->cptimg++;
    if (ATAT->cptimg>=ATAT->tmpimg){
        ATAT->cptimg=0;

        ATAT->imgcourante++;
        // quand l'indice de l'image courante arrive à NIMAGE
        // on termina la boucle en réafichant la 1ere image
        if (ATAT->imgcourante>=NIMAGE)
            ATAT->imgcourante=0;

    }
}

t_asteroide *creerAsteroide()
{
    t_asteroide *asteroide;
    asteroide = (t_asteroide *)malloc(1*sizeof(t_asteroide));

    asteroide->posax = rand()%(1600-800)+800;
    asteroide->posay = rand()%(SCREEN_H - asteroide->tay);

    asteroide->tax=150;
    asteroide->tay=141;

    asteroide->depax=rand()%(4-1)+1;
    asteroide->depay=rand()%(3-1)+1;

    asteroide->etat=0;
    asteroide->rota=rand()%(3000-200)+200;
    asteroide->coll=0;

    return asteroide;
}

// Remplir un tableau avec des (pointeurs sur) acteurs créés
void remplirTabAsteroide(t_asteroide * tab[NASTEROIDES])
{
    int i;
    // On "accroche" NACTEUR nouveaux acteurs à chaque case du tableau
    for (i=0;i<NASTEROIDES;i++)
        tab[i]=creerAsteroide();

   for (i=0; i<10;i++)
            tab[i]->etat=1;
}


// Actualiser un acteur (bouger ...)
void actualiserAsteroide(t_asteroide *asteroide)
{
    // contrôle des bords : ici on décide de rebondir sur les bords
    if (asteroide->posax < 0-asteroide->tax)
    {
        asteroide->posax=rand()%(2048-1200)+1200;
        asteroide->posay=rand()%(SCREEN_H-asteroide->tay);
        asteroide->rota=rand()%(3000-200)+200;
        asteroide->depay=rand()%(5-1)+1;
    }
    if (screenx>1500 && screenx<9000)
    {
        if(((asteroide->posay<0)&&(asteroide->depay<0))||(((asteroide->posay)+(asteroide->tay)/2>SCREEN_H)&&(asteroide->depay>0)))
        asteroide->depay = - asteroide->depay;
    }
    if (screenx>9000)
    {
        if(asteroide->posay<0-asteroide->tay || asteroide->posay>SCREEN_H || asteroide->posax-asteroide->tax<0)
            asteroide->etat=0;
    }

    asteroide->posax=asteroide->posax-asteroide->depax;
    asteroide->posay=asteroide->posay+asteroide->depay;
}


// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabAsteroide(t_asteroide * tab[NASTEROIDES])
{
    int i;

    for (i=0;i<NASTEROIDES;i++)
        actualiserAsteroide(tab[i]);
}

// Dessiner un acteur sur une bitmap bmp
void dessinerAsteroide(BITMAP *bmp, t_asteroide *asteroide, BITMAP *imgAs, BITMAP *page, float phase, float alpha)
{
    rotate_sprite(page, imgAs, asteroide->posax, asteroide->posay, ftofix((phase-7*alpha)*asteroide->rota/M_PI));
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerTabAsteroide(BITMAP *bmp,t_asteroide *tab[NASTEROIDES], BITMAP *imgAs, BITMAP *page, float phase, float alpha)
{
    int i;
    for (i=0; i<NASTEROIDES; i++)
    {
        if (tab[i]->etat==1)
            dessinerAsteroide(bmp,tab[i], imgAs, page, phase, alpha);
    }
}


t_bonus * creerBonus(char *nomimage, char *nomimage2, int niveau){

    // Allouer
    t_bonus *nouv;
    nouv = (t_bonus *)malloc(1*sizeof(t_bonus));

    // Initialiser
    nouv->img=charger_image(nomimage);
    nouv->img2=charger_image(nomimage2);
    nouv->tx=64;
    nouv->ty=100;

    //if (niveau==2)  nouv->x=rand()%(7000-500)+500;
    //else    nouv->x=rand()%(10000-500)+500;
    nouv->y=rand()%(720-nouv->tx);
    nouv->etat=0;   //on affiche ou pas le bonus
    nouv->compteur=0;   //timer du bonus
    nouv->cadence=0;
    nouv->nuke=0;
    nouv->accel=0;
    nouv->bouclier=0;
    nouv->actif=0;  //tps d'activation du bonus
    nouv->dx=-1;

    return nouv;
}


void remplirTabBonus(t_bonus * bonus[NBONUS], int niveau){

    int i, j;

    // On "accroche" Narme nouveaux armes
    // à chaque case du tableau
    for (i=0;i<NBONUS;i++)
    {
        bonus[i]=creerBonus("images/bonus/vador.bmp", "images/bonus/yoda.bmp", niveau);

        //1000 est la pas d'apparition des bonus et i!=0 sinon bonus des le 1er pixel
        if (niveau==1)
        {
            if(i>=4)    bonus[i]->x=i*1000;
            bonus[i]->etat=1;
        }

        //idem pour l'instant, on pourra augmenter le nb d'ennemis
        if (niveau==2)
        {
            if(i>=4)    bonus[i]->x=i*700;
            bonus[i]->etat=1;
        }
        if (niveau==3)
        {
            if(i>=4)    bonus[i]->x=i*500;
            bonus[i]->etat=1;
        }

        if(niveau!=3)
        {
            j=rand()%3;
            switch(j)
            {
                case 0:
                    bonus[i]->accel=1;
                    bonus[i]->cadence=0;
                    bonus[i]->bouclier=0;
                    bonus[i]->nuke=0;
                    break;
                case 1:
                    bonus[i]->cadence=1;
                    bonus[i]->bouclier=0;
                    bonus[i]->nuke=0;
                    bonus[i]->accel=0;
                    break;
                case 2:
                    bonus[i]->bouclier=1;
                    bonus[i]->cadence=0;
                    bonus[i]->nuke=0;
                    bonus[i]->accel=0;
                    break;
            }
        }

        if(niveau==3 && i<=5)
        {
            j=rand()%2;

            switch(j)
            {
                case 0:
                    bonus[i]->accel=0;
                    bonus[i]->cadence=0;
                    bonus[i]->bouclier=1;
                    bonus[i]->nuke=0;
                    break;
                case 1:
                    bonus[i]->cadence=0;
                    bonus[i]->bouclier=0;
                    bonus[i]->nuke=0;
                    bonus[i]->accel=1;
                    break;
            }
        }
        if(niveau==3 && i>5)
        {
            j=rand()%3;

            switch(j)
            {
                case 0:
                    bonus[i]->accel=0;
                    bonus[i]->cadence=0;
                    bonus[i]->bouclier=1;
                    bonus[i]->nuke=0;
                    break;
                case 1:
                    bonus[i]->cadence=0;
                    bonus[i]->bouclier=0;
                    bonus[i]->nuke=0;
                    bonus[i]->accel=1;
                    break;
                case 2:
                    bonus[i]->cadence=1;
                    bonus[i]->bouclier=0;
                    bonus[i]->nuke=0;
                    bonus[i]->accel=0;
            }
        }
    }

}

void actualiserBonus(t_bonus *bonus, int niveau, t_joueur *joueur){

    int x1g, x2d,x2g,x1d,y1h,y2b,y2h,y1b;
    x1g=joueur->x;
    x2d=bonus->x+bonus->tx;
    x2g=bonus->x;
    x1d=joueur->x+joueur->tx;
    y1h=joueur->y;
    y2b=bonus->y+bonus->ty;
    y2h=bonus->y;
    y1b=joueur->y+joueur->ty;
    //bonus->compteur++;


    //Si joueur touche bonus il devient actif
    if ( x1g<=x2d && x2g<=x1d && y1h<=y2b && y2h<=y1b && bonus->etat==1)
    {
        bonus->actif=1;
        bonus->etat=0;
    }
    /*if (joueur->x>bonus->x)
    {
        if(joueur->x-bonus->x-bonus->tx>1024)
            bonus->etat=0;
            bonus->actif=0;
    }*/
    //le bonus avance pour ne pas etre fixe
    bonus->x=bonus->x+bonus->dx;

}

void actualiserTabBonus(t_bonus * bonus[NBONUS], t_joueur *joueur, int niveau){

    int i;
    for (i=0;i<NBONUS;i++)
        if (bonus[i]!=NULL && bonus[i]->etat==1)
        {
            actualiserBonus(bonus[i], niveau, joueur);
        }

}

void dessinerBonus(BITMAP *bmp,t_bonus *bonus){
    //si bonus suivants on affiche vador
    if ((bonus->nuke==1 || bonus->cadence==1) && bonus->etat==1)
        draw_sprite(bmp,bonus->img,bonus->x,bonus->y);
    //si bonus suivant on affiche yoda
    if ((bonus->accel==1 || bonus->bouclier==1) && bonus->etat==1)
        draw_sprite(bmp,bonus->img2,bonus->x,bonus->y);
}

void dessinerTabBonus(BITMAP *bmp, t_bonus *bonus[NBONUS]){

    int i;
    for (i=0; i<NBONUS; i++)
    {
        if (bonus[i]->etat==1)
            dessinerBonus(bmp,bonus[i]);
    }
}


t_ennemi *creerBoss(char *nomimage){

    t_ennemi *nouv;

    // Allouer
    nouv = (t_ennemi *)malloc(1*sizeof(t_ennemi));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H/2-nouv->ty/2;
    nouv->dx=0;
    nouv->dy=0;
    nouv->vivant=1;
    nouv->comportement=0;
    nouv->cpttir0=0;
    nouv->cpttir1=0;
    nouv->touche=0;
    nouv->cptexplo=0;
    nouv->vie=500;

    return nouv;
}

void actualiserBoss(t_ennemi *boss, t_listearmes *la){

    boss->cpttir0++;
    boss->cpttir1++;

    // proba de changement de déplacement : une chance sur 20
    if ( rand()%20==0 ){
        // Nouveau vecteur déplacement
        boss->dx = rand()%7-2;
        boss->dy = rand()%7-2;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (  ( boss->x < SCREEN_W/2 && boss->dx < 0 ) ||
           ( boss->x + boss->tx > SCREEN_W && boss->dx > 0) )
        boss->dx = -boss->dx;

    if  (  ( boss->y < 0 && boss->dy < 0 ) ||
           ( boss->y + boss->ty > SCREEN_H && boss->dy > 0) )
        boss->dy = -boss->dy;

    //le boss tire tout les 10 atteint
    //laser
    if (boss->cpttir0>=50 && boss->vivant==1){
        ajouterarme(la,boss->x+boss->tx,boss->y+boss->ty/2,4);
        boss->cpttir0 = 0;
    }

    if (boss->comportement==1)
    {
        boss->cptexplo++;
        if (boss->cptexplo > 7)
        {
            boss->vivant=0;
            gagne = 1;
        }
    }
   // if (boss->vivant=0)gagne = 1;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    boss->x = boss->x + boss->dx;
    boss->y = boss->y + boss->dy;

}

// Dessiner ennemi sur la bitmap bmp
void dessinerBoss(BITMAP *bmp,t_ennemi *boss, BITMAP *bosshitimg){

    if (boss->touche==0 && boss->vivant==1)
        draw_sprite(bmp,boss->img,boss->x,boss->y);
    if (boss->touche==1 && boss->vivant==1)
    {
        draw_sprite(bmp,bosshitimg,boss->x,boss->y);
        boss->touche=0;
    }
    if (boss->comportement==1)
        circlefill(bmp,boss->x+boss->tx/2,boss->y+boss->ty/2,200-4*boss->cptexplo,makecol(255,255-15*boss->cptexplo,255-30*boss->cptexplo));
}

void collisionBoss(t_joueur *joueur, t_ennemi *boss, t_bonus *bonus[NBONUS], int invincibiliteTotale){

    int x1g4, x2d4,x2g4,x1d4,y1h4,y2b4,y2h4,y1b4;
    int j, ok=0;
    if(invincibiliteTotale==0)  ok=0;
    if(invincibiliteTotale==1)  ok=1;

    x1g4=joueur->x;
    x2d4=boss->x+boss->tx;
    x2g4=boss->x;
    x1d4=joueur->x+joueur->tx;
    y1h4=joueur->y;
    y2b4=boss->y+boss->ty;
    y2h4=boss->y;
    y1b4=joueur->y+joueur->ty;


    for(j=0; j<NBONUS; j++)
    {
        if(bonus[j]->actif==1 && bonus[j]->bouclier==1)
        {
            ok=1;
            bonus[j]->compteur++;
            //le decompte du compteur pour le bouclier
            if(bonus[j]->compteur>500)
            {
                bonus[j]->actif=0;
                bonus[j]->compteur=0;
            }
        }
    }

    if ( x1g4<=x2d4 && x2g4<=x1d4 && y1h4<=y2b4 && y2h4<=y1b4 && ok!=1 && boss->vivant==1)destinJoueur(joueur);
}
