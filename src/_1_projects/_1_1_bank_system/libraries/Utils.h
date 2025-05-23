#pragma once
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Utils {
public:
    static void activeRandom() {
        srand(
            static_cast<unsigned>(
                time(
                    nullptr
                )
            )
        );
    }

    static void swapValues(
        short &firstValue,
        short &secondValue
    ) {
        firstValue = static_cast<short>(firstValue + secondValue);
        secondValue = static_cast<short>(firstValue - secondValue);
        firstValue = static_cast<short>(firstValue - secondValue);
    }

    static void swapValues(
        int &firstValue,
        int &secondValue
    ) {
        firstValue += secondValue;
        secondValue = firstValue - secondValue;
        firstValue -= secondValue;
    }

    static void swapValues(
        float &firstValue,
        float &secondValue
    ) {
        firstValue += secondValue;
        secondValue = firstValue - secondValue;
        firstValue -= secondValue;
    }

    static void swapValues(
        double &firstValue,
        double &secondValue
    ) {
        firstValue += secondValue;
        secondValue = firstValue - secondValue;
        firstValue -= secondValue;
    }

    static void swapValues(
        long double &firstValue,
        long double &secondValue
    ) {
        firstValue += secondValue;
        secondValue = firstValue - secondValue;
        firstValue -= secondValue;
    }

    static void swapValues(
        char &firstValue,
        char &secondValue
    ) {
        const char TEMPORARY_VALUE = firstValue;
        firstValue = secondValue;
        secondValue = TEMPORARY_VALUE;
    }

    static void swapValues(
        string &firstValue,
        string &secondValue
    ) {
        const string TEMPORARY_VALUE = firstValue;
        firstValue = secondValue;
        secondValue = TEMPORARY_VALUE;
    }

    static void swapValues(
        bool &firstValue,
        bool &secondValue
    ) {
        const bool TEMPORARY_VALUE = firstValue;
        firstValue = secondValue;
        secondValue = TEMPORARY_VALUE;
    }

    static short randomNumber(
        const short FROM,
        const short TO
    ) { return rand() % (TO - FROM + 1) + FROM; }

    static int randomNumber(
        const int FROM,
        const int TO
    ) { return rand() % (TO - FROM + 1) + FROM; }

    static float randomNumber(
        const float FROM,
        const float TO
    ) {
        return FROM + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (TO - FROM);
    }

    static double randomNumber(
        const double FROM,
        const double TO
    ) {
        return FROM + static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (TO - FROM);
    }

    static long double randomNumber(
        const long double FROM,
        const long double TO
    ) {
        return FROM + static_cast<long double>(rand()) / static_cast<long double>(RAND_MAX) * (TO - FROM);
    }

    static char randomLetter() {
        const int RANDOM_NUMBER = randomNumber(
            0,
            51
        );
        return static_cast<char>(
            RANDOM_NUMBER < 26
                ? 'A' + RANDOM_NUMBER
                : 'a' + (RANDOM_NUMBER - 26)
        );
    }

    static string randomText(
        size_t length
    ) {
        string text;
        while (length--)
            text += randomLetter();
        return text;
    }

    static void fillRandomNumbers(
        short numbers[],
        int numberCount,
        const short &FROM,
        const short &TO
    ) {
        while (numberCount--)
            numbers[numberCount] = randomNumber(
                FROM,
                TO
            );
    }

    static void fillRandomNumbers(
        int numbers[],
        int numberCount,
        const int &FROM,
        const int &TO
    ) {
        while (numberCount--)
            numbers[numberCount] = randomNumber(
                FROM,
                TO
            );
    }

    static void fillRandomNumbers(
        float numbers[],
        int numberCount,
        const float &FROM,
        const float &TO
    ) {
        while (numberCount--)
            numbers[numberCount] = randomNumber(
                FROM,
                TO
            );
    }

    static void fillRandomNumbers(
        double numbers[],
        int numberCount,
        const double &FROM,
        const double &TO
    ) {
        while (numberCount--)
            numbers[numberCount] = randomNumber(
                FROM,
                TO
            );
    }

    static void fillRandomNumbers(
        long double numbers[],
        int numberCount,
        const long double &FROM,
        const long double &TO
    ) {
        while (numberCount--)
            numbers[numberCount] = randomNumber(
                FROM,
                TO
            );
    }

    static void fillRandomLetters(
        char letters[],
        int numberCount
    ) {
        while (numberCount--)
            letters[numberCount] = randomLetter();
    }

    static void fillRandomTexts(
        string texts[],
        int numberCount,
        const size_t TEXT_LENGTH
    ) {
        while (numberCount--)
            texts[numberCount] = randomText(
                TEXT_LENGTH
            );
    }

    static string encryptText(
        string text,
        const short ENCRYPTION_KEY
    ) {
        for (int index = 0; index < text.length(); ++index)
            text[index] = static_cast<char>(static_cast<int>(text[index]) + ENCRYPTION_KEY);
        return text;
    }

    static string decryptText(
        string text,
        const short ENCRYPTION_KEY
    ) {
        for (int index = 0; index < text.length(); ++index)
            text[index] = static_cast<char>(static_cast<int>(text[index]) - ENCRYPTION_KEY);
        return text;
    }

    static string generateKey() {
        return randomText(
                4
            ) + '-' +
            randomText(
                4
            ) + '-' +
            randomText(
                4
            ) + '-' +
            randomText(
                4
            );
    }

    static void generateKeys(
        string keys[],
        int keyCount
    ) {
        while (keyCount--)
            keys[keyCount] = generateKey();
    }

    static void shuffleValues(
        short values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        int values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        float values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        double values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        long double values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        char values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        string values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static void shuffleValues(
        bool values[],
        const int NUMBER_COUNT
    ) {
        for (int counter = 0; counter < NUMBER_COUNT; counter++) {
            const int FIRST_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1,
                      SECOND_INDEX = randomNumber(
                          1,
                          NUMBER_COUNT
                      ) - 1;
            swapValues(
                values[FIRST_INDEX],
                values[SECOND_INDEX]
            );
        }
    }

    static string tab(
        short tabCount
    ) {
        string tabs;
        while (tabCount--)
            tabs += '\t';
        return tabs;
    }

    static void displayMenu(
        const string &TITLE,
        const short &COUNT_OF_LINES,
        const string LINES[]
    ) {
        cout << "~{ " << TITLE << " }~" << endl;
        for (short index = 0; index < COUNT_OF_LINES; ++index)
            cout << (index + 1) << " - " << LINES[index] << endl;
    }

    static void displayMessage(
        const string &MESSAGE
    ) {
        cout << MESSAGE << endl;
    }

    static void displayNote(
        const string &MESSAGE
    ) {
        cout << "~ " << MESSAGE << endl;
    }

    static void displayMessage(
        const string &MESSAGE,
        const short &LENGTH
    ) {
        cout << setw(
            LENGTH
        ) << MESSAGE << "|";
    }

    static void displayMessage(
        const bool &STATUS,
        const short &LENGTH
    ) {
        cout << setw(
            LENGTH
        ) << boolalpha << STATUS << "|";
    }

    static void displayLine(
        const char &CHARACTER,
        const short &COUNT
    ) {
        cout << string(
            COUNT,
            CHARACTER
        ) << endl;
    }
};