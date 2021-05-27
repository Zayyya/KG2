#pragma once

#include "data.h"

#include <QtOpenGL>
#include <QtWidgets/QOpenGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/qtopenglglobal.h>

class View : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
protected:
    Data data;
    int layer;
    enum {VISUALIZATION_QUADS, VISUALIZATION_QUADSTRIP, VISUALIZATION_TEXTURE} visualisation_state;
    enum {x, y, z} axis_cut;

    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;

    void VisualisationQuads();
    void VisualisationQuadStrip();
    void VisualisationTexture();

    float TransferFunction(short value);

    GLuint VBOtexture;
    void Load2dTexture();
    QImage textureImage;
    void genTextureImage();

public:
    View(QWidget *parent = nullptr);
    void loadData(QString filename);

    short getMin();
    short getMax();

public slots:
    void setMin(short value);
    void setMax(short value);

    void goUp();
    void goDown();
    void changeMethod();

    void setX();
    void setY();
    void setZ();
};
