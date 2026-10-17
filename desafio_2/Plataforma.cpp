#include <iostream>
#include "Plataforma.h"

// ===================== Constructor y destructor =====================

// El gestor se crea con la carpeta de los datos.
// La matriz todavia no existe: se crea en cargar(), cuando ya sabemos
// cuantos usuarios hay.
Plataforma::Plataforma(string carpeta) : gestor(carpeta) {
    matriz = nullptr;
    idActual = -1;

    // Semilla distinta cada vez que se abre el programa,
    // asi las fotos que salen al iniciar sesion cambian
    random_device semilla;
    generador.seed(semilla());
}

// Al terminar se libera lo que se creo con new:
// cada mensaje (una sola vez, desde la lista general) y la matriz.
Plataforma::~Plataforma() {
    for (int i = 0; i < mensajes.getCantidad(); i++) {
        delete mensajes[i];
    }
    delete matriz;
}

// ===================== Cargar y guardar =====================

// Lee los 6 archivos. Devuelve false si no se pudieron leer los usuarios.
bool Plataforma::cargar() {
    Metricas::reiniciar();

    if (!gestor.cargarUsuarios(usuarios)) {
        return false;
    }
    matriz = new MatrizAmistad(usuarios.getCantidad());
    gestor.cargarAmistades(usuarios, *matriz);
    gestor.cargarAlbumes(usuarios);
    gestor.cargarFotos(usuarios);
    gestor.cargarSolicitudes(usuarios);
    gestor.cargarMensajes(usuarios, mensajes);

    cout << "Se cargaron " << usuarios.getCantidad() << " usuarios y "
         << mensajes.getCantidad() << " mensajes." << endl;
    Metricas::mostrar("Cargar datos", memoriaDelSistema());
    return true;
}

// Guarda lo que pudo cambiar mientras el programa estaba abierto
void Plataforma::guardar() {
    Metricas::reiniciar();

    gestor.guardarAmistades(usuarios);
    gestor.guardarFotos(usuarios);
    gestor.guardarSolicitudes(usuarios);
    gestor.guardarMensajes(usuarios, mensajes);

    cout << "Cambios guardados." << endl;
    Metricas::mostrar("Guardar datos", memoriaDelSistema());
}

// ===================== Ayudantes =====================

// Lee una linea del teclado y la convierte en numero.
// Si la persona escribe algo que no es un numero, devuelve -1.
int Plataforma::leerOpcion() {
    string texto;
    // Si ya no hay nada que leer (se cerro la entrada), se toma como 0 = salir
    if (!getline(cin, texto)) {
        return 0;
    }

    if (texto == "") {
        return -1;
    }
    int largo = texto.size();
    for (int i = 0; i < largo; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return -1;
        }
    }
    return stoi(texto);
}

// Devuelve la posicion del usuario con ese nombre, o -1 si no existe
int Plataforma::buscarUsuario(string nombre) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Metricas::contar();
        if (usuarios[i].getNombreUsuario() == nombre) {
            return i;
        }
    }
    return -1;
}

// Memoria de todas las estructuras del sistema:
// usuarios (con todo lo que tienen adentro), mensajes y matriz.
// Estos ciclos NO cuentan iteraciones: medir no es parte de la funcionalidad.
int Plataforma::memoriaDelSistema() {
    int total = sizeof(Plataforma);

    total = total + usuarios.memoriaArreglo();
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        total = total + usuarios[i].memoriaExtra();
    }

    total = total + mensajes.memoriaArreglo();
    for (int i = 0; i < mensajes.getCantidad(); i++) {
        total = total + mensajes[i]->memoria();
    }

    if (matriz != nullptr) {
        total = total + matriz->memoria();
    }
    return total;
}

// ===================== Menu principal =====================

void Plataforma::ejecutar() {
    int opcion = -1;

    while (opcion != 0) {
        cout << endl << "===== Ude@Book =====" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "0. Salir y guardar" << endl;
        cout << "Opcion: ";
        opcion = leerOpcion();

        if (opcion == 1) {
            iniciarSesion();
        } else if (opcion == 0) {
            guardar();
            cout << "Hasta pronto." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    }
}

// ===================== Iniciar sesion =====================

void Plataforma::iniciarSesion() {
    Metricas::reiniciar();

    string nombre;
    string clave;
    cout << "Usuario: ";
    getline(cin, nombre);
    cout << "Contrasena: ";
    getline(cin, clave);
    Metricas::agregarMemoriaLocal(sizeof(nombre) + sizeof(clave));

    int id = buscarUsuario(nombre);
    if (id == -1 || !usuarios[id].contrasenaCorrecta(clave)) {
        // No decimos cual de los dos fallo, por seguridad
        cout << "Usuario o contrasena incorrectos." << endl;
        Metricas::mostrar("Iniciar sesion", memoriaDelSistema());
        return;
    }

    idActual = id;
    cout << "Bienvenido(a), " << nombre << "!" << endl;
    mostrarFotosAmigos();
    Metricas::mostrar("Iniciar sesion", memoriaDelSistema());

    menuUsuario();

    idActual = -1;   // al volver del menu, la sesion queda cerrada
}

// ===================== Fotos de amigos al iniciar sesion =====================

// Peso de un amigo segun cuantos amigos tienen en comun.
// El enunciado dice 1, 2.5 y 3.5. Los multiplicamos por 2 (2, 5 y 7)
// para trabajar solo con enteros: las proporciones son las mismas.
int Plataforma::pesoAmigo(int comunes) {
    if (comunes <= 10) {
        return 2;
    }
    if (comunes <= 20) {
        return 5;
    }
    return 7;
}

// Calcula el peso de cada amigo, muestra 3 fotos al azar
// y deja refrescarlas una sola vez.
void Plataforma::mostrarFotosAmigos() {
    Usuario& yo = usuarios[idActual];
    int cantidad = yo.getCantidadAmigos();

    if (cantidad == 0) {
        cout << "Todavia no tienes amigos." << endl;
        return;
    }

    // pesos[i] es el peso del amigo que esta en la posicion i de mi lista de amigos
    Lista<int> pesos;
    for (int i = 0; i < cantidad; i++) {
        Metricas::contar();
        int comunes = matriz->contarAmigosEnComun(idActual, yo.getAmigo(i));
        pesos.agregar(pesoAmigo(comunes));
    }
    Metricas::agregarMemoriaLocal(sizeof(pesos) + pesos.memoriaArreglo());

    elegirFotos(pesos);

    cout << "Quieres refrescar las fotos? (1 = si, 0 = no): ";
    if (leerOpcion() == 1) {
        elegirFotos(pesos);
    }
}

// Sortea hasta 3 amigos distintos. Un amigo con mas peso tiene mas
// probabilidad de salir. "pesos" llega por COPIA, asi los ceros que
// ponemos aqui no dañan la lista original (sirve para el refresco).
void Plataforma::elegirFotos(Lista<int> pesos) {
    Metricas::agregarMemoriaLocal(sizeof(pesos) + pesos.memoriaArreglo());
    Usuario& yo = usuarios[idActual];

    int aMostrar = 3;
    if (pesos.getCantidad() < 3) {
        aMostrar = pesos.getCantidad();
    }

    cout << "Fotos de tus amigos:" << endl;
    for (int k = 0; k < aMostrar; k++) {
        // 1) Sumar los pesos de los que todavia no han salido
        int total = 0;
        for (int i = 0; i < pesos.getCantidad(); i++) {
            Metricas::contar();
            total = total + pesos[i];
        }

        // 2) Numero al azar entre 1 y el total
        uniform_int_distribution<int> dist(1, total);
        int sorteo = dist(generador);
        Metricas::registrarUsoExterno();

        // 3) Ir sumando pesos hasta alcanzar el sorteo
        int elegido = -1;
        int acumulado = 0;
        for (int i = 0; i < pesos.getCantidad() && elegido == -1; i++) {
            Metricas::contar();
            acumulado = acumulado + pesos[i];
            if (sorteo <= acumulado) {
                elegido = i;
            }
        }

        // 4) Ese amigo ya salio: peso 0 para que no salga otra vez
        pesos[elegido] = 0;

        Usuario& amigo = usuarios[yo.getAmigo(elegido)];
        cout << "  " << (k + 1) << ". " << amigo.getNombreUsuario()
             << ": " << amigo.getRutaFotoPerfil() << endl;
    }
}

// ===================== Menu del usuario =====================

// Por ahora solo muestra las opciones.
// Cada funcionalidad se agrega en los siguientes pasos.
void Plataforma::menuUsuario() {
    int opcion = -1;

    while (opcion != 0) {
        cout << endl << "===== " << usuarios[idActual].getNombreUsuario() << " =====" << endl;
        cout << "1. Ver solicitudes de amistad" << endl;
        cout << "2. Enviar solicitud de amistad" << endl;
        cout << "3. Visitar el perfil de un amigo" << endl;
        cout << "4. Sugerencias de amistad" << endl;
        cout << "5. Enviar mensaje" << endl;
        cout << "6. Leer mensajes nuevos" << endl;
        cout << "7. Buscar mensajes por fecha" << endl;
        cout << "0. Cerrar sesion" << endl;
        cout << "Opcion: ";
        opcion = leerOpcion();

        if (opcion >= 1 && opcion <= 7) {
            cout << "(Esta opcion la programamos en los siguientes pasos)" << endl;
        } else if (opcion == 0) {
            cout << "Sesion cerrada." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    }
}
