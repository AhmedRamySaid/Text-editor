#include "Trie.h"

Trie::Trie() {
    root = new Node();
    const string nounpath = R"(Dictionary\NounDictionary.txt)";
    readDictionary(nounpath);
    const string verbpath = R"(Dictionary\VerbDictionary.txt)";
    readDictionary(verbpath);
}

// Insert a word into the Trie
void Trie::insert(const string& word) const{
    Node* temp = root;
    Node* prev = nullptr;
    int letterPos = 0;
    //loop until it finds the last letter present in the trie
    while (temp->getchild((word[letterPos])) != nullptr) {
        temp = temp->getchild(word[letterPos++]);
        if(letterPos == word.length()) {
            temp->isEndOfWord = true;
            return; //word already exists
        }
    }
    //insert the rest of the word
    while (letterPos < word.length()-1) {
        Node *temp2 = new Node(word[letterPos++], false);
        temp->setchild(temp2);
        temp = temp2;
    }
    temp->setchild(new Node(word[letterPos], true));
}

// Search for a word in the Trie
bool Trie::search(string word) const {
    if (isPunctuation(word[word.length()-1])) {
        word.pop_back();
    }
    Node* current = root;
    int letterPos = 0;
    while(current != nullptr) {
        current = current->getchild(word[letterPos++]);
        if(letterPos == word.length() && current != nullptr) {
            return current->isEndOfWord;
        }
    }
    return false;
}
void Trie::readDictionary(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open dictionary file at " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string word;

        while (ss >> word) {
            if (!word.empty()) {
                insert(word);
            }
        }
    }
    file.close();
}

bool Trie::isPunctuation(char c) {
    const string punctuation = ".,!?!";
    return punctuation.find(c) != string::npos;
}

string *Trie::getSuggestion(const string &word, int &suggestionCount) {
    string *suggestions = new string[4];
    string suggestion;
    suggestionCount = 0;
    //make sure word doesn't already exist
    if (search(word)) {
        return nullptr;
    }

    Node *lastLetterFound = root;
    int letterPos = 0;
    //see how many letters of the word already exist
    while (lastLetterFound->getchild((word[letterPos])) != nullptr) {
        suggestion += word[letterPos];
        lastLetterFound = lastLetterFound->getchild(word[letterPos++]);
    }

    string temp = suggestion;
    char c = 'a';
    while (c <= 'z') { //from 'a' -> 'z'
        if(lastLetterFound->getchild(c) != nullptr) {
            if(lastLetterFound->getchild(c)->isEndOfWord) {
                suggestion += c;
                suggestions[suggestionCount++] = suggestion;
            }
        }
        if (suggestionCount == 4) {
            return suggestions;
        }
        suggestion = temp;
        c++;
    }
    return suggestions;
}

void Trie::printTrie(const Node* node, string prefix) {
    if (node->isEndOfWord) {
        cout << prefix << node->letter << endl;
    }

    for (char index = 0; index < 26; ++index) {
        char next = node->letter;
        Node const* pChild = node->children[index];
        if (pChild) {
            prefix.push_back(next);
            printTrie(pChild, prefix);
            prefix.pop_back();
        }
    }
}