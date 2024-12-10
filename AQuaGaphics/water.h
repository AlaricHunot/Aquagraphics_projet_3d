#ifndef WATER_H
#define WATER_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>

class Water : public QOpenGLWidget, protected QOpenGLExtraFunctions {
    Q_OBJECT

public:
    explicit Water(int resolution, QWidget* parent = nullptr);
    ~Water();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int resolution;
    GLuint waterVAO, waterVBO;
    float* vertices;             // Tableau dynamique pour les sommets
    int vertexCount;             // Nombre total de sommets
    QMatrix4x4 projectionMatrix;

    void createGrid();
    void updateSimulation();
    void clearResources();
};

#endif // WATER_H
