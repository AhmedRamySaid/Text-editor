#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QFileDialog>
#include "../../Data Structure/Stack/Stack.h"
#include "../../Data Structure/Trie/Trie.h"
#include "../Widget/Widget.h"
#include <QRegularExpression>

class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    void bold();
    void italic();
    void biggerFont();
    void smallerFont();
    void openFile();
    void save();
    void saveAs();
    void checkTextSpelling();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Trie trie = Trie();
    Stack undoStack;  // Stack for undo
    Stack redoStack;  // Stack for redo
    void undo();
    void redo();
    QString currentFile;
    std::unique_ptr<Widget> tooltipWidget;
};

#endif // TEXTEDITOR_H
