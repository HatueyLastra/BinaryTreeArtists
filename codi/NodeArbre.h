/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A
*/
#include"Artista.h"
#include"Artista.cpp"
#ifndef NODEARBRE_H
#define NODEARBRE_H

#pragma once
template <class CLAU, class VALOR >
class NodeArbre {
public:
NodeArbre(const CLAU& key, const VALOR& v); // cost O(1)
NodeArbre(const NodeArbre<CLAU,VALOR>& orig); // cost O(n) on n: nombre nodes de l'arbre
virtual ~NodeArbre(); // cost O(n) on n: nombre nodes de l'arbre
/* Modificadors */
// declareu aquí els modificadors (setters) dels atributs que necessiteu

void insereixClau(CLAU clau);                        //O(1)
void insereixDreta(NodeArbre<CLAU, VALOR>* d);       //O(1)
void insereixEsquerra(NodeArbre<CLAU, VALOR>* e);    //O(1)
void insereixPare(NodeArbre<CLAU, VALOR>* p);        //O(1)

/* Consultors */

const CLAU& obteClau() const; // cost O(1)
const VALOR& obteValor() const; // cost O(1)
NodeArbre<CLAU, VALOR>* obteDreta() const; // cost O(1)
NodeArbre<CLAU, VALOR>* obteEsquerra() const; // cost O(1)
NodeArbre<CLAU, VALOR>* obtePare() const; // cost O(1)

// declareu aquí els consultors (getters) dels atributs que necessiteu
/* Operacions */
bool esArrel() const; // cost O(1)
bool teEsquerra() const; // cost O(1)
bool teDreta() const; // cost O(1)
bool esExtern() const; // cost O(1)
void insereixValor(const VALOR & v); // cost O(1)
int altura() const; // cost O(n)
int balanç() const; // cost O(n)
bool operator==(const NodeArbre<CLAU,VALOR>& node) const; // cost O(1)
private:
CLAU key;
VALOR value;
NodeArbre<CLAU, VALOR>* dreta;
NodeArbre<CLAU, VALOR>* esquerra;
NodeArbre<CLAU, VALOR>* pare;
 // afegiu aquí els atributs que falten
};

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>:: NodeArbre(const CLAU& key, const VALOR& v){ // constructor de NodeArbre, defineix la seva clau i el seu valor
    this->key = key;                                                 // i deix els seus punters a nullptr
    this->value = v;
    this->dreta = nullptr;
    this->esquerra = nullptr;
    this->pare = nullptr;
    
}

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>:: NodeArbre(const NodeArbre<CLAU,VALOR>& orig):NodeArbre<CLAU, VALOR>(orig.key, orig.value){

        this->value = orig.value;
    if (orig.esquerra != nullptr) { //Si té fills a l'esquerra cridem al constructor copia per copiar-los fent un recorregut recursiu
        this->esquerra = new NodeArbre<CLAU,VALOR>(*orig.esquerra);
        this->esquerra->insereixPare(this);
    }
    if (orig.dreta != nullptr) { //El mateix amb el fills drets
       this->dreta = new NodeArbre<CLAU,VALOR>(*orig.dreta);
       this->dreta->insereixPare(this);
    }
}

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>:: ~NodeArbre(){
    delete esquerra;
    delete dreta;
}

template<class CLAU, class VALOR>
void NodeArbre<CLAU, VALOR>:: insereixClau(CLAU clau){  // setter de la clau
    key = clau;
}

template<class CLAU, class VALOR>
void NodeArbre<CLAU, VALOR>:: insereixDreta(NodeArbre<CLAU, VALOR>* d){ // setter de la dreta
    dreta = d;
}

template<class CLAU, class VALOR>
void NodeArbre<CLAU, VALOR>:: insereixEsquerra(NodeArbre<CLAU, VALOR>* e){ // setter de l'esquerra
    esquerra = e;
}

template<class CLAU, class VALOR>
void NodeArbre<CLAU, VALOR>:: insereixPare(NodeArbre<CLAU, VALOR>* p){ // setter del pare
    pare = p;
}

template<class CLAU, class VALOR>
const CLAU& NodeArbre<CLAU, VALOR>:: obteClau() const{ // getter de la clau
    return key;
}

template<class CLAU, class VALOR>
const VALOR& NodeArbre<CLAU, VALOR>:: obteValor() const{ // getter del valor
    return value;
}

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>* NodeArbre<CLAU, VALOR>:: obteDreta() const{ // getter de la dreta
    return dreta;
}

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>* NodeArbre<CLAU, VALOR>:: obteEsquerra() const{ // getter de l'esquerra
    return esquerra;
}

template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>* NodeArbre<CLAU, VALOR>:: obtePare() const{ // getter del pare
    return pare;
}


template<class CLAU, class VALOR>
bool NodeArbre<CLAU, VALOR>:: esArrel() const{ // retorna true si el node no té pare
    return pare == nullptr;
}

template<class CLAU, class VALOR>
bool NodeArbre<CLAU, VALOR>:: teEsquerra() const{ // retorna true si el node té esquerra
    return esquerra != nullptr;
}

template<class CLAU, class VALOR>
bool NodeArbre<CLAU, VALOR>:: teDreta() const{ // retorna true si el node té dreta
    return dreta != nullptr;
}

template<class CLAU, class VALOR>
bool NodeArbre<CLAU, VALOR>:: esExtern() const{ // retorna true si no té ni dreta ni esquerra
    return esquerra == nullptr && dreta == nullptr;
}

template<class CLAU, class VALOR>
void NodeArbre<CLAU, VALOR>:: insereixValor(const VALOR & v){ // setter del valor
    value = v;
}

template<class CLAU, class VALOR>
int NodeArbre<CLAU, VALOR>:: altura() const{  // Es tracta d'una funció recursiva, si el node té un fill es torna a cridar la funció
        if (this == nullptr) {                // amb un +1, d'aquesta manera podem saber l'altura
        return 0; 
    } else {
        int alturaEsquerra = (esquerra != nullptr) ? esquerra->altura() : 0;
        int alturaDreta = (dreta != nullptr) ? dreta->altura() : 0;
        return max(alturaEsquerra, alturaDreta) + 1;
    }                   

}

template<class CLAU, class VALOR>
bool NodeArbre<CLAU, VALOR>:: operator==(const NodeArbre<CLAU,VALOR>& node) const{ // retorna true si les claus i els valor dels nodes coincideixen
    return key == node->obteClau() && value == node->obteValor();
    
}

template <class CLAU, class VALOR>
int NodeArbre<CLAU,VALOR>::balanç() const {
    int alturaEsquerra = (teEsquerra()) ? obteEsquerra()->altura() : 0;  // Calcula l'altura del subarbre esquerre.
    int alturaDreta = (teDreta()) ? obteDreta()->altura() : 0;           // Calcula l'altura del subarbre dret.
    return alturaEsquerra - alturaDreta;                                 // Retorna el balanç.
}


#endif
