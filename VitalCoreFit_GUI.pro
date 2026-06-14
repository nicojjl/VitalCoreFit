QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    mainwindow.h \
    include/models/Usuario.h \
    include/models/Alimento.h \
    include/models/Nutricion.h \
    include/models/ListaComidas.h \
    include/models/Entrenamiento.h \
    include/models/Dashboard.h \
    include/models/Rutinas.h \
    include/models/Historial.h \
    include/models/Validacion.h \
    include/models/PersistenciaUsuario.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/Usuario.cpp \
    src/Nutricion.cpp \
    src/ListaComidas.cpp \
    src/Entrenamiento.cpp \
    src/Dashboard.cpp \
    src/Rutinas.cpp \
    src/Historial.cpp \
    src/Validacion.cpp \
    src/PersistenciaUsuario.cpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    include/models/.gitkeep \
    include/ui/.gitkeep

INCLUDEPATH += $$PWD/include \
               $$PWD/include/models
