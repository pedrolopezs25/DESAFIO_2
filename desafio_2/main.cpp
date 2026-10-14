// Prueba general: una mini red social con 4 usuarios
// para ver como se relacionan todas las clases que llevamos.
#include <iostream>
#include "Usuario.h"

using namespace std;

// Busca un usuario por su nombre y devuelve su posicion en la lista.
// Si no existe, devuelve -1.
int buscarUsuario(Lista<Usuario>& usuarios, string nombre) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        if (usuarios[i].getNombreUsuario() == nombre) {
            return i;
        }
    }
    return -1;
}

// Crea la amistad en los dos sentidos
void hacerAmigos(Usuario& a, Usuario& b) {
    a.agregarAmigo(b.getId());
    b.agregarAmigo(a.getId());
}

// ¿El usuario "a" tiene como amigo al id "idOtro"?
bool sonAmigos(Usuario& a, int idOtro) {
    for (int i = 0; i < a.getCantidadAmigos(); i++) {
        if (a.getAmigo(i) == idOtro) {
            return true;
        }
    }
    return false;
}

void titulo(string texto) {
    cout << endl << "========== " << texto << " ==========" << endl;
}

int main() {
    // ---------------------------------------------------------
    titulo("1. Crear usuarios (Usuario + Fecha + Lista)");
    // ---------------------------------------------------------
    Lista<Usuario> usuarios;
    usuarios.agregar(Usuario(0, "erika", "secreto", "erika@correo.com",
                             "Medellin", "Colombia", Fecha(10, 7, 2003), Fecha(2, 2, 2025)));
    usuarios.agregar(Usuario(1, "juanito76", "clave123", "juan@correo.com",
                             "Cartagena", "Colombia", Fecha(5, 3, 2000), Fecha(1, 1, 2025)));
    usuarios.agregar(Usuario(2, "maria_p", "maria1", "maria@correo.com",
                             "Bogota", "Colombia", Fecha(22, 11, 2001), Fecha(3, 4, 2025)));
    usuarios.agregar(Usuario(3, "pedro99", "pedro1", "pedro@correo.com",
                             "Cali", "Colombia", Fecha(1, 1, 1999), Fecha(9, 9, 2025)));

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        cout << "id " << usuarios[i].getId() << ": " << usuarios[i].getNombreUsuario()
        << " (" << usuarios[i].getCiudad() << "), inscrito el "
        << usuarios[i].getFechaInscripcion() << endl;
    }

    // ---------------------------------------------------------
    titulo("2. Iniciar sesion (contrasenaCorrecta)");
    // ---------------------------------------------------------
    int pos = buscarUsuario(usuarios, "erika");
    if (pos != -1 && usuarios[pos].contrasenaCorrecta("secreto")) {
        cout << "Bienvenida, " << usuarios[pos].getNombreUsuario() << endl;
    }
    if (!usuarios[pos].contrasenaCorrecta("123")) {
        cout << "Con la clave '123' no puede entrar" << endl;
    }

    // Desde aqui, "yo" es la usuaria que inicio sesion
    Usuario& yo = usuarios[pos];

    // ---------------------------------------------------------
    titulo("3. Amistades (Usuario guarda ids de amigos)");
    // ---------------------------------------------------------
    hacerAmigos(yo, usuarios[1]);   // erika - juanito76
    hacerAmigos(yo, usuarios[2]);   // erika - maria_p
    hacerAmigos(usuarios[1], usuarios[2]);   // juanito76 - maria_p

    cout << "Amigos de erika:" << endl;
    for (int i = 0; i < yo.getCantidadAmigos(); i++) {
        Usuario& amigo = usuarios[yo.getAmigo(i)];
        cout << "  " << amigo.getNombreUsuario()
             << "  foto de perfil: " << amigo.getRutaFotoPerfil() << endl;
    }

    // ---------------------------------------------------------
    titulo("4. Solicitud de amistad (Solicitud + eliminar)");
    // ---------------------------------------------------------
    Usuario& pedro = usuarios[3];
    cout << "pedro99 ya es amigo de erika? " << sonAmigos(pedro, yo.getId()) << endl;
    cout << "erika ya tiene solicitud de pedro99? " << yo.tieneSolicitudDe("pedro99") << endl;

    yo.agregarSolicitud(Solicitud(pedro.getNombreUsuario(), Fecha(13, 10, 2026)));
    cout << "pedro99 le envia solicitud a erika. Solicitudes de erika: "
         << yo.getCantidadSolicitudes() << endl;
    if (yo.tieneSolicitudDe("pedro99")) {
        cout << "Puede pedro99 enviarle otra? No, ya hay una pendiente" << endl;
    } else {
        cout << "Puede pedro99 enviarle otra? Si" << endl;
    }

    // erika acepta la primera solicitud
    Solicitud s = yo.getSolicitud(0);
    int idNuevoAmigo = usuarios[buscarUsuario(usuarios, s.getEmisor())].getId();
    hacerAmigos(yo, usuarios[idNuevoAmigo]);
    yo.eliminarSolicitud(0);
    cout << "erika acepta. Ahora tiene " << yo.getCantidadAmigos() << " amigos y "
         << yo.getCantidadSolicitudes() << " solicitudes" << endl;

    // ---------------------------------------------------------
    titulo("5. Albumes y fotos (Usuario -> Album -> Foto)");
    // ---------------------------------------------------------
    Usuario& juan = usuarios[1];

    Album cartagena("Cartagena2026", "amigos");
    cartagena.agregarFoto(Foto("Malecon2612", Fecha(15, 6, 2026), 2048, 3));
    cartagena.agregarFoto(Foto("Bocagrande1", Fecha(16, 6, 2026), 1500, 0));
    cartagena.agregarFoto(Foto("Murallas", Fecha(17, 6, 2026), 1800, 7));
    juan.agregarAlbum(cartagena);

    Album viaje("Viaje2025", "publico");
    viaje.agregarFoto(Foto("Playa", Fecha(2, 1, 2025), 900, 1));
    juan.agregarAlbum(viaje);

    Album privado("Diario", "privado");
    privado.agregarFoto(Foto("Secreto1", Fecha(1, 2, 2026), 500, 0));
    juan.agregarAlbum(privado);

    cout << "juanito76 tiene " << juan.getCantidadAlbumes() << " albumes" << endl;

    // ---------------------------------------------------------
    titulo("6. Erika visita el perfil de juanito76 (privacidad)");
    // ---------------------------------------------------------
    cout << "Albumes que erika puede ver:" << endl;
    for (int i = 0; i < juan.getCantidadAlbumes(); i++) {
        Album& a = juan.getAlbum(i);
        if (a.loPuedeVerUnAmigo()) {
            cout << "  " << a.getNombre() << " (" << a.getPrivacidad() << ", "
                 << a.getCantidadFotos() << " fotos)" << endl;
        }
    }
    cout << "(El album 'Diario' es privado y no aparece)" << endl;

    // ---------------------------------------------------------
    titulo("7. Carrusel circular y likes");
    // ---------------------------------------------------------
    Album& album = juan.getAlbum(0);
    string rutaAlbum = album.getRuta(juan.getRuta());
    int actual = 0;
    int total = album.getCantidadFotos();

    // Recorremos 4 veces "siguiente" en un album de 3 fotos: vuelve a la primera
    for (int paso = 0; paso < 4; paso++) {
        cout << "Viendo: " << album.getFoto(actual).getRuta(rutaAlbum)
        << "  likes=" << album.getFoto(actual).getLikes() << endl;
        actual = actual + 1;
        if (actual == total) {
            actual = 0;   // despues de la ultima, vuelve a la primera
        }
    }

    album.getFoto(1).darLike();
    cout << "erika le da like a Bocagrande1 -> likes="
         << juan.getAlbum(0).getFoto(1).getLikes()
         << " (quedo guardado dentro del album de juanito76)" << endl;

    // ---------------------------------------------------------
    titulo("8. Mensajes compartidos (Mensaje*)");
    // ---------------------------------------------------------
    // Todos los mensajes se guardan aqui para poder borrarlos al final
    Lista<Mensaje*> todosLosMensajes;

    Mensaje* m1 = new Mensaje("juanito76", "erika", "Hola, como vas?", Fecha(1, 9, 2026, 8, 15));
    Mensaje* m2 = new Mensaje("maria_p", "erika", "Ya viste las fotos?", Fecha(20, 9, 2026, 19, 2));
    Mensaje* m3 = new Mensaje("juanito76", "erika", "Nos vemos el viernes", Fecha(10, 10, 2026, 12, 0));

    todosLosMensajes.agregar(m1);
    todosLosMensajes.agregar(m2);
    todosLosMensajes.agregar(m3);

    // Cada mensaje va a los enviados del emisor y a los recibidos del receptor
    for (int i = 0; i < todosLosMensajes.getCantidad(); i++) {
        Mensaje* m = todosLosMensajes[i];
        usuarios[buscarUsuario(usuarios, m->getEmisor())].agregarMensajeEnviado(m);
        usuarios[buscarUsuario(usuarios, m->getReceptor())].agregarMensajeRecibido(m);
    }

    cout << "Mensajes nuevos de erika:" << endl;
    for (int i = 0; i < yo.getCantidadRecibidos(); i++) {
        Mensaje* m = yo.getMensajeRecibido(i);
        if (!m->estaLeido()) {
            cout << "  " << *m << endl;
            m->marcarLeido();
        }
    }
    cout << "juanito76 ve su primer mensaje enviado como leido? "
         << juan.getMensajeEnviado(0)->estaLeido() << endl;

    Fecha inicio(15, 9, 2026);
    Fecha fin(10, 10, 2026, 23, 59);
    cout << "Mensajes de erika entre " << inicio << " y " << fin << ":" << endl;
    for (int i = 0; i < yo.getCantidadRecibidos(); i++) {
        Mensaje* m = yo.getMensajeRecibido(i);
        if (m->estaEnRango(inicio, fin)) {
            cout << "  " << *m << endl;
        }
    }

    // ---------------------------------------------------------
    titulo("9. Liberar memoria");
    // ---------------------------------------------------------
    for (int i = 0; i < todosLosMensajes.getCantidad(); i++) {
        delete todosLosMensajes[i];
    }
    cout << "Se borraron " << todosLosMensajes.getCantidad() << " mensajes." << endl;
    cout << "Las listas, albumes y fotos se liberan solos con sus destructores." << endl;

    return 0;
}

