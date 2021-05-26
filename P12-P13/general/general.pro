TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    ChaineDeMontagnes.cpp \
    MontGaussienne.cpp \
    Systeme.cpp\
    ChampPotentiels.cpp\
    Ciel.cpp\
    Constantes.cpp\
    CubedAir.cpp\
    Montagne.cpp\
    Potentiel.cpp\
    Vecteur.tpp

HEADERS += \
    ChaineDeMontagnes.h \
    MontGaussienne.h \
    Systeme.h\
    ChampPotentiels.h\
    Ciel.h\
    Vecteur.h\
    Collection3D.h\
    Potentiel.h\
    Montagne.h\
    Constantes.h\
    CubedAir.h\
    Dessinable.h \
    SupportADessin.h
