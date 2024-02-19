TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

# Lisätään Qt:n verkko-ohjelmointikirjastot
QT += network

SOURCES += \
    client.c \
    main.c \
    server.c

HEADERS += \
    client.h \
    server.h

LIBS += -lws2_32

