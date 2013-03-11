TEMPLATE = app
TARGET   = cg3D
CONFIG  += qt opengl glut warn_on release thread openmp debug
QT *= xml opengl 

HEADERS  = viewer.h renderable.h cube.h cylinder.h sphere.h lightsMaterials.h
SOURCES  = viewer.cpp main.cpp cube.cpp cylinder.cpp sphere.cpp lightsMaterials.cpp


# Qt 2.3 users must edit config.pri
#include( config.pri )
LIBS *= -lglut # -ltiff

exists( /usr/lib/libqglviewer-qt4.so) |
exists( /usr/lib/x86_64-linux-gnu/libqglviewer-qt4.so )
{
  LIBS *= -lqglviewer-qt4
} else {
  LIBS *= -lqglviewer
}
