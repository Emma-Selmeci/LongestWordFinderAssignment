#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "woodpecker.hpp"
#include "szokereso.hpp"


std::vector<std::string> readFile(Szokereso &szokereso) {
    std::vector<std::string> v;
    std::ifstream inputFile("words_alpha.txt");
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        szokereso.insertWord(line);
        v.push_back(line);
    }
    inputFile.close();
    return v;
}

bool checkOnlyAllowedCharactersAreUsed(const std::string& candidate, std::string words) {
    for (char i : candidate) {
        auto location = std::find(words.begin(), words.end(), i);
        if (location == words.end()) return false;
        words.erase(location);
    }
    return true;
}

TEST("alpentuqp -> 8") {
    std::string letters = "alpentuqp";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 8);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("lmjdiniwlq -> 8") {
    std::string letters = "lmjdiniwlq";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 8);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("efycseicn -> 7") {
    std::string letters = "efycseicn";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 7);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("qnkqnkqnqkqnqnkqnkqnkkn -> no solution") {
    std::string letters = "qnkqnkqnqkqnqnkqnkqnkkn";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    CHECK_GE(result.length(), (size_t) 0);
    CHECK_GE(50000L*letters.size(), solutionTime);
}

TEST("erogleekddlawk -> 9") {
    std::string letters = "erogleekddlawk";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 9);
    CHECK_GE(50000L*letters.size(), solutionTime);
}

TEST("iavuinymtngiale -> 15") {
    std::string letters = "iavuinymtngiale";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 15);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("aamagrcilroyiucztuo -> 19") {
    std::string letters = "aamagrcilroyiucztuo";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 19);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("acgnnosniocmoesamntd -> 20") {
    std::string letters = "acgnnosniocmoesamntd";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 20);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("aabcdflegktmctoeigjy -> 12") {
    std::string letters = "aabcdflegktmctoeigjy";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 12);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("xabfftgthklmjfqetgkb -> 7") {
    std::string letters = "xabfftgthklmjfqetgkb";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 7);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
TEST("abcdefghijklmnopqrst -> 13") {
    std::string letters = "abcdefghijklmnopqrst";
    Szokereso szokereso = Szokereso();
    std::vector<std::string> raw = readFile(szokereso);
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = szokereso.play(letters);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned solutionTime = duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Your solution ran for " << solutionTime << "us and returned: " << result << "\n";
    auto wordCheck = std::find(raw.begin(), raw.end(), result);
    bool validWord = !(wordCheck == raw.end());
    CHECK_EQ(validWord, true); //Check if the word you returned is a valid word
    CHECK_EQ(checkOnlyAllowedCharactersAreUsed(result, letters),
             true); //Check if you used only the allowed characters
    CHECK_GE(result.length(), (size_t) 13);
    CHECK_GE(50000L*letters.size(), solutionTime);
}
WOODPECKER_TEST_MAIN()
