// Copyright (c) 2026 Shkelev Egor

#include "textgen.h"
#include <random>
#include <string>
#include <iostream>

TextGenerator::TextGenerator() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cout << "Error: couldn't open the file :(";
        throw std::runtime_error("Cannot open file");
    }

    prefix pref;
    std::string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(file >> word)) {
            std::cout << "Error: file contains less than " << NPREF
                << " words :(";
            throw std::invalid_argument(
                "Error: file contains less than NPREF words :(");
        }
        pref.push_back(word);
    }

    firstPref = pref;

    while (file >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }

    file.close();
}

TextGenerator::TextGenerator(std::ifstream& file) {
    if (!file) {
        std::cout << "Error: couldn't open the file :(";
        throw std::runtime_error("Cannot open file");
    }

    prefix pref;
    std::string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(file >> word)) {
            std::cout << "Error: file contains less than " << NPREF
                << " words :(";
            throw std::invalid_argument(
                "Error: file contains less than NPREF words :(");
        }
        pref.push_back(word);
    }

    firstPref = pref;

    while (file >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }

    file.close();
}

TextGenerator::TextGenerator(std::string text) {
    std::istringstream iss(text);
    prefix pref;
    std::string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(iss >> word)) {
            std::cout << "Error: file contains less than " << NPREF
                << " words :(";
            throw std::invalid_argument(
                "Error: file contains less than NPREF words :(");
        }
        pref.push_back(word);
    }

    firstPref = pref;

    while (iss >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
}

std::string TextGenerator::Generate() {
    if (statetab.empty()) {
        return "";
    }

    static std::mt19937 gen(std::random_device{}());

    std::string result;
    prefix curr = firstPref;
    for (const auto& w : curr) {
        result += w + " ";
    }

    int wordCounter = curr.size();

    while (wordCounter < MAXGEN) {
        auto it = statetab.find(curr);
        if (it == statetab.end() || it->second.empty()) {
            break;
        }

        const auto& suffixes = it->second;
        std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
        int index = dist(gen);
        std::string nextWord = suffixes[index];

        result += nextWord + " ";
        curr.pop_front();
        curr.push_back(nextWord);
        wordCounter++;
    }

    std::ofstream out("output.txt");
    if (!out) {
        std::cout << "Error: creating output.txt :(\n";
        return result;
    }
    out << result;
    out.close();

    return result;
}
