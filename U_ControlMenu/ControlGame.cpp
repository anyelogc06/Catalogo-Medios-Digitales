#include "ControlGame.h"
#include <iostream>
using namespace std;

void pausar () {
    cout << "\nPresione ENTER para volver.";
    cin.ignore();
    cin.get();
}

void limpiar () {
    system("cls");
}

void registGame (Categoria<Game>& catalogo, const TS& almBin, ostream& os){
    limpiar();
    os << "------ REGISTRANDO JUEGO ------\n";
    Game insertarJuego;
    cin.ignore();
    insertarJuego.add_info(cin);
    catalogo.add_obj(insertarJuego, almBin);
    pausar();
}

void removeGame (Categoria<Game>& catalogo, const TS& almBin, ostream& os){
    limpiar();
    os << "\n--- REMOVIENDO JUEGO ---\n";
    os << "Ingrese el indice del juego: ";
    TI ind;
    cin >> ind;
    catalogo.remove_obj(ind, almBin);
    pausar();
}

void showValue  (Categoria<Game>& catalogo, const TS& almBin, ostream& os){
    limpiar();
    os << "\n--- MEJORES JUEGOS EVALUADOS (+9.5) ---\n";
    Categoria<Game> bestGames = catalogo.some([](const Game& g)
        { return g.GetRating() > 9.5; });

    //Orden con SortToAll
    bestGames.SortToAll(quickSort<Game, bool(*)(const Game&, const Game&)>, EsMayorR<Game>);
    os << bestGames;
    pausar();
}

void showOfert  (Categoria<Game>& catalogo, const TS& almBin, ostream& os){
    limpiar();
    os << "\n--- MEJORES OFERTAS DE LA TEMPORADA ---\n";
    Categoria<Game> bestOferts = catalogo.some([](const Game& g)
        { return g.getOferta() > 0.0 ; });

    //Orden con SortToAll
    bestOferts.SortToAll(quickSort<Game, bool(*)(const Game&, const Game&)>, EsMayorF<Game>);
    os << bestOferts;
    pausar();
}

void showGenre  (Categoria<Game>& catalogo, const TS& almBin, ostream& os){
    limpiar();
    os << "\n--- BUSCAR JUEGOS POR GENERO ---\n";
    TS genero;
    cin.ignore();
    os << "Ingrese el genero a buscar: ";
    // cin.ignore();
    getline(cin, genero);

    Categoria<Game> generoGames = catalogo.some([&genero](const Game& g)
        { return g.GetGenre() == genero; });

    //Orden con SortToAll
    generoGames.SortToAll(quickSort<Game, bool(*)(const Game&, const Game&)>, EsMayorR<Game>);
    os << generoGames;
    pausar();
}