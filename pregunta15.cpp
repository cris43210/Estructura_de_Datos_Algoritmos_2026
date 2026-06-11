#include <iostream>
#include <string>
#include <limits> // para poder usar numeric_limits y limpiar la memoria

using namespace std;

int main() {
    //  variables por defecto para la boleta
    int pagoPorHora = 120;
    string nombreTrabajador = "Cristian Rivera Panduro";
    string fecha_hora = "28 de mayo del 2026 a \nlas 8:30PM"; // salto de linea para cuadrar el margen

    // variables de control
    int horasSemanales = 0;
    int salarioBase = 0;
    bool horasIngresadas = false; // bandera para saber si ya pasó por la opcion 1
    int opcion = 0;
    string continuar = "";

    int max_items = 3; // limite de los arreglos estaticos 

    // arreglos para guardar los conceptos y los montos
    string conceptos_desc[3];
    float montos_desc[3];
    int contador_desc = 0;

    string conceptos_ben[3];
    float montos_ben[3];
    int contador_ben = 0;

    do {
        cout << "   SISTEMA DE NOMINA - " << nombreTrabajador << "\n";
        cout << "1. Ingresar horas trabajadas por semana\n";
        cout << "2. Mostrar Salario base mensual\n";
        cout << "3. Ingresar descuento(s)\n";
        cout << "4. Ingresar beneficio(s)\n";
        cout << "5. Imprimir boleta\n";
        cout << "6. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        // evita errores por si se ingresa letras o simbolos en vez del numero del menu
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nError: Entrada invalida. Debes ingresar un numero.\n\n";
            opcion = 0; 
            continue; // regresa al inicio del menu
        }

        switch(opcion) {
            case 1:
                cout << "\nIngresa las horas trabajadas por semana: ";
                cin >> horasSemanales;

                // evita errores al ingresar letras u otros deifeentes aenteros
                if (cin.fail() || horasSemanales < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Cantidad de horas invalida.\n\n";
                    break;
                }

                salarioBase = horasSemanales * 4 * pagoPorHora;
                horasIngresadas = true; // Estado de ya pagó

                cout << "Horas guardadas correctamente.\n\n";
                break;

            case 2:
                // si no han metido horas, no muestra nada para evitar que salga 0
                if (horasIngresadas == false) {
                    cout << "\nError: Faltan datos, porfavor ingresa primero las horas (Opcion 1).\n\n";
                } else {
                    cout << "\nSalario base mensual acumulado: " << salarioBase << " $\n\n"; 
                }
                break;

            case 3:
                continuar = "s";
                // mientras se ponga "s", ingresa mas descuentos
                while (continuar == "s" || continuar == "S") {
                    if (contador_desc >= max_items) {
                        cout << "\nAlerta: El arreglo de descuentos esta lleno.\n\n";
                        break; // salir si ya completó los descuentos
                    }

                    cout << "\nIngresa el concepto del descuento (por ej. AFP, Seguro): ";
                    getline(cin >> ws, conceptos_desc[contador_desc]); // para que salte el getline

                    cout << "Ingresa el monto del descuento: ";
                    cin >> montos_desc[contador_desc];

                    // validacion del monto igual que con las horas
                    if (cin.fail() || montos_desc[contador_desc] < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Error: Monto invalido. No se registro el descuento.\n";
                    } else {
                        contador_desc = contador_desc + 1; 
                    }

                    cout << "Deseas ingresar otro descuento? (s/n): ";
                    cin >> continuar;
                }
                break;

            case 4:
                continuar = "s";
                // misma logica de la opcion 3, pero para sumar beneficios
                while (continuar == "s" || continuar == "S") {
                    if (contador_ben >= max_items) {
                        cout << "\nAlerta: El arreglo de beneficios esta lleno.\n\n";
                        break; 
                    }

                    cout << "\nIngresa el concepto del beneficio (por ej. Manutencion, Bono): ";
                    getline(cin >> ws, conceptos_ben[contador_ben]);

                    cout << "Ingresa el monto del beneficio: ";
                    cin >> montos_ben[contador_ben];

                    // para evitar que se ingresa texto o bonos negativos
                    if (cin.fail() || montos_ben[contador_ben] < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Error: Monto invalido. No se registro el beneficio.\n";
                    } else {
                        contador_ben = contador_ben + 1;
                    }

                    cout << "Deseas ingresar otro beneficio? (s/n): ";
                    cin >> continuar;
                }
                break;

            case 5:
                // para asegurar de que haya datos basicos antes de imprimir todo
                if (horasIngresadas == false) {
                    cout << "\nError: Faltan datos base, ingresa las horas primero.\n\n";
                } else {
                    cout << "\n========================================\n";
                    cout << "            BOLETA DE PAGO\n";
                    cout << "========================================\n";
                    cout << "Trabajador: " << nombreTrabajador << "\n";
                    cout << "Fecha de emision: " << fecha_hora << "\n";
                    cout << "----------------------------------------\n";
                    cout << "Salario Base: " << salarioBase << " $\n";
                    cout << "----------------------------------------\n";

                    float total_descuentos = 0.0;
                    cout << "Descuentos aplicados:\n";
                    if (contador_desc > 0) {
                        for (int i = 0; i < contador_desc; i = i + 1) {
                            cout << " - " << conceptos_desc[i] << ": " << montos_desc[i] << " $\n";
                            total_descuentos = total_descuentos + montos_desc[i];
                        }
                    } else {
                        cout << " - Ninguno\n";
                    }

                    float total_beneficios = 0.0;
                    cout << "\nBeneficios aplicados:\n";
                    if (contador_ben > 0) {
                        for (int i = 0; i < contador_ben; i = i + 1) {
                            cout << " - " << conceptos_ben[i] << ": " << montos_ben[i] << " $\n";
                            total_beneficios = total_beneficios + montos_ben[i];
                        }
                    } else {
                        cout << " - Ninguno\n";
                    }
                    cout << "----------------------------------------\n";
                    
                    float sueldoNeto = salarioBase - total_descuentos + total_beneficios;
                    cout << "SUELDO NETO FINAL: " << sueldoNeto << " $\n";
                    cout << "========================================\n\n";
                }
                break;
                
            case 6:
                cout << "\nCerrando el programa. Hasta luego!\n";
                break;

            default:
               
                cout << "\nOpcion incorrecta. Por favor elige un numero del 1 al 6.\n\n";
                break;
        }

    } while (opcion != 6); 

    return 0;
}