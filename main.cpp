#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <unordered_map>

using namespace std;

void StartNewGame(vector<string> &words, string &currentWord, string &scrambledWord);
string ScrambleWord(const string &word);
void CustomShuffle(vector<string> &vec);
wchar_t ReplaceDiacritic(wchar_t ch);
wstring StripDiacritics(const wstring &input);
wstring ConvertToWideString(const string &input);

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(TEXT("Word Scramble"));

    vector<string> words = {
        "adiabatic", "aforism",
        "aleatoriu", "amnezic", "analogic",
        "pozitiv", "apropou",
        "arborescent", "archeologie", "astenic",
        "atotștiutor", "atriu", "avers", "axioma",
        "bacovian", "bântuitor", "bizar", "bravură",
        "cheltuitor",
        "chiriaș", "cibernetic", "clopotar", "cognitiv", "corespondent", "criptic",
        "cucernic", "cumulativ", "decadență", "decorativ", "denotativ",
        "derizoriu", "diabolic", "dialectic", "dicție", "diligență",
        "dogmă", "echivoc", "elucida", "empatic", "endemic", "enigmatic",
        "esoterism", "evaziv",
        "exoteric", "explicit", "falimentar", "fantomatic",
        "felonie", "fluvial", "fortuit",
        "galactic"
    };
    string currentWord, scrambledWord;
    char playAgain;

    do {
        StartNewGame(words, currentWord, scrambledWord);

        string guess;
        bool correct = false;
        int failures = 0;
        int maxFailures = 5;

        while (!correct && failures < maxFailures) {
            cout << "Scrambled Word: " << scrambledWord << endl;
            cout << "Enter your guess: ";
            cin >> guess;

            wstring wideGuess = ConvertToWideString(guess);
            wstring wideCurrentWord = ConvertToWideString(currentWord);

            if (StripDiacritics(wideGuess) == StripDiacritics(wideCurrentWord)) {
                cout << "Correct! The word was: " << currentWord << endl;
                correct = true;
            } else {
                failures++;
                cout << "Incorrect! Try again. Remaining attempts: " << (maxFailures - failures) << endl;
            }
        }

        if(failures < maxFailures) {
            cout << "Do you want to play again? (y/n): ";
            cin >> playAgain;
        } else {
            cout << "Game over. The word was: " << currentWord << endl;
            cout << "Do you want to play again? (y/n): ";
            cin >> playAgain;
        }


    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}

void StartNewGame(vector<string> &words, string &currentWord, string &scrambledWord) {
    srand(unsigned(time(0)));
    currentWord = words[rand() % words.size()];
    scrambledWord = ScrambleWord(currentWord);
}

string ScrambleWord(const string &word) {
    vector<string> utf8_chars;
    for (size_t i = 0; i < word.size(); ) {
            // 1 byte character
        if ((word[i] & 0x80) == 0) {
            utf8_chars.push_back(word.substr(i, 1));
            i += 1;
            // 2 byte character
        } else if ((word[i] & 0xE0) == 0xC0) {
            utf8_chars.push_back(word.substr(i, 2));
            i += 2;
            // 3 byte character
        } else if ((word[i] & 0xF0) == 0xE0) {
            utf8_chars.push_back(word.substr(i, 3));
            i += 3;
            // 4 byte character
        } else if ((word[i] & 0xF8) == 0xF0) {
            utf8_chars.push_back(word.substr(i, 4));
            i += 4;
        }
    }

    CustomShuffle(utf8_chars);

    string scrambled;
    for (const auto &ch : utf8_chars) {
        scrambled += ch;
    }
    return scrambled;
}

void CustomShuffle(vector<string> &vec) {
    srand(unsigned(time(0)));
    for (size_t i = vec.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}

wstring StripDiacritics(const wstring &input) {
    wstring output;
    for (wchar_t ch : input) {
        output += ReplaceDiacritic(ch);
    }
    return output;
}

wstring ConvertToWideString(const string &input) {
    return converter.from_bytes(input);
}

string ConvertToUtf8String(const wstring &input) {
    return converter.to_bytes(input);
}

wchar_t ReplaceDiacritic(wchar_t ch) {
    static unordered_map<wchar_t, wchar_t> diacriticMap = {
        {L'ă', L'a'}, {L'â', L'a'}, {L'î', L'i'}, {L'ș', L's'}, {L'ț', L't'},
        {L'Ă', L'A'}, {L'Â', L'A'}, {L'Î', L'I'}, {L'Ș', L'S'}, {L'Ț', L'T'}
    };

    auto it = diacriticMap.find(ch);
    if (it != diacriticMap.end()) {
        return it->second;
    }
    return ch;
}

string StripDiacritics(const string &input) {
    string output;
    for (char ch : input) {
        output += ReplaceDiacritic(ch);
    }
    return output;
}
