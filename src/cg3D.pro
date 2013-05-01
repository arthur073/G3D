TEMPLATE = app
TARGET   = cg3D
CONFIG  += qt opengl glut warn_on release thread openmp debug
QT *= xml opengl 

HEADERS  = viewer.h renderable.h man.h textures.h spring.h particle.h dynamicSystem.h 
SOURCES  = viewer.cpp main.cpp man.cpp textures.cpp spring.cpp particle.cpp dynamicSystem.cpp


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
