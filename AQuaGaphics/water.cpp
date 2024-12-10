#include "water.h"
#include <cmath>
#include <stdexcept>
#include <QDebug>

Water::Water(int resolution, QWidget* parent)
    : QOpenGLWidget(parent), resolution(resolution), waterVAO(0), waterVBO(0), vertices(nullptr), vertexCount(0) {}

Water::~Water() {
    clearResources();
}

void Water::initializeGL() {
    qDebug() << "Initializing OpenGL...";
    initializeOpenGLFunctions();

    createGrid();

    glGenVertexArrays(1, &waterVAO);
    Q_ASSERT(waterVAO != 0);
    glBindVertexArray(waterVAO);

    glGenBuffers(1, &waterVBO);
    Q_ASSERT(waterVBO != 0);
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Water::resizeGL(int w, int h) {
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
    glViewport(0, 0, w, h);
}

void Water::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(waterVAO);
    glColor3f(0.0f, 0.5f, 1.0f);

    for (int z = 0; z < resolution; ++z) {
        glDrawArrays(GL_TRIANGLE_STRIP, z * (resolution + 1), (resolution + 1) * 2);
    }

    glBindVertexArray(0);
    updateSimulation();
}

void Water::createGrid() {
    vertexCount = (resolution + 1) * (resolution + 1);
    vertices = new float[vertexCount * 3];  // Allouer de la mémoire pour les sommets

    float step = 2.0f / resolution;
    int index = 0;

    for (int z = 0; z <= resolution; ++z) {
        for (int x = 0; x <= resolution; ++x) {
            vertices[index++] = -1.0f + x * step; // Coordonnée X
            vertices[index++] = 0.0f;             // Coordonnée Y (hauteur)
            vertices[index++] = -1.0f + z * step; // Coordonnée Z
        }
    }
}

void Water::updateSimulation() {
    static float time = 0.0f;
    time += 0.01f;

    for (int i = 1; i < vertexCount * 3; i += 3) {
        vertices[i] = 0.1f * std::sin(time + vertices[i - 1] + vertices[i + 1]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * 3 * sizeof(float), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    update();
}

void Water::clearResources() {
    makeCurrent();
    if (waterVAO) {
        glDeleteVertexArrays(1, &waterVAO);
        waterVAO = 0;
    }
    if (waterVBO) {
        glDeleteBuffers(1, &waterVBO);
        waterVBO = 0;
    }
    if (vertices) {
        delete[] vertices;
        vertices = nullptr;
    }
    doneCurrent();
}
