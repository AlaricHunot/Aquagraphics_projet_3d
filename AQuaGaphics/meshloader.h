#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <QOpenGLExtraFunctions>
#include <vector>

class MeshLoader : protected QOpenGLExtraFunctions {
public:
    MeshLoader();
    ~MeshLoader();

    GLuint createCube();           // Générer le VAO pour le cube
    GLuint createSphere(int stacks, int slices); // Générer le VAO pour une sphère
    int getSphereVertexCount() const;  // Récupérer le nombre de sommets de la sphère

private:
    int sphereVertexCount = 0; // Nombre de sommets pour la sphère
};

#endif // MESHLOADER_H
