/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A
*/
#ifndef ARBREBST_H
#define ARBREBST_H
#include "NodeArbre.h"
#include<iostream>
#include<stdexcept>
#include<list>
using namespace std;

#pragma once
template <class CLAU, class VALOR>
class ArbreBST {
 public:
ArbreBST();  // O(1)
ArbreBST(const ArbreBST<CLAU, VALOR>& orig); // O(n) on n: elements arbre orig
virtual ~ArbreBST(); // O(n) on n: elements arbre
bool buida() const; // O(1)
int altura() const; // O(log(n)), O(n) pitjor cas
int obteMida() const; // O(log(n)), O(n) pitjor cas
NodeArbre<CLAU,VALOR>* insereix(const CLAU& clau, const VALOR& value); // O(log(n)), O(n) pitjor cas
const VALOR& valorDe(const CLAU& clau) const; // O(log(n)), O(n) pitjor cas
void imprimeixPreordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
void imprimeixInordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
void imprimeixPostordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
 bool conteClau(const CLAU& clau) const; // O(log(n)), O(n) pitjor cas
 void arbreMirall(); // O(n) on n: elements arbre orig
 list<NodeArbre<CLAU, VALOR>*> obteFullesArbre(bool esq) const; // O(log(n)), O(n) pitjor cas
 void setArrel(NodeArbre<CLAU,VALOR>* arr);
protected:
NodeArbre<CLAU,VALOR>* arrel;
NodeArbre<CLAU,VALOR>* cercar(const CLAU& k) const; // O(log(n)), O(n) pitjor cas
private:
int _mida;
int obteMidaAux(NodeArbre<CLAU,VALOR>* n) const; // igual que obteMida
void invertir(NodeArbre<CLAU,VALOR>* n) const; // igual que arbremirall
void obteFulles(NodeArbre<CLAU,VALOR>* n, list<NodeArbre<CLAU, VALOR>*>& llista) const; // igual que obteFullesArbre

 /* Mètodes auxiliars definiu aquí els que necessiteu */
};

template<class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>:: ArbreBST(){  // el constructor de l'arbre, amb una mida 0, sense nodes
    this->_mida = 0;
}

template<class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>:: ArbreBST(const ArbreBST<CLAU, VALOR>& orig){ // aquesta funció utilitza el constructor cópia de NodeArbre
    this->_mida = orig.obteMida();                                   // que va copiant recursivament els nodes fills del node seleccionat
            if(buida())                                              // per fer la cópia de l'arbre utilitzem l'arrel de l'arbre
        throw new invalid_argument("L'arbre està buit!");
    else{
        this->arrel = new NodeArbre<CLAU, VALOR>(*orig.arrel);
    }


}


template<class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>:: ~ArbreBST(){ // fa ús del destructor de NodeArbe, el qual elimina els fills de forma recursiva
        if(!buida())                  // per eliminar l'arbre es fa el delete de l'arrel i després s'elimina l'arrel
        delete arrel;                 // afegint un nullptr i es posa la mida a 0
        arrel = nullptr;
        _mida = 0; 
}

template<class CLAU, class VALOR>
bool ArbreBST<CLAU, VALOR>:: buida() const{  //Si la mida és 0, llavors l'arbre estará buit
    return _mida == 0;
}

template<class CLAU, class VALOR>
int ArbreBST<CLAU, VALOR>:: altura() const{ // si obtenim l'altura de l'arrel, obtenim l'altura d el'arbre
    if(buida()){
        return 0;
        throw new invalid_argument("L'arbre està buit!");
    }
    else{
        return arrel->altura();
    }
}

template<class CLAU, class VALOR>
NodeArbre<CLAU,VALOR>* ArbreBST<CLAU, VALOR>:: insereix(const CLAU& clau, const VALOR& value){ // per inserir un node anem iterant per una rama de l'arbre
    NodeArbre<CLAU,VALOR>* node = new NodeArbre<CLAU,VALOR>(clau,value);                       // amb dos nodes auxiliars per obtenir el valor que necessitem per crear el node
    NodeArbre<CLAU,VALOR>* nodeAux = arrel;
    NodeArbre<CLAU,VALOR>* pare;
    if(_mida == 0){
        _mida++;
        arrel = node;
        return node;
    }else{
while(nodeAux != nullptr){
    if(node->obteClau() < nodeAux->obteClau()){
        pare = nodeAux;
        nodeAux = nodeAux->obteEsquerra();
    }
    else{
        pare = nodeAux;
        nodeAux = nodeAux->obteDreta();
    }
}
    if(node->obteClau() < pare->obteClau())
        pare->insereixEsquerra(node);
    else
    pare->insereixDreta(node);
    node->insereixPare(pare);
    _mida = obteMida(); 
    return node; 
}
    }

template<class CLAU, class VALOR>
const VALOR& ArbreBST<CLAU, VALOR>:: valorDe(const CLAU& clau) const{ // es comprova si la clau pertany a l'arbre i després
    NodeArbre<CLAU,VALOR>* nodeAux = arrel;                           // es va iterant per la branca de l'arbe fins arribar al node
    if (buida())                                                      // que conté la clau i ens dona el seu valor
    throw new invalid_argument("L'arbre està buit \n");
    else if (!conteClau(clau))
    throw new invalid_argument("La clau no es troba a l'arbre \n");
    else{
    while(nodeAux->obteClau() != clau){
    if(nodeAux->obteClau() > clau){
        nodeAux = nodeAux->obteEsquerra();
    }
    else{
        nodeAux = nodeAux->obteDreta();
    }
    }
    return nodeAux->obteValor();
}
}


template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>:: imprimeixPreordre(const NodeArbre<CLAU,VALOR>* n) const{
    if (buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    if (n == nullptr) 
    imprimeixPreordre(arrel); //Si el node és null imprimeix tot el arbre
    else {
    cout << "Clau " << n->obteClau() << " amb valor " << n->obteValor() << "\n"; //Imprimeix la clau del pare i després la dels fills
    if (n->teEsquerra()) imprimeixPreordre(n->obteEsquerra());
    if (n ->teDreta()) imprimeixPreordre(n->obteDreta());
}
}

template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>:: imprimeixInordre(const NodeArbre<CLAU,VALOR>* n) const{
    if (buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    if (n == nullptr) 
    imprimeixInordre(arrel); //Si el node és null imprimeix tot el arbre
    else {
    if (n->teEsquerra()) imprimeixInordre(n->obteEsquerra());
    cout << "Clau " << n->obteClau() << " amb valor " << n->obteValor() << "\n"; //Imprimeix la clau del pare després dels esquerres i abans dels drets
    if (n ->teDreta()) imprimeixInordre(n->obteDreta());
}
}

template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>:: imprimeixPostordre(const NodeArbre<CLAU,VALOR>* n) const{
    if (buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    if (n == nullptr) 
    imprimeixPostordre(arrel); //Si el node és null imprimeix tot el arbre
    else {
    if (n->teEsquerra()) imprimeixPostordre(n->obteEsquerra());
    if (n ->teDreta()) imprimeixPostordre(n->obteDreta());
     cout << "Clau " << n->obteClau() << " amb valor " << n->obteValor() << "\n"; //Imprimeix primer els fills i després els pares
}
}

template<class CLAU, class VALOR>
bool ArbreBST<CLAU, VALOR>:: conteClau(const CLAU& clau) const{ // Va iterant per una branca de l'arbre i si no trova claus coincidents
    const NodeArbre<CLAU,VALOR>* nodeAux = arrel;               // llavors el node auxiliar acabará sent nullptr i la funció retornará false
    if (buida())                                                // indicant que la clau no es troba a l'arbre
    throw new invalid_argument("L'arbre està buit \n");
    else{
    while(nodeAux != nullptr && nodeAux->obteClau() != clau){
    if(nodeAux->obteClau() > clau){
        nodeAux = nodeAux->obteEsquerra();
    }
    else{
        nodeAux = nodeAux->obteDreta();
    }
    }
    return nodeAux != nullptr;
}
}

template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>:: arbreMirall(){  // Amb la funció "invertir" fa l'arbre mirall
    if (buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    else{
        invertir(arrel);
    }
}

    template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>:: invertir(NodeArbre<CLAU,VALOR>* n) const{ // de forma recursiva va pasant per tots els nodes de l'arbe
    if(!n->esExtern() && n != nullptr){                                // i inverteix els seus valors de dreta i esquerra
        NodeArbre<CLAU,VALOR>* dreta = n->obteDreta();
        NodeArbre<CLAU,VALOR>* esquerra = n->obteEsquerra();
        n->insereixDreta(esquerra);
        n->insereixEsquerra(dreta);
        invertir(dreta);
        invertir(esquerra);
    } 
}

    template<class CLAU, class VALOR>
 list<NodeArbre<CLAU, VALOR>*> ArbreBST<CLAU, VALOR>:: obteFullesArbre(bool esq) const{ // Depenent del palor del bool, es fa ús de la funció boteFulles
    list<NodeArbre<CLAU, VALOR>*> llistaFulles;                                         // per la part dreta o esquerra de l'arrel per aixií obtenir les fulles
    if(esq)                                                                             // d'una de les dos parts
       obteFulles(arrel->obteEsquerra(), llistaFulles);
    else
        obteFulles(arrel->obteDreta(), llistaFulles);
    return llistaFulles;
}

    template<class CLAU, class VALOR>
 void ArbreBST<CLAU, VALOR>:: obteFulles(NodeArbre<CLAU,VALOR>* n, list<NodeArbre<CLAU, VALOR>*>& llista) const{ // de forma recursiva va recorrent l'arbre
    if(n->esExtern()){                                                                                           // i quan troba una fulla l'afegeix a la llista
       llista.push_front(n);
    }
    else{
        obteFulles(n->obteEsquerra(), llista);
        obteFulles(n->obteDreta(), llista);

    }
}

    template<class CLAU, class VALOR>
  NodeArbre<CLAU,VALOR>* ArbreBST<CLAU, VALOR>:: cercar(const CLAU& k) const{ // busca de forma iterativa per les branques de l'arbre
    NodeArbre<CLAU,VALOR>* nodeAux = arrel;                                   // i quan trova la clau retorna el node que la conté
    if(buida()){
        throw new invalid_argument("L'arbre està buit \n");
    }
    else if (!conteClau(k))
    throw new invalid_argument("La clau no es troba a l'arbre \n");
    else{
    while(nodeAux->obteClau() != k){
    if(nodeAux->obteClau() > k){
        nodeAux = nodeAux->obteEsquerra();
    }
    else{
        nodeAux = nodeAux->obteDreta();
    }
    }
    return nodeAux;
    }
}

    template<class CLAU, class VALOR>
  int ArbreBST<CLAU, VALOR>:: obteMida() const{ // amb obteMidaAux aconsegueix retornar la mida de l'arbre
    if (buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    else if(arrel->esExtern())
    return 1;
    else{
        return obteMidaAux(arrel);
    }
}

    template<class CLAU, class VALOR>
  int ArbreBST<CLAU, VALOR>:: obteMidaAux(NodeArbre<CLAU,VALOR>* n) const{ // va de forma recursiva sumant els nodes de l'arbre
    if (n == nullptr) return 0;                                            // per acabar retornant el nombre total de nodes de l'arbre
    else return obteMidaAux(n->obteEsquerra()) + 1 + obteMidaAux(n->obteDreta());
    }

    template<class CLAU, class VALOR>
  void ArbreBST<CLAU, VALOR>:: setArrel( NodeArbre<CLAU,VALOR>* arr){
    arrel = arr;
  } 



#endif