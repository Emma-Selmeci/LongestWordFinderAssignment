#include "szokereso.hpp"

#include <algorithm>
#include <stdexcept>

std::string Szokereso::Node::searchPhrase; //The character set that we're using as a query
unsigned int Szokereso::Node::currentMax; //The longest word we've yet found
Szokereso::Node* Szokereso::Node::nodeMax; //The Node corresponding to the longest word

//offset is the number of the child that represents the character we're trying to add
//For a Node that represents 'b', adding a Node representing 'd' would mean an offset of 2
//Each Node can only have children that are equal or greater than them in terms of character representation
Szokereso::Node* Szokereso::Node::addChar(int offset) {

    if(numOfChildren <= offset) { //Oh, we don't even have enough children in our array!
        //Make a new, larger array, copy and insert
        //Yes, we could use a vector, but it would have a bit of memory/processing overhead ;)
        Node** newArray = new Node*[offset+1];
        for(int i = 0; i < numOfChildren; ++i) {
            newArray[i] = children[i];
        }
        if(numOfChildren != 0) {
            delete[] children; //We don't delete an array of size 0 (which would be garbage)
        }

        for(int i = numOfChildren; i < offset+1; ++i) { //Populating the array with nullptrs to know that these are dead ends (that might later be refreshed)
            newArray[i] = nullptr;
        }

        children = newArray;
        numOfChildren = offset+1;

        children[offset] = new Node(); //Creating the Node for the new letter being inserted

    } else {
        //Making a new Node if we don't have one on that particular place
        if(children[offset] == nullptr) children[offset] = new Node();
    }
    return children[offset];
}

//Recursively determining the longest word possible from each node of the tree
//Basically for each node, we get the size of the largest subtree under it
unsigned int Szokereso::Node::setLength(int size) {
    wordSize = size;
    ++size;
    for(int i = 0; i < numOfChildren; ++i) {
        if(children[i] == nullptr) continue;
        unsigned int getAndSetLength = children[i]->setLength(size);
        if(getAndSetLength > wordSize) wordSize = getAndSetLength;
    }
    return wordSize;
}

//This should handle empty strings as well
void Szokereso::insertWord(std::string word) {
    if(isInitialized) throw std::runtime_error("InsertWord() can't be called on the same object after play()"); //No new words should be inserted after the char tree is finalized
    std::string sorted = word;
    //Using a lambda to sort a copy of word
    std::sort(sorted.begin(), sorted.end(),
        [](unsigned char c1, unsigned char c2) {
            return c1 < c2;
        }
    );

    Node* n = head;
    char c = 'a'; //We pretend head represents an 'a' so that math works out
    for(size_t i = 0; i < word.size(); ++i) {
        n = n->addChar(sorted[i]-c);
        c = sorted[i];
    }
    //We should have arrived at the last Node in our chain
    if(n->innerString.size() == 0) n->innerString = word; //Overwriting wouldn't be a problem, but it would waste some performance

}

//I'm very proud of how this method has turned out :)
//It has many optimizations, working especially quickly with small and general searchphrases, and slowly with long searchphrases with no matches
//Returns bool so that we can eliminate some redundant checks
bool Szokereso::Node::search(char c, int num) {
    bool result = false;
    //We iterate through the remainder of the searchphrase from where we are currently (which is num)
    for(size_t i = num; i < searchPhrase.size(); ) {
        int offset = searchPhrase[i]-c;
        if(offset >= numOfChildren) break; //We don't have a child for this letter, we break
        int searchChar = searchPhrase[i];
        if(children[offset] != nullptr && children[offset]->wordSize > currentMax) { //We optimize by not checking nodes with short possible routes
            if(children[offset]->search(searchChar,i+1)) {
                if(currentMax >= wordSize || currentMax == searchPhrase.size()) return true; //Optimizations go brrrr - we return to a level up if this level cannot yield longer words
                //We also return if we've found a word of equal length to our searchphrase - shortcircuiting comes handy
                result = true;
            }
        }

        //We have to make sure we won't search for the same character twice
        char last = searchPhrase[i];
        do {
            ++i;
        } while(last == searchPhrase[i]); //Actually using a do/while loop!
    }

    //If we haven't found a long enough substring in the children, we return this (which would be an empty string if nothing can be found)
    if(innerString.size() != 0 && innerString.size() > currentMax) {
        currentMax = innerString.size();
        nodeMax = this;
        result = true;
    }
    return result;
}

std::string Szokereso::play(std::string characters){
    if(characters.size() == 0) return ""; //This is not a trick to get around that one test, it is needed to so that less calls of search() are made
    if(!isInitialized) {
        head->setLength(0); //We also get the value of the longest possible string - we stop searching if we hit this value (this should be 31)
        isInitialized = true;
    }

    std::sort(characters.begin(), characters.end(),
        [](unsigned char c1, unsigned char c2) {
            return c1 < c2;
        });

    Node::searchPhrase = characters;
    Node::currentMax = 0; //The longest word we've found yet
    Node::nodeMax = head; //This line might be unnecessary, I should check this later

    head->search('a',0); //We pretend that we've called search from char 'a'

    return Node::nodeMax->innerString;
}