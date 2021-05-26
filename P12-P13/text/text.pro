QMAKE_CXXFLAGS += -std=c++11

TARGET = P13_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    testSimulationText.cpp \
    TextViewer.cpp

HEADERS += \
    ../general/Systeme.h \
    TextViewer.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h
