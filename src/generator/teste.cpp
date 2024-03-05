#include <GL/glut.h>
#include "point.hpp"
#include "box.cpp"
#include <vector>

std::vector<Point> box;

// Função para desenhar a caixa
void drawBox() {
    glBegin(GL_TRIANGLES);
    for (const auto& p : box) {
        glVertex3f(p.x(), p.y(), p.z());
    }
    glEnd();
}

// Função de renderização chamada pelo GLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

    drawBox();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Box Test");

    // Configurações de visualização e projeção
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    // Gere sua caixa
    box = generateBox(2.0f, 10); // Exemplo: dimensão 2, com 10 divisões

    // Definir função de callback para renderização
    glutDisplayFunc(display);

    // Iniciar o loop de eventos do GLUT
    glutMainLoop();

    return 0;
}
