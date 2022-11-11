#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <conio.h>
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include <ctime>

//#include <SDL2/SDL.h>
#define CP_UTF8 65001
using namespace std;

// Prototipos de funciones
map<string, string> cargarUsuarios();
string login(map<string, string> users);
string validarUsr(map<string, string> users, int i);
string leerPassword(string palabra);
void pintarMenuRoot(map<string, string> users);
map<string, string> crearUsuario(map<string, string> users);
map<string, string> borrarUsuario(map<string, string> users);
void listarAccesosPorUsuario(map<string, string> users);
void listarAccesosTodosUsuarios(map<string, string> users);
void imprimirGraficoRoot();
map<string, string> cambiarPassword(map<string, string> users, string usr);
map<string, string> cambiarPasswordUsuario(map<string, string> users);
void pintarMenuUsuario(map<string, string> users, string usr);
void crearGrafico(string usr);
void borrarGrafico();
void listarAccesos(string usr);
void imprimirGrafico(string usr);
void escribirArchivoGraficos(map<string, string> graficos);
map<string, string> ordenarGraficosFechaAsc(map<string, string> graficos);
map<string, string> ordenarGraficosFechaDes(map<string, string> graficos);
string getFecha();
string secuenciaGrafico(map<string, string> graficos);
bool validarEntrada(string cadena);
void abirirVentana();

// Constantes
const int WIDTH = 800, HEIGHT = 600;
const char ca= 160, ce=130, ci=161, co=162, cu=163, caa=181, cee=144, cii=214, coo=224, cuu=23, cn=164, cnn=165;


int main( int argc, char *argv[] )
{
    map<string, string> users = cargarUsuarios();
    cout << "Aplicativo - Graficador - UTP" << endl;
    string usr;
    usr = login(users);
    if(usr != ""){
        if(usr == "root"){
            pintarMenuRoot(users);
        } else {
            pintarMenuUsuario(users, usr);
        }
    }else{
        system("pause");
    }
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
                listarAccesosPorUsuario(users);
                break;
            case 4:
                listarAccesosTodosUsuarios(users);
                break;
            case 5:
                void imprimirGraficoRoot();
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

// Opcion 1
map<string, string> crearUsuario(map<string, string> users){
    string usr, pwd;
    cout << "Username: ";
    cin >> usr;
    if(!users.count(usr)){
        // TODO validar que el usuario no tenga espacios en blanco.
        pwd = leerPassword("Password: ");
        if(pwd.length() > 3){
            // TODO encriptar password.
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

// Opcion 3
void listarAccesosPorUsuario(map<string, string> users){
    string usr;
    system("cls");
    cout << "Aplicativo - Graficador - UTP" << endl;
    cout << "Listado de acceso por usuario" << endl;
    cout << "Entre el usuario: ";
    cin >> usr;
    if(users.count(usr)){
        string usuario, fecha, nroGrafico, polinomio, orden;
        map<string, string> graficos;
        ifstream archivoGrafico ("graficos.txt");
        if ( archivoGrafico.is_open() ) {
            while ( archivoGrafico.good() ) {
                archivoGrafico >> usuario;
                archivoGrafico >> fecha;
                archivoGrafico >> nroGrafico;
                archivoGrafico >> polinomio;
                if(usuario == usr){
                    graficos[nroGrafico] = fecha + " " + nroGrafico + " " + polinomio;
                }
            }
        }
        archivoGrafico.close();
        cout << "Usuario: " << usr << endl;
        cout << "Fecha Nro grafico Polinomio-F(x)" << endl;
        cout << "________________________________" << endl;
        if(graficos.empty()){
            cout << "No existen registros." << endl;
        }else{
            graficos = ordenarGraficosFechaAsc(graficos);
            for (pair<string, string> it : graficos) {
                cout << it.second << endl;
            }
        }
        cout << "--------------------------------" << endl;
        cout << graficos.size() << " Registros" << endl;
        cout << endl;
    } else {
        cout << "Usuario no existe." << endl;
    }
    system("pause"); 
}

// opcion 4
void listarAccesosTodosUsuarios(map<string, string> users){
    string usr;
    system("cls");
    cout << "Aplicativo - Graficador - UTP" << endl;
    cout << "Listado de accesos todos los usuario" << endl;

    for (pair<string, string> it : users) {
        usr = it.first;
        if(usr != "root"){
            string usuario, fecha, nroGrafico, polinomio, orden;
            map<string, string> graficos;
            ifstream archivoGrafico ("graficos.txt");
            if ( archivoGrafico.is_open() ) {
                while ( archivoGrafico.good() ) {
                    archivoGrafico >> usuario;
                    archivoGrafico >> fecha;
                    archivoGrafico >> nroGrafico;
                    archivoGrafico >> polinomio;
                    if(usuario == usr){
                        graficos[nroGrafico] = fecha + " " + nroGrafico + " " + polinomio;
                    }
                }
            }
            archivoGrafico.close();
            cout << "Usuario: " << usr << endl;
            cout << "Fecha Nro grafico Polinomio-F(x)" << endl;
            cout << "________________________________" << endl;
            if(graficos.empty()){
                cout << "No existen registros." << endl;
            }else{
                graficos = ordenarGraficosFechaAsc(graficos);
                for (pair<string, string> it : graficos) {
                    cout << it.second << endl;
                }
            }
            cout << "--------------------------------" << endl;
            cout << graficos.size() << " Registros" << endl;
            cout << endl;
        }
    }
    system("pause"); 
}

// Opcion 5
void imprimirGraficoRoot(){
    string usuario, fecha, nroGrafico, polinomio, referencia;
    map<string, string> graficos;
    ifstream archivoGrafico ("graficos.txt");
    if ( archivoGrafico.is_open() ) {
        while ( archivoGrafico.good() ) {
            archivoGrafico >> usuario;
            archivoGrafico >> fecha;
            archivoGrafico >> nroGrafico;
            archivoGrafico >> polinomio;
            graficos[nroGrafico] = polinomio;
        }
    }
    archivoGrafico.close();

    cout << "Escriba el numero de referencia del grafico a imprimir: ";
    cin >> referencia;

    if(graficos.count(referencia)){
        cout << "Polinomio: " << graficos[referencia] << endl << endl;
        system("pause");
        // TODO pintar grafico
    } else {
        cout << "No se encuntra el grafico." << endl;
        system("pause");
    }

}

// Opcion 6
map<string, string> cambiarPassword(map<string, string> users, string usr){
    string pwd, newPwd1, newPwd2;
    pwd = leerPassword("Password root: ");
    // TODO Encriptar password
    if(users[usr] == pwd){
        newPwd1 = leerPassword("Ingrese el nuevo password: ");
        newPwd2 = leerPassword("Confirme el nuevo Password: ");
        if(newPwd1 == newPwd2 && newPwd1.length() > 3){
            // TODO Encriptar nueva password
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
            // TODO encriptar Password
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
                crearGrafico(usr);
                break;
            case 2:
                borrarGrafico();
                break;
            case 3:
                listarAccesos(usr);
                break;
            case 4:
                imprimirGrafico(usr);
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

// opcion 1 usuarios
void crearGrafico(string usr){
    string usuario, fecha, nroGrafico, polinomio;
    map<string, string> graficos;
    ifstream archivoGrafico ("graficos.txt");
    if ( archivoGrafico.is_open() ) {
        while ( archivoGrafico.good() ) {
            archivoGrafico >> usuario;
            archivoGrafico >> fecha;
            archivoGrafico >> nroGrafico;
            archivoGrafico >> polinomio;
            graficos[nroGrafico] = usuario + " " + fecha + " " + nroGrafico + " " + polinomio;
        }
    }
    archivoGrafico.close();

    fecha = getFecha();
    nroGrafico = secuenciaGrafico(graficos);
    cout << "Polinomio (Sin espacios en blanco): ";
    cin >> polinomio;
    // TODO validar Polinomio (Sin espacios en blanco)
    graficos[nroGrafico] = usr + " " + fecha + " " + nroGrafico + " " + polinomio;
    escribirArchivoGraficos(graficos);
    cout << "Grafico creado con exito." << endl;
    system("pause");
}

// opcion 2 Usuarios
void borrarGrafico(){
    string usuario, fecha, nroGrafico, polinomio, referencia;
    map<string, string> graficos;
    ifstream archivoGrafico ("graficos.txt");
    if ( archivoGrafico.is_open() ) {
        while ( archivoGrafico.good() ) {
            archivoGrafico >> usuario;
            archivoGrafico >> fecha;
            archivoGrafico >> nroGrafico;
            archivoGrafico >> polinomio;
            graficos[nroGrafico] = usuario + " " + fecha + " " + nroGrafico + " " + polinomio;
        }
    }
    archivoGrafico.close();

    cout << "Escriba el numero de referencia del grafico a borrar: ";
    cin >> referencia;

    if(graficos.count(referencia)){
        graficos.erase(referencia);
        escribirArchivoGraficos(graficos);
        cout << "Grafico borrado con exito." << endl;
        system("pause");
    } else {
        cout << "No se encuntra el grafico." << endl;
        system("pause");
    }
}

// opcion 3 Usuarios
void listarAccesos(string usr){
    system("cls");
    string usuario, fecha, nroGrafico, polinomio, orden;
    map<string, string> graficos;
    ifstream archivoGrafico ("graficos.txt");
    if ( archivoGrafico.is_open() ) {
        while ( archivoGrafico.good() ) {
            archivoGrafico >> usuario;
            archivoGrafico >> fecha;
            archivoGrafico >> nroGrafico;
            archivoGrafico >> polinomio;
            if(usuario == usr){
                graficos[nroGrafico] = fecha + " " + nroGrafico + " " + polinomio;
            }
        }
    }
    archivoGrafico.close();

    cout << "Aplicativo - Graficador - UTP" << endl;
    cout << "Modulo listar accesos - Usuario: " << usr << endl;
    cout << "Ordenar por fecha. Presione(1) Orden ascendente (2) Orden Descendente:";
    cin >> orden;
    if(orden == "1"){
        cout << endl << "Listado de accesos ordenado ascendente (0-9) por fecha" << endl; 
        cout << "Fecha Nro grafico Polinomio-F(x)" << endl;
        cout << "________________________________" << endl;
        if(graficos.empty()){
            cout << "No existen registros." << endl;
        }else{
            graficos = ordenarGraficosFechaAsc(graficos);
            for (pair<string, string> it : graficos) {
                cout << it.second << endl;
            }
        }
        cout << "--------------------------------" << endl;
        cout << graficos.size() << " Registros" << endl;
        cout << endl;
    } else if(orden == "2"){
        cout << endl << "Listado de accesos ordenado descendente (0-9) por fecha" << endl; 
        cout << "Fecha Nro grafico Polinomio-F(x)" <<endl;
        cout << "________________________________" <<endl;
        if(graficos.empty()){
                cout << "No existen registros." << endl;
        }else{
            graficos = ordenarGraficosFechaDes(graficos);
            for (pair<string, string> it : graficos) {
                cout << it.second << endl;
            }
        }
        cout << "--------------------------------" << endl;
        cout << graficos.size() << " Registros" << endl;
        cout << endl;
    } else{
        cout << "Opcion no valida." << endl;
    }
    system("pause"); 
}

// opcion 4 usuarios
void imprimirGrafico(string usr){
    string usuario, fecha, nroGrafico, polinomio, referencia;
    map<string, string> graficos;
    ifstream archivoGrafico ("graficos.txt");
    if ( archivoGrafico.is_open() ) {
        while ( archivoGrafico.good() ) {
            archivoGrafico >> usuario;
            archivoGrafico >> fecha;
            archivoGrafico >> nroGrafico;
            archivoGrafico >> polinomio;
            if(usr == usuario || usr == "root"){
                graficos[nroGrafico] = polinomio;
            }
        }
    }
    archivoGrafico.close();

    cout << "Escriba el numero de referencia del grafico a imprimir: ";
    cin >> referencia;

    if(graficos.count(referencia)){
        cout << "Polinomio: " << graficos[referencia] << endl << endl;
        system("pause");
        // TODO pintar grafico
    } else {
        cout << "No se encuntra el grafico." << endl;
        system("pause");
    }

}

map<string, string> ordenarGraficosFechaDes(map<string, string> graficos){
    map<string, string> graficosSalida;
    string entrada[graficos.size()][3];
    string aux_elem1,aux_elem2,aux_elem3;
    int i = 0;
    for (pair<string, string> it : graficos) {
        entrada[i][0] = it.second.substr(0, 10);
        entrada[i][1] = it.second.substr(11, 4);
        entrada[i][2] = it.second.substr(16, it.second.length()-16);
        i++;
    }

    for (int i = 0; i < graficos.size() - 1; i++){
        for (int j = 1; j < graficos.size(); j++){
            if (entrada[j][0] > entrada[j-1][0]){   
                aux_elem1 = entrada[j][0];
                aux_elem2 = entrada[j][1];
                aux_elem3 = entrada[j][2];
                entrada[j][0] = entrada[j-1][0];
                entrada[j][1] = entrada[j-1][1];
                entrada[j][2] = entrada[j-1][2];
                entrada[j-1][0] = aux_elem1;
                entrada[j-1][1] = aux_elem2;
                entrada[j-1][2] = aux_elem3;
            }
        }
    }

    for (size_t i = 0; i < graficos.size(); i++){
        graficosSalida[to_string(i)] = entrada[i][0] + " " + entrada[i][1] + " " + entrada[i][2];
    }
    return graficosSalida;
}

map<string, string> ordenarGraficosFechaAsc(map<string, string> graficos){
    map<string, string> graficosSalida;
    string entrada[graficos.size()][3];
    string aux_elem1,aux_elem2,aux_elem3;
    int i = 0;
    for (pair<string, string> it : graficos) {
        entrada[i][0] = it.second.substr(0, 10);
        entrada[i][1] = it.second.substr(11, 4);
        entrada[i][2] = it.second.substr(16, it.second.length()-16);
        i++;
    }

    for (int i = 0; i < graficos.size() - 1; i++){
        for (int j = 1; j < graficos.size(); j++){
            if (entrada[j][0] < entrada[j-1][0]){   
                aux_elem1 = entrada[j][0];
                aux_elem2 = entrada[j][1];
                aux_elem3 = entrada[j][2];
                entrada[j][0] = entrada[j-1][0];
                entrada[j][1] = entrada[j-1][1];
                entrada[j][2] = entrada[j-1][2];
                entrada[j-1][0] = aux_elem1;
                entrada[j-1][1] = aux_elem2;
                entrada[j-1][2] = aux_elem3;
            }
        }
    }

    for (size_t i = 0; i < graficos.size(); i++){
        graficosSalida[to_string(i)] = entrada[i][0] + " " + entrada[i][1] + " " + entrada[i][2];
    }
    return graficosSalida;
}

void escribirArchivoGraficos(map<string, string> graficos){
    fstream fs;
    fs.open ("graficos.txt", fstream::in | fstream::out | fstream::trunc);
    ofstream archivoGraficoW ("graficos.txt");
    for (pair<string, string> it : graficos) {
        archivoGraficoW << it.second << endl;
    }
    archivoGraficoW.close();
}

string secuenciaGrafico(map<string, string> graficos){
    int grafico;
    int mayor = 1;
    string salida;
    for (pair<string, string> it : graficos) {
        grafico = stoi(it.first);
        if(grafico > mayor){
            mayor = grafico;
        }
    }
    salida = to_string(mayor+1);
    if(salida.length() < 4){
        salida = "0" + salida;
    }
    if(salida.length() < 4){
        salida = "0" + salida;
    }
    if(salida.length() < 4){
        salida = "0" + salida;
    }
    return salida;
}

string getFecha(){
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    string str = oss.str();
    return str;
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
                //  TODO encriptar password
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
        // TODO Encriptar Password
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