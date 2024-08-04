/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A
*/

#ifndef CERCADORARTISTESBST_H
#define CERCADORARTISTESBST_H

#include<iostream>
#include<fstream>
using namespace std;
#include"ArbreBST.h"
#include"Artista.h"

#pragma once
class CercadorArtistesBST: protected ArbreBST<int, Artista>{
 public:
 CercadorArtistesBST();   // cost O(1)
 CercadorArtistesBST(const CercadorArtistesBST & orig);   // cost O(1)
 virtual ~CercadorArtistesBST();   // cost O(1)
 void afegeixArtistes(string filename);   // cost O(n) on n -> nombre d'artistes en el fitxer
 void insereixArtista(int ArtistaID, string name, string gender, string country,
 string styles, int counts);   // // O(log(n)), O(n) pitjor cas
 string mostrarArtista(int ArtistaID);   // O(log(n)), O(n) pitjor cas
 bool buscarArtista(int ArtistaID);   // O(log(n)), O(n) pitjor cas
 int buscarRecompteArtistes(int playcount);   // cost O(n) on n -> nombre d'artistes en l'arbre
 int height() const;   // O(log(n)), O(n) pitjor cas
 list<int> obtenirArtistesPerEstil(const string estil);   // cost O(n) on n -> nombre d'artistes en l'arbre
 void imprimirArbreOrdenat() const;   // cost O(n) on n -> nombre d'artistes en l'arbre
 private:
 int comptaPlayCount(int playcount, NodeArbre<int,Artista>* node);   // mateix que buscarRecompteArtistes
 void mateixEstil(list<int>& llista,const string estil, NodeArbre<int,Artista>* node);   // mateix que obtenirArtistesPerEstil
 void imprimirArtistes(NodeArbre<int,Artista>* node, int comptador, bool parar) const;   // mateix que imprimirArbreOrdenat
 // Aqui posareu tots els mètodes auxiliars
};


CercadorArtistesBST::CercadorArtistesBST(){}  // Constructor per defecte

CercadorArtistesBST::CercadorArtistesBST(const CercadorArtistesBST & orig){}  // Constructor còpia

CercadorArtistesBST::~CercadorArtistesBST(){}  // Destructor

void CercadorArtistesBST::afegeixArtistes(string filename){  // Afegeix artistes des d'un fitxer i els va afegint a l'arbre amb insereix

    int IdArtista, playCount;
    string id, name, country, gender, styles, play, linia;

    ifstream fitxer(filename);

    getline(fitxer, linia);

 while (getline(fitxer, id, ',')) {
        IdArtista = stoi(id);
        getline(fitxer, name, ',');
        getline(fitxer, gender, ',');
        getline(fitxer, country, ',');
        getline(fitxer, styles, ',');
        getline(fitxer, play, '\n');
        playCount = stoi(play);
        Artista artista(IdArtista,name,gender,country,styles,playCount);
        this->insereix(IdArtista,artista);
    }
}


void CercadorArtistesBST::insereixArtista(int ArtistaID, string name, string gender, string country,
 string styles, int counts){  // Insereix un artista en l'arbre
    Artista artista(ArtistaID,name,gender,country,styles,counts);
    this->insereix(ArtistaID,artista);
 }

string CercadorArtistesBST::mostrarArtista(int ArtistaID){  // Mostra les dades d'un artista donat el seu ID
    return this->valorDe(ArtistaID).toString();
}

bool CercadorArtistesBST::buscarArtista(int ArtistaID){  // Busca si un artista existeix en l'arbre donat el seu ID
    return this->conteClau(ArtistaID);
}

int CercadorArtistesBST::buscarRecompteArtistes(int playcount){  // Busca el recompte d'artistes amb un nombre mínim de reproduccions
    if(this->arrel == nullptr) throw new invalid_argument("L'arbre està buit!");
    else return comptaPlayCount(playcount, this->arrel);
}

int CercadorArtistesBST::comptaPlayCount(int playcount, NodeArbre<int,Artista>* node){ // compta de forma recursiva el nombre d'artistes
    if(node != nullptr){                                                               // segons un nombre de reproduccions
    if(node->obteValor().getPlayCount() >= playcount)
    return comptaPlayCount(playcount, node->obteEsquerra()) + comptaPlayCount(playcount, node->obteDreta()) + 1;
    else
    return comptaPlayCount(playcount, node->obteEsquerra()) + comptaPlayCount(playcount, node->obteDreta());  
    }
    return 0;
}



int CercadorArtistesBST::height() const{  // Retorna l'altura de l'arbre
    return this->altura();
}

list<int> CercadorArtistesBST::obtenirArtistesPerEstil(const string estil){  // retorna una llista d'artistes d'un estil determinat per l'usuari
    if(this->arrel == nullptr) throw new invalid_argument("L'arbre està buit!");
    else{
        list<int> llista;
        mateixEstil(llista, estil, this->arrel);
        return llista;
    }
}

void CercadorArtistesBST::mateixEstil(list<int>& llista, const string estil, NodeArbre<int,Artista>* node){  // afegeix a la llista de forma recursiva
    string delim = "|";                                                                                      // si un dels estils de l'artista coincideix
    int pos = node->obteValor().getStyles().find(delim);
    if(pos != -1){
        string cadenaAux = node->obteValor().getStyles();
        while(pos != -1){
        if(cadenaAux.substr(0,pos) == estil || cadenaAux.substr(pos + 1) == estil) llista.push_back(node->obteClau());
        cadenaAux = cadenaAux.substr(pos + 1);
        pos = cadenaAux.find(delim);
    }
    }
    else if(node->obteValor().getStyles() == estil) llista.push_back(node->obteClau());
    if(node->teEsquerra()) mateixEstil(llista, estil, node->obteEsquerra());
    if(node->teDreta()) mateixEstil(llista, estil, node->obteDreta());  
}

void CercadorArtistesBST::imprimirArbreOrdenat() const{  // Imprimeix l'arbre en inordre
    int comptador = 0;
    bool parar = false;
    if (this->buida()) 
    throw new invalid_argument("L'arbre està buit \n");
    else
    imprimirArtistes(this->arrel, comptador, parar);

}

void CercadorArtistesBST::imprimirArtistes(NodeArbre<int,Artista>* n, int comptador, bool parar) const{ // Imprimeix l'arbre en inordre, amb la capacitat de
    if(!parar){                                                                                         // poder deixar d'imprimir per cada 40 artistes impressos.
    if (n->teEsquerra()) imprimirArtistes(n->obteEsquerra(), comptador, parar);
    if(!parar) cout << "Clau " << n->obteClau() << " amb valor:\n" << n->obteValor().toString() << "\n"; 
    comptador++;
    if(comptador >= 40){
        string option;
        cout << "Veure més? (S/N)\n";
        cin >> option;
        if(option == "S" || option == "Si" || option == "si" || option == "SI") comptador = 0;
        else{
            cout << "Deixant de mostrar artistes.\n";
            comptador = 0; 
            parar = true;
        }
    }
    if (n ->teDreta()) imprimirArtistes(n->obteDreta(), comptador, parar);
    }
}


#endif