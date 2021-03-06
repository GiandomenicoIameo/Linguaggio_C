#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"
#include <time.h>

Coda* creaCoda( int vertice, int distanza ) {

  Coda* newPtr = ( Coda* )malloc( sizeof( Coda ) );
  newPtr->vertice = vertice;
  newPtr->distanza = distanza;
  newPtr->next = NULL;

  return newPtr;
}

void insertCoda( Coda** Testa, int vertice, int distanza ) {

  Coda* newPtr = NULL;
  Coda* currentPtr = NULL;
  Coda* previousPtr = NULL;

  if( *Testa == NULL )
      *Testa = creaCoda( vertice, distanza );

  else {
    currentPtr = *Testa;
    previousPtr = NULL;

    while( currentPtr != NULL && distanza > currentPtr->distanza ) {
       previousPtr = currentPtr;
       currentPtr = currentPtr->next;
    }

    if( !previousPtr ) {
      newPtr = creaCoda( vertice, distanza );
      newPtr->next = *Testa;
      *Testa = newPtr;
    }
    else {
      newPtr = creaCoda( vertice, distanza );
      previousPtr->next = newPtr;
      newPtr->next = currentPtr;
    }
  }
}

int removeCoda( Coda** Testa ) {

  Coda* deletePtr = NULL;
  int vertice = ( *Testa )->vertice;

  deletePtr = *Testa;
  *Testa = ( *Testa )->next;
  free( deletePtr );

  return vertice;
}

void removeNodo( Coda** Testa, int vertice ) {

     Coda* currentPtr;
     Coda* previousPtr;
     Coda* deletePtr;

     if( *Testa == NULL ) {
       return;
     }

     if( vertice == ( *Testa )->vertice ) {
         deletePtr = *Testa;
         *Testa = ( *Testa )->next;
         free( deletePtr );
     }
     else {
       previousPtr = *Testa;
       currentPtr = ( *Testa )->next;

     while( currentPtr != NULL && currentPtr->vertice != vertice ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
     }

     if( currentPtr != NULL ) {
        deletePtr = currentPtr;
        previousPtr->next = currentPtr->next;
        free( deletePtr );
     }
   }
}

void calcoloDistanzaCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

     ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

     while( tempTesta != NULL ) {
        if( distanze[ verticeSrc ] + tempTesta->prezzo < distanze[ tempTesta->vertice ] ) {
            distanze[ tempTesta->vertice ] = distanze[ verticeSrc ] + tempTesta->prezzo;
            predecessori[ tempTesta->vertice ] = verticeSrc;
            removeNodo( Testa, tempTesta->vertice );
            insertCoda( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
        }
        tempTesta = tempTesta->next;
     }
}

void AggiornaNodoCosti( Coda** Testa, int vertice, int distanze ) {

     Coda* tempTesta = *Testa;

     while( tempTesta != NULL ) {
        if( tempTesta->vertice == vertice ) {
            tempTesta->distanza = distanze;
            return;
        }
        tempTesta = tempTesta->next;
    }
}

void inserimentoAdiacenzeCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

    while( tempTesta != NULL ) {
        distanze[ tempTesta->vertice ] = tempTesta->prezzo;
        predecessori[ tempTesta->vertice ] = verticeSrc;
        AggiornaNodo( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
        tempTesta = tempTesta->next;
    }
}

void algoritmoDijkstraCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    int vertice;

    for( int indice = verticeSrc + 1; indice < graph->numeroVertici; indice++ )
          insertCoda( Testa, indice, INF );

  distanze[ verticeSrc ] = 0;
  inserimentoAdiacenze( Testa, graph, verticeSrc, distanze, predecessori );

  while( *Testa != NULL ) {
       vertice = removeCoda( Testa );
       calcoloDistanza( Testa, graph, vertice, distanze, predecessori );
  }
}

void stampaCostoPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze ) {

     if( distanze[ verticeDst ] == INF ) {
         puts( "NULL" );
         return;
     }

     if( predecessori[ verticeDst ] == verticeSrc ) {
         printf( "%s < ", citta[ verticeDst ] );
         printf( "%s", citta[ verticeSrc ] );
         return;
     }
     else {
        printf( "%s < ", citta[ verticeDst ] );
        stampaCostoPercorsoMinimo( predecessori[ verticeDst ], verticeSrc, predecessori, citta, distanze );
    }
}

int stampaArray( int* array, int size, int verticeDst ) {

   for( int indice = 0; indice < size; indice++ ) {
        if( verticeDst == indice )
             continue;
        else
            printf( "%d\n", array[ indice ] );
        }
}
