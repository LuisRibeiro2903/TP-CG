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


float camX, camY, camZ;
float eyeX, eyeY, eyeZ;
float upX, upY, upZ;
float fov, near, far;
vector<GLuint> vertices;
vector<GLuint> verticeCount;

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
	gluPerspective(fov ,ratio, near ,far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    //Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Reset transformations
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
			  eyeX, eyeY, eyeZ,
			  upX, upY, upZ);

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
	for(size_t i = 0; i < vertices.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertices[i]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, verticeCount[i]);
	}

    glutSwapBuffers();
}




int main (int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file_name.3d>" << std::endl;
        return 1;
    }

    std::string input_file_name = argv[1];
	ParsedWorld world = worldParser(input_file_name.c_str());
	camX = world._lookAt[0].x();
	camY = world._lookAt[0].y();
	camZ = world._lookAt[0].z();
	eyeX = world._lookAt[1].x();
	eyeY = world._lookAt[1].y();
	eyeZ = world._lookAt[1].z();
	upX = world._lookAt[2].x();
	upY = world._lookAt[2].y();
	upZ = world._lookAt[2].z();
	fov = world._projection[0];
	near = world._projection[1];
	far = world._projection[2];

	std::vector<std::vector<Point>> vertices_parsed = parse3dFile(world._models);
	for (int i = 0; i < vertices_parsed.size(); i++)
	{
		verticeCount.push_back(vertices_parsed[i].size());
	}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(world._windowWidth, world._windowHeight);
    glutCreateWindow("CONIG-COIN");
    glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);	
	glutReshapeFunc(changeSize);

    #ifndef __APPLE__
	glewInit();
    #endif

	
	vertices.resize(vertices_parsed.size());

    glGenBuffers(vertices_parsed.size(), vertices.data());

	for(size_t i = 0; i < vertices_parsed.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertices[i]);
		glBufferData(GL_ARRAY_BUFFER, vertices_parsed[i].size() * sizeof(Point), vertices_parsed[i].data(), GL_STATIC_DRAW);
	}

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}