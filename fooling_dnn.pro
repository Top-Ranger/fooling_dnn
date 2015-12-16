#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T21:30:36
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fooling_dnn
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

# Do not use GPU
DEFINES += CPU_ONLY

SOURCES += src/main.cpp\
        src/foolingdnn.cpp \
    src/simulation/alexnetsimulation.cpp \
    src/finalimage.cpp \
    src/runner.cpp

HEADERS  += src/foolingdnn.h \
    src/simulation/alexnetsimulation.h \
    src/finalimage.h \
    src/runner.h

FORMS    += src/foolingdnn.ui \
    src/finalimage.ui \
    src/runner.ui

# Kubuntu serach for HDF5
INCLUDEPATH += /usr/include/hdf5/serial
DEPENDPATH += /usr/include/hdf5/serial
LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial/

# protobuf
LIBS += -lprotobuf

# caffe

INCLUDEPATH += $$PWD/caffe/include/
DEPENDPATH += $$PWD/caffe/include/
LIBS += -L$$PWD/caffe/build/lib/ -lcaffe

# qnn

INCLUDEPATH += $$PWD/qnn/src/
DEPENDPATH += $$PWD/qnn/src/
LIBS += -L$$PWD/qnn -lqnn

# qnn-image-generators

INCLUDEPATH += $$PWD/qnn-image-generators/src/
DEPENDPATH += $$PWD/qnn-image-generators/src/
LIBS += -L$$PWD/qnn-image-generators/ -lqnn-image-generators
