#include "mainwindow.h"
#include <QMenuBar>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this))
{
    setCentralWidget(textEdit);
    createActions();
    createMenu();

    setWindowTitle("Simple Text Editor");
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    QAction *openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApp);
}

void MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open"));
    fileMenu->addAction(tr("&Save"));
    fileMenu->addAction(tr("&Exit"));
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            currentFile = fileName;
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
        }
    }
}

void MainWindow::saveFile()
{
    QString fileName = currentFile.isEmpty() ? QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)")) : currentFile;
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            currentFile = fileName;
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
        }
    }
}

void MainWindow::exitApp()
{
    QApplication::quit();
}
