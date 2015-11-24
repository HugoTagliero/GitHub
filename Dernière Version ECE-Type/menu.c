#include "header.h"

int main()
{
    //Declaration des images
    BITMAP *decor;
    BITMAP *page;
    BITMAP *regles;
    BITMAP *options;
    BITMAP *credits;
    BITMAP *quitter;
    BITMAP *curseur;
    BITMAP *texte_menu;
    BITMAP *texte_jouer;
    BITMAP *texte_options;
    BITMAP *texte_clavier;
    BITMAP *texte_souris;
    BITMAP *texte_oui;
    BITMAP *texte_non;
    BITMAP *texte_guide_du_rebelle;
    BITMAP *texte_credits;
    BITMAP *texte_quitter;
    BITMAP *texte_retour;
    BITMAP *texte_1;
    BITMAP *texte_2;
    BITMAP *texte_3;

    //booleens
    int quitterjeu=0;
    int retourmenu=0;
    int musique=1;
    int aiemesoreilles = 0;
    clavier = 1;//défini en variable globale donc pas de int
    int niveau = 1;


    // Lancer allegro et le mode graphique
    //lancerAllegro(1024,768);
    lancerAllegro(1024,720); //pour nos PC portables

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    //musique
    SAMPLE *theme = load_sample("starwarstheme.wav");
    if (theme==NULL)
         printf("chargement thème Star Wars impossible");//charger le fichier wav

    SAMPLE *selection = load_sample("selectionmenu.wav");
    if (selection==NULL)
         printf("chargement effet sonore impossible");//charger le fichier wav

    // chargement des images du menu
    decor=charger_image("images/menu/menu.bmp");
    regles=charger_image("images/menu/regles.bmp");
    options=charger_image("images/menu/options.bmp");
    credits=charger_image("images/menu/credits.bmp");
    quitter=charger_image("images/menu/quitter.bmp");
    curseur=charger_image("images/menu/curseur.bmp");
    texte_menu=charger_image("images/menu/texte_menu.bmp");
    texte_jouer=charger_image("images/menu/texte_jouer.bmp");
    texte_options=charger_image("images/menu/texte_options.bmp");
    texte_clavier=charger_image("images/menu/texte_clavier.bmp");
    texte_souris=charger_image("images/menu/texte_souris.bmp");
    texte_oui=charger_image("images/menu/texte_oui.bmp");
    texte_non=charger_image("images/menu/texte_non.bmp");
    texte_guide_du_rebelle=charger_image("images/menu/texte_guide_du_rebelle.bmp");
    texte_credits=charger_image("images/menu/texte_credits.bmp");
    texte_quitter=charger_image("images/menu/texte_quitter.bmp");
    texte_retour=charger_image("images/menu/texte_retour.bmp");
    texte_1=charger_image("images/menu/texte_1.bmp");
    texte_2=charger_image("images/menu/texte_2.bmp");
    texte_3=charger_image("images/menu/texte_3.bmp");
    if(musique == 1) play_sample( theme, 150, 128, 1000,1); //star wars theme yay


    while(!quitterjeu)
    {
        retourmenu=0;
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, texte_menu, 342,100);
        if (niveau ==1) draw_sprite(page, texte_1, 411, 181);
        if (niveau ==2) draw_sprite(page, texte_2, 477, 181);
        if (niveau ==3) draw_sprite(page, texte_3, 551, 181);

        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
       // textprintf_ex(page,font,60,300,makecol(0,0,0),makecol(255,0,0),"%4d %4d",mouse_x,mouse_y);

        // afficher le texte en jaune quand on passe le curseur dessus
        if ((mouse_x>406 && mouse_x<602) && (mouse_y>126 && mouse_y<171))draw_sprite(page, texte_jouer, 407, 126);
        if ((mouse_x>377 && mouse_x<635) && (mouse_y>248 && mouse_y<290))draw_sprite(page, texte_options, 377, 246);
        if ((mouse_x>365 && mouse_x<658) && (mouse_y>330 && mouse_y<430))draw_sprite(page, texte_guide_du_rebelle, 365, 330);
        if ((mouse_x>372 && mouse_x<632) && (mouse_y>483 && mouse_y<524))draw_sprite(page, texte_credits, 372, 483);
        if ((mouse_x>377 && mouse_x<630) && (mouse_y>580 && mouse_y<620))draw_sprite(page, texte_quitter, 374, 575);

        if ((mouse_x>410 && mouse_x<460) && (mouse_y>180 && mouse_y<230)){
            draw_sprite(page, texte_1, 411, 181);
            if(mouse_b&1) niveau = 1;
        }
        if ((mouse_x>476 && mouse_x<526) && (mouse_y>180 && mouse_y<230)){
            draw_sprite(page, texte_2, 477, 181);
            if(mouse_b&1) niveau = 2;
        }
        if ((mouse_x>551 && mouse_x<602) && (mouse_y>180 && mouse_y<230)){
            draw_sprite(page, texte_3, 551, 181);
            if(mouse_b&1) niveau = 3;
        }

        draw_sprite(page, curseur, mouse_x,mouse_y);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        //lancer le jeu
        if ( mouse_b&1 && (mouse_x>350 && mouse_x<670) && (mouse_y>130 && mouse_y<180)){

            //on arrête la musique du menu
            stop_sample(theme);
            if(musique == 1)play_sample( selection, 255, 128, 1000,0);
            jeu(niveau);
            if ((niveau==1)&&(gagne==1)){
                niveau = 2;
                jeu(niveau);
            }
            if ((niveau==2)&&(gagne==1)){
                niveau = 3;
                jeu(niveau);
            }

            if(musique == 1)play_sample( theme, 150, 128, 1000,1); //quand on retourne au menu après le jeu, on relance la musique
        }


        //ajouter options ici
        if ( mouse_b&1 && (mouse_x>377 && mouse_x<635) && (mouse_y>250 && mouse_y<290)){

            if(musique == 1)play_sample( selection, 255, 128, 1000,0);
            do{
                clear_bitmap(page);
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page, options, 204, 153);

                if (( mouse_b&1)&&(mouse_x>268 && mouse_x<467) && (mouse_y>290 && mouse_y<320)){//si on clique sur "clavier"
                    clavier = 1;
                    if ((musique==1))play_sample( selection, 255, 128, 1000,0);
                }

                if (clavier==1)draw_sprite(page, texte_clavier, 268, 290);//afficher "clavier" en jaune

                if (( mouse_b&1)&&(mouse_x>572 && mouse_x<731) && (mouse_y>293 && mouse_y<320)){//si on clique sur "souris"
                    clavier = 0;
                    if (musique==1)play_sample( selection, 255, 128, 1000,0);
                }
                if (clavier==0)draw_sprite(page, texte_souris, 572, 293);//afficher "souris" en jaune

                if (( mouse_b&1)&&(mouse_x>367 && mouse_x<438) && (mouse_y>479 && mouse_y<507))musique = 1;//si on clique sur "oui" pour le son
                if (musique==1)
                {
                    draw_sprite(page, texte_oui, 367, 479);//afficher "oui" en jaune
                    if (aiemesoreilles == 0)play_sample( selection, 255, 128, 1000,0);
                    if (aiemesoreilles == 0)play_sample( theme, 150, 128, 1000,1);
                    aiemesoreilles++;

                }

                if (( mouse_b&1)&&(mouse_x>550 && mouse_x<639) && (mouse_y>478 && mouse_y<505))musique = 0;//si on clique sur "non" pour le son
                if (musique==0)
                {
                    draw_sprite(page, texte_non, 550, 478);//afficher "non" en jaune
                    stop_sample(theme);
                    aiemesoreilles = 0;
                }

                if ( mouse_b&1 && (mouse_x>675 && mouse_x<800) && (mouse_y>555 && mouse_y<585)){
                    if(musique == 1)play_sample( selection, 255, 128, 1000,0);
                    retourmenu=1;//retour au menu
                }


                if ((mouse_x>672 && mouse_x<800) && (mouse_y>561 && mouse_y<580)) draw_sprite(page, texte_retour, 672, 561);

               // textprintf_ex(page,font,60,300,makecol(0,0,0),makecol(255,0,0),"%4d %4d",mouse_x,mouse_y); //=> affiche les coordonnées souris
                draw_sprite(page, curseur, mouse_x,mouse_y);

                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

            }while (retourmenu!=1);
        }

        //Guide du rebelle
        if ( mouse_b&1 && (mouse_x>350 && mouse_x<670) && (mouse_y>330 && mouse_y<440))
        {if(musique == 1)play_sample( selection, 255, 128, 1000,0);
            do{
                clear_bitmap(page);
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page, regles, 204, 153);
                if ((mouse_x>672 && mouse_x<800) && (mouse_y>561 && mouse_y<580)) draw_sprite(page, texte_retour, 672, 561);
                draw_sprite(page, curseur, mouse_x,mouse_y);
               // textprintf_ex(page,font,60,300,makecol(0,0,0),makecol(255,0,0),"%4d %4d",mouse_x,mouse_y); //=> sert a afficher les coordonnées pour la hitbox du retour au menu
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                if ( mouse_b&1 && (mouse_x>675 && mouse_x<800) && (mouse_y>555 && mouse_y<585))
                {
                    if(musique == 1)play_sample( selection, 255, 128, 1000,0);
                    retourmenu=1;//condition pour sortir de cette boucle en cliquant sur retour puis reboucle au menu
                    quitterjeu=0;
                }
            }while (retourmenu!=1);
        }

        //Crédits
        if ( mouse_b&1 && (mouse_x>350 && mouse_x<670) && (mouse_y>480 && mouse_y<530))
        {if(musique == 1)play_sample( selection, 255, 128, 1000,0);
            do{
                clear_bitmap(page);
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page, credits, 204, 153);
                if ((mouse_x>672 && mouse_x<800) && (mouse_y>561 && mouse_y<580)) draw_sprite(page, texte_retour, 672, 561);
                draw_sprite(page, curseur, mouse_x,mouse_y);
               // textprintf_ex(page,font,60,300,makecol(0,0,0),makecol(255,0,0),"%4d %4d",mouse_x,mouse_y); //=> sert a afficher les coordonnées pour la hitbox du retour au menu
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                if ( mouse_b&1 && (mouse_x>675 && mouse_x<800) && (mouse_y>555 && mouse_y<585))
                {
                    if(musique == 1)play_sample( selection, 255, 128, 1000,0);
                    retourmenu=1;//condition pour sortir de cette boucle en cliquant sur retour puis reboucle au menu
                    quitterjeu=0;
                }
            }while (retourmenu!=1);
        }

        //Quitter
        if ( mouse_b&1 && (mouse_x>350 && mouse_x<670) && (mouse_y>570 && mouse_y<625)){
            if(musique == 1)play_sample( selection, 255, 128, 1000,0);
            draw_sprite(page, quitter, 0, 0);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            quitterjeu=1;
            rest(3000);
        }
    }
    rest(20);
    return 0;

}
END_OF_MAIN();
