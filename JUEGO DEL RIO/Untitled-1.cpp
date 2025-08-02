#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void mostrarEstado(vector<string> ladoIzq, vector<string> ladoDer, string bote) {
    cout << "\nLado Izquierdo: ";
    for (string item : ladoIzq) cout << item << " ";
    cout << "\nLado Derecho: ";
    for (string item : ladoDer) cout << item << " ";
    cout << "\nBote lleva: " << bote << "\n";
    cout << "-------------------------\n";
}

bool verificarPeligro(vector<string> lado) {
    bool hayLobo = find(lado.begin(), lado.end(), "Lobo") != lado.end();
    bool hayCaperucita = find(lado.begin(), lado.end(), "Caperucita") != lado.end();
    bool hayUvas = find(lado.begin(), lado.end(), "Uvas") != lado.end();

    if (hayLobo && hayCaperucita && lado.size() == 2) {
        cout << "¡PELIGRO! El lobo se queda con Caperucita.\n";
        return true;
    }

    if (hayUvas && hayCaperucita && lado.size() == 2) {
        cout << "¡PELIGRO! Caperucita podría comerse las uvas.\n";
        return true;
    }

    return false;
}

int main() {
    vector<string> ladoIzq = {"Caperucita", "Lobo", "Uvas"};
    vector<string> ladoDer;
    string bote;

    cout << "Inicio del cruce del río:\n";

    auto mover = [&](string pasajero, bool alDerecho) {
        if (alDerecho) {
            bote = pasajero;
            mostrarEstado(ladoIzq, ladoDer, bote);
            if (pasajero != "ninguno") {
                ladoIzq.erase(find(ladoIzq.begin(), ladoIzq.end(), pasajero));
                ladoDer.push_back(pasajero);
            }
            bote = "ninguno";
            if (verificarPeligro(ladoIzq)) exit(1);
        } else {
            bote = pasajero;
            mostrarEstado(ladoIzq, ladoDer, bote);
            if (pasajero != "ninguno") {
                ladoDer.erase(find(ladoDer.begin(), ladoDer.end(), pasajero));
                ladoIzq.push_back(pasajero);
            }
            bote = "ninguno";
            if (verificarPeligro(ladoDer)) exit(1);
        }
    };

    mover("Caperucita", true);     // 1. Lleva a Caperucita
    mover("ninguno", false);       // 2. Regresa solo
    mover("Lobo", true);           // 3. Lleva al Lobo
    mover("Caperucita", false);    // 4. Regresa con Caperucita
    mover("Uvas", true);           // 5. Lleva las Uvas
    mover("ninguno", false);       // 6. Regresa solo
    mover("Caperucita", true);     // 7. Lleva a Caperucita
        cout << "\n¡Todos cruzaron con seguridad! 🛶🐺👧🍇\n";
    return 0;
} 