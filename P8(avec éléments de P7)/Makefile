CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11  # C++11, ou autre suivant vos préférences

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall       # pour les purs et durs
CXXFLAGS += -g                    # pour debugger
#CXXFLAGS += -pg                 # pour profiler
# LDFLAGS  += -pg                 # pour profiler
# CXXFLAGS += -O2                 # pour optimiser la vitesse

#########################################################################

all:testMontagne testVecteur testPotentiel testLaplace testNuage


testMontagne: testMontagne.o Montagne.o
testMontagne.o: testMontagne.cpp Montagne.h
Montagne.o : Montagne.cpp Montagne.h

testVecteur: testVecteur.o 
testVecteur.o: testVecteur.cpp Vecteur.h

testPotentiel: testPotentiel.o Potentiel.o ChampPotentiels.o Montagne.o
testPotentiel.o : testPotentiel.cpp ChampPotentiels.h Potentiel.h Montagne.h 
Potentiel.o : Potentiel.h Potentiel.cpp Montagne.h Vecteur.h
ChampPotentiels.o : ChampPotentiels.h ChampPotentiels.cpp Montagne.h  Potentiel.h Constantes.h Collection3D.h

testLaplace: testLaplace.o Potentiel.o ChampPotentiels.o Montagne.o Constantes.o
Constantes.o: Constantes.cpp Constantes.h

testNuage: testNuage.o ChampPotentiels.o Potentiel.o Montagne.o Ciel.o CubedAir.o Constantes.o
testNuage.o: testNuage.cpp ChampPotentiels.h Potentiel.h Montagne.h Ciel.h CubedAir.h Constantes.h Collection3D.h
Ciel.o:Ciel.cpp Ciel.h ChampPotentiels.h CubedAir.h
CubedAir.o: CubedAir.cpp CubedAir.h Constantes.h