#include "header.h"

/*
       Respecter les regles suivantes :
       Noms de fonctions du type "nomFonction"
       Premiere lettre en minuscule
 *      Pour ne pas melanger avec les structures
*/

void lancerAllegro(int largeur, int hauteur)
{
    allegro_init();

    if(install_sound(DIGI_AUTODETECT , MIDI_AUTODETECT ,0) == -1)
    {
        allegro_message("Erreur (son): %s",allegro_error);
        exit(EXIT_FAILURE);
    }

    install_keyboard();
    if(install_mouse() == -1)
    {
        allegro_message("Erreur (souris): %s",allegro_error);
        exit(EXIT_FAILURE);
    }
    set_color_depth(desktop_color_depth());
    //if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0) != 0)
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0) != 0)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Erreur (mode video) : %s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

BITMAP *charger_image(char *source)
{
    BITMAP *image;
    image = load_bitmap(source,NULL);
    if(!image)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Erreur ! Impossible de lire le fichier image %s !",source);
        exit(EXIT_FAILURE);
    }
    return image;
}

BITMAP *creer_image(int x,int y)
{
    BITMAP *image;
    image = create_bitmap(x,y);
    if(!image)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Erreur ! Impossible de creer le bitmap");
        exit(EXIT_FAILURE);
    }
    return image;
}
