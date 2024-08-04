/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A

L'arbreAVL és similar al arbreBST, la diferència es que l'AVL té unes funcions extra que li permeten estar balancejat,
aixó és molt més preferible a l'hora d'emmagatzemar una gran quantitat de dades, ja que amb un arbre ben distribuït ens
costarà un menor nombre de passos en arribar al valor necessari, i també ens ajuda en certs casos desfavorables amb 
arbres irregulars.
*/
#ifndef ARBREAVL_HPP
#define ARBREAVL_HPP

#include "ArbreBST.h"
using namespace std;

template<class K, class V>
class ArbreAVL : public ArbreBST<K,V> {
    public:
ArbreAVL();
ArbreAVL(const ArbreAVL<K, V>& orig);
virtual ~ArbreAVL();
NodeArbre<K,V>* insereix(const K& k, const V& value);       
bool buida() const; // O(1)
int altura() const; // O(log(n)), O(n) pitjor cas
int obteMida() const; // O(log(n)), O(n) pitjor cas
const V& valorDe(const K& clau) const; // O(log(n)), O(n) pitjor cas
void imprimeixPreordre(const NodeArbre<K,V>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
void imprimeixInordre(const NodeArbre<K,V>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
void imprimeixPostordre(const NodeArbre<K,V>* n = nullptr) const; // O(log(n)), O(n) pitjor cas
 bool conteClau(const K& clau) const; // O(log(n)), O(n) pitjor cas
 void arbreMirall(); // O(n) on n: elements arbre orig
 list<NodeArbre<K,V>*> obteFullesArbre(bool esq) const; // O(log(n)), O(n) pitjor cas
protected:
NodeArbre<K,V>* cercar(const K& k) const; // O(log(n)), O(n) pitjor cas
private:
NodeArbre<K,V>* rotacioDD(NodeArbre<K,V>* n); // O(1)
NodeArbre<K,V>* rotacioEE(NodeArbre<K,V>* n); // O(1)
NodeArbre<K,V>* rotacioED(NodeArbre<K,V>* n); // O(1)
NodeArbre<K,V>* rotacioDE(NodeArbre<K,V>* n); // O(1)
};


template<class K, class V>
ArbreAVL<K,V>::ArbreAVL() {}

template<class K, class V>
ArbreAVL<K,V>::ArbreAVL(const ArbreAVL<K, V>& orig) : ArbreBST<K, V>(orig) {}

template<class K, class V>
ArbreAVL<K,V>::~ArbreAVL() {}

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>::insereix(const K& k, const V& value) {
    NodeArbre<K,V>* node = ArbreBST<K,V>::insereix(k, value);
            while (node != nullptr) {
            if (node->balanç() == 2) {
                if (node->obteEsquerra()->balanç() == 1) {
                    node = rotacioEE(node);
                } else {
                    node = rotacioED(node);
                }
            } else if (node->balanç() == -2) {
                if (node->obteDreta()->balanç() == -1) {
                    node = rotacioDD(node);
                } else {
                    node = rotacioDE(node);
                }
            }

            if (node->obtePare() == nullptr) {
                break; // El node és l'arrel
            }

            node = node->obtePare();
        }

        // trobar l'arrel
        while (node->obtePare() != nullptr) {
            node = node->obtePare();
        }

        return node;
    }
    

template<class K, class V>
bool ArbreAVL<K,V>::buida() const {return ArbreBST<K,V>::buida();}  // Comprova si l'arbre està buit

template<class K, class V>
int ArbreAVL<K,V>::altura() const {return ArbreBST<K,V>::altura();}  // Retorna l'altura de l'arbre

template<class K, class V>
int ArbreAVL<K,V>::obteMida() const {return ArbreBST<K,V>::obteMida();}  // Retorna la mida de l'arbre

template<class K, class V>
const V& ArbreAVL<K,V>::valorDe(const K& clau) const { return ArbreBST<K,V>::valorDe(clau);}  // Retorna el valor associat a una clau

template<class K, class V>
bool ArbreAVL<K,V>::conteClau(const K& clau) const {return ArbreBST<K,V>::conteClau(clau);}  // Comprova si l'arbre conté una clau

template<class K, class V>
void ArbreAVL<K,V>::arbreMirall() {ArbreBST<K,V>::arbreMirall();}  // Fa que un arbre es torni en la seva versió mirall

template<class K, class V>
list<NodeArbre<K,V>*> ArbreAVL<K,V>::obteFullesArbre(bool esq) const {return ArbreBST<K,V>::obteFullesArbre(esq);}  // Retorna una llista de fulles de l'arbre

template<class K, class V>
void ArbreAVL<K,V>::imprimeixPreordre(const NodeArbre<K,V>* n) const {ArbreBST<K,V>::imprimeixPreordre(n);}  // Imprimeix en preordre

template<class K, class V>
void ArbreAVL<K,V>::imprimeixInordre(const NodeArbre<K,V>* n) const {ArbreBST<K,V>::imprimeixInordre(n);}  // Imprimeix en inordre

template<class K, class V>
void ArbreAVL<K,V>::imprimeixPostordre(const NodeArbre<K,V>* n) const {ArbreBST<K,V>::imprimeixPostordre(n);}  // Imprimeix en postordre

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>:: cercar(const K& k) const{}  // Cerca un node amb una clau donada

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>::rotacioEE(NodeArbre<K,V>* n) {  // Rotació doble a l'esquerra
    NodeArbre<K,V>* esquerra = n->obteEsquerra();
        n->insereixEsquerra(esquerra->obteDreta());
        if (esquerra->teDreta()) {
            esquerra->obteDreta()->insereixPare(n);
        }
        esquerra->insereixDreta(n);
        esquerra->insereixPare(n->obtePare());

        if (!n->esArrel()) {
        if (n == n->obtePare()->obteEsquerra()) {
            n->obtePare()->insereixEsquerra(esquerra);
        } else {
            n->obtePare()->insereixDreta(esquerra);
        }
    } else {
        ArbreBST<K,V>::setArrel(esquerra);
    }
    n->insereixPare(esquerra);
        return esquerra;
    }

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>::rotacioDD(NodeArbre<K,V>* n) {  // Rotació doble a la dreta
       NodeArbre<K,V>* dreta = n->obteDreta();
        n->insereixDreta(dreta->obteEsquerra());
        if (dreta->teEsquerra()) {
            dreta->obteEsquerra()->insereixPare(n);
        }
        dreta->insereixEsquerra(n);
        dreta->insereixPare(n->obtePare());
            if (!n->esArrel()) {
        if (n == n->obtePare()->obteEsquerra()) {
            n->obtePare()->insereixEsquerra(dreta);
        } else {
            n->obtePare()->insereixDreta(dreta);
        }
    } else {
        ArbreBST<K,V>::setArrel(dreta);
    }

        n->insereixPare(dreta);
        return dreta;
}

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>::rotacioDE(NodeArbre<K,V>* n) {  // Rotació dreta-esquerra
        n->insereixDreta(rotacioEE(n->obteDreta()));
        return rotacioDD(n);
}

template<class K, class V>
NodeArbre<K,V>* ArbreAVL<K,V>::rotacioED(NodeArbre<K,V>* n) {  // Rotació esquerra-dreta
        n->insereixEsquerra(rotacioDD(n->obteEsquerra()));
        return rotacioEE(n);
}

#endif





