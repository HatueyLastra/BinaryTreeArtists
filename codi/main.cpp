/*
nom: Hatuey Lastra Barnes
Grup de pràctiques: A


Els resultats que obtenim al fer les proves de rendiment són les següents:
(tenint en compte que els resultats poden variar bastant entre prova y prova, he fet varies proves i he agafat els valors mitjants
 que he obtingut en el meu ordinador)

+----------------------------------------------+----------------------+
| OPERACIÓ             |  ArbreBST             |  ArbreAVL            |
+----------------------------------------------+----------------------+
| Inserció arbre petit |  4158 microsegons.    |  5598 microsegons.   |
+----------------------+-----------------------+----------------------+
| Inserció arbre Gran  |  180375 microsegons.  |  620615 microsegons. |
+----------------------+-----------------------+----------------------+
| Cerca arbre petit    |  27 microsegons.      |  31 microsegons.     |
+----------------------+-----------------------+----------------------+
| Cerca arbre gran     |  174 microsegons.     |  44 microsegons.     |
+----------------------+-----------------------+----------------------+

Amb aquestes dades podem veure que l'arbreAVL triga una mica més de temps en insertar els fitxers, aixó té sentit degut a que l'arbreAVL
té que fer operacions de balanç cada cop que l'arbre no es troba balancejat. A l'hora de la cerca en un arbre petit es podria dir
que abdós arbres triguen gairebé el mateix. La diferència més notable entre els dos arbres és amb la cerca amb un fitxer gran,
on l'arbreAVL és molt més ràpid que l'arbreBST. Aixó té sentit degut a que l'arbreAVL es troba balancejat i té que fer menys iteracions
per arribar a la clau necessària.

Podem veure clarament aquesta diferència quan ens fixem en la profunditat dels arbres, on l'arbreBST té una profunditat de 4089,
mentre que l'arbreAVL té una profunditat de 11 (abdós casos en el fitxer gran).
*/
#include "NodeArbre.h"
#include "ArbreBST.h"
#include "ArbreAVL.h"
#include "CercadorArtistesBST.h"
#include "CercadorArtistesAVL.h"
#include "Artista.h"
#include<iostream>
#include<list>
#include<stdexcept>
#include<vector>
#include<chrono>
using namespace std;


vector<string> arr_options = {"Llegir fitxer", "Mostrar artistes","Cercar artistes d'un fitxer","Profunditat arbre","Buscar artista","Mostrar artista","Recompte artistes amb més playcount", "Cercar artistes per estil","Sortir"};
    int option;
    
    int optionList(){
            cout << "Hola, que vols fer?\n";
            for(int i = 0; i < arr_options.size(); i++){
                cout << i + 1 << ". " << arr_options[i] << "\n";
            }
    cin >> option;
    return option;
}



void casDeProvaExercici1_2023_2024() {
 std::cout << " ------------- cas de prova exercici 1 ----------- " << std::endl; 
 ArbreBST<int, int> tree1;
 int testKeys[] = {2, 0, 8, 45, 76, 5, 6, 3, 40};
 int testValues[] = {5, 5, 1, 88, 99, 6, 12, 9, 11};
 for (int i = 0; i < 9 ; i++) { tree1.insereix(testKeys[i], testValues[i]); }

 cout << "preordre={ "; tree1.imprimeixPreordre(); cout << "}" << endl;
 cout << "inordre={ "; tree1.imprimeixInordre(); cout << "}" << endl;
 cout << "postordre={ "; tree1.imprimeixPostordre(); cout << "}" << endl;
 cout << " Conte clau 45 " << tree1.conteClau(45) << endl;
 cout << " Conte clau 37 " << tree1.conteClau(37) << endl;
 cout << " Conte clau 76 " << tree1.conteClau(76) << endl;
 cout << " Conte clau 2 " << tree1.conteClau(2) << endl << endl;
 ArbreBST<int, int> tree2(tree1);
 cout << "postordre copia ={ "; tree2.imprimeixPostordre(); cout << "}" << endl;
 cout << "preordre copia ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;
 tree2.arbreMirall();
 cout << "preordre arbre mirall 1 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl;
 tree2.arbreMirall();
 cout << "preordre arbre mirall 2 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl <<
endl;
 list<NodeArbre<int, int>*> llista = tree1.obteFullesArbre(true);
 cout << "obteFullesArbre(esq)={ ";
 for(NodeArbre<int, int>* n: llista){
 cout << n->obteClau() << " ";
 }
 cout << "}" << endl<< endl;
list<NodeArbre<int, int>*> llista2 = tree1.obteFullesArbre(false);
 cout << "obteFullesArbre(dreta)={ ";
 for(NodeArbre<int, int>* n: llista2){
 cout << n->obteClau() << " ";
 }
 cout << "}" << endl<< endl;
 std::cout << " ------------- FI cas de prova exercici 1 ----------- " << std::endl;
}

void casDeProvaExercici2() {
 std::cout << " ------------- cas de prova prova exercici 2 ----------- " <<
std::endl;
 // Crear una instància del cercador d'artistes
 CercadorArtistesBST cercador;
 // Afegir artistes des d'un fitxer
 try {
 cercador.afegeixArtistes("spanishArtists.csv");
 } catch (const std::invalid_argument& e) {
 std::cerr << "Error: " << e.what() << std::endl;
 return;
 }
 // Mostrar l'altura de l'arbre BST
 std::cout << "Altura de l'arbre BST: " << cercador.height() << std::endl;
 // Mostrar l'artista amb un ID específic
 std::cout << "Artista amb ID 1370: " << cercador.mostrarArtista(1370) << std::endl;
 // Comprovar si un artista amb un ID específic existeix
 int artistID = 4893;
 if (cercador.buscarArtista(artistID)) {
 std::cout << "L'artista amb ID " << artistID << " existeix." << std::endl;
 } else {
 std::cout << "L'artista amb ID " << artistID << " no existeix." << std::endl;
 }
 // Mostrar l'arbre BST ordenat
 std::cout << "Arbre BST ordenat:" << std::endl;
 cercador.imprimirArbreOrdenat(); /*imprimirOrdenat()*/
// Quants artistes amb més playcount
 std::cout << "Quants artistes amb mes de 100000 reproduccions :" << std::endl;
 std::cout << cercador.buscarRecompteArtistes(100000) << std::endl;
 // Obtenir tots els artistes d'un estil específic
 std::string estil = "folk";
 std::list<int> artistesRock = cercador.obtenirArtistesPerEstil(estil);
 std::cout << "Artistes d'estil Rock (IDs): ";
 for (int id : artistesRock) {
 std::cout << id << " ";
 }
 std::cout << std::endl;
 std::cout << " ------------- Fi cas de prova prova exercici 2 ----------- " <<
std::endl;
}

void casDeProvaExercici3() {
 std::cout << " ------------- cas de prova exercici 3 ----------- " << std::endl; 
 ArbreAVL<int, int> tree1;
 int testKeys[] = {2, 0, 8, 45, 76, 5, 6, 3, 40};
 int testValues[] = {5, 5, 1, 88, 99, 6, 12, 9, 11};
 for (int i = 0; i < 9 ; i++) { tree1.insereix(testKeys[i], testValues[i]); }

 cout << "preordre={ "; tree1.imprimeixPreordre(); cout << "}" << endl;
 cout << "inordre={ "; tree1.imprimeixInordre(); cout << "}" << endl;
 cout << "postordre={ "; tree1.imprimeixPostordre(); cout << "}" << endl;
 cout << " Conte clau 45 " << tree1.conteClau(45) << endl;
 cout << " Conte clau 37 " << tree1.conteClau(37) << endl;
 cout << " Conte clau 76 " << tree1.conteClau(76) << endl;
 cout << " Conte clau 2 " << tree1.conteClau(2) << endl << endl;
 ArbreBST<int, int> tree2(tree1);
 cout << "postordre copia ={ "; tree2.imprimeixPostordre(); cout << "}" << endl;
 cout << "preordre copia ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;
 tree2.arbreMirall();
 cout << "preordre arbre mirall 1 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl;
 tree2.arbreMirall();
 cout << "preordre arbre mirall 2 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl <<
endl;
 list<NodeArbre<int, int>*> llista = tree1.obteFullesArbre(true);
 cout << "obteFullesArbre(esq)={ ";
 for(NodeArbre<int, int>* n: llista){
 cout << n->obteClau() << " ";
 }
 cout << "}" << endl<< endl;
list<NodeArbre<int, int>*> llista2 = tree1.obteFullesArbre(false);
 cout << "obteFullesArbre(dreta)={ ";
 for(NodeArbre<int, int>* n: llista2){
 cout << n->obteClau() << " ";
 }
 cout << "}" << endl<< endl;
 std::cout << " ------------- FI cas de prova exercici 3 ----------- " << std::endl;
}

void casDeProvaExercici4() {
 std::cout << " ------------- cas de prova prova exercici 4 ----------- " <<
std::endl;
 // Crear una instància del cercador d'artistes
 CercadorArtistesAVL cercador;
 // Afegir artistes des d'un fitxer
 try {
 cercador.afegeixArtistes("spanishArtists.csv");
 } catch (const std::invalid_argument& e) {
 std::cerr << "Error: " << e.what() << std::endl;
 return;
 }
 // Mostrar l'altura de l'arbre BST
 std::cout << "Altura de l'arbre BST: " << cercador.height() << std::endl;
 // Mostrar l'artista amb un ID específic
 std::cout << "Artista amb ID 1370: " << cercador.mostrarArtista(1370) << std::endl;
 // Comprovar si un artista amb un ID específic existeix
 int artistID = 4893;
 if (cercador.buscarArtista(artistID)) {
 std::cout << "L'artista amb ID " << artistID << " existeix." << std::endl;
 } else {
 std::cout << "L'artista amb ID " << artistID << " no existeix." << std::endl;
 }
 // Mostrar l'arbre BST ordenat
 std::cout << "Arbre AVL ordenat:" << std::endl;
 cercador.imprimirArbreOrdenat(); /*imprimirOrdenat()*/
// Quants artistes amb més playcount
 std::cout << "Quants artistes amb mes de 100000 reproduccions :" << std::endl;
 std::cout << cercador.buscarRecompteArtistes(100000) << std::endl;
 // Obtenir tots els artistes d'un estil específic
 std::string estil = "folk";
 std::list<int> artistesRock = cercador.obtenirArtistesPerEstil(estil);
 std::cout << "Artistes d'estil Rock (IDs): ";
 for (int id : artistesRock) {
 std::cout << id << " ";
 }
 std::cout << std::endl;
 std::cout << " ------------- Fi cas de prova prova exercici 4 ----------- " <<
std::endl;
}

void mainExercici4(){
    CercadorArtistesAVL cercador;
    do{
    switch(optionList()){
        case 1: {
        string option;
        cout << "Quin fitxer vols? (P/G)\n";
        cin >> option;
        if(option == "P"){
            chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
            cercador.afegeixArtistes("spanishArtists.csv");
            chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
                    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end1 -
begin1).count() << " microsegons." << endl;
        }
        else if(option == "G"){
            chrono::steady_clock::time_point begin2 = chrono::steady_clock::now();
            cercador.afegeixArtistes("usArtists.csv");
            chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
            cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end2 -
begin2).count() << " microsegons." << endl;
        }
        else{
            cout << "La teva opció no correspon amb cap tipus de fitxer\n";
        }
        break;
        }
        case 2: {
                try{
            cercador.imprimirArbreOrdenat();
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        }
        break;
        }
        case 3: {
            string linia, num;
            int ID, contador = 0;
            ifstream fitxer("cercaArtists.csv");
            getline(fitxer, linia);
            chrono::steady_clock::time_point begin3 = chrono::steady_clock::now();
            while (getline(fitxer, num, ',')) {
                 ID = stoi(num);
                try{
                    if(cercador.buscarArtista(ID)) contador++;
                }
                catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
     }
                getline(fitxer, linia, '\n');
    }
            chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
            cout << "El nombre d'artistes que es coincideixen en els dos fitxers és " << contador << "\n";
            cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end3 -
begin3).count() << " microsegons.\n" << endl;
        break;
        }
        case 4: {
            int profunditat;
        try{
           profunditat = cercador.height() - 1;
           cout << "La profunditat de l'arbre és de: " << profunditat << "\n";

        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 5: {
        int artistaId;
        cout << "Escriu l'id de l'artista que vols buscar: \n";
        try{
        if (!(std::cin >> artistaId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Id incorrecte.");
        }
        if(cercador.buscarArtista(artistaId))
        cout << "S'ha trobat l'artista a l'arbre\n";
        else
        cout << "No s'ha trobat l'artista a l'arbre\n";
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 6: {
        int artistaId;
        cout << "Escriu l'id de l'artista que vols buscar: \n";
        try{
        if (!(cin >> artistaId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Id incorrecte.");
        }
        cout << cercador.mostrarArtista(artistaId);
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 7: {
        int playCount;
        cout << "A partir de quantes reproduccions vols buscar? \n";
        try{
        if (!(cin >> playCount)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Error al introduïr reproduccions");
        }
        cout << "Aquest es el recompte d'artistes:";
        cout << cercador.buscarRecompteArtistes(playCount) << "\n";
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 8: {
        int id;
        list<int> artistes;
        string estil;
        cout << "Escriu l'estil del que vols buscar artistes:\n";
        cin >> estil;
        try{
            artistes = cercador.obtenirArtistesPerEstil(estil);
            if(artistes.size() < 1) throw invalid_argument("No existeis cap artista amb aquest estil!");
            else{
            cout << "Aquest és el recompte d'artistes:\n ";
            for(int num : artistes){
            id = num;
            cout << cercador.mostrarArtista(id) << "\n";
            }
        }
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        }
        break;
        }
        case 9:
        cout << "Fins la propera!\n";
        break;

    }
    }while(option != 9);
}

void mainExercici2(){
    CercadorArtistesBST cercador;
    do{
    switch(optionList()){
        case 1: {
        string option;
        cout << "Quin fitxer vols? (P/G)\n";
        cin >> option;
        if(option == "P"){
            chrono::steady_clock::time_point begin4 = chrono::steady_clock::now();
            cercador.afegeixArtistes("spanishArtists.csv");
            chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
                    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end4 -
begin4).count() << " microsegons." << endl;
        }
        else if(option == "G"){
            chrono::steady_clock::time_point begin5 = chrono::steady_clock::now();
            cercador.afegeixArtistes("usArtists.csv");
            chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
            cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end5 -
begin5).count() << " microsegons." << endl;
        }
        else{
            cout << "La teva opció no correspon amb cap tipus de fitxer\n";
        }
        break;
        }
        case 2: {
                try{
            cercador.imprimirArbreOrdenat();
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        }
        break;
        }
        case 3: {
            string linia, num;
            int ID, contador = 0;
            ifstream fitxer("cercaArtists.csv");
            getline(fitxer, linia);
            chrono::steady_clock::time_point begin6 = chrono::steady_clock::now();
            while (getline(fitxer, num, ',')) {
                 ID = stoi(num);
                try{
                    if(cercador.buscarArtista(ID)) contador++;
                }
                catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
     }
                getline(fitxer, linia, '\n');
    }
            chrono::steady_clock::time_point end6 = chrono::steady_clock::now();
            cout << "El nombre d'artistes que es coincideixen en els dos fitxers és " << contador << "\n";
            cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end6 -
begin6).count() << " microsegons.\n" << endl;
        break;
        }
        case 4: {
            int profunditat;
        try{
           profunditat = cercador.height() - 1;
           cout << "La profunditat de l'arbre és de: " << profunditat << "\n";

        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 5: {
        int artistaId;
        cout << "Escriu l'id de l'artista que vols buscar: \n";
        try{
        if (!(std::cin >> artistaId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Id incorrecte.");
        }
        if(cercador.buscarArtista(artistaId))
        cout << "S'ha trobat l'artista a l'arbre\n";
        else
        cout << "No s'ha trobat l'artista a l'arbre\n";
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 6: {
        int artistaId;
        cout << "Escriu l'id de l'artista que vols buscar: \n";
        try{
        if (!(cin >> artistaId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Id incorrecte.");
        }
        cout << cercador.mostrarArtista(artistaId);
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 7: {
        int playCount;
        cout << "A partir de quantes reproduccions vols buscar? \n";
        try{
        if (!(cin >> playCount)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Error al introduïr reproduccions");
        }
        cout << "Aquest es el recompte d'artistes:";
        cout << cercador.buscarRecompteArtistes(playCount) << "\n";
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
        break;
        }
        case 8: {
        int id;
        list<int> artistes;
        string estil;
        cout << "Escriu l'estil del que vols buscar artistes:\n";
        cin >> estil;
        try{
            artistes = cercador.obtenirArtistesPerEstil(estil);
            if(artistes.size() < 1) throw invalid_argument("No existeis cap artista amb aquest estil!");
            else{
            cout << "Aquest és el recompte d'artistes:\n ";
            for(int num : artistes){
            id = num;
            cout << cercador.mostrarArtista(id) << "\n";
            }
        }
        }
        catch(const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        }
        break;
        }
        case 9:
        cout << "Fins la propera!\n";
        break;

    }
    }while(option != 9);
}

int main(){
    casDeProvaExercici1_2023_2024();
    casDeProvaExercici3();
    casDeProvaExercici2();
    casDeProvaExercici4();
    mainExercici2();
    mainExercici4();
    return 0;
}