// Copyright (c) 2026 Shekelev Egor

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <sstream>

typedef std::deque<std::string> prefix;

class TextGenerator {
 public:
    const int NPREF = 2;
    const int MAXGEN = 1000;

    const std::map<prefix, std::vector<std::string>>& getStateTable() {
        return statetab;
    }
    const prefix& getFirstPrefix() { return firstPref; }

    TextGenerator();
    explicit TextGenerator(std::ifstream& file);
    explicit TextGenerator(std::string text);
    std::string Generate();

 private:
    std::map<prefix, std::vector<std::string>> statetab;
    prefix firstPref;
};
