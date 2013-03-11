
#include <qapplication.h>
#include "viewer.h"
#include <GL/glut.h>

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
	// Read command lines arguments.
	QApplication application(argc,argv);

	// Instantiate the viewer.
	Viewer viewer;

	viewer.setWindowTitle("viewer");
	// Make the viewer window visible on screen.
	viewer.show();
  
	// Run main loop.
	return application.exec();
}
