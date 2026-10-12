#ifndef FECHA_H
#define FECHA_H

#include <iostream>
using namespace std;

// Clase Fecha: guarda dia, mes, año, hora y minuto.
// La usan Usuario, Foto, Mensaje y Solicitud.
class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

public:
    // Constructores
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(int d, int m, int a, int h, int min);
    Fecha(const Fecha& otra);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

    // Setters
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
    void setHora(int h);
    void setMinuto(int min);

    // Operadores
    bool operator<(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    Fecha& operator=(const Fecha& otra);

    // Funcion amiga para imprimir con cout
    friend ostream& operator<<(ostream& salida, const Fecha& f);
};

#endif

