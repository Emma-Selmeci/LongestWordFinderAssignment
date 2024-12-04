#ifndef SZOKERESO_HPP
#define SZOKERESO_HPP

#include <string>

/*
 * The class stores the input words in alphabetical order, getting an ordered set of characters
 * These characters are stored in alphabetical order in a tree where each route from node to leaf represents a word
 * We can quickly find the longest possible solution if we order our query set in alphabetical order as well
 * There are some extra optimisations such as a dynamic number of children and saving the longest possible route from each Node
 * This last optimisation makes it so that words cannot be inserted after calling play() for the first time
 *
 * I don't know much about threads but play() is definitely not Thread-safe, as static members of Node are used
 */

class Szokereso{
    bool isInitialized = false;

    class Node {
    public:
        int numOfChildren = 0;
        unsigned int wordSize = 0; //The longest possible word down the tree
        std::string innerString; //Should have size 0 by default, this indicates that the this Node is not the end of any word
        Node** children;
        Node* addChar(int offset); //Method used to add a new child to the tree or return an existing one
        unsigned int setLength(int);
        bool search(char, int);
        ~Node() {
            //My first programming war crime - deleting children
            if(numOfChildren == 0) return; //We don't delete garbage
            for(int i = 0; i < numOfChildren; ++i) {
                if(children[i] != nullptr) delete children[i];
            }
            delete[] children;
        }

        static std::string searchPhrase; //The character set that we're using as a query
        static unsigned int currentMax; //The longest word we've yet found
        static Node* nodeMax; //The Node corresponding to the longest word
    };

    Node* head = new Node{};
public:
    Szokereso() = default;
    ~Szokereso(){
        delete head;
    }

    //No shallow copy allowed!
    Szokereso(const Szokereso& other) = delete;
    Szokereso operator=(const Szokereso& other) = delete;

    void insertWord(std::string word);
    std::string play(std::string characters);

};



#endif //SZOKERESO_HPP