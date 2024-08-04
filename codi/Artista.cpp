/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A
*/
#include<iostream>
using namespace std;
#include"Artista.h"

Artista::Artista(){}

Artista::Artista(int _artist_id, string _name, string _gender, string _country, string _styles, int _playCount){
    this->artist_id = _artist_id;
    this->name = _name;
    this->gender = _gender;
    this->country = _country;
    this->styles = _styles;
    this->playCount = _playCount;
}

Artista::Artista(Artista& orig){
    this->artist_id = orig.getId();
    this->name = orig.getName();
    this->gender = orig.getGender();
    this->country = orig.getCountry();
    this->styles = orig.getStyles();
    this->playCount = orig.getPlayCount();
}

Artista::~Artista(){}

// Setters

void Artista::setId(int id){artist_id = id;}

void Artista::setName(string n){name = n;}

void Artista::setCountry(string c){country = c;}

void Artista::setGender(string g){country = g;}

void Artista::setStyles(string s){styles = s;}

void Artista::setPlayCount(int p){playCount = p;}

// Getters

int Artista::getId() const{return artist_id;}

string Artista::getName() const{return name;}

string Artista::getCountry() const{return country;}

string Artista::getGender() const{return gender;}

string Artista::getStyles() const{return styles;}

int Artista::getPlayCount() const{return playCount;}

string Artista::toString() const{  // Transforma en un string tots els atributs de l'artista
    return "ID de l'artista: " + to_string(artist_id) + "\n" +
    "Nom de l'artista: " + name + "\n" +
    "Génere de l'artista: " + gender + "\n" +
    "País de l'artista: " + country + "\n" +
    "Estils de l'artista: " + styles + "\n" +
    "Nombre de reproduccions del artista: " + to_string(playCount) + "\n";
}

void Artista::print(Artista& artista) const{ // mostra l'artista
    cout << toString();
}
