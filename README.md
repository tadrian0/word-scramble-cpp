# Word Scramble Game

## Overview
Word Scramble is a simple console-based game written in C++. The objective of the game is to guess the original word from a scrambled version of it. The game includes a list of Romanian words, and it also strips diacritics from the words to allow for easier comparison.

## Features
- Random selection of words from a predefined list.
- Scrambling of selected words.
- User input for guessing the original word.
- Strips diacritics from Romanian words for comparison.
- UTF-8 encoding support for proper display of Romanian characters.
- Multiple attempts for guessing the word.

## Requirements
- A C++ compiler for Windows (e.g., MinGW, Visual Studio)
- C++11 or later

## Installation
1. **Install MinGW**: Download and install MinGW from [MinGW official website](https://www.mingw-w64.org/).

1. Clone the repository:
    ```sh
    git clone https://github.com/tadrian0/word-scramble-cpp.git
    cd word-scramble-cpp
    ```

2. Compile the program:
    ```sh
    g++ -o main main.cpp
    ```

3. Run the program:
    ```sh
    WordScramble.exe
    ```

## Usage
1. The game will display a scrambled word.
2. Enter your guess for the original word.
3. If your guess is correct, the game will congratulate you.
4. If your guess is incorrect, the game will prompt you to try again, showing the remaining attempts.
5. After five incorrect attempts, the game will reveal the correct word.
6. You can choose to play again or exit the game.

## Code Explanation
- `ReplaceDiacritic`: This function replaces Romanian diacritic characters with their non-diacritic equivalents.
- `StripDiacritics`: This function strips diacritics from a wide string using the `ReplaceDiacritic` function.
- `ConvertToWideString` and `ConvertToUtf8String`: These functions convert between UTF-8 and wide strings.
- The `main` function initializes the game, handles user input, and compares stripped versions of the guess and the original word.
