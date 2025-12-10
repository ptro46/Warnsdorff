#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "cheval.h"

int play(void) {
    int **echiquier ;

    echiquier = (int **)malloc(8 * sizeof(int*)) ;
    for(int i=0;i<8;i++) {
        echiquier[i] = (int *)malloc(8 * sizeof(int));
        for(int j=0;j<8;j++) {
            echiquier[i][j] = 0 ; // initialise toutes les cases comme etant libre (0) 
        }
    }

    //---
    // calcule la position initiale du cheval et le place
    srand(time(NULL));
    int x = rand() % 8 ;
    int y = rand() % 8 ;
    
    printf("position initiale %c,%d\n",('A'+y),(x+1));
    echiquier[x][y] = 1 ;
    afficher_plateau(echiquier);
    
    int index_cavalier = 2 ;
    bool can_continue = true ;
    while ( case_libre(echiquier) && can_continue == true ) {
        sPosition nouvelle_position = calcule_position_suivante(echiquier, x, y) ;
        x = nouvelle_position.x ;
        y = nouvelle_position.y ;
        printf("nouvelle position %d,%c,%d\n",y,('A'+y),(x+1));
        if ( x >= 0 && y >= 0 && x < 8 && y < 8 ) {
            echiquier[x][y] = index_cavalier++ ;
            afficher_plateau(echiquier);
        } else {
            printf("BREAK\n");
            can_continue = false ;
        }
    }

    //---
    // liberation de l'echiquier
    for(int i=0;i<8;i++) {
        free( echiquier[i] );
    }
    free( echiquier ) ;
    return 0;
}

void afficher_plateau(int **echiquier) {
    int decompte_cases_libres = 0 ;
    printf("----------------------------------------------\n");
    printf("|    |  A |  B |  C |  D |  E |  F |  G |  H |\n");
    printf("----------------------------------------------\n");
    for(int i=0;i<8;i++) {
        printf("| %2d |",(i+1));
        for(int j=0;j<8;j++) {
            printf(" %2d |",echiquier[i][j]);
            if ( echiquier[i][j] == 0 ) {
                decompte_cases_libres++;
            }
        }
        printf("\n");
    printf("----------------------------------------------\n");
    }
    
    printf("%d cases libres\n",decompte_cases_libres);
}

bool case_libre(int **echiquier) {
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            if ( echiquier[i][j] == 0 ) {
                return true;
            }
        }
    }
    return false ;
}

void          calcule_positions_possibles(int x, int y, psPosition positions) {
    int x2 = 0, y2 = 0 ;
    int position_index = 0 ;

    // calcul du point 1 
    if ( y < 8 - 2 ) {
        y2 = y + 2 ;
        if ( x >= 1 ) {
            x2 = x - 1 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul du point 2
    if ( y < 8 - 2 ) {
        y2 = y + 2 ;
        if ( x < 8 - 1 ) {
            x2 = x + 1 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul du point 3
    if ( y >= 2 ) {
        y2 = y - 2 ;
        if ( x >= 1 ) {
            x2 = x - 1 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;
    
    // calcul du point 4
    if ( y >=  2 ) {
        y2 = y - 2 ;
        if ( x < 8 - 1 ) {
            x2 = x + 1 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul de la position 5
    if ( y >= 1 ) {
        y2 = y - 1 ;
        if ( x < 8 - 2 ) {
            x2 = x + 2 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul de la position 6
    if ( y < 8 - 1 ) {
        y2 = y + 1 ;
        if ( x < 8 - 2 ) {
            x2 = x + 2 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul de la position 7
    if ( y >= 1 ) {
        y2 = y - 1 ;
        if ( x >= 2 ) {
            x2 = x - 2 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;

    // calcul de la position 8
    if ( y < 8 - 1 ) {
        y2 = y + 1 ;
        if ( x >= 2 ) {
            x2 = x - 2 ;
            positions[position_index].x = x2 ;
            positions[position_index].y = y2 ;
        } else {
            positions[position_index].x = -1 ;
            positions[position_index].y = -1 ;            
        }
    } else {
        positions[position_index].x = -1 ;
        positions[position_index].y = -1 ;            
    }
    position_index++;
}


sPosition calcule_position_suivante(int **echiquier, int x, int y) {
    sPosition positions[8];
    int score_faible = 65535;
    int position_score_faible = 0 ;
    
    memset(positions, -1, sizeof(positions));
    calcule_positions_possibles(x, y, positions);
    for(int i=0;i<8;i++) {
        positions[i].score = compte_possibilite(echiquier, positions[i].x, positions[i].y);
    }

    for(int i=0;i<8;i++) {
        if ( positions[i].score >= 0 && echiquier[positions[i].x][positions[i].y] == 0 && positions[i].score < score_faible ) {
            score_faible =  positions[i].score ;
            position_score_faible = i ;
        }
    }

    
    return positions[position_score_faible];
}

int           compte_possibilite(int **echiquier, int x, int y) {
    sPosition positions[8];
    int score = 0 ;

    if ( x == -1 || y == -1 ) return -1 ;
    
    memset(positions, -1, sizeof(positions));
    calcule_positions_possibles(x, y, positions);
    for(int i=0;i<8;i++) {
        if ( positions[i].x != -1 && positions[i].y != -1 &&
             echiquier[positions[i].x][positions[i].y] == 0 ) {
            score++;
        }
    }
    
    return score ;
}
