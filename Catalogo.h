#ifndef __CATALOGO_H__
#define __CATALOGO_H__

#include "util.h"
using namespace std;

template <typename T>
class Categoria {
    TI m_size;
    T* m_vector;

    void reasignar_memoria(TI tam_mod){
        if (tam_mod < 0) return;
        T* new_vector = (tam_mod > 0) ? new T[tam_mod] : nullptr;

        TI lim = (tam_mod < m_size) ? tam_mod : m_size;

    
        if (new_vector != nullptr) {
            for(TI i = 0; i < lim; ++i) 
                new_vector[i] = move(m_vector[i]);
        }
        delete[] m_vector;
        m_vector = new_vector;
        m_size = tam_mod;
    }

public:
    Categoria() : m_size(0), m_vector(nullptr) {}; //constructor default
    Categoria(const TS& archivo); 
    Categoria(const Categoria&); //deep copy constructor
    Categoria(Categoria&&) noexcept;//move constructor
    ~Categoria(); //destructor

    template <typename F>
    Categoria<T> some (F funcion);//best_rank //season_offer  //genero (vector, comparar)

    template <typename F1, typename F2>
    void SortToAll (F1 sorting, F2 comp);
    //funcion externa que genere el archivo.txt
    
    void add_obj(const T& obj, const TS& archivo);
    void remove_obj(TI ind, const TS& archivo);
    void guardar(const TS& archivo) const;

    Categoria<T>& operator=(const Categoria&);
    
    template <typename U>
    friend ostream& operator<<(ostream& os, const Categoria<U>&);
};

//Copy Constructor
template <typename T>
Categoria<T>::Categoria(const Categoria& other){
    if(other.m_vector != nullptr){
        m_size = other.m_size;
        m_vector = new T[m_size];
        for(TI i=0; i<m_size; i++)
            m_vector[i] = other.m_vector[i];
    }
}

//Move Constructor
template <typename T>
Categoria<T>::Categoria(Categoria&& other) noexcept{
    m_size = exchange(other.m_size, 0);
    m_vector = exchange(other.m_vector, nullptr);
} 

//Lectura de archivo
template <typename T>
Categoria<T>::Categoria(const TS& archivo){
    m_size = 0; 
    m_vector = nullptr;
    ifstream in(archivo, ios::binary);
    if(!in.is_open())
        return;

    T obj;
    while (true) {
        obj.readBin(in);
        if (!in) { break; }
        add_obj(obj, "reservar"); 
    }
    in.close();
}


//Destructor
template <typename T>
Categoria<T>::~Categoria(){
    if(m_vector != nullptr){
        delete[] m_vector;
        m_vector = nullptr;
        m_size = 0;
    }
}


//Creación de vectores condicionales
template <typename T>
template <typename F>
Categoria<T> Categoria<T>::some (F funcion){
    Categoria <T> aux;
    TI conteo = 0;
    for(TI i=0; i<m_size; ++i){
        if(funcion(m_vector[i]))
            conteo++;
    }
    TI ind = 0;        
    aux.m_vector = new T[conteo];
    aux.m_size = conteo;
    for(TI i=0; i<m_size; ++i){
        if(funcion(m_vector[i]))
            aux.m_vector[ind++] = m_vector[i];
    }
    return aux;
}

//Recordar que ordenaremos: valoracion, precios.
template <typename T>
template <typename F1, typename F2>
void Categoria<T>::SortToAll (F1 sorting, F2 comparar){
    sorting(m_vector, m_size, comparar);
}

//Agregar objetos
template<typename T>
void Categoria<T>::add_obj(const T& obj, const TS& archivo){
    reasignar_memoria(m_size + 1);
    m_vector[m_size - 1] = obj;
    if(archivo != "reservar")
        guardar(archivo);
}

//Remove objetos
template <typename T>
void Categoria<T>::remove_obj(TI ind, const TS& archivo){
    for(TI i=ind; i<m_size-1; ++i){
        m_vector[i] = move(m_vector[i+1]);
    }
    reasignar_memoria(m_size -1);
    if(archivo != "reservar")
        guardar(archivo);
}

//Guardar los cambios
template <typename T>
void Categoria<T>::guardar(const TS& archivo) const{
    ofstream out(archivo, ios::binary | ios::trunc);
    if (!out.is_open())
        return;
    for(TI i=0; i<m_size; ++i)
        m_vector[i].writeBin(out);
}


template <typename U>
ostream& operator<<(ostream& os, const Categoria<U>& x){
    for(TI i=0; i<x.m_size; ++i){
        os << "*************************\n" 
           << x.m_vector[i]<< endl;
    }
    return os;
}

template <typename T>
Categoria<T>& Categoria<T>::operator=(const Categoria& other){
    if(this != &other){
        delete[] m_vector;
        if(other.m_vector != nullptr){
            m_size      = other.m_size;
            m_vector    = new T[other.m_size];
            for(TI i=0; i<m_size; ++i)
                m_vector[i] = other.m_vector[i];
        }else{
            m_vector    = nullptr;
            m_size      = 0;
        }
    }
    return *this;
}

#endif //__CATALOGO_H__