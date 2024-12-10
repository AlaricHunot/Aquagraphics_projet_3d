#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "water.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Water* waterWidget; // Widget pour afficher l'eau
};

#endif // MAINWINDOW_H
