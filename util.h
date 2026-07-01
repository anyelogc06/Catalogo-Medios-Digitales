#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>
// #include <optional>
#include <utility>
#include <iomanip>
#include <cstdlib>

using namespace std;

using TI  = int;
using TD  = double;
using TLL = long long;
using TS  = string;
using TB  = bool;

using UTI   = unsigned int;
using UTLL  = unsigned long long;


//Tipos primitivos:

template <typename T>
inline void WriteP(ostream& os, const T& valor) {
    os.write(reinterpret_cast<const char*>(&valor), sizeof(T));
}

template <typename T>
inline void ReadP(istream& is, T& valor) {
    is.read(reinterpret_cast<char*>(&valor), sizeof(T));
}

// Tipo string
inline void WriteS(ostream& os, const TS& texto) {
    size_t tam = texto.size();
    os.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
    if (tam > 0) {
        os.write(texto.c_str(), tam);
    }
}

inline void ReadS(istream& is, TS& texto) {
    size_t tam = 0;
    if (!is.read(reinterpret_cast<char*>(&tam), sizeof(tam))) {
        texto.clear();
        return;
    }
    texto.resize(tam);
    if (tam > 0) {
        is.read(&texto[0], tam);
    }
}


#endif // __UTIL_H__