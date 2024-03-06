#include <iostream>
#include "parser.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>



GLuint vertices, verticeCount;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    //Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Reset transformations
    glLoadIdentity();
    gluLookAt(3.0f, 5.0f, 4.0f,    // Position of the camera
              0.0f, 0.0f, 0.0f,    // Point to where the camera is looking
              0.0f, 1.0f, 0.0f);   // Vector that points upwards

    glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, verticeCount);

    glutSwapBuffers();
}




int main (int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file_name.3d>" << std::endl;
        return 1;
    }

    std::string input_file_name = argv[1];

    std::vector<Point> vertices_parsed = parse3dFile(input_file_name.c_str());
    verticeCount = vertices_parsed.size();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CONIG-COIN");

    glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);	
	glutReshapeFunc(changeSize);

    #ifndef __APPLE__
	glewInit();
    #endif

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices_parsed.size() * sizeof(Point), vertices_parsed.data(), GL_STATIC_DRAW);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}