#ifndef SZOKERESO_HPP
#define SZOKERESO_HPP

#include <string>
#include <iostream>

/* I have to say that I'd use a different design pattern if given the chance - maybe a sort of factory that takes words and returns the object after finalization
 * This class is finalized when play() is called for the first time - words cannot be inserted into the word-bank after that point
 * The words are stored in a character-tree but not in alphabetical order but by the frequency of the letters
 */

class Szokereso {
    //I'm storing the letters by frequency to save on memory and hopefully speed as well
    //The fastest approach would use some formula to calculate the letters which are most likely to be parts of long words
    const static unsigned char FREQUENCY_TO_CHAR[]; //Stores letters by frequency https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
    static int CHAR_TO_FREQUENCY[0x7b]; //Same but the inverse - more explanation at population
    const static int NUMBER_OF_LETTERS_IN_THE_ENGLISH_ALPHABET = 26;

    static bool isCharBankInitialized;
    bool isWordBankInitialized = false;
    int recordWordSize;

    class Node {
    public:
        bool canEnd = false; //Tells if this node is the end of a particular word or not
        Node** children;
        int numOfChildren = 0; //We dynamically allocate children Node*s to save on performance. Node*s are ordered by frequency so this hopefully results in as few redundant Node*s as possible
        int wordSize;
        ~Node() {
            //My first programming warcrime - deleting children
            for(int i = 0; i < numOfChildren; ++i) {
                if(children[i] != nullptr) delete children[i];
            }
            if(numOfChildren != 0) delete[] children; //We don't delete garbage
        }
        Node* addChar(unsigned char); //This function increases the size of the array if needed and returns the pointer to the corresponding child
        int setLength(int);
    };

    Node* head = new Node();

    char search(Node*);

public:
    Szokereso();

    void insertWord(std::string word);

    std::string play(std::string characters);

    ~Szokereso(){
        delete head;
    }
};

#endif //SZOKERESO_HPP