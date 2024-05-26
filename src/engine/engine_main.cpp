#include "groups.hpp"
#include "parser.hpp"
#include "point.hpp"
#include "engine/frustum/frustumG.hpp"
#include "engine/imgui/imgui.h"
#include "engine/imgui/imgui_impl_opengl3.h"
#include "engine/imgui/imgui_impl_glut.h"
#include <cmath>
#include <string>
#include <vector>
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

float debugCam_alpha, debugCam_beta, debugCam_radius;

float camX, camY, camZ;
float eyeX, eyeY, eyeZ;
float upX, upY, upZ;

float debugCamX, debugCamY, debugCamZ;
float debugEyeX, debugEyeY, debugEyeZ;
float debugUpX, debugUpY, debugUpZ;

std::vector<std::string*> models;

float fov, near, far;

bool imguiGodMode = false;
bool wireframe = false;
bool axis = true;
bool debugNormals = false;
bool debugBoxes = false;
bool frustumOn = false;
bool debugCamera = false;
char fixedModel[256] = "";
bool fixedCamera = false;
Point fixedModelCenter = Point(0, 0, 0);

int modelosDesenhados = 0, modelosTotais = 0;

float frames = 0;

float ratio = 0;

ParsedWorld *world;
FrustumG frustum;

float time0 = 0;

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
    h = 1;

  // compute window's aspect ratio
  ratio = w * 1.0 / h;

  frustum.setCamInternals(fov, ratio, near, far);
  

  // Set the projection matrix as current
  glMatrixMode(GL_PROJECTION);
  // Load Identity Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set perspective
  if (debugCamera){
    gluPerspective(90, ratio, 0.1f, 1000);
  } else {
    gluPerspective(fov, ratio, near, far);
  }

  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
  ImGui_ImplGLUT_ReshapeFunc(w, h);

}

void renderLights() {
  for (int i = 0; i < world->n_lights; i++) {
    world->lights[i]->applyLight();
  }
}

void switchCameras();

void renderImGui() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGLUT_NewFrame();
  ImGui::NewFrame();
  ImGuiIO &io = ImGui::GetIO();
    

  {
    ImGui::Begin("Settings");

    ImGui::Text("Scene Settings");
    ImGui::Checkbox("Axis", &axis);
    ImGui::Checkbox("Frustum", &frustumOn);


    ImGui::Text("Model Settings");
    ImGui::Checkbox("AABoxes", &debugBoxes);
    ImGui::Checkbox("Normals", &debugNormals);
    ImGui::Checkbox("Wireframe", &wireframe);

    ImGui::Text("Camera Settings");

    if(!debugCamera)
    {
      if(ImGui::Button("GOD MODE")) {
        switchCameras();
      }
    } else {
      if(ImGui::Button("Normal Mode")) {
        switchCameras();
      }
    }

    if(ImGui::CollapsingHeader("Models")) {
      ImGui::Text("Choose a model to fix the camera on");
      if(ImGui::Button("Reset")) {
        fixedCamera = false;
        strcpy(fixedModel, "");
      }

      int index = 0;
      for (std::string* model : models) {
          ImGui::Text("%s", model->c_str());

          std::string buttonLabel = "Choose##" + std::to_string(index);
          if (ImGui::Button(buttonLabel.c_str())) {
              fixedCamera = true;
              strcpy(fixedModel, model->c_str());
          }
          index++;
      } 
    }

    ImGui::End();
  }


  ImGui::Render();
  glViewport(0, 0, (GLsizei) io.DisplaySize.x, (GLsizei) io.DisplaySize.y);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void renderScene(void) {
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char s[256];
  // Reset transformations
  glLoadIdentity();
  if(!fixedCamera)
  {
    if(debugCamera) {
      gluLookAt(debugCamX, debugCamY, debugCamZ, debugEyeX, debugEyeY, debugEyeZ, debugUpX, debugUpY, debugUpZ);
      frustum.drawFrustum(debugNormals);
    } else {
      gluLookAt(camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ);
    }
  } else {
    if (fixedModelCenter.x() == 0 && fixedModelCenter.y() == 0 && fixedModelCenter.z() == 0) {
      gluLookAt(camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ);
      strcpy(fixedModel, "");
      fixedCamera = false;
    }else {
      gluLookAt(fixedModelCenter.x() + 5, fixedModelCenter.y() + 5, fixedModelCenter.z() + 5, fixedModelCenter.x(), fixedModelCenter.y(), fixedModelCenter.z(), 0, 1, 0);
    }
  }

  if (wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (axis) {
    glDisable(GL_LIGHTING); 
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
    glEnable(GL_LIGHTING);
  }

  // Draw the lights
  renderLights();

  

  // draw the scene
  modelosDesenhados = 0;
  frustum.setCamDef(camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ);
  float matrix[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  world->rootGroup->resetAABox();
  world->rootGroup->draw(debugNormals, frustumOn, &modelosDesenhados, &frustum, matrix, fixedModel, fixedModelCenter);
  if (debugBoxes)
    world->rootGroup->drawAABox();

  frames++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float fps;
	if (time - time0 > 1000) {
		fps = frames*1000.0/(time-time0);
		time0 = time;
		frames = 0;
		sprintf(s, "CG_ENGINE | FPS: %.2f; Modelos totais: %d; Modelos desenhados: %d", fps, modelosTotais, modelosDesenhados);
		glutSetWindowTitle(s);
	}

  renderImGui();
  glutSwapBuffers();
}

void updatePos() {
  if(debugCamera) {
    debugCamX = debugCam_radius * sin(debugCam_alpha) * cos(debugCam_beta);
    debugCamY = debugCam_radius * sin(debugCam_beta);
    debugCamZ = debugCam_radius * cos(debugCam_alpha) * cos(debugCam_beta);
  } else {
    camX = cam_radius * sin(cam_alpha) * cos(cam_beta);
    camY = cam_radius * sin(cam_beta);
    camZ = cam_radius * cos(cam_alpha) * cos(cam_beta);
  }
}

void handleSpecialKeys(int key, int x, int y) {


  switch (key) {
  case GLUT_KEY_PAGE_DOWN: {
    if (debugCamera) {
      debugCam_radius -= RADIUS_STEP;
    } else {
      cam_radius -= RADIUS_STEP;
    }
    if (cam_radius < 2)
      cam_radius = 2;
    if (debugCam_radius < 2)
      debugCam_radius = 2;
    break;
  }
  case GLUT_KEY_PAGE_UP: {
    if (debugCamera) {
      debugCam_radius += RADIUS_STEP;
    } else {
      cam_radius += RADIUS_STEP;
    }
    break;
  }
  }
  updatePos();
  ImGui_ImplGLUT_SpecialFunc(key, x, y);
}

void handleMouse(int button, int state, int x, int y) {
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}


void handleMotion(int x, int y) {
    ImGui_ImplGLUT_MotionFunc(x, y);
}



void switchCameras() {
  bool debug = !debugCamera;
  if (debug) {
    debugCamX = camX + 4;
    debugCamY = camY + 1;
    debugCamZ = camZ + 4;
    debugEyeX = camX;
    debugEyeY = camY;
    debugEyeZ = camZ;
    debugUpX = upX;
    debugUpY = upY;
    debugUpZ = upZ;
    debugCam_radius = sqrt(debugCamX * debugCamX + debugCamY * debugCamY + debugCamZ * debugCamZ);
    debugCam_alpha = atan2f(debugCamX, debugCamZ);
    debugCam_beta = asinf(debugCamY / cam_radius);
  }
  debugCamera = debug;
  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);
  changeSize(width, height);
}

void handleKeyboard(unsigned char key, int x, int y) {
  
  switch (key) {
    case 'w': {
      if (debugCamera) {
        if (debugCam_beta < 1.5f)
          debugCam_beta += ANGLE_STEP;
      } else {
        if (cam_beta < 1.5f)
          cam_beta += ANGLE_STEP;
      }
      break;
    }
    case 's': {
      if(debugCamera) {
        if (debugCam_beta > -1.5f)
          debugCam_beta -= ANGLE_STEP;
      } else {
        if (cam_beta > -1.5f)
          cam_beta -= ANGLE_STEP;
      }
      break;
    }
    case 'a': {
      if (debugCamera) {
        debugCam_alpha -= ANGLE_STEP;
      } else { 
        cam_alpha -= ANGLE_STEP;
      }
      break;
    }
    case 'd': {
      if (debugCamera) {
        debugCam_alpha += ANGLE_STEP;
      } else {
        cam_alpha += ANGLE_STEP;
      }
      break;
    }
  }
  updatePos();
  ImGui_ImplGLUT_KeyboardFunc(key, x, y);
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
  frustum = FrustumG();

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
  frustum.setCamInternals(fov, world->windowWidth / world->windowHeight, near, far);

}

void initImGUI() {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  ImGui_ImplGLUT_Init();
  ImGui_ImplOpenGL3_Init();


}


void cleanupImGUI() {
  ImGui_ImplGLUT_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
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
  glutCreateWindow("CG_ENGINE");
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutKeyboardFunc(handleKeyboard);
  glutSpecialFunc(handleSpecialKeys);
  glutMouseFunc(handleMouse);
  glutMotionFunc(handleMotion);

#ifndef __APPLE__
  glewInit();
#endif
  
  initImGUI();
  
  //  OpenGL settings
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_RESCALE_NORMAL);

  time0 = glutGet(GLUT_ELAPSED_TIME);

  // We only obtain the window width and height after parsing the file
  world->rootGroup->initVBOs();
  models = world->rootGroup->getNames();
  modelosTotais = world->rootGroup->totalModels();
  initializeLights();

  

  // enter GLUT's main cycle
  glutMainLoop();

  cleanupImGUI();

  return 1;
}
