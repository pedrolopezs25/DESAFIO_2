TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Album.cpp \
        Fecha.cpp \
        Foto.cpp \
        Mensaje.cpp \
        Solicitud.cpp \
        Usuario.cpp \
        main.cpp

HEADERS += \
    Fecha.h \
    Foto.h \
    Mensaje.h \
    Solicitud.h \
    Usuario.h \
    album.h \
    lista.h
