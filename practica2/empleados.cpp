#include "empleados.h"
#include <fstream>
#include <sstream>

///////////////////////////// IMPLEMENTACIÓN DE EMPLEADOS ////////////////////////////////////////

Empleado::Empleado() { sueldo = 0; nivelCargo = 0; }

void Empleado::setDatosBasicos(string name, int age, string cargoAsignado, int f[3]) {
    Nombre = name;
    edad = age;
    cargo = cargoAsignado;
    Fecha[0] = f[0]; Fecha[1] = f[1]; Fecha[2] = f[2];

    if (cargo == "gerente") nivelCargo = 3;
    else if (cargo == "supervisor") nivelCargo = 2;
    else if (cargo == "operario") nivelCargo = 1;
    else nivelCargo = 0;
}

void Empleado::mostrarEmpleado() {
    cout << "Nombre: " << Nombre << " | Cargo: " << cargo 
         << " | Sueldo: S/" << sueldo 
         << " | Ingreso: " << Fecha[0] << "/" << Fecha[1] << "/" << Fecha[2] << endl;
}

int Empleado::getSueldo() { return sueldo; }
string Empleado::getNombre() { return Nombre; }
int Empleado::getNivelCargo() { return nivelCargo; }
int Empleado::getValorFecha() { return (Fecha[2] * 10000) + (Fecha[1] * 100) + Fecha[0]; } 

void EmpleadoPlanta::calcularSueldo() {
    int tarifa = 0;
    if (cargo == "operario") tarifa = 50;
    else if (cargo == "supervisor") tarifa = 80;
    else if (cargo == "gerente") tarifa = 100;
    sueldo = tarifa * 40; 
}

void EmpleadoPorHora::setHoras(int horas) { horasTrabajadas = horas; }

void EmpleadoPorHora::calcularSueldo() {
    int tarifa = 0;
    if (cargo == "operario") tarifa = 50;
    else if (cargo == "supervisor") tarifa = 80;
    else if (cargo == "gerente") tarifa = 100;
    sueldo = tarifa * horasTrabajadas; 
}

///////////////////////////// IMPLEMENTACIÓN GESTOR NOMINA ////////////////////////////////////////

GestorNomina::GestorNomina() {
    contador = 0;
    for (int i = 0; i < 20; i++) nomina[i] = nullptr;
}

GestorNomina::~GestorNomina() {
    liberarMemoria();
}

void GestorNomina::liberarMemoria() {
    for (int i = 0; i < contador; i++) {
        delete nomina[i];
        nomina[i] = nullptr;
    }
    contador = 0;
}

bool GestorNomina::agregarEmpleado(Empleado* nuevoEmp) {
    if (contador < 20) {
        nomina[contador] = nuevoEmp;
        contador++;
        return true;
    }
    cout << "[ERROR] La nomina esta llena (Max 20 empleados).\n";
    return false;
}

void GestorNomina::guardarDatos() {
    ofstream archivo(nombreArchivo, ios::out | ios::trunc);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo " << nombreArchivo << ".\n";
        return;
    }
    
    for (int i = 0; i < contador; i++) {
        archivo << nomina[i]->getTipoEmpleado() << "|"
                << nomina[i]->getNombre() << "|"
                << nomina[i]->getEdad() << "|"
                << nomina[i]->getCargo() << "|"
                << nomina[i]->getDia() << "|"
                << nomina[i]->getMes() << "|"
                << nomina[i]->getAnio() << "|";
        
        if (nomina[i]->getTipoEmpleado() == "HORA") {
            EmpleadoPorHora* h = static_cast<EmpleadoPorHora*>(nomina[i]);
            archivo << h->getHoras();
        } else {
            archivo << "0";
        }
        archivo << "\n";
    }
    archivo.close();
    cout << "[SISTEMA] Se guardaron " << contador << " registros en '" << nombreArchivo << "'.\n";
}

void GestorNomina::cargarDatos() {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[SISTEMA] No hay archivo previo. Iniciando base de datos vacia.\n";
        return;
    }

    liberarMemoria(); // Limpiamos antes de cargar
    string linea;
    
    while (getline(archivo, linea) && contador < 20) {
        stringstream ss(linea);
        string tipo, nombre, edadStr, cargo, diaStr, mesStr, anioStr, horasStr;

        getline(ss, tipo, '|');
        getline(ss, nombre, '|');
        getline(ss, edadStr, '|');
        getline(ss, cargo, '|');
        getline(ss, diaStr, '|');
        getline(ss, mesStr, '|');
        getline(ss, anioStr, '|');
        getline(ss, horasStr, '|');

        int f[3] = { stoi(diaStr), stoi(mesStr), stoi(anioStr) };
        
        if (tipo == "PLANTA") {
            EmpleadoPlanta* emp = new EmpleadoPlanta();
            emp->setDatosBasicos(nombre, stoi(edadStr), cargo, f);
            emp->calcularSueldo();
            agregarEmpleado(emp);
        } 
        else if (tipo == "HORA") {
            EmpleadoPorHora* emp = new EmpleadoPorHora();
            emp->setDatosBasicos(nombre, stoi(edadStr), cargo, f);
            emp->setHoras(stoi(horasStr));
            emp->calcularSueldo();
            agregarEmpleado(emp);
        }
    }
    archivo.close();
    cout << "[SISTEMA] Se cargaron " << contador << " empleados desde el archivo.\n";
}

void GestorNomina::mostrarReporte() {
    if (contador == 0) {
        cout << "\n[SISTEMA] La nomina esta vacia actualmente.\n";
        return;
    }

    // Ordenamiento temporal por Cargo (Gerente > Supervisor > Operario)
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - 1 - i; j++) {
            if (nomina[j]->getNivelCargo() < nomina[j + 1]->getNivelCargo()) {
                Empleado* temp = nomina[j];
                nomina[j] = nomina[j + 1];
                nomina[j + 1] = temp;
            }
        }
    }

    // Busqueda de Maximos
    Empleado* maxSalarioEmp = nomina[0];
    Empleado* veteranoEmp = nomina[0];
    for (int i = 1; i < contador; i++) {
        if (nomina[i]->getSueldo() > maxSalarioEmp->getSueldo()) maxSalarioEmp = nomina[i];
        if (nomina[i]->getValorFecha() < veteranoEmp->getValorFecha()) veteranoEmp = nomina[i];
    }

    cout << "\n============================================\n";
    cout << "LISTA DE EMPLEADOS (" << contador << " en total):\n";
    for (int i = 0; i < contador; i++) nomina[i]->mostrarEmpleado();
    
    cout << "\n--------------------------------------------\n";
    cout << "RESUMEN DESTACADO:\n";
    cout << "EMPLEADO CON MAYOR SALARIO:\n";
    maxSalarioEmp->mostrarEmpleado();
    cout << "\nEMPLEADO MAS ANTIGUO:\n";
    veteranoEmp->mostrarEmpleado();
    cout << "============================================\n";
}

///////////////////////////// FUNCIONES AUXILIARES /////////////////////////////////////

int solicitarEdadValida() {
    int age_temp;
    bool edadValida = false;
    while (!edadValida) {
        cout << "Edad: "; 
        cin >> age_temp;

        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n'); 
            cout << "[ERROR] Entrada no valida. Ingrese valores numericos.\n";
        } else if (cin.peek() != '\n') { 
            cin.clear(); cin.ignore(10000, '\n');
            cout << "[ERROR] No se permiten decimales ni texto extra.\n";
        } else if (age_temp < 18 || age_temp > 80) {
            cout << "[ERROR] Edad invalida. Digite una edad real (18-80).\n";
        } else { edadValida = true; }
    }
    return age_temp;
}

void Validador_de_fecha(int ingreso[]) {
    bool fechaValida = false;
    while (!fechaValida) {
        cout << "Dia: "; cin >> ingreso[0];
        cout << "Mes: "; cin >> ingreso[1];
        cout << "Anio: "; cin >> ingreso[2];
        
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "\n[ERROR] Formato incorrecto. Solo numeros enteros.\n\n"; continue;
        }
        if (ingreso[2] < 1960 || ingreso[2] > 2026) {
            cout << "\n[ERROR] Anio invalido (1960 - 2026).\n\n"; continue;
        }
        if (ingreso[1] < 1 || ingreso[1] > 12) {
            cout << "\n[ERROR] Mes invalido (1 - 12).\n\n"; continue;
        }
        
        int diasMaximos = 31;
        if (ingreso[1] == 4 || ingreso[1] == 6 || ingreso[1] == 9 || ingreso[1] == 11) diasMaximos = 30;
        else if (ingreso[1] == 2) diasMaximos = ((ingreso[2] % 4 == 0 && ingreso[2] % 100 != 0) || (ingreso[2] % 400 == 0)) ? 29 : 28;
        
        if (ingreso[0] < 1 || ingreso[0] > diasMaximos) {
            cout << "\n[ERROR] Dia invalido para ese mes.\n\n"; continue;
        }
        fechaValida = true;
    }
}

string elegirCargo() {
    int alternativa;
    string cargoSeleccionado;
    while (true) {
        cout << "Cargo (1: Operario, 2: Supervisor, 3: Gerente): ";
        cin >> alternativa;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); cin.ignore(10000, '\n'); cout << "[ERROR] Debe ingresar un numero entero.\n"; continue;
        }
        if (alternativa == 1) return "operario";
        if (alternativa == 2) return "supervisor";
        if (alternativa == 3) return "gerente";
        cout << "[ERROR] Opcion inexistente.\n";
    }
}