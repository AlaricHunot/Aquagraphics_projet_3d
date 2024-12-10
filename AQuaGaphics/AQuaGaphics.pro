QT       += core gui widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# Inclure les fichiers sources
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    meshloader.cpp \
    water.cpp

# Inclure les fichiers d'en-tête
HEADERS += \
    mainwindow.h \
    meshloader.h \
    water.h

# Inclure les fichiers de formulaires Qt Designer (si applicable)
FORMS += \
    mainwindow.ui

# Options de compilation pour éviter les erreurs liées à des fonctionnalités C++ modernes
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

# Lien avec des bibliothèques supplémentaires
LIBS += -lGL -lstdc++ -lpthread

# Définir les chemins de déploiement pour QNX ou Unix
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Nettoyage automatique des fichiers intermédiaires
clean.target = clean-all
clean.commands = rm -rf *.o *~ build-*
QMAKE_EXTRA_TARGETS += clean
