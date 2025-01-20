#include "Widget.h"

#include "../TextEditor/texteditor.h"

Widget::Widget(QWidget *parent, Trie &myTrie, const std::string& word, int startPos) : QWidget(parent) {
    setWindowFlags(Qt::ToolTip); // Make the widget behave like a tooltip
    setLayout(new QVBoxLayout);

    int suggestionCount = 0;
    string *suggestions = myTrie.getSuggestion(word, suggestionCount);
    QLabel *label = new QLabel("Suggested fixes", this);
    layout()->addWidget(label);

    for (int i = 0; i < suggestionCount; i++) {
        QString QSuggestion = QString::fromStdString(suggestions[i]);
        QPushButton *suggestion = new QPushButton(QSuggestion, this);
        layout()->addWidget(suggestion);

        connect(suggestion, &QPushButton::clicked, this, [parent, startPos, word, QSuggestion]() {
            QString newtext = ((TextEditor *)parent)->toPlainText();
            for (int i = startPos; i < startPos + QSuggestion.length(); i++) {
                newtext[i] = QSuggestion[i-startPos];
            }
            if (QSuggestion.length() > word.length()) {
                newtext.insert(startPos + QSuggestion.length(),' ');
            }
            ((TextEditor *)parent)->setPlainText(newtext);
        });
    }

    QPushButton *addToDictionary = new QPushButton("Add to dictionary", this);
    layout()->addWidget(addToDictionary);

    connect(addToDictionary, &QPushButton::clicked, this, [myTrie, word, parent]() {
        myTrie.insert(word);
        ((TextEditor *)parent)->checkTextSpelling();
    });
}

void Widget::showAt(const QPoint &pos) {
    move(pos);
    show();
}

void Widget::enterEvent(QEnterEvent *event) {
    show();
    QWidget::enterEvent(event);
}

void Widget::leaveEvent(QEvent *event) {
    hide();
}

void Widget::changeWord(QWidget *parent, Trie &myTrie, const std::string &word, int startPos) {
    if (this->isVisible()) {
        return;
    }

    QLayoutItem *item; //this is to clear the old layout
    while ((item = layout()->takeAt(0))) {
        delete item->widget();  // Delete the widget contained in the layout
        delete item;  // Delete the item itself
    }

    int suggestionCount = 0;
    string *suggestions = myTrie.getSuggestion(word, suggestionCount);
    QLabel *label = new QLabel("Suggested fixes", this);
    layout()->addWidget(label);

    for (int i = 0; i < suggestionCount; i++) {
        QString QSuggestion = QString::fromStdString(suggestions[i]);
        QPushButton *suggestion = new QPushButton(QSuggestion, this);
        layout()->addWidget(suggestion);

        connect(suggestion, &QPushButton::clicked, this, [parent, QSuggestion, startPos, word]() {
            QString newtext = ((TextEditor *)parent)->toPlainText();
            for (int i = startPos; i < startPos + QSuggestion.length(); i++) {
                newtext[i] = QSuggestion[i-startPos];
            }
            if (QSuggestion.length() > word.length()) {
                newtext.insert(startPos + QSuggestion.length(),' ');
            }
            ((TextEditor *)parent)->setPlainText(newtext);
        });
    }

    QPushButton *addToDictionary = new QPushButton("Add to dictionary", this);
    layout()->addWidget(addToDictionary);

    connect(addToDictionary, &QPushButton::clicked, this, [myTrie, word, parent]() {
        myTrie.insert(word);
        ((TextEditor *)parent)->checkTextSpelling();
    });
}
