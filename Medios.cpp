#include "Medios.h"
#include "util.h"

Channel::Channel() {
    detalles.name_ID = "";
    detalles.rating = 0.0;
    detalles.genre = "";
    detalles.release = {0, 0, 0};
}

Channel::~Channel() = default;

TD Channel::GetRating() const { return detalles.rating; }
TS Channel::GetGenre() const { return detalles.genre; }
TS Channel::GetNameId() const { return detalles.name_ID; }

void Channel::add_info(istream& in) {
    cout << "Ingrese el nombre-ID: ";
    // cin.ignore();
    getline(in, detalles.name_ID);
    
    cout << "Ingrese el rating (0.0 - 10.0): ";
    in >> detalles.rating;
    in.ignore();
    
    cout << "Ingrese el genero: ";
    getline(in, detalles.genre);
    
    cout << "Ingrese fecha de lanzamiento: ";
    in >> detalles.release.day >> detalles.release.month >> detalles.release.year;
    in.ignore();
}

void Channel::writeBin(ostream& os) const {
    WriteS(os, detalles.name_ID);
    WriteS(os, detalles.genre);
    WriteP(os, detalles.rating);
    WriteP(os, detalles.release);
}

void Channel::readBin(istream& is) {
    ReadS(is, detalles.name_ID);
    ReadS(is, detalles.genre);
    ReadP(is, detalles.rating);
    ReadP(is, detalles.release);
}

// template <typename U>
ostream& operator<<(ostream& os, const Channel& canal) {
    os << "Nombre/ID: " << canal.detalles.name_ID <<"\n"
       << "Rating: " << canal.detalles.rating 
       << " | Genre: " << canal.detalles.genre 
       << " | Lanzamiento: " 
       << canal.detalles.release.day    << "/" 
       << canal.detalles.release.month  << "/" 
       << canal.detalles.release.year   << "\n";
    return os;
}