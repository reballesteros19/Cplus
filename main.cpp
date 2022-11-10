#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <conio.h>
#include <Windows.h>
#include <sstream>

//#include <SDL2/SDL.h>
#define CP_UTF8 65001
using namespace std;

// Prototipos de funciones
map<string, string> cargarUsuarios();
void abirirVentana();
string leerPassword(string palabra);
string login(map<string, string> users);
string validarUsr(map<string, string> users, int i);
void pintarMenuRoot(map<string, string> users);
void pintarMenuUsuario(map<string, string> users, string usr);
bool validarEntrada(string cadena);
map<string, string> cambiarPassword(map<string, string> users, string usr);
map<string, string> cambiarPasswordUsuario(map<string, string> users);
map<string, string> crearUsuario(map<string, string> users);
map<string, string> borrarUsuario(map<string, string> users);

// Constantes
const int WIDTH = 800, HEIGHT = 600;
const char ca= 160, ce=130, ci=161, co=162, cu=163, caa=181, cee=144, cii=214, coo=224, cuu=23, cn=164, cnn=165;


int main( int argc, char *argv[] )
{
    map<string, string> users = cargarUsuarios();
    cout << "Aplicativo - Graficador - UTP" << endl;
    
    
    pintarMenuUsuario(users, "ricardo");
    return EXIT_SUCCESS;
    
    
    string usr;
    usr = login(users);
    if(usr != ""){
        cout << "Usario OK";
        if(usr == "root"){
            pintarMenuRoot(users);
        } else {
            pintarMenuUsuario(users, usr);
        }
    }else{
        cout << "Usario Not OK";
        system("pause");
    }
    
    //abirirVentana();
    return EXIT_SUCCESS;
}

void pintarMenuRoot(map<string, string> users){
    int option=10;
    string entrada;
    while (option != 0){
        system("cls");
        cout << "Aplicativo - Graficador - UTP" << endl;
        cout << "Men" <<cu<< " principal para usuario: root" << endl;
        cout << "0. Salir del aplicativo" << endl;
        cout << "1. Crear nuevo usuario" << endl;
        cout << "2. Borrar usuario" << endl;
        cout << "3. Listar accesos por usuario" << endl;
        cout << "4. Listar accesos todos los usuarios" << endl;
        cout << "5. Imprimir gr" << ca << "fico por referencia" << endl;
        cout << "6. Cambiar password del usuario root" << endl;
        cout << "7. Cambiar password de un usuario" << endl;
        cout << "Digite la opcion deseada: ";
        cin >> entrada;
        if(validarEntrada(entrada)){
            option = stoi(entrada);
        }
        switch(option) {
            case 0:
                cout << "Gracias por utilizar el aplicativo." << endl;
                system("pause");
                break;
            case 1:
                users = crearUsuario(users);
                break;
            case 2:
                users = borrarUsuario(users);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                users = cambiarPassword(users, "root");
                break;
            case 7:
                users = cambiarPasswordUsuario(users);
                break;
            default:
                cout << "Opcion no valida" << endl;
                system("pause");
        }
    }
}

void pintarMenuUsuario(map<string, string> users, string usr){
    int option=10;
    string entrada;
    while (option != 0){
        system("cls");
        cout << "Aplicativo - Graficador - UTP" << endl;
        cout << "Men" <<cu<< " principal para usuario: "<< usr << endl;
        cout << "0. Salir del aplicativo" << endl;
        cout << "1. Crear un nuevo gr" << ca << "fico" << endl;
        cout << "2. Borrar un gr" << ca << "fico existente" << endl;
        cout << "3. Listar accesos" << endl;
        cout << "4. Imprimir gr" << ca << "fico por referencia (Si es suyo)" << endl;
        cout << "5. Cambiar password del usuario " <<usr << endl;
        cout << "Digite la opcion deseada: ";
        cin >> entrada;
        if(validarEntrada(entrada)){
            option = stoi(entrada);
        }
        switch(option) {
            case 0:
                cout << usr << ": Gracias por utilizar el aplicativo." << endl;
                system("pause");
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                users = cambiarPassword(users, usr);
                break;
            default:
                cout << "Opcion no valida" << endl;
                system("pause");
        }
    }
}

// Opcion 1
map<string, string> crearUsuario(map<string, string> users){
    string usr, pwd;
    cout << "Username: ";
    cin >> usr;
    if(!users.count(usr)){
        pwd = leerPassword("Password: ");
        if(pwd.length() > 3){
            users[usr] = pwd;
            fstream fs;
            fs.open ("usuarios.txt", fstream::in | fstream::out | fstream::trunc);
            ofstream archivoUsuariosW ("usuarios.txt");
            for (pair<string, string> it : users) {
                archivoUsuariosW << it.first << " " << it.second << endl;
            }
            archivoUsuariosW.close();
            cout << "Usuario creado con exito." << endl << endl;
            users = cargarUsuarios();
            system("pause");
        } else {
            cout << "Password incorrecto." << endl;
            system("pause");
        }
    } else {
        cout << "Usuario ya existe." << endl;
        system("pause");
    }
    return users;
}

// Opcion 2
map<string, string> borrarUsuario(map<string, string> users){
    string usr, pwd;
    cout << "Username: ";
    cin >> usr;
    if(users.count(usr)){
        users.erase(usr);
        fstream fs;
        fs.open ("usuarios.txt", fstream::in | fstream::out | fstream::trunc);
        ofstream archivoUsuariosW ("usuarios.txt");
        for (pair<string, string> it : users) {
            archivoUsuariosW << it.first << " " << it.second << endl;
        }
        archivoUsuariosW.close();
        cout << "Usuario eliminado con exito." << endl << endl;
        users = cargarUsuarios();
        system("pause");
    } else {
        cout << "Usuario no existe." << endl;
        system("pause");
    }
    return users;
}

// Opcion 6
map<string, string> cambiarPassword(map<string, string> users, string usr){
    string pwd, newPwd1, newPwd2;
    pwd = leerPassword("Password root: ");
    if(users[usr] == pwd){
        newPwd1 = leerPassword("Ingrese el nuevo password: ");
        newPwd2 = leerPassword("Confirme el nuevo Password: ");
        if(newPwd1 == newPwd2 && newPwd1.length() > 3){
            users[usr] = newPwd1;
            fstream fs;
            fs.open ("usuarios.txt", fstream::in | fstream::out | fstream::trunc);
            ofstream archivoUsuariosW ("usuarios.txt");
            for (pair<string, string> it : users) {
                archivoUsuariosW << it.first << " " << it.second << endl;
            }
            archivoUsuariosW.close();
            cout << "password cambiada con exito." << endl << endl;
            users = cargarUsuarios();
            system("pause");
        } else {
            cout << "Password no coinciden o incorrectos." << endl;
            system("pause");
        }
    } else {
        cout << "Password incorrecto." << endl;
        system("pause");
    }
    return users;
}

// opcion 7
map<string, string> cambiarPasswordUsuario(map<string, string> users){
    string usr, newPwd1, newPwd2;
    cout << "Username: ";
    cin >> usr;
    if(users.count(usr)){
        newPwd1 = leerPassword("Ingrese el nuevo password: ");
        newPwd2 = leerPassword("Confirme el nuevo Password: ");
        if(newPwd1 == newPwd2 && newPwd1.length() > 3){
            users[usr] = newPwd1;
            fstream fs;
            fs.open ("usuarios.txt", fstream::in | fstream::out | fstream::trunc);
            ofstream archivoUsuariosW ("usuarios.txt");
            for (pair<string, string> it : users) {
                archivoUsuariosW << it.first << " " << it.second << endl;
            }
            archivoUsuariosW.close();
            cout << "password cambiada con exito." << endl << endl;
            users = cargarUsuarios();
            system("pause");
        } else {
            cout << "Password no coinciden o incorrectos." << endl;
            system("pause");
        }
    } else {
        cout << "Usuario no existe." << endl;
        system("pause");
    }
    return users;
}

bool validarEntrada(string cadena){
  if(cadena.length() > 1){
    return false;
  }
  if(cadena == "0" || cadena == "1" || cadena == "2" || cadena == "3" 
        || cadena == "4" || cadena == "5" || cadena == "6" || cadena == "7"){
    return true;
  }
  return false;
}

string login(map<string, string> users){
    string usr, pwd;

    cout << "Username: ";
    cin >> usr;
    if(users.empty()) {
        if(usr == "root"){
            pwd = leerPassword("Password: ");
            if(pwd.length() < 4){
                cout << "El password debe contener minimo 4 caracteres";
            }else {
                ofstream archivoUsuariosW ("usuarios.txt");
                archivoUsuariosW << usr << " " << pwd;
                archivoUsuariosW.close();
                cout << "password de root registrada con exito.";
            }
        }else{
            cout << "Usuario incorrecto." << endl << endl;
        }
        return "";
    }else{
        if(users.count(usr)){
            pwd = leerPassword("Password: ");
            if(users[usr] == pwd){
                return usr;
            }
        }
        return validarUsr(users, 1);
    }
}

string validarUsr(map<string, string> users, int i){
    system("cls");
    cout << "i: " << i << endl;
    cout << "Aplicativo - Graficador - UTP" << endl;
    string usr, pwd;
    cout << "Username: ";
    cin >> usr;

    if(users.count(usr)){
        pwd = leerPassword("Password: ");
        if(users[usr] == pwd){
            return usr;
        }
    }
    i++;
    if(i > 2){
        return "";
    } else {
        return validarUsr(users, i);
    }
}

string leerPassword(string palabra){
    string pwd;
    cout << palabra;
    int c = 0;
    while(VK_RETURN != (c = _getch()) ){
        cout << '*';
        pwd += static_cast<char>(c);
    }
    cout << endl;
    return pwd;
}

map<string, string> cargarUsuarios(){
    map<string, string> users;
    ifstream archivoUsuarios ("usuarios.txt");
    string usr, pwd;
    if ( archivoUsuarios.is_open() ) {
        while ( archivoUsuarios.good() ) {
            archivoUsuarios >> usr;
            archivoUsuarios >> pwd;
            if( usr.length() != 0 && pwd.length() != 0 ) {
                users[usr] = pwd;
            }
        }
    }
    archivoUsuarios.close();

    /*
    if(users.empty()){
        cout << "Mapa Vacio" << endl;
    }

    for (pair<string, string> it : users) {
        cout << it.first << " - " << it.second << endl;
    }
    */
    return users;
}

void abirirVentana(){
    cout << "*** En Contruccion ***" << endl;
    /*SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window = SDL_CreateWindow(
        "Hello SDL WORLD", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_ALLOW_HIGHDPI);

    if ( NULL == window )
    {
        cout << "Could not create window: " << SDL_GetError( ) << endl;
        return 1;
    }

    SDL_Event windowEvent;

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            { break; }
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit( );*/
}