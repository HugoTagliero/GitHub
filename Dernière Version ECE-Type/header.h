#ifndef HEADER_H //     Si premiere inclusion
#define HEADER_H //     Bloque les futures inclusions

///Librairies

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
//#include<windows.h>

///Defines

#define NENNEMIS 20
#define NIMAGE 14
#define NASTEROIDES 50
#define NEXEMPLES 8
#define NBONUS 20

BITMAP* page;
int screenx;
int screeny;
int clavier;
int gagne;


///Structures (typedef)

typedef struct arme
{
    int x, y;          // coordonnée (du coin sup. gauche)
    int precx, precy;  // coordonnées précédent le déplacement
    float dx, dy;      // vecteur deplacement
    int couleur;
    int tx,ty;         // tailles : horizontal/vertical
    int type;          // type vaisseau asteroide...
    int etat;          //à afficher ou non sur l'écran
    int tir;
    BITMAP *img;       // sprite de l'arme
    int comportement;
    int cptexplo; // temps depuis l'explosion
    int vivant;

} t_arme;

typedef struct listearmes
{
    // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int max;

    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int n;

    // le tableau de pointeurs (alloué dynamiquement)
    t_arme **tab;

} t_listearmes;

// Un élément à déplacement interactif
typedef struct joueur{
    int x,y;     // position
    int tx,ty;   // taille
    int precx, precy; //ancienne position (utile pour le deplacement à la souris)
    int vit;     // vitesse des déplacements (nombre de pixels)
    int dx, dy; // vitesse selon chaque composante (pour la souris
    int comportement;
    int cptexplo;
    int vivant;
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image chargée)
    int collisionDecor; //Booleen : si collision alors 1
    int niveauReussi; //Booleen : si fin du niveau, alors 1
} t_joueur;

// Un élément à déplacement automatique aléatoire
typedef struct ennemi{
    int x,y;     // position
    int dx,dy;   // vecteur déplacement
    int tx,ty;   // taille
    int vivant;  //on affiche ou non le vaisseau
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    int comportement;
    int cptexplo;
    int vie;
    int touche;
    BITMAP *img; // sprite (image chargée)
} t_ennemi;

// Un ennemi particulier : l'AT-AT, qui est animé
typedef struct ATAT{
    int x,y;
    int dx,dy;
    int tx,ty;
    int cptdx, tmpdx;
    int imgcourante;
    int cptimg, tmpimg;
    BITMAP *img[NIMAGE];
    int vivant;
    int cpttir0;
}t_ATAT;

//ennemi destructible, mais qui ne tire pas (étonnant, pour un astéroide !)
typedef struct asteroide
{
    int posax;
    int posay;
    int depax;
    int depay;
    int tax;
    int tay;
    int etat;
    int rota;
    int coll;
}t_asteroide;

typedef struct bonus
{
    int x;
    int y;
    int dx;
    int tx;
    int ty;
    int etat;
    int actif;
    BITMAP *img;
    BITMAP *img2;
    int bouclier;
    int accel;
    int nuke;
    int cadence;
    int compteur;
}t_bonus;


///Prototypes

void lancerAllegro(int largeur, int hauteur);
BITMAP *charger_image(char *source);
BITMAP *creer_image(int x,int y);

void scrolling(BITMAP *decor, int niveau);
void versSourisarme(t_arme *arme,int screenx,int screeny);


// Allouer et initialiser une arme
t_arme * creerarme(int x,int y,int type);

// Allouer et initialiser une liste (vide) d'armes
t_listearmes * creerListearmes(int maxarmes);

// booléen : retourne vrai si il reste de la place dans la liste
int libreListearmes(t_listearmes *la);

// Allouer et ajouter une arme à la liste
// retourne l'adresse de ce l'arme, NULL si problème
t_arme * ajouterarme(t_listearmes *la,int x,int y,int type);

// Enlever et libèrer une arme qui était dans la liste en indice i
void enleverarme(t_listearmes *la,int i);
void enleverEnnemi2(t_ennemi *tab2[NENNEMIS], int i);


// Actualiser une arme (bouger ...)
//void actualiserarme(t_arme *arme, t_joueur *joueur, t_ATAT *ATAT);
void actualiserarme(t_arme *arme, t_joueur *joueur, t_ATAT *ATAT, t_ennemi *boss);

// Gérer l'évolution de l'ensemble des armes
//void actualiserListearmes(t_listearmes *la, t_joueur *joueur, t_ATAT *ATAT);
void actualiserListearmes(t_listearmes *la, t_joueur *joueur, t_ATAT *ATAT,t_ennemi *boss);

// Dessiner une arme sur la bitmap bmp
void dessinerarme(BITMAP *bmp,t_arme *arme);

// Dessiner sur une bitmap l'ensemble des armes
void dessinerListearmes(BITMAP *bmp,t_listearmes *la);

// Une élément a été touché : il explose (comportement passe à 1)
void destinarme(t_arme *arme);
void destinJoueur(t_joueur *joueur);
void destinEnnemi2(t_ennemi *ennemi2);

//Gérer les collisions entre le joueur et le décor
void collisionDecor(t_joueur *joueur, BITMAP *joueurCollision, int niveau, BITMAP *carteCollision);

// Gérer collision (éventuelle) entre un arme (un tir) et un ennemi
void collisionarme(t_ennemi *ennemi,t_arme *arme, t_ennemi *ennemi2, t_joueur *joueur, t_ATAT *ATAT, t_ennemi *boss, t_bonus *bonus[NBONUS], int inv, int niveau);

// Gérer les collisions entre les armes (tous les tirs) et un ennemi
void collisionListearmes(t_ennemi *ennemi,t_listearmes *la,t_ennemi *tab2[NENNEMIS],t_joueur *joueur, t_ATAT *ATAT, t_bonus *bonus[NBONUS], t_ennemi *boss, int inv, int niveau);

// Allouer et initialiser joueur
t_joueur * creerJoueur(char *nomimage);

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur *joueur,t_listearmes *la, int niveau, t_bonus *bonus[NBONUS]);

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur *joueur, t_bonus *bonus[NBONUS], int niveau);

// Allouer et initialiser ennemi
t_ennemi * creerEnnemi(char *nomimage);
t_ennemi * creerEnnemi2(char *nomimage, int niveau);
void remplirTabEnnemi(t_ennemi * tab[NENNEMIS], int niveau);

// Actualiser ennemi (bouger automatiquement au hasard...)
void actualiserTabEnnemi(t_ennemi * tab2[NENNEMIS], t_listearmes *la, int niveau);
void actualiserEnnemi(t_ennemi *ennemi, int niveau);
void actualiserEnnemi2(t_ennemi *ennemi, t_listearmes *la, int niveau);

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi);
void dessinerTabEnnemi(BITMAP *bmp, t_ennemi *tab2[NENNEMIS]);


//Cas particulier des AT-AT
t_ATAT *creerATAT(char nomfichier[256]);
void actualiserATAT(t_ATAT *ATAT, t_listearmes *la);
void dessinerATAT(BITMAP *bmp, t_ATAT *ATAT);

//Pour la pluie d'astéroides
void remplirTabAsteroide(t_asteroide * tab[NASTEROIDES]);
void actualiserAsteroide(t_asteroide *asteroide);
void actualiserTabAsteroide(t_asteroide * tab[NASTEROIDES]);
void dessinerAsteroide(BITMAP *bmp, t_asteroide *asteroide, BITMAP *imgAs, BITMAP *page, float phase, float alpha);
void dessinerTabAsteroide(BITMAP *bmp,t_asteroide * tab[NASTEROIDES], BITMAP *imgAs, BITMAP *page, float phase, float alpha);
void collisionTabAsteroide(t_joueur *joueur, t_asteroide * asteroide[NASTEROIDES], t_bonus *bonus[NBONUS], int invincibilite);
void collisionAsteroide(t_joueur *joueur, t_asteroide * asteroide);

//Pour les bonus
t_bonus * creerBonus(char *nomimage, char *nomimage2, int niveau);
void remplirTabBonus(t_bonus * bonus[NBONUS], int niveau);
void actualiserBonus(t_bonus *bonus, int niveau, t_joueur *joueur);
void actualiserTabBonus(t_bonus * bonus[NBONUS], t_joueur *joueur, int niveau);
void dessinerBonus(BITMAP *bmp,t_bonus *bonus);
void dessinerTabBonus(BITMAP *bmp, t_bonus *bonus[NBONUS]);

//Pour le boss
t_ennemi *creerBoss(char *nomimage);
void actualiserBoss(t_ennemi *boss, t_listearmes *la);
void dessinerBoss(BITMAP *bmp,t_ennemi *boss, BITMAP *bosshitimg);
void collisionBoss(t_joueur *joueur, t_ennemi *boss, t_bonus *bonus[NBONUS], int inv);

#endif

/* /!\ Ne rien mettre apres le endif, sauf si inclusions multiples*/
