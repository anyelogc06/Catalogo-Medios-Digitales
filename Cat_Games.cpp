#include "util.h"
#include "Cat_Games.h"

Game::Game(){
    detalles    = {};
    precios     = 0.0;
    ofertas     = 0;
    num_p       = 0;
    plataformas = nullptr;
}

Game::Game(const Info& config, TD pre, TI ofe, TI n_p, const TS plats[]){
    detalles    = config;
    precios     = pre;
    ofertas     = ofe;
    num_p       = n_p;
    plataformas = new TS[num_p];
    for(TI i = 0; i<num_p; ++i)
        plataformas[i] = plats[i];

}

Game::Game(const Game& otro){
    detalles    = otro.detalles;
    precios     = otro.precios;
    ofertas     = otro.ofertas;
    num_p       = otro.num_p;
    plataformas = new TS[num_p];
    for (int i = 0; i < num_p; ++i) 
        plataformas[i] = otro.plataformas[i];
}

Game::Game(Game&& otro) noexcept : Channel(move(otro)) {
    precios     = exchange(otro.precios, 0.0);
    ofertas     = exchange(otro.ofertas, 0.0);
    num_p       = exchange(otro.num_p, 0);
    plataformas = exchange(otro.plataformas, nullptr);
} //Medio(otro.info)

Game& Game::operator=(const Game& otro) {
    if (this != &otro) {
        detalles    = otro.detalles;
        precios     = otro.precios;
        ofertas     = otro.ofertas;

        delete[] plataformas;
        num_p       = otro.num_p;
        plataformas = new TS[num_p];
        for (int i = 0; i < num_p; ++i) 
            plataformas[i] = otro.plataformas[i];
    }
    return *this;
}

Game::~Game() {
    delete[] plataformas;
    plataformas = nullptr;
}


TD Game::getPrecioFinal() const {
    TD precio_rebajado = precios - (precios * (ofertas / 100.0));
    return precio_rebajado;
}
TI Game::getOferta() const { return ofertas; }

//Tambien serviria para modificar objetos ya definidos gracias al delete[] plataformas
void Game::add_info(istream& in) {
    Channel::add_info(in);
    cout<< "Ingrese Precio: "; 
    in  >> precios;
    
    cout<< "Ingrese Porcentaje de Oferta (0-100): "; 
    in  >> ofertas;
    
    cout<< "Ingrese Cantidad de Plataformas: "; 
    in  >> num_p;
    
    in.ignore();

    delete[] plataformas; //es necesario
    if (num_p > 0) {
        plataformas = new TS[num_p];
        for (TI i = 0; i < num_p; ++i) {
            cout << "Plataforma [" << i + 1 << "]: ";
            getline(in, plataformas[i]);
        }
    } else {
        plataformas = nullptr;
    }
}

void Game::writeBin(ostream& os) const {
    Channel::writeBin(os);
    WriteP(os, precios);
    WriteP(os, ofertas);
    WriteP(os, num_p);
    for (int i = 0; i < num_p; ++i) {
        WriteS(os, plataformas[i]);
    }
}

void Game::readBin(istream& is) {
    Channel::readBin(is);
    ReadP(is, precios);
    ReadP(is, ofertas);
    ReadP(is, num_p);
    
    delete[] plataformas;
    plataformas = new TS[num_p];
    for (int i = 0; i < num_p; ++i) {
        ReadS(is, plataformas[i]);
    }
}

ostream& operator<<(ostream& os, const Game& juego) {
    os << static_cast<const Channel&>(juego);

    os << "Precio Regular: $"           << juego.precios 
       << " | !! Rebaja temporal !!: "  << juego.ofertas << "%"
       << " | Precio Actual: $"         << fixed << setprecision(2)
                                        <<  juego.getPrecioFinal() << "\n"
       << "Plataformas: ";
    for (int i = 0; i < juego.num_p; ++i) {
        os << juego.plataformas[i];

        if (i == juego.num_p - 1)   { os << ""; } 
        else                        { os << ", "; }
    }
    return os;
}