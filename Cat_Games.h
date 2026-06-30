#ifndef __CAT_GAMES_H__
#define __CAT_GAMES_H__
#include "util.h"
#include "Medios.h"

// template <typename T>
// struct Nodo{
//     T          elemento;
//     Nodo<T>*   next;
// };

class Game : public Channel{
    TD precios;
    TI ofertas;
    TI num_p;
    TS* plataformas;

public:

    Game();
    Game(const Info& caract, TD pre, TI ofe, TI num_p, const TS plats[]);
    Game(const Game& otro);
    Game(Game&& otro) noexcept;
    Game& operator=(const Game& otro);
    ~Game() override;

    TD getPrecioFinal() const;
    TI getOferta() const;

    void add_info(istream& entrada) override;
    void writeBin(ostream& os) const override;
    void readBin(istream& is) override;

    friend ostream& operator<<(std::ostream& os, const Game& game);

};

#endif //__CAT_GAMES_H__