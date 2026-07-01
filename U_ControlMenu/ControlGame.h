#ifndef __CONTROLGAME_H__
#define __CONTROLGAME_H__
#include "../util.h"
#include "../Catalogo.h"
#include "../Cat_Games.h"
#include "../Sorting.h"
using namespace std;


enum OpcionesGame {
    REGISTRAR,
    RETIRAR,
    MEJOR_VALORADOS,
    TEMPORADA_OFERTAS,
    GENERO,
};

using ControladorGame = void(*)(Categoria<Game>&, const TS&, ostream&);

void pausar();
void limpiar();

void registGame (Categoria<Game>& catalogo, const TS& archBin, ostream& os);
void removeGame (Categoria<Game>& catalogo, const TS& archBin, ostream& os);
void showValue  (Categoria<Game>& catalogo, const TS& archBin, ostream& os);
void showOfert  (Categoria<Game>& catalogo, const TS& archBin, ostream& os);
void showGenre  (Categoria<Game>& catalogo, const TS& archBin, ostream& os);


#endif //__CONTROLGAME__