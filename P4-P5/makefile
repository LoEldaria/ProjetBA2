CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11  # C++11, ou autre suivant vos préférences

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall       # pour les purs et durs
CXXFLAGS += -g                    # pour debugger
# CXXFLAGS += -pg                 # pour profiler
# LDFLAGS  += -pg                 # pour profiler
# CXXFLAGS += -O2                 # pour optimiser la vitesse

#########################################################################

all: testVecteur2D

testVecteur2D: testVecteur2D.o Vecteur2D.o

Vecteur2D.o: Vecteur2D.cpp Vecteur2D.h
testVecteur2D.o: testVecteur2D.cpp Vecteur2D.h

#########################################################################

all: testMontagne

testMontagne: testMontagne.o Montagne.o

testMontagne.o: testMontagne.cpp Montagne.h
Montagne.o : Montagne.cpp Montagne.h
