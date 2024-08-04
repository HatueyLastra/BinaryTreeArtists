/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A
*/
#ifndef ARTISTA_H
#define ARTISTA_H

#pragma once

#include<iostream>
using namespace std;

class Artista
{
public:
    Artista();  // cost O(1)
    Artista(int artist_id, string name, string country, string gender, string styles, int playCount);  // cost O(1)
    Artista(Artista& orig);  // cost O(1)
    ~Artista();  // cost O(1)

    // Setters
    void setId(int id);  // cost O(1)
    void setName(string n);  // cost O(1)
    void setCountry(string c);  // cost O(1)
    void setGender(string g);  // cost O(1)
    void setStyles(string s);  // cost O(1)
    void setPlayCount(int p);  // cost O(1)

    // Getters
    int getId() const;  // cost O(1)
    string getName() const;  // cost O(1)
    string getCountry() const;  // cost O(1)
    string getGender() const;  // cost O(1)
    string getStyles() const;  // cost O(1)
    int getPlayCount() const;  // cost O(1)

    string toString() const;  // cost O(1)
    void print(Artista& artista) const;  // cost O(1)

private:

int artist_id;
string name;
string country;
string gender;
string styles;
int playCount;


};

#endif