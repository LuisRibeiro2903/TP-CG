#include "groups.hpp"
#include "parser.hpp"
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#define ANGLE_STEP 0.1;
#define RADIUS_STEP 0.25;

float cam_alpha, cam_beta, cam_radius;

float camX, camY, camZ;
float eyeX, eyeY, eyeZ;
float upX, upY, upZ;
float fov, near, far;

bool wireframe = false;
bool axis = true;

ParsedWorld *world;

float time0 = 0;

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
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
  gluPerspective(fov, ratio, near, far);

  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
}

void renderLights() {
  for (int i = 0; i < world->n_lights; i++) {
    world->lights[i]->applyLight();
  }
}

void renderScene(void) {
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  gluLookAt(camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ);

  if (wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glDisable(GL_LIGHTING);
  if (axis) {
    // Draw axis
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
  }

  // Set the color to white by default
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_LIGHTING);

  // Draw the lights
  renderLights();

  // draw the scene
  world->rootGroup->draw();

  glutSwapBuffers();
}

void updatePos() {
  camX = cam_radius * sin(cam_alpha) * cos(cam_beta);
  camY = cam_radius * sin(cam_beta);
  camZ = cam_radius * cos(cam_alpha) * cos(cam_beta);
}

void handleSpecialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_PAGE_DOWN: {
    cam_radius -= RADIUS_STEP;
    if (cam_radius < 2)
      cam_radius = 2;
    break;
  }
  case GLUT_KEY_PAGE_UP: {
    cam_radius += RADIUS_STEP;
    break;
  }
  }
  updatePos();
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'w': {
    if (cam_beta < 1.5f)
      cam_beta += ANGLE_STEP;

    break;
  }
  case 's': {
    if (cam_beta > -1.5f)
      cam_beta -= ANGLE_STEP;

    break;
  }
  case 'a': {
    cam_alpha -= ANGLE_STEP;

    break;
  }
  case 'd': {
    cam_alpha += ANGLE_STEP;

    break;
  }
  case 'p': {
    wireframe = !wireframe;
    break;
  }
  case 'l': {
    axis = !axis;
    break;
  }
  }
  updatePos();
}

void initializeLights() {
  float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
  if (world->n_lights > 0) {
    if (world->n_lights > 8) {
      std::cerr << "Too many lights, only the first 8 will be used"
                << std::endl;
      world->n_lights = 8;
    }
    for (int i = 0; i < world->n_lights; i++) {
      world->lights[i]->initialize();
    }
  } else {
    std::cerr << "No lights in the scene" << std::endl;
  }
}

void init(std::string input_file_name) {
  world = worldParser(input_file_name.c_str());

  camX = world->lookAt[0].x();
  camY = world->lookAt[0].y();
  camZ = world->lookAt[0].z();

  eyeX = world->lookAt[1].x();
  eyeY = world->lookAt[1].y();
  eyeZ = world->lookAt[1].z();
  upX = world->lookAt[2].x();
  upY = world->lookAt[2].y();
  upZ = world->lookAt[2].z();
  fov = world->projection[0];
  near = world->projection[1];
  far = world->projection[2];

  cam_radius = sqrt(camX * camX + camY * camY + camZ * camZ);
  cam_alpha = atan2f(camX, camZ);
  cam_beta = asinf(camY / cam_radius);

  time0 = glutGet(GLUT_ELAPSED_TIME);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file.xml>" << std::endl;
    return 1;
  }

  init(argv[1]);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(world->windowWidth, world->windowHeight);
  // TODO: Ouvi dizer que era para alterar isto :(
  glutCreateWindow("CONIG-COIN");
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutKeyboardFunc(handleKeyboard);
  glutSpecialFunc(handleSpecialKeys);

#ifndef __APPLE__
  glewInit();
#endif

  initializeLights();

  // We only obtain the window width and height after parsing the file

  //  OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_RESCALE_NORMAL);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  // enter GLUT's main cycle
  glutMainLoop();

  return 1;
}
