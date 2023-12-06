// Clientes.h
#include <iostream>
#ifndef CLIENTE_H
#define CLIENTE_H
#include "Laboratorio.h"
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>
#include <stdlib.h>

using namespace std;

const int tamanoCliente = 11;

struct Cliente
{
    string cedulaCliente = "";
    string nombreCliente = "";
    string direccionCliente = "";
    string celularCliente = "";
    string fechaNacimientoCliente = "";
    string emailCliente = "";
};

int validarGuardado(vector<Cliente> &client, int tamanoCliente)
{
    for (int i = 0; i < tamanoCliente; i++)
    {
        if (client[i].cedulaCliente.empty() && client[i].nombreCliente.empty() && client[i].direccionCliente.empty() && client[i].celularCliente.empty() && client[i].fechaNacimientoCliente.empty() && client[i].emailCliente.empty())
        {
            return i;
        }
    }
    return 11;
}

bool validarCliente(vector<Cliente> &client, int tamanoCliente, string cedulaCliente)
{
    for (int i = 0; i < tamanoCliente; i++)
    {
        if (client[i].cedulaCliente == cedulaCliente)
        {
            return true;
        }
    }
    return false;
}

void verClientes(vector<Cliente> &client, int tamanoCliente)
{
    system("cls");
    color(15);
    cout << "CLIENTES GUARDADOS\n\n";
    color(11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 11);
    cout << "+-----+-------------+------------------------------+----------------------+-------------+-------------------------+\n";
    cout << "|  No |   CEDULA    |     NOMBRE DEL CLIENTE       |      DIRECCION       |  # CELULAR  |  @ E-MAIL DEL CLIENTE   |\n";
    cout << "+-----+-------------+------------------------------+----------------------+-------------+-------------------------+\n";
    for (int i = 0; i < tamanoCliente; i++)
    {
        string cedulaCliente = "";
        cedulaCliente = client[i].cedulaCliente;
        if (!cedulaCliente.empty())
        {
            cout << "| " << setw(2) << i + 1 << "  | " << setw(6) << client[i].cedulaCliente
                 << "  | " << setw(27) << client[i].nombreCliente
                 << "  | " << setw(19) << client[i].direccionCliente
                 << "  | " << setw(8) << client[i].celularCliente
                 << "  | " << setw(22) << client[i].emailCliente
                 << "  |\n";
        }
        else
        {
            cout << "+-----+-------------+------------------------------+----------------------+-------------+-------------------------+\n";
            color(15);
            cout << "\nINGRESE MAS CLIENTES. (# DE ESPACIOS DISPONIBLES:" << tamanoCliente - i << ")\n";
            system("pause");
            break;
        }
    }
}

void crearCliente(vector<Cliente> &client, int tamanoCliente)
{
    system("cls");
    cout << "COMPLETE EL FORMULARIO PARA REGISTRAR UN CLIENTE\n";
    int dato = validarGuardado(client, tamanoCliente);
    string cedula = "";
    string nombre = "";

    if (dato >= 0 && dato < tamanoCliente)
    {
        // Validación del nombre
        cout << "INGRESE EL NOMBRE DEL CLIENTE\n";
        cout << "~ ";
        while (true)
        {
            getline(cin, nombre);
            transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
            bool nombreValido = true;

            if (nombre.empty())
            {
                system("cls");
                cout << "EL NOMBRE NO PUEDE ESTAR VACIO\n";
                cout << "~ ";
                nombreValido = false;
                continue;
            }
            for (int i = 0; i < nombre.size(); i++)
            {
                if (nombre[i] == 32)
                {
                    continue;
                }

                if (nombre[i] < 97 || nombre[i] > 122)
                {
                    nombreValido = false;
                    break;
                }
            }
            if (!nombreValido)
            {
                system("cls");
                cout << "NOMBRE NO VALIDADO, INGRESE SOLO LETRAS\n";
                cout << "~ ";
                nombre = "";
            }
            else
            {
                cout << "NOMBRE INGRESADO CORRECTAMENTE\n";
                break;
            }
        }

        bool cedulaValida = false;
        cout << "INGRESE LA CEDULA DEL CLIENTE\n";
        cout << "~ ";
        do
        {
            cin >> cedula;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool digitosValidos = true;
            for (char c : cedula) // Verifica si el número de celular contiene solo dígitos
            {
                if (!isdigit(c))
                {
                    system("cls");
                    digitosValidos = false;
                    cout << "LA CEDULA SOLO DEBE CONTENER DIGITOS\n";
                    cout << "~ ";
                    break;
                }

                else if (cedula.length() != 10)
                {
                    system("cls");
                    digitosValidos = false;
                    cout << "LA CEDULA DEBE CONTENER 10 DIGITOS\n";
                    cout << "~ ";
                    break;
                }
            }
            if (digitosValidos && cedula.length() == 10)
            {
                cout << "CEDULA INGRESADA CORRECTAMENTE\n";
                cedulaValida = true;
                break;
            }
        } while (!cedulaValida);

        if (!validarCliente(client, tamanoCliente, cedula))
        {
            client[dato].nombreCliente = nombre;
            client[dato].cedulaCliente = cedula;

            cout << "INGRESE EL EMAIL DEL CLIENTE\n";
            cout << "~ ";
            string email = "";
            bool emailValido = false;

            do
            {
                cin >> email;
                size_t posArroba = email.find('@');  // Busca la posición del '@' en el correo electrónico
                if (email.find('@') == string::npos) // Verifica si el correo electrónico no contiene el símbolo '@'
                {
                    system("cls");
                    cout << "EL CORREO ELECTRONICO DEBE CONTENER UN @\n";
                    cout << "~ ";
                    continue;
                }
                if (posArroba != string::npos) // Verifica si se encontró el símbolo '@' en el correo electrónico
                {
                    string dominio = email.substr(posArroba + 1); // Extrae el dominio del correo electrónico

                    if (!dominio.empty() && (dominio == "gmail.com" || dominio == "hotmail.com" || dominio == "yahoo.com" || dominio == "email.com" || dominio == "outlook.com"))
                    {
                        client[dato].emailCliente = email;
                        cout << "CORREO ELECTRONICO INGRESADO CORRECTAMENTE\n";
                        emailValido = true;
                    }
                    else
                    {
                        system("cls");
                        cout << "INGRESE UN CORREO VALIDO\n";
                        cout << "~ ";
                        cin.clear();                                                   // Limpiar el estado de error
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada adicional en el buffer
                    }
                }
            } while (!emailValido);

            bool direccionValida = false;
            cin.get();
            cout << "INGRESE LA DIRECCION DEL CLIENTE\n";
            cout << "~ ";
            do
            {
                // cin.ignore();
                getline(cin, client[dato].direccionCliente); // Permite espacios en la dirección

                if (client[dato].direccionCliente.empty())
                {
                    system("cls");
                    cout << "LA DIRECCION NO PUEDE ESTAR VACIA\n";
                    cout << "~ ";
                    continue;
                }
                else
                {
                    cout << "DIRECCION INGRESADA CORRECTAMENTE\n";
                    direccionValida = true;
                    break;
                }
            } while (!direccionValida);

            bool celularValido = false;
            string celular = "";
            cout << "INGRESE EL CELULAR DEL CLIENTE\n";
            cout << "~ ";
            do
            {
                cin >> celular;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bool digitosValidos = true;

                for (char c : celular) // Verifica si el número de celular contiene solo dígitos
                {
                    if (!isdigit(c))
                    {
                        system("cls");
                        digitosValidos = false;
                        cout << "EL CELULAR DEBE CONTENER SOLO DIGITOS\n";
                        cout << "~ ";
                        continue;
                    }
                }
                if (digitosValidos && celular.length() == 10)
                {
                    cout << "CELULAR INGRESADO CORRECTAMENTE\n";
                    client[dato].celularCliente = celular;
                    celularValido = true;
                }
                else
                {
                    if (!digitosValidos)
                    {
                        system("cls");
                        cout << "EL CELULAR DEBE CONTENER SOLO DIGITOS\n";
                        cout << "~ ";
                    }
                    else
                    {
                        system("cls");
                        cout << "EL CELULAR DEBE CONTENER 10 DIGITOS\n";
                        cout << "~ ";
                    }
                }

            } while (!celularValido);
        }
        else
        {
            for (int i = 0; i < tamanoCliente; i++)
            {
                if (client[i].cedulaCliente == cedula)
                {
                    cout << "EL CLIENTE-> " << client[i].nombreCliente << " CON CEDULA->" << client[i].cedulaCliente << " YA ESTA REGISTRADO\n";
                    cin.ignore();
                    system("pause");
                    return; // Salir de la función si la cédula ya está registrada
                }
            }
        }

        cout << "SE HA REGISTRADO EL CLIENTE\n";
        system("pause");
    }
}

void eliminarCliente(vector<Cliente> &client, int tamanoCliente)
{
    system("cls");
    cout << "COMPLETE EL FORMULARIO PARA ELIMINAR UN CLIENTE\n";
    string cedula = "";
    cout << "INGRESE LA CEDULA DEL CLIENTE-->";
    cin >> cedula;

    bool clienteEncontrado = false;

    for (int i = 0; i < tamanoCliente; i++)
    {
        if (cedula == client[i].cedulaCliente)
        {
            client.erase(client.begin() + i);
            cout << "EL CLIENTE HA SIDO ELIMINADO.\n";
            clienteEncontrado = true;
            break;
        }
    }
    if (!clienteEncontrado)
    {
        cout << "LA CEDULA INGRESADA NO HA SIDO ENCONTRADA.\n";
    }
    system("pause");
}

void actualizarCliente(vector<Cliente> &client, int tamanoCliente)
{
    system("cls");
    cout << "COMPLETE EL FORMULARIO PARA ACTUALIZAR UN CLIENTE\n";
    string cedula = "";
    cout << "INGRESE LA CEDULA DEL CLIENTE\n";
    cout << "~";
    cin >> cedula;
    bool clienteEncontrado = false;
    for (int i = 0; i < tamanoCliente; i++)
    {
        if (cedula == client[i].cedulaCliente)
        {
            clienteEncontrado = true;
            int opcion = 0;
            do
            {
                system("cls");
                cout << "ACTUALIZAR NOMBRE------>(1)\n";
                cout << "ACTUALIZAR DIRECCION--->(2)\n";
                cout << "ACTUALIZAR CELULAR----->(3)\n";
                cout << "ACTUALIZAR EMAIL------->(4)\n";
                cout << "ACTUALIZAR TODO-------->(5)\n";
                color(12);
                cout << "SALIR------------------>(6)\n";
                color(7);
                cout << "DIGITE UNA OPCION\n";
                cout << "~ ";
                cin >> opcion;

                switch (opcion)
                {
                case 1:
                {
                    system("cls");
                    break;
                }
                case 2:
                {
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    break;
                }
                case 4:
                {
                    system("cls");
                    break;
                }
                case 5:
                {
                    system("cls");
                    break;
                }
                }

            } while (opcion >= 1 && opcion <= 6);
        }
    }
}
vector<Cliente> client(tamanoCliente);

void mostrarOpcionesCliente(int Set[], int numOpciones)
{
    gotos(0, 0);
    color(15);
    cout << "--MENU DE CLIENTE (CRUD)\n\n";
    for (int i = 0; i < numOpciones; ++i)
    {
        color(Set[i]);
        switch (i + 1)
        {
        case 1:
            cout << "1. CREAR CLIENTE\n";
            break;
        case 2:
            cout << "2. VER CLIENTE\n";
            break;
        case 3:
            cout << "3. ACTUALIZAR CLIENTE\n";
            break;
        case 4:
            cout << "4. ELIMINAR CLIENTE\n";
            break;
        case 5:
            cout << "5. SALIR\n";
            break;
        }
    }
    color(7);
}

void crudCliente()
{
    bool flag = true;
    do
    {
        int Set[] = {15, 15, 15, 15, 15};
        int counter = 0;
        char llave;

        do
        {
            mostrarOpcionesCliente(Set, 5);

            llave = _getch();
            if (llave == 72 && counter > 1)
            {
                Set[counter - 1] = 15;
                counter--;
            }
            else if (llave == 80 && counter < 5)
            {
                Set[counter - 1] = 15;
                counter++;
            }
            else if (llave == '\r')
            {
                break;
            }
            Set[counter - 1] = 12;
        } while (true);
        gotos(0, 9);
        for (int i = 0; i < 20; ++i)
        {
            cout << "                                         "; // Espacios en blanco para borrar
        }
        switch (counter)
        {
        case 1:
        {
            crearCliente(client, tamanoCliente);
            flag = false;
            system("cls");
            break;
        }
        case 2:
        {
            verClientes(client, tamanoCliente);
            flag = false;
            system("cls");
            break;
        }
        case 3:
        {
            // actualizarCliente();
            flag = false;
            system("cls");
            break;
            ;
        }
        case 4:
        {
            eliminarCliente(client, tamanoCliente);
            flag = false;
            system("cls");
            break;
        }
        case 5:
        {
            system("cls");
            color(15);
            cout << "SALIENDO DEL CRUD CLIENTE...\n";
            flag = true;
            break;
        }
        default:
        {
            system("cls");
            color(15);
            cout << "NINGUNA OPCION FUE SELECCIONADA.\n";
            break;
        }
        }
    } while (!flag);
}

void limpiarCliente()
{
    for (int i = 0; i < tamanoCliente; i++)
    {
        client[i].cedulaCliente = "";
        client[i].nombreCliente = "";
        client[i].direccionCliente = "";
        client[i].celularCliente = "";
        client[i].fechaNacimientoCliente = "";
        client[i].emailCliente = "";
    }
}

#endif // CLIENTES_H
