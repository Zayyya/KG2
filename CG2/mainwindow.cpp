#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent, const char* input)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->openGLWidget->loadData(input);

    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged),
            ui->openGLWidget, &View::setMin);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            ui->openGLWidget, &View::setMax);

    ui->radioButton->setFocus();

    ui->spinBox_2->setValue(ui->openGLWidget->getMin());
    ui->spinBox->setValue(ui->openGLWidget->getMax());

    connect(ui->radioButton, &QRadioButton::clicked,
            ui->openGLWidget, &View::setX);
    connect(ui->radioButton_2, &QRadioButton::clicked,
            ui->openGLWidget, &View::setY);
    connect(ui->radioButton_3, &QRadioButton::clicked,
            ui->openGLWidget, &View::setZ);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    quint32 key_pressed = event->nativeVirtualKey();

    if (key_pressed == Qt::Key_W)
    {
        ui->openGLWidget->goUp();
    }
    else if (key_pressed == Qt::Key_S)
    {
        ui->openGLWidget->goDown();
    }
    else if (key_pressed == Qt::Key_N)
    {
        ui->openGLWidget->changeMethod();
    }
}
