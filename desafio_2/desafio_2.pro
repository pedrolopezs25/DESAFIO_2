TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Album.cpp \
        Fecha.cpp \
        Foto.cpp \
        MatrizAmistad.cpp \
        Mensaje.cpp \
        Metricas.cpp \
        Solicitud.cpp \
        Usuario.cpp \
        main.cpp

HEADERS += \
    Fecha.h \
    Foto.h \
    MatrizAmistad.h \
    Mensaje.h \
    Metricas.h \
    Solicitud.h \
    Usuario.h \
    album.h \
    lista.h
