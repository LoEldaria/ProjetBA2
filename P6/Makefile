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

all:testMontagne testVecteur2D testPotentiel 


testMontagne: testMontagne.o Montagne.o
testMontagne.o: testMontagne.cpp Montagne.h
Montagne.o : Montagne.cpp Montagne.h

Vecteur2D.o : Vecteur2D.cpp Vecteur2D.h
testVecteur2D.o: testVecteur2D.cpp Vecteur2D.h 
testVecteur2D: testVecteur2D.o Vecteur2D.o

testPotentiel: testPotentiel.o Potentiel.o ChampPotentiels.o Montagne.o Vecteur2D.o
testPotentiel.o : testPotentiel.cpp ChampPotentiels.h Potentiel.h Montagne.h 
Potentiel.o : Potentiel.h Potentiel.cpp Montagne.h Vecteur2D.h
ChampPotentiels.o : ChampPotentiels.h ChampPotentiels.cpp Montagne.h  Potentiel.h

