#ifndef TRIE_H
#define TRIE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "../Queue/Queue.h"
#include "../Queue/Queue.cpp"

using namespace std;
inline int tester = 0;

class Trie {

private:
    struct Node {
        Node* children[26]; // Assuming only lowercase letters
        char letter;
        bool isEndOfWord;
        Node() {
            letter = ' ';
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isEndOfWord = false;
        }
        Node(char c, bool endOfWord) {
            letter = tolower(c);
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isEndOfWord = endOfWord;
        }
        Node* getchild(char Char) {
            Char = tolower(Char);
            if (Char - 'a' < 0 || Char - 'a' >= 26) {
                return nullptr;
            }
            return children[Char - 'a'];
        }
        void setchild(Node* newNode) {
            if (newNode == nullptr) {
                cerr << "Trie error: Can't insert null Node" << endl;
                return;
            }
            if (getchild(newNode->letter) != nullptr) {
                cerr << "Trie error: Can't insert duplicate letter" << endl;
                delete newNode;
                return;
            }
            children[newNode->letter - 'a'] = newNode;
        }
    };
    Node* root;
public:
    Trie();
    void printTrie(const Node* node, string prefix);
    void insert(const string& word) const;
    bool search(string word) const;
    void readDictionary(const string& filePath);
    string* getSuggestion(const string& word, int &suggestionCount);
    static bool isPunctuation(char c);
};



#endif //TRIE_H
