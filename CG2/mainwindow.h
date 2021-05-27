#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const char* input = "");
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
