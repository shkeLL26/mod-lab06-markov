// Copyright (c) 2026 Shkelev Egor

#include <iostream>
#include <string>
#include "textgen.h"

int main() {
    std::ifstream file = std::ifstream("input.txt");
    TextGenerator gen = TextGenerator(file);
    std::string text = gen.Generate();
    std::cout << text;
}
