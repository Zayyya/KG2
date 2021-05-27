#include "view.h"

View::View(QWidget *parent) : QOpenGLWidget(parent), data(), layer(0), visualisation_state(VISUALIZATION_QUADS), axis_cut(x) {}

void View::loadData(QString filename)
{
    data.readFile(filename);
}

void View::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glGenTextures(1, &VBOtexture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void View::resizeGL(int n_width, int n_height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, data.getWidth() - 1, 0.f, data.getHeight() - 1, -1.f, 1.f);
    glViewport(0, 0, n_width, n_height);
    update();
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (visualisation_state)
    {
        case VISUALIZATION_QUADS:
            VisualisationQuads();
            break;
        case VISUALIZATION_QUADSTRIP:
            VisualisationQuadStrip();
            break;
        case VISUALIZATION_TEXTURE:
            VisualisationTexture();
            break;
    }
}

void View::VisualisationQuads()
{
    float c;
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();

    switch (axis_cut)
    {
        case x:
        for (int y = 0; y < h - 1; y++)
        {
            for (int x = 0; x < w - 1; x++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[layer * w * h + y * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, y);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, y + 1);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + x + 1]);
                glColor3f(c, c, c);
                glVertex2i(x + 1, y + 1);

                c = TransferFunction(data[layer * w * h + y * w + x + 1]);
                glColor3f(c, c, c);
                glVertex2i(x + 1, y);
                glEnd();
            }
        }
        break;

    case y:
        for (int y = 0; y < h - 1; y++)
        {
            for (int z = 0; z < d - 1; z++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[w * h * z + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z, y);

                c = TransferFunction(data[w * h * z + (y + 1) * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z, y + 1);

                c = TransferFunction(data[w * h * (z + 1) + (y + 1) * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z + 1, y + 1);

                c = TransferFunction(data[w * h * (z + 1) + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z + 1, y);
                glEnd();
            }
        }
        break;

    case z:
        for (int z = 0; z < d - 1; z++)
        {
            for (int x = 0; x < w - 1; x++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[x + z * w * h + layer * w]);
                glColor3f(c, c, c);
                glVertex2i(x, z);

                c = TransferFunction(data[x + (z + 1) * w * h + layer * w]);
                glColor3f(c, c, c);
                glVertex2i(x, z + 1);

                c = TransferFunction(data[(x + 1) + (z + 1) * w * h + layer * w]);
                glColor3f(c, c, c);
                glVertex2i(x + 1, z + 1);

                c = TransferFunction(data[(x + 1) + z * w * h + layer * w]);
                glColor3f(c, c, c);
                glVertex2i(x + 1, z);
                glEnd();
            }
        }
        break;
    }
}

void View::VisualisationQuadStrip()
{
    float c;
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();

    switch(axis_cut)
    {
    case x:
        for (int y = 0; y < h - 1; y++)
        {
                glBegin(GL_QUAD_STRIP);
                for (int x = 0; x < w; x++)
                {
                    c = TransferFunction(data[layer * w * h + y * w + x]);
                    glColor3f(c, c, c);
                    glVertex2i(x, y);

                    c = TransferFunction(data[layer * w * h + (y + 1) * w + x]);
                    glColor3f(c, c, c);
                    glVertex2i(x, y + 1);
                }
                glEnd();
         }
        break;

    case y:
        for (int y = 0; y < h - 1; y++)
        {
                glBegin(GL_QUAD_STRIP);
                for (int z = 0; z < d; z++)
                {
                    c = TransferFunction(data[w * h * z + y * w + layer]);
                    glColor3f(c, c, c);
                    glVertex2i(z, y);

                    c = TransferFunction(data[w * h * z + (y + 1) * w + layer]);
                    glColor3f(c, c, c);
                    glVertex2i(z, y + 1);
                }
                glEnd();
         }
        break;

    case z:
        for (int z = 0; z < d - 1; z++)
        {
                glBegin(GL_QUAD_STRIP);
                for (int x = 0; x < w; x++)
                {
                    c = TransferFunction(data[x + z * w * h + layer * w]);
                    glColor3f(c, c, c);
                    glVertex2i(x, z);

                    c = TransferFunction(data[x + (z + 1) * w * h + layer * w]);
                    glColor3f(c, c, c);
                    glVertex2i(x, z + 1);
                }
                glEnd();
         }
        break;
    }
}

void View::VisualisationTexture()
{
    genTextureImage();
    Load2dTexture();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i(0, 0);
    glTexCoord2f(0, 1);
    glVertex2i(0, data.getHeight());
    glTexCoord2f(1, 1);
    glVertex2i(data.getWidth(), data.getHeight());
    glTexCoord2f(1, 0);
    glVertex2i(data.getWidth(), 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void View::genTextureImage()
{
    float c;
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();
    textureImage = QImage(w, h, QImage::Format_RGB32);

    switch(axis_cut)
    {
    case x:
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
            {
                c = TransferFunction(data[layer * w * h + w * y + x]) * 255;
                if (c > 255)
                    c = 255;
                else if (c < 0)
                    c = 0;
                textureImage.setPixelColor(x, y, QColor(c,c,c));
            }
        break;

    case y:
        for (int y = 0; y < h; y++)
            for (int z = 0; z < d; z++)
            {
                c = TransferFunction(data[w * h * z + y * w + layer]) * 255;
                if (c > 255)
                    c = 255;
                else if (c < 0)
                    c = 0;
                textureImage.setPixelColor(z, y, QColor(c,c,c));
            }
        break;
    case z:
        for (int z = 0; z < d; z++)
            for (int x = 0; x < w; x++)
            {
                c = TransferFunction(data[x + z * w * h + layer * w]) * 255;
                if (c > 255)
                    c = 255;
                else if (c < 0)
                    c = 0;
                textureImage.setPixelColor(x, z, QColor(c,c,c));
            }
        break;
    }
}

void View::Load2dTexture()
{
    glBindTexture(GL_TEXTURE_2D, VBOtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(),
    0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

float View::TransferFunction(short value)
{
    return float(value - data.getMin()) / float(data.getMax() - data.getMin());
}

void View::setMin(short value)
{
    qDebug() << "SET_MIN " << value;
    data.setMin(value);
    update();
}

void View::setMax(short value)
{
    qDebug() << "SET_MAX " << value;
    data.setMax(value);
    update();
}

void View::goUp()
{
    switch(axis_cut)
    {
    case x:
        layer = std::min(layer + 1, data.getDepth() - 1);
        break;
    case y:
        layer = std::min(layer + 1, data.getWidth() - 1);
        break;
    case z:
        layer = std::min(layer + 1, data.getHeight() - 1);
        break;
    }

    update();
}

void View::goDown()
{
    layer = std::max(layer - 1, 0);
    update();
}

void View::changeMethod()
{
    switch (visualisation_state)
    {
        case VISUALIZATION_QUADS:
            visualisation_state = VISUALIZATION_QUADSTRIP; qDebug() << "QUAD_STRIP"; break;
        case VISUALIZATION_QUADSTRIP:
            visualisation_state = VISUALIZATION_TEXTURE; qDebug() << "TEX"; break;
        case VISUALIZATION_TEXTURE:
            visualisation_state = VISUALIZATION_QUADS; qDebug() << "QUADS"; break;
    }
    update();
}

void View::setX()
{
    if (layer > data.getDepth() - 1)
        layer = data.getDepth() - 1;

    axis_cut = x;
    qDebug() << "x";
    update();
}

void View::setY()
{
    if (layer > data.getWidth() - 1)
        layer = data.getWidth() - 1;

    axis_cut = y;
    qDebug() << "y";
    update();
}

void View::setZ()
{
    if (layer > data.getHeight() - 1)
        layer = data.getHeight() - 1;

    axis_cut = z;
    qDebug() << "z";
    update();
}

short View::getMin()
{
    return data.getMin();
}

short View::getMax()
{
    return data.getMax();
}

