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

// Fecha y hora de hoy en Colombia, a partir del reloj del computador.
// <chrono> da los segundos que han pasado desde el 01/01/1970 00:00 (hora UTC).
// Con ciclos sencillos convertimos esos segundos en dia, mes, año, hora y minuto.
Fecha Plataforma::fechaDeHoy() {
    long long segundos = chrono::duration_cast<chrono::seconds>(
                             chrono::system_clock::now().time_since_epoch()).count();
    segundos = segundos - 5 * 3600;   // Colombia esta 5 horas atras de UTC

    long long dias = segundos / 86400;            // dias completos desde 1970
    int segundosDelDia = segundos % 86400;
    int hora = segundosDelDia / 3600;
    int minuto = (segundosDelDia % 3600) / 60;

    // Quitar años completos
    int anio = 1970;
    while (true) {
        int diasDelAnio = 365;
        if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
            diasDelAnio = 366;   // año bisiesto
        }
        if (dias < diasDelAnio) {
            break;
        }
        dias = dias - diasDelAnio;
        anio++;
    }

    // Quitar meses completos
    int diasMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
        diasMes[2] = 29;
    }
    int mes = 1;
    while (dias >= diasMes[mes]) {
        dias = dias - diasMes[mes];
        mes++;
    }

    int dia = dias + 1;   // los dias que sobran son del mes actual (empezando en 1)
    return Fecha(dia, mes, anio, hora, minuto);
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

// Muestra las opciones y llama a la funcionalidad que se escoja
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

        if (opcion == 1) {
            verSolicitudes();
        } else if (opcion == 2) {
            enviarSolicitud();
        } else if (opcion == 3) {
            visitarPerfil();
        } else if (opcion == 4) {
            sugerencias();
        } else if (opcion == 5) {
            enviarMensaje();
        } else if (opcion == 6) {
            leerMensajesNuevos();
        } else if (opcion == 7) {
            buscarMensajes();
        } else if (opcion == 0) {
            cout << "Sesion cerrada." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    }
}

// ===================== Solicitudes de amistad =====================

// Muestra las solicitudes recibidas y deja aceptar una (o volver con 0)
void Plataforma::verSolicitudes() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    if (yo.getCantidadSolicitudes() == 0) {
        cout << "No tienes solicitudes de amistad." << endl;
        Metricas::mostrar("Ver solicitudes", memoriaDelSistema());
        return;
    }

    cout << "Solicitudes de amistad:" << endl;
    for (int i = 0; i < yo.getCantidadSolicitudes(); i++) {
        Metricas::contar();
        Solicitud sol = yo.getSolicitud(i);
        cout << "  " << (i + 1) << ". " << sol.getEmisor() << " (" << sol.getFecha() << ")" << endl;
    }
    cout << "Numero de la solicitud que quieres aceptar (0 = volver): ";
    int numero = leerOpcion();
    Metricas::agregarMemoriaLocal(sizeof(numero));

    if (numero < 1 || numero > yo.getCantidadSolicitudes()) {
        if (numero != 0) {
            cout << "Numero no valido." << endl;
        }
        Metricas::mostrar("Ver solicitudes", memoriaDelSistema());
        return;
    }

    // En pantalla empezamos en 1, pero en la lista se empieza en 0
    int posicion = numero - 1;
    string nombreEmisor = yo.getSolicitud(posicion).getEmisor();
    int idEmisor = buscarUsuario(nombreEmisor);
    Metricas::agregarMemoriaLocal(sizeof(posicion) + sizeof(nombreEmisor) + sizeof(idEmisor));

    // La amistad se guarda en los dos lados: la matriz y las dos listas de amigos
    if (idEmisor != -1 && !matriz->sonAmigos(idActual, idEmisor)) {
        matriz->agregarAmistad(idActual, idEmisor);
        yo.agregarAmigo(idEmisor);
        usuarios[idEmisor].agregarAmigo(idActual);
    }
    yo.eliminarSolicitud(posicion);

    cout << "Ahora " << nombreEmisor << " y tu son amigos." << endl;
    Metricas::mostrar("Aceptar solicitud", memoriaDelSistema());
}

// Envia una solicitud de amistad a otro usuario
void Plataforma::enviarSolicitud() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    string nombre;
    cout << "Nombre del usuario: ";
    getline(cin, nombre);
    Metricas::agregarMemoriaLocal(sizeof(nombre));

    int idOtro = buscarUsuario(nombre);
    Metricas::agregarMemoriaLocal(sizeof(idOtro));

    if (idOtro == -1) {
        cout << "Ese usuario no existe." << endl;
    } else if (idOtro == idActual) {
        cout << "No te puedes enviar una solicitud a ti mismo." << endl;
    } else if (matriz->sonAmigos(idActual, idOtro)) {
        cout << "Ya eres amigo de " << nombre << "." << endl;
    } else if (usuarios[idOtro].tieneSolicitudDe(yo.getNombreUsuario())) {
        cout << "Ya le enviaste una solicitud a " << nombre << "." << endl;
    } else if (yo.tieneSolicitudDe(nombre)) {
        cout << nombre << " ya te envio una solicitud. Aceptala en la opcion 1." << endl;
    } else {
        // La solicitud se guarda en la lista del que la RECIBE
        usuarios[idOtro].agregarSolicitud(Solicitud(yo.getNombreUsuario(), fechaDeHoy()));
        cout << "Solicitud enviada a " << nombre << "." << endl;
    }

    Metricas::mostrar("Enviar solicitud", memoriaDelSistema());
}

// ===================== Elegir un amigo =====================

// Muestra mis amigos numerados y devuelve el id del que se escoja.
// Devuelve -1 si no tengo amigos, si escribe 0 o si el numero no es valido.
int Plataforma::elegirAmigo() {
    Usuario& yo = usuarios[idActual];

    if (yo.getCantidadAmigos() == 0) {
        cout << "Todavia no tienes amigos." << endl;
        return -1;
    }

    cout << "Tus amigos:" << endl;
    for (int i = 0; i < yo.getCantidadAmigos(); i++) {
        Metricas::contar();
        cout << "  " << (i + 1) << ". " << usuarios[yo.getAmigo(i)].getNombreUsuario() << endl;
    }
    cout << "Numero del amigo (0 = volver): ";
    int numero = leerOpcion();
    Metricas::agregarMemoriaLocal(sizeof(numero));

    if (numero < 1 || numero > yo.getCantidadAmigos()) {
        if (numero != 0) {
            cout << "Numero no valido." << endl;
        }
        return -1;
    }
    return yo.getAmigo(numero - 1);
}

// ===================== Visitar el perfil de un amigo =====================

void Plataforma::visitarPerfil() {
    Metricas::reiniciar();

    int idAmigo = elegirAmigo();
    if (idAmigo == -1) {
        Metricas::mostrar("Visitar perfil", memoriaDelSistema());
        return;
    }
    Usuario& amigo = usuarios[idAmigo];

    // Datos del perfil
    cout << endl << "Perfil de " << amigo.getNombreUsuario() << endl;
    cout << "  Foto de perfil: " << amigo.getRutaFotoPerfil() << endl;
    cout << "  Ciudad: " << amigo.getCiudad() << ", " << amigo.getPais() << endl;
    cout << "  Amigos: " << amigo.getCantidadAmigos() << endl;

    // Solo se muestran los albumes que un amigo puede ver.
    // "visibles" guarda la posicion de cada uno en la lista de albumes del amigo.
    Lista<int> visibles;
    for (int a = 0; a < amigo.getCantidadAlbumes(); a++) {
        Metricas::contar();
        if (amigo.getAlbum(a).loPuedeVerUnAmigo()) {
            visibles.agregar(a);
        }
    }
    Metricas::agregarMemoriaLocal(sizeof(idAmigo) + sizeof(visibles) + visibles.memoriaArreglo());

    if (visibles.getCantidad() == 0) {
        cout << "No tiene albumes que puedas ver." << endl;
        Metricas::mostrar("Visitar perfil", memoriaDelSistema());
        return;
    }

    cout << "Albumes:" << endl;
    for (int i = 0; i < visibles.getCantidad(); i++) {
        Metricas::contar();
        Album& album = amigo.getAlbum(visibles[i]);
        cout << "  " << (i + 1) << ". " << album.getNombre() << " ("
             << album.getCantidadFotos() << " fotos, " << album.getPrivacidad() << ")" << endl;
    }
    cout << "Numero del album (0 = volver): ";
    int numero = leerOpcion();

    if (numero < 1 || numero > visibles.getCantidad()) {
        if (numero != 0) {
            cout << "Numero no valido." << endl;
        }
        Metricas::mostrar("Visitar perfil", memoriaDelSistema());
        return;
    }

    Album& album = amigo.getAlbum(visibles[numero - 1]);
    carrusel(album, album.getRuta(amigo.getRuta()));

    Metricas::mostrar("Visitar perfil", memoriaDelSistema());
}

// Carrusel circular: muestra una foto a la vez.
// Despues de la ultima sigue la primera, y antes de la primera va la ultima.
void Plataforma::carrusel(Album& album, string rutaAlbum) {
    int cantidad = album.getCantidadFotos();
    if (cantidad == 0) {
        cout << "El album no tiene fotos." << endl;
        return;
    }

    // leDiLike[i] dice si en esta visita ya le di like a la foto i,
    // asi no se puede dar like dos veces ni quitar un like que no di
    Lista<bool> leDiLike;
    for (int i = 0; i < cantidad; i++) {
        Metricas::contar();
        leDiLike.agregar(false);
    }
    Metricas::agregarMemoriaLocal(sizeof(cantidad) + sizeof(leDiLike) + leDiLike.memoriaArreglo());

    int actual = 0;
    int opcion = -1;
    while (opcion != 0) {
        Metricas::contar();
        Foto& foto = album.getFoto(actual);
        cout << endl << "[" << (actual + 1) << "/" << cantidad << "] " << foto.getNombre() << endl;
        cout << "  Ruta: " << foto.getRuta(rutaAlbum) << endl;
        cout << "  Tomada: " << foto.getFechaCaptura() << "   Tamanio: "
             << foto.getTamanio() << " KB   Likes: " << foto.getLikes() << endl;
        cout << "1. Siguiente  2. Anterior  3. Like  4. Quitar like  0. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerOpcion();

        if (opcion == 1) {
            actual = (actual + 1) % cantidad;              // de la ultima vuelve a la primera
        } else if (opcion == 2) {
            actual = (actual - 1 + cantidad) % cantidad;   // de la primera va a la ultima
        } else if (opcion == 3) {
            if (leDiLike[actual]) {
                cout << "Ya le diste like a esta foto." << endl;
            } else {
                foto.darLike();
                leDiLike[actual] = true;
            }
        } else if (opcion == 4) {
            if (leDiLike[actual]) {
                foto.quitarLike();
                leDiLike[actual] = false;
            } else {
                cout << "No le has dado like a esta foto." << endl;
            }
        } else if (opcion != 0) {
            cout << "Opcion no valida." << endl;
        }
    }
}

// ===================== Sugerencias de amistad =====================

// Sugiere K usuarios (1 a 20) que no son mis amigos, ordenados por la
// cantidad de amigos en comun conmigo (de mayor a menor).
void Plataforma::sugerencias() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    cout << "Cuantas sugerencias quieres? (1 a 20): ";
    int k = leerOpcion();
    if (k < 1 || k > 20) {
        cout << "Debe ser un numero entre 1 y 20." << endl;
        Metricas::mostrar("Sugerencias", memoriaDelSistema());
        return;
    }

    // comunes[j] = cuantos amigos tengo en comun con el usuario j.
    // En vez de comparar con cada uno de los 1000 usuarios, recorremos
    // los amigos de mis amigos: cada vez que aparece j, es un amigo en comun mas.
    int n = usuarios.getCantidad();
    int* comunes = new int[n];
    for (int j = 0; j < n; j++) {
        Metricas::contar();
        comunes[j] = 0;
    }
    for (int i = 0; i < yo.getCantidadAmigos(); i++) {
        Usuario& amigo = usuarios[yo.getAmigo(i)];
        for (int a = 0; a < amigo.getCantidadAmigos(); a++) {
            Metricas::contar();
            int j = amigo.getAmigo(a);
            if (j != idActual && !matriz->sonAmigos(idActual, j)) {
                comunes[j]++;
            }
        }
    }
    Metricas::agregarMemoriaLocal(sizeof(k) + sizeof(n) + sizeof(comunes) + n * sizeof(int));

    // Escoger K veces el que mas amigos en comun tenga.
    // Despues de mostrarlo se pone en -1 para que no vuelva a salir.
    cout << "Sugerencias de amistad:" << endl;
    int mostradas = 0;
    for (int s = 0; s < k; s++) {
        int mejor = -1;
        for (int j = 0; j < n; j++) {
            Metricas::contar();
            if (comunes[j] > 0 && (mejor == -1 || comunes[j] > comunes[mejor])) {
                mejor = j;
            }
        }
        if (mejor == -1) {
            break;   // ya no hay mas usuarios con amigos en comun
        }
        cout << "  " << (s + 1) << ". " << usuarios[mejor].getNombreUsuario()
             << " (" << comunes[mejor] << " amigos en comun)" << endl;
        comunes[mejor] = -1;
        mostradas++;
    }
    if (mostradas < k) {
        cout << "Solo hay " << mostradas << " usuarios con amigos en comun." << endl;
    }

    delete[] comunes;
    Metricas::mostrar("Sugerencias", memoriaDelSistema());
}

// ===================== Mensajes =====================

// Envia un mensaje a un amigo. El texto no puede estar vacio ni pasar de 512 caracteres.
void Plataforma::enviarMensaje() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    int idAmigo = elegirAmigo();
    if (idAmigo == -1) {
        Metricas::mostrar("Enviar mensaje", memoriaDelSistema());
        return;
    }

    string texto;
    cout << "Mensaje (maximo 512 caracteres): ";
    getline(cin, texto);
    Metricas::agregarMemoriaLocal(sizeof(idAmigo) + sizeof(texto));

    if (texto == "") {
        cout << "El mensaje no puede estar vacio." << endl;
    } else if (texto.size() > 512) {
        cout << "El mensaje tiene " << texto.size() << " caracteres. El maximo es 512." << endl;
    } else {
        // El mensaje se crea UNA vez y lo comparten tres listas:
        // la general, la de enviados mia y la de recibidos de mi amigo
        Mensaje* m = new Mensaje(yo.getNombreUsuario(), usuarios[idAmigo].getNombreUsuario(),
                                 texto, fechaDeHoy());
        mensajes.agregar(m);
        yo.agregarMensajeEnviado(m);
        usuarios[idAmigo].agregarMensajeRecibido(m);
        cout << "Enviado: " << *m << endl;
    }

    Metricas::mostrar("Enviar mensaje", memoriaDelSistema());
}

// Muestra los mensajes recibidos que no he leido y los marca como leidos
void Plataforma::leerMensajesNuevos() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    int nuevos = 0;
    for (int i = 0; i < yo.getCantidadRecibidos(); i++) {
        Metricas::contar();
        Mensaje* m = yo.getMensajeRecibido(i);
        if (!m->estaLeido()) {
            cout << "  " << *m << endl;
            m->marcarLeido();
            nuevos++;
        }
    }
    Metricas::agregarMemoriaLocal(sizeof(nuevos));

    if (nuevos == 0) {
        cout << "No tienes mensajes nuevos." << endl;
    } else {
        cout << "Leiste " << nuevos << " mensajes nuevos." << endl;
    }
    Metricas::mostrar("Leer mensajes nuevos", memoriaDelSistema());
}

// Convierte "dd/mm/aaaa" en una Fecha, revisando que exista.
// Devuelve false si el texto no tiene ese formato o la fecha no existe.
bool Plataforma::leerFecha(string texto, Fecha& resultado) {
    if (texto.size() != 10 || texto[2] != '/' || texto[5] != '/') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && (texto[i] < '0' || texto[i] > '9')) {
            return false;
        }
    }

    int dia = stoi(texto.substr(0, 2));
    int mes = stoi(texto.substr(3, 2));
    int anio = stoi(texto.substr(6, 4));

    if (mes < 1 || mes > 12) {
        return false;
    }
    int diasMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
        diasMes[2] = 29;
    }
    if (dia < 1 || dia > diasMes[mes]) {
        return false;
    }

    resultado = Fecha(dia, mes, anio);
    return true;
}

// Busca mis mensajes (recibidos y enviados) entre dos fechas, ambas incluidas
void Plataforma::buscarMensajes() {
    Metricas::reiniciar();
    Usuario& yo = usuarios[idActual];

    string texto;
    Fecha inicio;
    Fecha fin;
    Metricas::agregarMemoriaLocal(sizeof(texto) + sizeof(inicio) + sizeof(fin));

    cout << "Fecha inicial (dd/mm/aaaa): ";
    getline(cin, texto);
    if (!leerFecha(texto, inicio)) {
        cout << "Fecha no valida." << endl;
        Metricas::mostrar("Buscar mensajes", memoriaDelSistema());
        return;
    }
    cout << "Fecha final (dd/mm/aaaa): ";
    getline(cin, texto);
    if (!leerFecha(texto, fin)) {
        cout << "Fecha no valida." << endl;
        Metricas::mostrar("Buscar mensajes", memoriaDelSistema());
        return;
    }
    // La fecha final incluye todo ese dia, hasta las 23:59
    fin.setHora(23);
    fin.setMinuto(59);

    if (fin < inicio) {
        cout << "La fecha final no puede ser antes de la inicial." << endl;
        Metricas::mostrar("Buscar mensajes", memoriaDelSistema());
        return;
    }

    // Las listas estan ordenadas por fecha: cuando un mensaje ya es
    // posterior a la fecha final, los siguientes tambien lo son y paramos.
    int encontrados = 0;
    cout << "Recibidos:" << endl;
    for (int i = 0; i < yo.getCantidadRecibidos(); i++) {
        Metricas::contar();
        Mensaje* m = yo.getMensajeRecibido(i);
        if (fin < m->getFechaEnvio()) {
            break;
        }
        if (m->estaEnRango(inicio, fin)) {
            cout << "  " << *m << endl;
            encontrados++;
        }
    }
    cout << "Enviados:" << endl;
    for (int i = 0; i < yo.getCantidadEnviados(); i++) {
        Metricas::contar();
        Mensaje* m = yo.getMensajeEnviado(i);
        if (fin < m->getFechaEnvio()) {
            break;
        }
        if (m->estaEnRango(inicio, fin)) {
            cout << "  " << *m << endl;
            encontrados++;
        }
    }
    Metricas::agregarMemoriaLocal(sizeof(encontrados));

    cout << "Se encontraron " << encontrados << " mensajes." << endl;
    Metricas::mostrar("Buscar mensajes", memoriaDelSistema());
}
