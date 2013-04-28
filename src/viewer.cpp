#include <QKeyEvent>

#include "viewer.h"
#include "man.h"
#include "textures.h"

int lastPressed = 0;

Viewer::Viewer() {
   init();
}

Viewer::~Viewer()
{
   list<Renderable *>::iterator it;
   for (it = renderableList.begin(); it != renderableList.end(); ++it) {
      delete(*it);
   }
   renderableList.clear();
}


void Viewer::init()
{

   //=== VIEWING PARAMETERS
   restoreStateFromFile();   // Restore previous viewer state.

   toogleWireframe = false;  // filled faces
   toogleLight = true;       // light on
   //help();                   // display help

   if (toogleLight == true)
      glEnable(GL_LIGHTING);
   else
      glDisable(GL_LIGHTING);

   setSceneRadius(5.0f);
   glClearColor(.7, .7, .7, .0);


   //=== INIT SCENE: add everything you want in your scene to the renderableList
   //    (just an instance of Cube in this example)

   Textures *tex = new Textures();
   renderableList.push_back(tex);
   
   Man *man = new Man();
   renderableList.push_back(man);

}


void Viewer::draw()
{  
   // draw every objects in renderableList
   list<Renderable *>::iterator it;
   for(it = renderableList.begin(); it != renderableList.end(); ++it) {
      (*it)->draw();
   }
}


void Viewer::animate()
{
   // animate every objects in renderableList
   list<Renderable *>::iterator it;
   for(it = renderableList.begin(); it != renderableList.end(); ++it) {
      (*it)->animate();
   }

   // this code might change if some rendered objets (stored as
   // attributes) need to be specifically updated with common
   // attributes, like real CPU time (?)
}



void Viewer::keyPressEvent(QKeyEvent *e)
{
  if ( lastPressed == Qt::Key_F1 )
    {
      Man::currentMove = Man::EVENT_WALK;
      if( Man::isAnimationEnded() )
      {
         if (Man::currentMove != Man::EVENT_WALK) {
            // départ d'une animation
          //  Man::resetAnim();
         }
         lastPressed = 0;
      }
    }
    else if( lastPressed == Qt::Key_F2 )
    {
      animate();
      updateGL();
      if( Man::isAnimationEnded() )
      {
         if (Man::currentMove != Man::EVENT_APPLAUSE) {
            // départ d'une animation
          //  Man::resetAnim();
         }
         Man::currentMove = Man::EVENT_APPLAUSE;
         lastPressed = 0;
      }
    }
    else if( lastPressed == Qt::Key_F3 )
    {
      animate();
      updateGL();
      if( Man::isAnimationEnded() )
      {
         if (Man::currentMove != Man::EVENT_SPELL) {
            // départ d'une animation
           // Man::resetAnim();
         }
         Man::currentMove = Man::EVENT_SPELL;
         lastPressed = 0;
      }
    }
   // Get event modifiers key
   const Qt::KeyboardModifiers modifiers = e->modifiers();

   if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton)) {
      // events with modifiers: CTRL+W, ALT+W, ... to handle separately
      toogleWireframe = !toogleWireframe;
      if (toogleWireframe)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      updateGL();

   } else if ((e->key()==Qt::Key_L) && (modifiers==Qt::NoButton)) {
      toogleLight = !toogleLight;
      if (toogleLight == true)
         glEnable(GL_LIGHTING);
      else
         glDisable(GL_LIGHTING);
      updateGL();
   // Walk animation
   } else if (e->key()==Qt::Key_F1) {
      lastPressed = e->key();
   // Applause animation
   } else if (e->key()==Qt::Key_F2) {
      lastPressed = e->key();
   // Spell animation
   } else if (e->key()==Qt::Key_F3) {
      lastPressed = e->key();
   } else {
      // if the event is not handled here, process it as default
      QGLViewer::keyPressEvent(e);
   }

   if( lastPressed != 0 )
   {
      animate();
      updateGL();
      //decommenter pr mouvement auto, mais se fait une seule fois
      //et on peut plus zoomer ni rien
      //keyPressEvent(e);
   }
}

QString Viewer::helpString() const
{
   // Some usefull hints...
   QString text("<h2>V i e w e r</h2>");
   text += "Use the mouse to move the camera around the object. ";
   text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
   text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
   text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
   text += "Simply press the function key again to restore it. Several keyFrames define a ";
   text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
   text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
   text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
   text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
   text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
   text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
   text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
   text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
   text += "Press <b>Escape</b> to exit the viewer.";
   return text;
}

