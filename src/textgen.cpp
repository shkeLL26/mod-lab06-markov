#include "textgen.h"

TextGenerator::TextGenerator() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Error: couldn`t open the file :(";
        throw runtime_error("Cannot open file");
    }

    prefix pref;
    string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(file >> word)) {
            cout << "Error: file contains less then " << NPREF << " words :(";
            throw invalid_argument("Error: file contains less then NPREF words :(");
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

TextGenerator::TextGenerator(ifstream& file) {
    if (!file) {
        cout << "Error: couldn`t open the file :(";
        throw runtime_error("Cannot open file");
    }

    prefix pref;
    string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(file >> word)) {
            cout << "Error: file contains less then " << NPREF << " words :(";
            throw invalid_argument("Error: file contains less then NPREF words :(");
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

TextGenerator::TextGenerator(string text) {
    istringstream iss(text);
    prefix pref;
    string word;

    for (int i = 0; i < NPREF; ++i) {
        if (!(iss >> word)) {
            cout << "Error: file contains less then " << NPREF << " words :(";
            throw invalid_argument("Error: file contains less then NPREF words :(");
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

string TextGenerator::Generate() {
    if (statetab.empty()) {
        return "";
    }

    srand(time(nullptr));

    string result;
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
        int index = rand() % suffixes.size();
        string nextWord = suffixes[index];

        result += nextWord + " ";
        curr.pop_front();
        curr.push_back(nextWord);
        wordCounter++;
    }

    ofstream out("output.txt");
    if (!out) {
        std::cout << "Error: creating output.txt :(\n";
        return result;
    }
    out << result;
    out.close();

    return result;
}