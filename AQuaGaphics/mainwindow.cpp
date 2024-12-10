#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), waterWidget(new Water(50)) { // Initialisation avec une résolution
    setCentralWidget(waterWidget); // Affiche le widget Water dans la fenêtre principale
}

MainWindow::~MainWindow() {
    delete waterWidget; // Libération du widget Water
}
