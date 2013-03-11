#ifndef _RENDERABLE_
#define _RENDERABLE_

/**
 * General interface of renderable objetcs, that can be displayed
 * in the Viewer class.
 * It just defines three methods to override in child classes to
 * initialize, draw and animate a renderable objetc.
 */

class Renderable
{
	public:
		/// Virtual destructor (mandatory!)
		virtual ~Renderable() {};
		
		/** 
		 * Initializes a Renderable objet before it is draw.
		 * Default behavior: nothing is done.
		 */
		virtual void init() {};
	
		/** 
		 * Draw a Renderable object.
		 * This pure virtual method must be overriden if child classes.
		 */
		virtual void draw() = 0;

		/** 
		 * Animate an object. This method is invoked before each call of draw().
		 * Default behavior: nothing is done.
		 */
		virtual void animate() {};
};

#endif

