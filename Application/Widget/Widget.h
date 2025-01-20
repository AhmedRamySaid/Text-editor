#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QTextEdit>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "../../Data Structure/Trie/Trie.h"
#include <memory> // For std::unique_ptr

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent, Trie &myTrie, const std::string& word, int startPos);
    void showAt(const QPoint &pos);
    void changeWord(QWidget *praent, Trie &myTrie, const std::string& word, int startPos);
    void updateHoverLabel(const QString &word);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:

};


#endif //WIDGET_H
