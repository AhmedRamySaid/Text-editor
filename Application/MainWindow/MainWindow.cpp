#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the text editor instance
    textEditor = new TextEditor(this);

    // Set the text editor as the central widget
    setCentralWidget(textEditor);

    // Set window properties (optional)
    setWindowTitle("Wordia");
    resize(800, 600);

    createMenu();
}

MainWindow::~MainWindow()
{
    delete textEditor;  // Clean up the text editor when the main window is destroyed
}

void MainWindow::createMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu *textMenu = menuBar()->addMenu(tr("&Text"));
    QAction *saveAction = new QAction(tr("&Save"), this);
    fileMenu->addAction(saveAction);
    connect(saveAction, &QAction::triggered, textEditor, &TextEditor::save);

    QAction *openAction = new QAction(tr("&Open"), this);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, textEditor, &TextEditor::openFile);

    QAction *italicAction = new QAction(tr("&Italic"), this);
    textMenu->addAction(italicAction);
    connect(italicAction, &QAction::triggered, textEditor, &TextEditor::italic);

    QAction *boldAction = new QAction(tr("&Bold"), this);
    textMenu->addAction(boldAction);
    connect(boldAction, &QAction::triggered, textEditor, &TextEditor::bold);

    QAction *biggerAction = new QAction(tr("&Increase size"), this);
    textMenu->addAction(biggerAction);
    connect(biggerAction, &QAction::triggered, textEditor, &TextEditor::biggerFont);

    QAction *decreaseAction = new QAction(tr("&Decrease size"), this);
    textMenu->addAction(decreaseAction);
    connect(decreaseAction, &QAction::triggered, textEditor, &TextEditor::smallerFont);
}