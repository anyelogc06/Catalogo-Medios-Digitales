#include "Programa.h"
using namespace std;

// void PunteroAccion(){
//     TS* control = { "1. Registrar nuevo "}
// }

void DemoCatalogo(){
    TS almacenBin = "Dato1/juegos.bin";
    Categoria<Game> CatalogoGame (almacenBin);

    cout << "--- BIENVENIDO AL CATALOGO DE JUEGOS ---\n";
    cout << CatalogoGame;


    //Agregar un juego de prueba
    cout << "------ REGISTRANDO JUEGO ------\n";
    Game insertarJuego;
    insertarJuego.add_info(cin);
    CatalogoGame.add_obj(insertarJuego, almacenBin);
    //cout << "*Debera Reiniciar el sistema para actualizar el catalogo.*\n";

    //Filtro con FUNC lambda
    cout << "\n--- MEJORES JUEGOS EVALUADOS (+9.5) ---\n";
    Categoria<Game> mejoresJuegos = CatalogoGame.some([](const Game& g) 
        { return g.GetRating() > 9.5; });
    
    cout << mejoresJuegos;

    //Orden con SortToAll
    cout << "\n--- ORDENANDO TODO EL CATALOGO POR RATING (MAYOR A MENOR) ---\n";

    mejoresJuegos.SortToAll(quickSort<Game, bool(*)(const Game&, const Game&)>, EsMayor<Game>);
    cout << mejoresJuegos;
}