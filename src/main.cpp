#include "textgen.h"

int main() {
    ifstream file = ifstream("input.txt");
    TextGenerator gen = TextGenerator(file);
    string text = gen.Generate();
    cout << text;
}