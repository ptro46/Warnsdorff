#ifndef CHEVAL__H
#define CHEVAL__H

struct position {
    int    x ;
    int    y ;
    int    score;
} ;
typedef struct position  sPosition ;
typedef struct position* psPosition ;

void          afficher_plateau(int **echiquier);
bool          case_libre(int **echiquier);
void          calcule_positions_possibles(int x, int y,psPosition positions);
sPosition     calcule_position_suivante(int **echiquier, int x, int y);
int           compte_possibilite(int **echiquier, int x, int y);

#endif // CHEVAL__H
