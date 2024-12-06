#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void exitApp();
    void makeBold();
    void makeItalic();
    void increaseFontSize();
    void decreaseFontSize();
private:
    QTextEdit *textEdit;
    QString currentFile;
    void createActions();
    void createMenu();
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *boldAction;
    QAction *italicAction;
    QAction *incrementSizeAction;
    QAction *decrementSizeAction;
};

#endif // MAINWINDOW_H
