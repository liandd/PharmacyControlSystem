// Laboratorio.h
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <algorithm>
#ifndef LABORATORIO_H
#define LABORATORIO_H

using namespace std;

const int tamanoLaboratorio = 11;

struct Laboratorio
{
    string codigoLaboratorio = "";
    string nombreLaboratorio = "";
    string telefonoLaboratorio = "";
    string direccionLaboratorio = "";
    string emailLaboratorio = "";
};

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotos(int a, int b)
{
    COORD c;
    c.X = a;
    c.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int validarGuardado(vector<Laboratorio> &site, int tamanoLaboratorio)
{
    for (int i = 0; i < tamanoLaboratorio; i++)
    {
        if (site[i].codigoLaboratorio.empty() && site[i].nombreLaboratorio.empty() && site[i].telefonoLaboratorio.empty() && site[i].direccionLaboratorio.empty() && site[i].emailLaboratorio.empty())
        {
            return i;
        }
    }
    return 11;
}

bool validarLaboratorio(vector<Laboratorio> &site, int tamanoLaboratorio, string codigoLaboratorio)
{
    for (int i = 0; i < tamanoLaboratorio; i++)
    {
        if (site[i].codigoLaboratorio == codigoLaboratorio)
        {
            return true;
        }
    }
    return false;
}

void verLaboratorios(vector<Laboratorio> &site, int tamanoLaboratorio)
{
    system("cls");
    cout << "LABORATORIOS GUARDADOS\n";
    for (int i = 0; i < tamanoLaboratorio; i++)
    {
        string codigoLaboratorio = "";
        codigoLaboratorio = site[i].codigoLaboratorio;
        if (!codigoLaboratorio.empty())
        {
            cout << "\nLABORATORIO #" << i + 1 << "\n";
            cout << "CODIGO    LABORATORIO-->" << site[i].codigoLaboratorio << "\n";
            cout << "NOMBRE    LABORATORIO-->" << site[i].nombreLaboratorio << "\n";
            cout << "TELEFONO  LABORATORIO-->" << site[i].telefonoLaboratorio << "\n";
            cout << "DIRECCION LABORATORIO-->" << site[i].direccionLaboratorio << "\n";
            cout << "EMAIL     LABORATORIO-->" << site[i].emailLaboratorio << "\n";
        }
        else
        {
            cout << "\nINGRESE MAS LABORATORIOS. (# DE ESPACIOS DISPONIBLES:" << tamanoLaboratorio - i << ")\n";
            system("pause");
            break;
        }
    }
}

void crearLaboratorio(vector<Laboratorio> &site, int tamanoLaboratorio)
{
    system("cls");
    cout << "COMPLETE EL FORMULARIO PARA REGISTRAR UN LABORATORIO\n";
    int dato = validarGuardado(site, tamanoLaboratorio);
    string nombre = "";
    if (dato >= 0 && dato < tamanoLaboratorio)
    {
        cout << "INGRESE EL NOMBRE DEL LABORATORIO-->";
        while (true)
        {
            getline(cin, nombre);
            transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
            bool nombreValido = true;

            if (nombre.empty())
            {
                system("cls");
                cout << "EL NOMBRE NO PUEDE ESTAR VACIO\n";
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
                nombre = "";
            }
            else
            {
                cout << "NOMBRE INGRESADO CORRECTAMENTE\n";
                break;
            }
        }

        bool codigoValido = false;
        string codigo = "";
        cout << "INGRESE EL CODIGO DEL LABORATORIO-->";
        do
        {
            cin >> codigo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool digitosValidos = true;
            for (char c : codigo)
            {
                if (!isdigit(c))
                {
                    system("cls");
                    digitosValidos = false;
                    cout << "EL CODIGO DEBE CONTENER SOLO NUMEROS\n";
                    break;
                }
                else if (codigo.length() != 4)
                {
                    system("cls");
                    digitosValidos = false;
                    cout << "EL CODIGO DEBE CONTENER 4 DIGITOS\n";
                    break;
                }
            }
            if (digitosValidos && codigo.length() == 4)
            {
                cout << "CODIGO INGRESADO CORRECTAMENTE\n";
                codigoValido = true;
                break;
            }
        } while (!codigoValido);

        if (!validarLaboratorio(site, tamanoLaboratorio, codigo))
        {
            site[dato].codigoLaboratorio = codigo;
            site[dato].nombreLaboratorio = nombre;

            bool telefonoValido = false;
            string telefono = "";
            cout << "INGRESE EL TELEFONO DEL LABORATORIO-->";
            do
            {
                cin >> telefono;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bool digitosValidos = true;

                for (char c : telefono)
                {
                    if (!isdigit(c))
                    {
                        system("cls");
                        digitosValidos = false;
                        cout << "EL TELEFONO DEBE CONTENER SOLO DIGITOS\n";
                        continue;
                    }
                }
                if (digitosValidos && telefono.length() == 10)
                {
                    cout << "TELEFONO INGRESADO CORRECTAMENTE\n";
                    site[dato].telefonoLaboratorio = telefono;
                    telefonoValido = true;
                }
                else
                {
                    if (!digitosValidos)
                    {
                        system("cls");
                        cout << "EL TELEFONO DEBE CONTENER SOLO DIGITOS\n";
                    }
                    else
                    {
                        system("cls");
                        cout << "EL TELEFONO DEBE CONTENER 10 DIGITOS\n";
                    }
                }

            } while (!telefonoValido);

            bool direccionValida = false;
            cout << "INGRESE LA DIRECCION DEL LABORATORIO-->";
            do
            {
                getline(cin, site[dato].direccionLaboratorio);

                if (site[dato].direccionLaboratorio.empty())
                {
                    system("cls");
                    cout << "LA DIRECCION NO PUEDE ESTAR VACIA\n";
                    continue;
                }
                else
                {
                    cout << "DIRECCION INGRESADA CORRECTAMENTE\n";
                    direccionValida = true;
                    break;
                }
            } while (!direccionValida);

            cout << "INGRESE EL EMAIL DEL LABORATORIO-->";
            string email = "";
            bool emailValido = false;

            do
            {
                cin >> email;
                size_t posArroba = email.find('@');
                if (email.find('@') == string::npos)
                {
                    system("cls");
                    cout << "EL CORREO ELECTRONICO DEBE CONTENER UN @\n";
                    continue;
                }
                if (posArroba != string::npos)
                {
                    string dominio = email.substr(posArroba + 1);

                    if (!dominio.empty() && (dominio == "gmail.com" || dominio == "hotmail.com" || dominio == "yahoo.com" || dominio == "email.com" || dominio == "outlook.com"))
                    {
                        site[dato].emailLaboratorio = email;
                        cout << "CORREO ELECTRONICO INGRESADO CORRECTAMENTE\n";
                        emailValido = true;
                    }
                    else
                    {
                        system("cls");
                        cout << "INGRESE UN CORREO VALIDO\n";
                        cin.clear();                                                   // Limpiar el estado de error
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora entrada adicional en el buffer
                    }
                }
            } while (!emailValido);
        }
        else
        {
            for (int i = 0; i < tamanoLaboratorio; i++)
            {
                if (site[i].codigoLaboratorio == codigo)
                {
                    cout << "EL LABORATORIO-> " << site[i].nombreLaboratorio << " CON CODIGO-> " << site[i].codigoLaboratorio << " YA ESTA REGISTRADO\n";
                    cin.ignore();
                    system("pause");
                    return;
                }
            }
        }
        cout << "SE HA REGISTRADO EL LABORATORIO\n";
        system("pause");
    }
}

void eliminarLaboratorio(vector<Laboratorio> &site, int tamanoLaboratorio)
{
    system("cls");
    cout << "COMPLETE EL FORMULARIO PARA ELIMINAR UN LABORATORIO\n";
    string codigo = "";
    cout << "INGRESE EL CODIGO DEL LABORATORIO-->";
    cin >> codigo;

    bool laboratorioEncontrado = false;

    for (int i = 0; i < tamanoLaboratorio; i++)
    {
        if (codigo == site[i].codigoLaboratorio)
        {
            site.erase(site.begin() + i);
            cout << "EL LABORATORIO HA SIDO ELIMINADO.\n";
            laboratorioEncontrado = true;
            break;
        }
    }
    if (!laboratorioEncontrado)
    {
        cout << "EL CODIGO INGRESADO NO HA SIDO ENCONTRADO.\n";
    }
    system("pause");
}
vector<Laboratorio> site(tamanoLaboratorio);

void mostrarOpcionesLaboratorio(int Set[], int numOpciones)
{
    gotos(0, 0);
    color(15);
    cout << "--MENU DE LABORATORIOS (CRUD)\n\n";
    for (int i = 0; i < numOpciones; ++i)
    {
        color(Set[i]);
        switch (i + 1)
        {
        case 1:
            cout << "1. CREAR LABORATORIO\n";
            break;
        case 2:
            cout << "2. VER LABORATORIOS\n";
            break;
        case 3:
            cout << "3. ACTUALIZAR LABORATORIOS\n";
            break;
        case 4:
            cout << "4. ELIMINAR LABORATORIOS\n";
            break;
        case 5:
            cout << "5. SALIR\n";
            break;
        }
    }
    color(7);
}
void crudLaboratorios()
{
    bool flag = true;
    do
    {
        int Set[] = {15, 15, 15, 15, 15};
        int counter = 0;
        char llave;

        do
        {
            mostrarOpcionesLaboratorio(Set, 5);

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
            crearLaboratorio(site, tamanoLaboratorio);
            flag = false;
            system("cls");
            break;
        }
        case 2:
        {
            verLaboratorios(site, tamanoLaboratorio);
            flag = false;
            system("cls");
            break;
        }
        case 3:
        {
            // actualizarLaboratorio();
            flag = false;
            system("cls");
            break;
        }
        case 4:
        {
            eliminarLaboratorio(site, tamanoLaboratorio);
            flag = false;
            system("cls");
            break;
        }
        case 5:
        {
            system("cls");
            color(15);
            cout << "SALIENDO DEL CRUD LABORATORIO...\n";
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

void limpiarLaboratorio()
{
    for (int i = 0; i < tamanoLaboratorio; i++)
    {
        site[i].codigoLaboratorio = "";
        site[i].nombreLaboratorio = "";
        site[i].telefonoLaboratorio = "";
        site[i].direccionLaboratorio = "";
        site[i].emailLaboratorio = "";
    }
}

void actualizarLaboratorio()
{
}

#endif // LABORATORIO_H
