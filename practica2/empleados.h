#pragma once
#include <iostream>
#include <string>

using namespace std;

///////////////////////////// CLASES BASE Y DERIVADAS ////////////////////////////////////////

class Persona {
protected:
    int edad;
    string Nombre;
};

class Empleado : public Persona {
protected:
    string cargo;
    int sueldo;
    int Fecha[3]; // 0: Dia, 1: Mes, 2: Año
    int nivelCargo; 

public:
    Empleado();
    virtual ~Empleado() {} // Destructor virtual: Soluciona la fuga de memoria
    
    void setDatosBasicos(string name, int age, string cargoAsignado, int f[3]);
    virtual void calcularSueldo() = 0; 
    virtual string getTipoEmpleado() = 0; // Para identificar al guardar en archivo

    void mostrarEmpleado();
    int getSueldo();
    string getNombre();
    int getNivelCargo();
    int getValorFecha(); 

    // Getters auxiliares para exportar datos al .txt
    int getEdad() { return edad; }
    string getCargo() { return cargo; }
    int getDia() { return Fecha[0]; }
    int getMes() { return Fecha[1]; }
    int getAnio() { return Fecha[2]; }
};

class EmpleadoPlanta : public Empleado {
public:
    void calcularSueldo() override;
    string getTipoEmpleado() override { return "PLANTA"; }
};

class EmpleadoPorHora : public Empleado {
private:
    int horasTrabajadas;
public:
    void setHoras(int horas);
    int getHoras() { return horasTrabajadas; }
    void calcularSueldo() override;
    string getTipoEmpleado() override { return "HORA"; }
};

///////////////////////////// CLASE GESTORA DE PERSISTENCIA //////////////////////////////////

class GestorNomina {
private:
    Empleado* nomina[20];
    int contador;
    const string nombreArchivo = "nomina.txt";

public:
    GestorNomina();
    ~GestorNomina();
    
    bool agregarEmpleado(Empleado* nuevoEmp);
    void mostrarReporte();
    void guardarDatos();
    void cargarDatos();
    void liberarMemoria();
};

///////////////////////////// PROTOTIPOS AUXILIARES /////////////////////////////////////

int solicitarEdadValida();
void Validador_de_fecha(int ingreso[]);
string elegirCargo();