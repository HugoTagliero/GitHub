#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>


//////////////////////////////////////////////////////////////////
//////////Sous-programme d'initialisation de gotoligcol///////////   ///////////Fonctionnel
///////////////////Se suffit à lui-même///////////////////////////
void gotoligcol( int lig, int col )
{
//0. ressources
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}


/////////////////////////////////////////////////////////////////////
//////////Sous-programme de remplissage initial de la matrice//////// ///////////Fonctionnel
///////////////////Se suffit à lui-même//////////////////////////////
void remplissage_initial(char matrice_remplissage_initial[10][15])
{
//0.Déclaration des ressources
    int i,j,x;

//1.Remplissage
    for(i=0; i<10 ; i++)
    {
        for(j=0; j<15; j++)
        {
            x=rand()%5;
            switch(x)
            {
            case 0 :
                matrice_remplissage_initial[i][j]='F';
                break;
            case 1 :
                matrice_remplissage_initial[i][j]='S';
                break;
            case 2 :
                matrice_remplissage_initial[i][j]='P';
                break;
            case 3 :
                matrice_remplissage_initial[i][j]='M';
                break;
            case 4 :
                matrice_remplissage_initial[i][j]='O';
                break;
            }
        }
    }

}


////////////////////////////////
//////////Sauvegarde////////////
////////////////////////////////
void sauvegarde(int *vies,int *coupsrestants,int *scoreS,int *scoreF,int *scoreP,int *scoreO,int *scoreM)
{
//0. Déclaration des variables
    char pseudo[16];
    FILE *fic=NULL;
    fic=fopen("save.txt","w");
    //1 Début du traitement
    if (fic!=NULL) // blindage d'ouverture du fichier
    {
        printf("Entrez votre pseudo (15 caracteres maximum)\n\n\t\t\t");
        gets(pseudo);
        fprintf(fic,"%d\n%d\n%d\n%d\n%d\n%d\n%s",*vies,*coupsrestants,*scoreF,*scoreP,*scoreO,*scoreM,*scoreS,pseudo);
        printf("Sauvegarde reussie\n \n");

    }
    else printf("Erreur");
    fclose(fic);
    printf("Appuyez sur une touche sur continuer"); //pour éviter que l'exécutable ne se ferme sans qu'on puisse lire le résultat
    while(1)
    {
        if(kbhit())
        {
            break;
        }
    }
}


//////////////////////////////////////////////////////////////////////
//////////Sous-programme de détection et supression des figures///////  /////////fonctionnel
///////////////////Se suffit à lui-même///////////////////////////////
void destruction_items (char matrice_destruction[10][15],int ptsornot,int *pcompteurF,int *pcompteurO,int *pcompteurP,int *pcompteurS,int *pcompteurM)
{
//0. Déclaration des variables
    int i,j,k,l;
    int compteurF=0,compteurO=0,compteurP=0,compteurS=0,compteurM=0;
    char save;

//1. Traitement
    for(i=0; i<10; i++)
    {
        for(j=0; j<15; j++)
        {
            if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i][j+4] && j<11)
            {
                save=matrice_destruction[i][j];
                for(k=0; k<10; k++)
                {
                    for(l=0; l<15; l++)
                    {
                        if (matrice_destruction[k][l]==save)
                        {
                            if (save=='P') compteurP=compteurP++;
                            if (save=='O') compteurO=compteurO++;
                            if (save=='M') compteurM=compteurM++;
                            if (save=='S') compteurS=compteurS++;
                            if (save=='F') compteurF=compteurF++;
                            matrice_destruction[k][l]=' ';
                        }

                    }
                }
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+4][j] && j<6)
            {
                save=matrice_destruction[i][j];
                for(k=0; k<10; k++)
                {
                    for(l=0; l<15; l++)
                    {
                        if (matrice_destruction[k][l]==save)
                        {
                            if (save=='P') compteurP=compteurP++;
                            if (save=='O') compteurO=compteurO++;
                            if (save=='M') compteurM=compteurM++;
                            if (save=='S') compteurS=compteurS++;
                            if (save=='F') compteurF=compteurF++;
                            matrice_destruction[k][l]=' ';
                        }

                    }
                }
            }

            if (matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>0 && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+2]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>1 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-2]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>1 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>0 && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+3] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+1][j+2]=matrice_destruction[i+1][j+3]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-3] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>2 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-3]=matrice_destruction[i+2][j-2]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-3] && matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>2 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-3]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+3] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=matrice_destruction[i+2][j+3]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j-1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+2] && j>0 && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=matrice_destruction[i+3][j-1]=matrice_destruction[i+3][j+1]=matrice_destruction[i+3][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j-1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j-2] && j>1 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=matrice_destruction[i+3][j-1]=matrice_destruction[i+3][j+1]=matrice_destruction[i+3][j-2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j+1]=matrice_destruction[i+3][j+1]=' ';
            }

            else  if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+3][j+2] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j+2]=matrice_destruction[i+3][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+3][j-1] && matrice_destruction[i][j]==matrice_destruction[i+3][j-2] && matrice_destruction[i][j]==matrice_destruction[i+3][j-3] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+3][j-1]=matrice_destruction[i+3][j-2]=matrice_destruction[i+3][j-3]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+2] && matrice_destruction[i][j]==matrice_destruction[i+3][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i+3][j+1]=matrice_destruction[i+3][j+2]=matrice_destruction[i+3][j+3]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+3] && matrice_destruction[i][j]==matrice_destruction[i+2][j+3] && matrice_destruction[i][j]==matrice_destruction[i+3][j+3] && j<12 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+16;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+16;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+16;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+16;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+16;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+3]=matrice_destruction[i+2][j+3]=matrice_destruction[i+3][j+3]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j-1] && matrice_destruction[i][j]==matrice_destruction[i+3][j-2] && j>1 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=matrice_destruction[i+3][j-1]=matrice_destruction[i+3][j-2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j-1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && j>0 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=matrice_destruction[i+3][j-1]=matrice_destruction[i+3][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+2] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=matrice_destruction[i+3][j+1]=matrice_destruction[i+3][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>1 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-2]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>0 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>1 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j>0 && j<14 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+3][j+2] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j+2]=matrice_destruction[i+3][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+3][j+1] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j+1]=matrice_destruction[i+3][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && j<13 && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-3] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j>2 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-3]=matrice_destruction[i+2][j-2]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && j>1 && j<14 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-2]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && j>0 && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+3] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+1][j+2]=matrice_destruction[i+1][j+3]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-3] && matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j>2 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-3]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j>1 && j<14 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j>0 && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+3] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=matrice_destruction[i+2][j+3]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+3] && matrice_destruction[i][j]==matrice_destruction[i+2][j+3] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+3]=matrice_destruction[i+2][j+3]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && j<12 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+14;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+14;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+14;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+14;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+14;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j-2] && j>1 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j-2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && j>0 && j<14 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j-1]=matrice_destruction[i+2][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+2][j+1]=matrice_destruction[i+2][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j-2] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j] && j>1 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j-2]=matrice_destruction[i+1][j-1]=matrice_destruction[i+2][j]=matrice_destruction[i+1][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j-1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && j>0 && j<14 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+1][j-1]=matrice_destruction[i+1][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+1][j+1]=matrice_destruction[i+1][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+2] && matrice_destruction[i][j]==matrice_destruction[i+2][j+2] && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j+2]=matrice_destruction[i+2][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i+1][j+1] && matrice_destruction[i][j]==matrice_destruction[i+2][j+1] && j<13 && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+12;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+12;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+12;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+12;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+12;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i+1][j+1]=matrice_destruction[i+2][j+1]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && matrice_destruction[i][j]==matrice_destruction[i][j+3] && j<12)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+8;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+8;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+8;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+8;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+8;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=matrice_destruction[i][j+3]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && matrice_destruction[i][j]==matrice_destruction[i+3][j] && i<7)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+8;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+8;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+8;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+8;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+8;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=matrice_destruction[i+3][j]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i][j+1] && matrice_destruction[i][j]==matrice_destruction[i][j+2] && j<13)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+3;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+3;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+3;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+3;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+3;
                matrice_destruction[i][j]=matrice_destruction[i][j+1]=matrice_destruction[i][j+2]=' ';
            }

            else if (matrice_destruction[i][j]==matrice_destruction[i+1][j] && matrice_destruction[i][j]==matrice_destruction[i+2][j] && i<8)
            {
                if (matrice_destruction[i][j]=='P') compteurP=compteurP+3;
                if (matrice_destruction[i][j]=='O') compteurO=compteurO+3;
                if (matrice_destruction[i][j]=='M') compteurM=compteurM+3;
                if (matrice_destruction[i][j]=='S') compteurS=compteurS+3;
                if (matrice_destruction[i][j]=='F') compteurF=compteurF+3;
                matrice_destruction[i][j]=matrice_destruction[i+1][j]=matrice_destruction[i+2][j]=' ';
            }
        }

    }
    if(ptsornot==0)
    {
        compteurF=0;
        compteurP=0;
        compteurS=0;
        compteurO=0;
        compteurM=0;
    }
    if(ptsornot==1)
    {
        *pcompteurF=*pcompteurF+compteurF;
        *pcompteurO=*pcompteurO+compteurO;
        *pcompteurP=*pcompteurP+compteurP;
        *pcompteurS=*pcompteurS+compteurS;
        *pcompteurM=*pcompteurM+compteurM;
    }

}


////////////////////////////////////////////////////
//////////Sous-programme de gravité/////////////////     ////////////////////////Fonctionnel
/////////////Se suffit à lui-même///////////////////
void gravite(char matrice_gravite[10][15])
{
//0.Déclaration des variables
    int i,j,k;
    char modif;

//1.Initialisation

//2.Gravité
    for(k=0; k<10; k++)
    {
        for(i=0; i<10; i++)
        {
            for(j=0; j<15; j++)
            {
                if((matrice_gravite[i][j]!=' ')&&(matrice_gravite[i+1][j]==' '))
                {
                    modif=matrice_gravite[i][j];
                    matrice_gravite[i][j]=matrice_gravite[i+1][j];
                    matrice_gravite[i+1][j]=modif;
                }
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////
//////////Sous-programme de remplissage de la matrice après gravité///////   ///Fonctionnel
///////////////////Se suffit à lui-même///////////////////////////////////
int remplissage_gravite(char matrice_remplissage_gravite[10][15],int testlimite)
{
//0.Déclaration des variables
    int i,j,x;

//1.Initialisation

//2.Gravité
    for(i=0; i<10; i++)
    {
        for(j=0; j<15; j++)
        {
            if(matrice_remplissage_gravite[i][j]==' ')
            {
                x=rand()%5;
                if(x==0) matrice_remplissage_gravite[i][j]='S';
                if(x==1) matrice_remplissage_gravite[i][j]='P';
                if(x==2) matrice_remplissage_gravite[i][j]='M';
                if(x==3) matrice_remplissage_gravite[i][j]='O';
                if(x==4) matrice_remplissage_gravite[i][j]='F';
                testlimite++;
            }
        }
    }
    return testlimite;
}


//////////////////////////////////////////////////////////////////////
//////////Sous-programme d'affichage de la matrice à l'écran//////////      ///Fonctionnel
///////////////////Se suffit à lui-même///////////////////////////////
void affichage(char matrice_affichage[10][15],int *vie,int *numniveau,int *comptcoups,int *ptcompteurfigF,int *ptcompteurfigO,int *ptcompteurfigP,int *ptcompteurfigS,int *ptcompteurfigM, int *ptcontratP, int *ptcontratO, int *ptcontratM, int *ptcontratS, int *ptcontratF)
{
//0.Déclaration des ressources
    int i,j;

//1.Affichage
    system("cls");
    for(i=0; i<10 ; i++)
    {
        for(j=0; j<15; j++)
        {
            printf("%c  ",matrice_affichage[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");
    printf("\n");
    printf("Vous etes au niveau %d. Pour le finir, il vous faut :\n",*numniveau);
    printf("Pommes : %d/%d  Oignons : %d/%d  Mandarines : %d/%d  Soleils : %d/%d Fraises : %d/%d\n\n", *ptcompteurfigP,*ptcontratP,*ptcompteurfigO,*ptcontratO,*ptcompteurfigM,*ptcontratM,*ptcompteurfigS,*ptcontratS,*ptcompteurfigF,*ptcontratF);
    printf("Il vous reste %d coups",*comptcoups);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Sous-programme important, s'occupe d'appeler les ssp de nettoyage et affichage et gère///////////
///////////////////l'affichage de points ou non////////////////////////////////////////////////////////////    ////Problème
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void execution(char matrice_execution[10][15],int *vie,int *niveau,int *comptcoups,int points_ou_pas,int *ptcompteurfigF,int *ptcompteurfigO,int *ptcompteurfigP,int *ptcompteurfigS,int *ptcompteurfigM, int *ptcontratP, int *ptcontratO, int *ptcontratM, int *ptcontratS, int *ptcontratF)
{
    //0.Déclaration des ressources et Initialisation
    int limite=0,i=0,j=0,test=0;

    //1.Execution
    do
    {
        destruction_items(matrice_execution,points_ou_pas,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM);

        affichage(matrice_execution,vie,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
        Sleep(500);

        gravite(matrice_execution);

        affichage(matrice_execution,vie,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
        Sleep(500);

        limite=0;
        limite=remplissage_gravite(matrice_execution,test);

        affichage(matrice_execution,vie,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
        Sleep(500);

    }
    while(limite!=0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////    ////Problème
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void contrat(char matrice_contrat[10][15],int *vie,int points,int *niveau,int *comptcoups,int *ptcompteurfigF,int *ptcompteurfigO,int *ptcompteurfigP,int *ptcompteurfigS,int *ptcompteurfigM,int *ptcontratP, int *ptcontratO, int *ptcontratM, int *ptcontratS, int *ptcontratF)
{
//.Selection des niveaux

    if(*vie>0)
    {
        if (*niveau==1)
        {
            if((*comptcoups>0) && (*ptcompteurfigF>=*ptcontratF) && (*ptcompteurfigO>=*ptcontratO) && (*ptcompteurfigM>=*ptcontratM))
            {
                sauvegarde(*vie,*comptcoups,*ptcompteurfigS,*ptcompteurfigF,*ptcompteurfigP,*ptcompteurfigO,*ptcompteurfigM);
                (*niveau)++;
                *comptcoups=40;
                *ptcompteurfigF=*ptcompteurfigM=*ptcompteurfigO=*ptcompteurfigP=*ptcompteurfigS=0;
                *ptcontratP=25;
                *ptcontratS=30;
                points=0;
                execution(matrice_contrat,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
            }
            else if(*comptcoups==0)
            {
                (*vie)--;
                printf("DOMMAGE ! Vous perdez une vie. il vous en reste %d",vie);
            }
        }
        if(*niveau==2)
        {
            if((*comptcoups>0) && (*ptcompteurfigP>=*ptcontratP) && (*ptcompteurfigS>=ptcontratS))
            {
                sauvegarde(*vie,*comptcoups,*ptcompteurfigS,*ptcompteurfigF,*ptcompteurfigP,*ptcompteurfigO,*ptcompteurfigM);
                (*niveau)++;
                *comptcoups=50;
                *ptcompteurfigF=*ptcompteurfigM=*ptcompteurfigO=*ptcompteurfigP=*ptcompteurfigS=0;
                *ptcontratS=35;
                *ptcontratF=35;
                *ptcontratM=35;
                points=0;
                execution(matrice_contrat,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
            }
            else if(*comptcoups==0)
            {
                (*vie)--;
                printf("DOMMAGE ! Vous perdez une vie");
            }
        }
        if(*niveau==3)
        {
            if((*comptcoups>0) && (*ptcompteurfigS>=*ptcontratS) && (*ptcompteurfigF>=*ptcontratF) && (*ptcompteurfigM>=*ptcontratM))
               {
                   printf("Vous avez gagné !!!");
               }
            else if(*comptcoups==0)
            {
                (*vie)--;
                printf("DOMMAGE ! Vous perdez une vie");
            }
        }
    }
    else
    {
        printf("Vous avez perdu ! Vous recommencez au niveau 1 !!!");
        (*vie)=5;
        (*niveau)=1;
        *comptcoups=30;
        *ptcompteurfigF=*ptcompteurfigM=*ptcompteurfigO=*ptcompteurfigP=*ptcompteurfigS=0;
        points=0;
        execution(matrice_contrat,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
    }




}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Sous-programme principal, donne la main au joueur et appelle les autres sous-programmes en fonction des actions//////////     ///Problème ?
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void curseur(char matrice_curseur[10][15],int *vie,int *niveau,int *comptcoups,int *ptcompteurfigF,int *ptcompteurfigO,int *ptcompteurfigP,int *ptcompteurfigS,int *ptcompteurfigM,int *ptcontratP, int *ptcontratO, int *ptcontratM, int *ptcontratS, int *ptcontratF)
{
//0.Déclaration des ressources
    int i,j,k,x,y,points;
    char touche,touche2,t,modif;

//1.Initialisation
    i=0;
    j=0;
    k=1;
    x=0;
    y=0;
    points=1;
    gotoligcol(i,j);

//2.Boucle évenementielle
    do
    {
        Sleep(100);
        points=1;
        if(kbhit())
        {
            touche=getch();
            switch(touche)
            {
            case '8':
                if(i>0)
                {
                    i=i-2;
                    x=x-1;
                    gotoligcol(i,j);
                    k--;
                }
                break;

            case '4':
                if(j>0)
                {
                    j=j-3;
                    y=y-1;
                    gotoligcol(i,j);
                    k--;
                }
                break;

            case '2':
                if(i<18)
                {
                    i=i+2;
                    x=x+1;
                    gotoligcol(i,j);
                    k--;
                }
                break;

            case '6':
                if(j<42)
                {
                    j=j+3;
                    y=y+1;
                    gotoligcol(i,j);
                    k--;
                }
                break;

            case ' ':
                t=matrice_curseur[x][y];
                if(t>='A'&&t<='Z')
                {
                    t=t-'A'+'a';
                    matrice_curseur[x][y]=t;
                    affichage(matrice_curseur,vie,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                    touche2=getch();
                    switch(touche2)
                    {
                    case '8':
                        modif=matrice_curseur[x][y];
                        matrice_curseur[x][y]=matrice_curseur[x-1][y];
                        matrice_curseur[x-1][y]=modif-'a'+'A';
                        contrat(matrice_curseur,vie,points,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        (*comptcoups)--;
                        execution(matrice_curseur,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        break;

                    case '4':
                        modif=matrice_curseur[x][y];
                        matrice_curseur[x][y]=matrice_curseur[x][y-1];
                        matrice_curseur[x][y-1]=modif-'a'+'A';
                        contrat(matrice_curseur,vie,points,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        (*comptcoups)--;
                        execution(matrice_curseur,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        break;

                    case '2':
                        modif=matrice_curseur[x][y];
                        matrice_curseur[x][y]=matrice_curseur[x+1][y];
                        matrice_curseur[x+1][y]=modif-'a'+'A';
                        contrat(matrice_curseur,vie,points,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        (*comptcoups)--;
                        execution(matrice_curseur,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        break;

                    case '6':
                        modif=matrice_curseur[x][y];
                        matrice_curseur[x][y]=matrice_curseur[x][y+1];
                        matrice_curseur[x][y+1]=modif-'a'+'A';
                        contrat(matrice_curseur,vie,points,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        (*comptcoups)--;
                        execution(matrice_curseur,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        break;

                    case ' ':
                        t=t-'a'+'A';
                        matrice_curseur[x][y]=t;
                        execution(matrice_curseur,vie,niveau,comptcoups,points,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                        break;
                    }
                }
                else if(t>='a'&&t<='z')
                {
                    t=t-'a'+'A';
                    matrice_curseur[i][j]=t;
                    affichage(matrice_curseur,vie,niveau,comptcoups,ptcompteurfigF,ptcompteurfigO,ptcompteurfigP,ptcompteurfigS,ptcompteurfigM,ptcontratP,ptcontratO,ptcontratM,ptcontratS,ptcontratF);
                }
                break;
            }
        }

    }
    while(k<=1);



}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Programme principal, a pour rôle d'initialiser l'aléatoire///////////////////////////////////
/////////et d'appeler une première fois certains programmes avant de donner la main au joueur/////////          ////Fonctionnel
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
//0.Déclaration des ressources
    char matrice[10][15];
    int pasdepoints=0,compteurfigO=0,compteurfigF=0,compteurfigS=0,compteurfigM=0,compteurfigP=0;
    int niveau=1,compteurcoups=30,contratO=15,contratF=15,contratS=0,contratM=15,contratP=0,vie=5;
    char choixmenu;
    char chainevies[5],chainenbcoupsrestants[5],chainescoreS[5],chainescoreF[5],chainescoreP[5],chainescoreO[5],chainescoreM[5],choixsave;

//1.Initialisation
    srand(time(NULL));
    FILE *fic=NULL;


//2.Menu et Lancement du jeu
    printf("\n\t\t//////////////////////////////////////////////////\n\t\t//\tBonjour et bienvenue sur Plantamiz!\t//\n\t\t//////////////////////////////////////////////////");
    do
    {
        printf("\n\n\n(1) Nouvelle partie\n(2) Charger une partie\n(3) Regles du jeu");
        choixmenu=getch();
        switch(choixmenu)
        {
        case '1': //Démarrage d'une nouvelle partie
        {
            /*ICI POUR L'INSERTION DES APPELS*/
            remplissage_initial(matrice);
            affichage(matrice,&vie,&niveau,&compteurcoups,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
            execution(matrice,&vie,&niveau,&compteurcoups,pasdepoints,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
            curseur(matrice,&vie,&niveau,&compteurcoups,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
            break;
        }
       case '2': //Chargement d'une partie
        {
            FILE*fic=fopen("save.txt","r");
            char chainevies[5],chainenbcoupsrestants[5],chainescoreS[5],chainescoreF[5],chainescoreP[5],chainescoreO[5],chainescoreM[5],choixsave,pseudo[16];
            if (fic!=NULL) //blindage d'ouverture du fichier
            {
                rewind(fic);
                fgets(chainevies,5,fic);                   // là on prend chaque valeur à chaque ligne en se déplaçant
                fseek(fic,strlen(chainevies)+1,SEEK_SET);  //dans le fichier à partir des longueur des chaines précedentes
                fgets(chainenbcoupsrestants,5,fic);        //puis on met les valeurs du fichier dans des chaines de caractères
                fseek(fic,0,SEEK_CUR);
                fgets(chainescoreS,5,fic);
                fseek(fic,0,SEEK_CUR);
                fgets(chainescoreF,5,fic);
                fseek(fic,0,SEEK_CUR);
                fgets(chainescoreP,5,fic);
                fseek(fic,0,SEEK_CUR);
                fgets(chainescoreO,5,fic);
                fseek(fic,0,SEEK_CUR);
                fgets(chainescoreM,5,fic);
                fseek(fic,0,SEEK_CUR);
                fgets(pseudo,15,fic);

                vie=atoi(chainevies);          //puis pour une meilleure utilisation dans la matrice,
                compteurcoups=atoi(chainenbcoupsrestants);//(pour éviter les bugs quoi) et confondre entre entier 12
                compteurfigS=atoi(chainescoreS);       // et caractère 12 par exemple on convertit les
                compteurfigF=atoi(chainescoreF);       //valeurs sous forme de chaines en int
                compteurfigP=atoi(chainescoreP);
                compteurfigO=atoi(chainescoreO);
                compteurfigM=atoi(chainescoreM);
                fclose(fic);
                printf("\nDans la precedente sauvegarde, %s avait %d vies restantes, %d coups restants, \n%d points soleil, %d points fraise, %d points pomme,\n%d points oignon et %d points mandarine\n",pseudo,vie,compteurcoups,compteurfigS,compteurfigF,compteurfigP,compteurfigO,compteurfigM);
                printf("\n Voulez vous reprendre cette partie? O pour oui, une autre touche pour non");
                while(1)
                {
                    if (kbhit())
                    {
                        break;
                    }
                    choixsave=getch();
                    switch (choixsave)
                    {
                    case 'T':
                    case 't':
                    {
                        compteurcoups=1000;
                        printf("\n\nCode de triche actif! Vous avez maintenant 1000 coups restants :)");
                    }

                    case 'O':
                    case 'o':
                    {
                        printf("\nVotre partie a bien ete chargee et va reprendre la ou vous l'avez laissee.");
                        remplissage_initial(matrice);
                        affichage(matrice,&vie,&niveau,&compteurcoups,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
                        execution(matrice,&vie,&niveau,&compteurcoups,pasdepoints,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
                        curseur(matrice,&vie,&niveau,&compteurcoups,&compteurfigF,&compteurfigO,&compteurfigP,&compteurfigS,&compteurfigM,&contratP,&contratO,&contratM,&contratS,&contratF);
                        break;
                    }
                    default:
                    {
                        return 0;
                    }
                    }
                }

            }
            else
            {
                printf("Erreur dans l'ouverture du fichier");
                return 0;
            }


        }
        case '3': //Règles du jeu
        {
            system("cls");
            printf("\n\nRegles du jeu:\n\nVotre but est de consommer les items S pour soleil, F pour fraise, \nP pour pomme, O pour oignon, et M pour mandarine.\n");
            printf("Deplacez le curseur avec les touches 2, 6, 4 et 8. Selectionnez et \ndeselectionnez les items avec la touche espace.\n");
            printf("Gagnez le nombre de points contrats de chaque item tout en respectant\nle nombre de coups autorises pour gagner le niveau.\n");
            printf("5 vies vous sont attribuees des le depart et vous sont restaurees \nlorsque vous passez au niveau suivant. \n\n\t\t\t\tBONNE CHANCE!\n\n");
            choixmenu='4';
            break;
        }

        default:
            printf("\nVotre entree est erronee, veuillez reessayer\n");
        }

    }
    while((choixmenu<'1')||(choixmenu>'3'));

    return 0;
}
