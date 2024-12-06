#include "mainwindow.h"

#include <iostream>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , textEdit(new QTextEdit(this))
{
    setCentralWidget(textEdit);
    createActions();
    createMenu();

    setWindowTitle("Text Editor");
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));;
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    exitAction = new QAction("&Exit", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApp);

    boldAction = new QAction("&Bold", this);
    boldAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    connect(boldAction, &QAction::triggered, this, &MainWindow::makeBold);

    incrementSizeAction = new QAction("&Bigger", this);
    incrementSizeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));;
    connect(incrementSizeAction, &QAction::triggered, this, &MainWindow::increaseFontSize);

    decrementSizeAction = new QAction("&Smaller", this);
    decrementSizeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));;
    connect(decrementSizeAction, &QAction::triggered, this, &MainWindow::decreaseFontSize);

    italicAction = new QAction("&Italic", this);
    italicAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));;
    connect(italicAction, &QAction::triggered, this, &MainWindow::makeItalic);
}

void MainWindow::createMenu()
{
    //not sure what tr() did
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    QMenu *textMenu = menuBar()->addMenu("&Text");
    textMenu->addAction(boldAction);
    textMenu->addAction(incrementSizeAction);
    textMenu->addAction(decrementSizeAction);
    textMenu->addAction(italicAction);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));
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
    QString fileName = currentFile.isEmpty()
                           ? QFileDialog::getSaveFileName(this,
                                                          tr("Save File"),
                                                          "",
                                                          tr("Text Files (*.txt);;All Files (*)"))
                           : currentFile;
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

void MainWindow::makeBold() {
    QTextCursor cursor = textEdit->textCursor();  // Get the current cursor position
    if (cursor.hasSelection()) {
        // If text is selected, toggle bold for the selected text
        QTextCharFormat format = cursor.charFormat();
        format.setFontWeight(format.fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        cursor.mergeCharFormat(format);
    }
}

void MainWindow::makeItalic()
{
    QTextCursor cursor = textEdit->textCursor();  // Get the current cursor position
    if (cursor.hasSelection()) {
        // If text is selected, toggle italic for the selected text
        QTextCharFormat format = cursor.charFormat();
        format.setFontItalic(!format.fontItalic());  // Toggle the italic style
        cursor.mergeCharFormat(format);
    }
}

void MainWindow::increaseFontSize()
{
    QTextCursor cursor = textEdit->textCursor();  // Get the current cursor position
    if (cursor.hasSelection()) {
        // If text is selected, increase the font size for the selected text
        QFont currentFont = cursor.charFormat().font();
        currentFont.setPointSize(currentFont.pointSize() + 1);  // Increase font size by 1
        QTextCharFormat format = cursor.charFormat();
        format.setFont(currentFont);
        cursor.mergeCharFormat(format);
    }
}

void MainWindow::decreaseFontSize()
{
    QTextCursor cursor = textEdit->textCursor();  // Get the current cursor position
    if (cursor.hasSelection()) {
        // If text is selected, increase the font size for the selected text
        QFont currentFont = cursor.charFormat().font();
        currentFont.setPointSize(currentFont.pointSize() - 1);  // Increase font size by 1
        QTextCharFormat format = cursor.charFormat();
        format.setFont(currentFont);
        cursor.mergeCharFormat(format);
    }
}

void MainWindow::exitApp()
{
    QApplication::quit();
}
