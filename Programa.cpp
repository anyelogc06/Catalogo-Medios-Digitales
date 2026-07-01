#include "Programa.h"
#include "U_ControlMenu/ControlGame.h"
using namespace std;

void DemoCatalogoGame(){
    TS almacenBin = "Dato1/juegos.bin";
    Categoria<Game> CatalogoGame (almacenBin);

    ControladorGame interfaz[] = 
    {   registGame, removeGame, showValue,
        showOfert,   showGenre          };

    TI aux_option = 0;
    while (aux_option != 6){
        limpiar();
        cout << "--- BIENVENIDO AL CATALOGO DE JUEGOS ---\n";
        cout << CatalogoGame <<"\n";
        cout << "Opciones disponibles:\n"
             << "1. Registrar nuevo juego\n"
             << "2. Retirar juego\n"
             << "3. Ver juegos mejor valorados\n"
             << "4. Ver mejores ofertas\n"
             << "5. Buscar juegos por genero\n"
             << "6. Cerrar programa\n";
        cout << "Seleccione una opcion: ";
        cin >> aux_option;

        if (aux_option >= 1 && aux_option <= 5) {
            OpcionesGame select = static_cast<OpcionesGame>(aux_option - 1);
            
            interfaz[select](CatalogoGame, almacenBin, cout);
        } else if (aux_option != 6) {
            cout << "Opcion invalida. Vuelva a intentarlo.\n";
            pausar();
        }
    }
   
}
//En una proxima oportunidad, utilizando enum, dependiendo del catalogo a acceder
//llame al programa.cpp (Demo) adecuado. 