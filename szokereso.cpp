#include "szokereso.hpp"

#include <stdexcept>
#include <algorithm>

const unsigned char Szokereso::FREQUENCY_TO_CHAR[] = {"eariotnslcudpmhgbfywkvxzjq"};
bool Szokereso::isCharBankInitialized = false;
int Szokereso::CHAR_TO_FREQUENCY[];

Szokereso::Node *Szokereso::Node::addChar(unsigned char c) {
    //std::cout << "Adding char " << c << " with frequency " << CHAR_TO_FREQUENCY[c] << '\n';
    int letterFrequency = CHAR_TO_FREQUENCY[c];
    //std::cout << "Current number of children " << numOfChildren << '\n';
    if(numOfChildren <= letterFrequency) { //Our Node* array is not yet long enough to have this child -> we create a new, longer array and copy the content (like a vector does)
        //std::cout << "Insufficient array size, creating new array\n";
        Node** newArray = new Node*[letterFrequency+1];
        for(int i = 0; i < numOfChildren; ++i) {
            newArray[i] = children[i];
        }
        if(numOfChildren != 0) {
            delete[] children; //We don't delete an array of size 0 (which would be garbage)
            //std::cout << "Deleting old array\n";
        }

        //std::cout << "Populating new array with nullptrs\n";
        for(int i = numOfChildren; i < letterFrequency+1; ++i) { //Populating the array with nullptrs to know that these are dead ends (that might later be refreshed)
            newArray[i] = nullptr;
        }

        children = newArray;
        numOfChildren = letterFrequency+1;

        children[letterFrequency] = new Node(); //Creating the Node for the new letter being inserted
    } else {
        if(children[letterFrequency] == nullptr) children[letterFrequency] = new Node();
    }
    return children[letterFrequency];
}


Szokereso::Szokereso() {
    //We waste some space here but as a result, we can get the letter's frequency with a single indexing. The space wasted is well-worth the cost of the substraction in my opinion
    if(isCharBankInitialized) return;
    for(int i = 0; i < NUMBER_OF_LETTERS_IN_THE_ENGLISH_ALPHABET; ++i) {
        CHAR_TO_FREQUENCY[FREQUENCY_TO_CHAR[i]] = i;
    }
    isCharBankInitialized = true;
}

void Szokereso::insertWord(std::string word) {
    //std::cout << "Inserting word : " << word << '\n';
    if(isWordBankInitialized) throw std::runtime_error("InsertWord() can't be called on the same object after play()"); //No new words should be inserted after the char tree is finalized
    if(word.size() == 0) throw std::invalid_argument("Word of size 0 added"); //We don't want any size 0 words
    Node* n = head;
    for(size_t i = 0; i < word.size(); ++i) {
        n = n->addChar(word[i]);
    }
    //We should have arrived at the last Node in our chain
    n->canEnd = true;
}

//Recursively determining the longest word possible from each node of the tree
//Basically for each node, we get the size of the largest subtree under it
int Szokereso::Node::setLength(int size) {
    wordSize = size;
    ++size;
    for(int i = 0; i < numOfChildren; ++i) {
        if(children[i] == nullptr) continue;
        int getAndSetLength = children[i]->setLength(size);
        if(getAndSetLength > wordSize) wordSize = getAndSetLength;
    }
    return wordSize;
}

std::string Szokereso::play(std::string characters){
    if(!isWordBankInitialized) {
        recordWordSize = head->setLength(0); //We also get the value of the longest possible string - we stop searching if we hit this value (this should be 31)
        isWordBankInitialized = true;
    }
    std::sort(characters.begin(), characters.end(),
        [](unsigned char c1, unsigned char c2) {
            return CHAR_TO_FREQUENCY[c1] < CHAR_TO_FREQUENCY[c2];
        }
    ); //We sort the letters in our searchphrase by frequency

    return "";
}

char Szokereso::search(Szokereso::Node* n) {

}