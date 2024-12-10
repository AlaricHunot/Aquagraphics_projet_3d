#include "meshloader.h"
#include <cmath>
#include <stdexcept>
#include <limits>

MeshLoader::MeshLoader() {
    initializeOpenGLFunctions(); // Initialisation des fonctions OpenGL
}

MeshLoader::~MeshLoader() {}

GLuint MeshLoader::createCube() {
    // Sommets du cube (positions uniquement)
    const float vertices[] = {
        -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,
    };

    // Indices pour former les faces du cube
    const unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 0, 4, 7, 7, 3, 0,
        1, 5, 6, 6, 2, 1, 3, 7, 6, 6, 2, 3, 0, 4, 5, 5, 1, 0
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return vao;
}

GLuint MeshLoader::createSphere(int stacks, int slices) {
    if (stacks <= 0 || slices <= 0) {
        throw std::runtime_error("Stacks and slices must be positive.");
    }

    // Calculer le nombre de sommets nécessaires
    const int numVertices = (stacks + 1) * (slices + 1) * 3; // Chaque sommet a 3 coordonnées (x, y, z)
    float* vertices = new float[numVertices]; // Tableau dynamique pour les sommets

    int index = 0;
    for (int i = 0; i <= stacks; ++i) {
        float phi = M_PI * i / stacks;
        for (int j = 0; j <= slices; ++j) {
            float theta = 2.0f * M_PI * j / slices;

            vertices[index++] = sin(phi) * cos(theta); // x
            vertices[index++] = cos(phi);             // y
            vertices[index++] = sin(phi) * sin(theta); // z
        }
    }

    sphereVertexCount = numVertices / 3;

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);

    delete[] vertices; // Libérer la mémoire allouée dynamiquement

    return vao;
}

int MeshLoader::getSphereVertexCount() const {
    return sphereVertexCount;
}
