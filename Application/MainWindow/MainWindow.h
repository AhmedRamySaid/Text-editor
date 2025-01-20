#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../TextEditor/texteditor.h"
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TextEditor *textEditor;  // The custom text editor widget
    void createMenu();
};

#endif // MAINWINDOW_H
