#pragma once
#include <iostream>
#include <vector>

class String {
    std::string value;

    static char invertLetterCase(
        const char &CHARACTER
    ) {
        return static_cast<char>(
            isupper(
                CHARACTER
            )
                ? tolower(
                    CHARACTER
                )
                : toupper(
                    CHARACTER
                )
        );
    }

    static char lowercaseLetter(
        const char &CHARACTER
    ) { return static_cast<char>(CHARACTER | 32); }

    static bool isVowel(
        const char CHARACTER
    ) {
        static const std::string VOWELS = "aeiouAEIOU";
        return VOWELS.find(
            CHARACTER
        ) != std::string::npos;
    }

public:
    String() {
        value = "";
    }

    void setValue(
        const std::string &VALUE
    ) { value = VALUE; }

    std::string getValue() {
        return value;
    }

    static size_t wordCount(
        const std::string &TEXT
    ) {
        size_t index = 0,
               counter = 0;
        while (TEXT[index]) {
            if (
                TEXT[index] != ' ' &&
                TEXT[index] != '\t' &&
                TEXT[index] != '\n' &&
                (
                    index == 0 ||
                    TEXT[index - 1] == ' ' ||
                    TEXT[index - 1] == '\t' ||
                    TEXT[index - 1] == '\n'
                )
            )
                counter++;
            index++;
        }
        return counter;
    }

    size_t wordCount() {
        return wordCount(
            value
        );
    }

    static std::string toUppercaseText(
        std::string &text
    ) {
        for (char &character : text)
            character = static_cast<char>(
                toupper(
                    character
                )
            );
        return text;
    }

    static std::string toLowercaseText(
        std::string &text
    ) {
        for (char &character : text)
            character = static_cast<char>(
                tolower(
                    character
                )
            );
        return text;
    }

    static std::string invertAllLetterCases(
        std::string text
    ) {
        for (char &character : text)
            character = invertLetterCase(
                character
            );
        return text;
    }

    static size_t capitalLetterCount(
        const std::string &TEXT
    ) {
        size_t counter = 0;
        for (const char &CHARACTER : TEXT)
            if (
                isupper(
                    CHARACTER
                )
            )
                counter++;
        return counter;
    }

    static size_t smallLetterCount(
        const std::string &TEXT
    ) {
        size_t counter = 0;
        for (const char &CHARACTER : TEXT)
            if (
                islower(
                    CHARACTER
                )
            )
                counter++;
        return counter;
    }

    static size_t targetLetterCount(
        const std::string &TEXT,
        const char &TARGET_CHARACTER,
        const bool &MATCH_CASE = true
    ) {
        size_t counter = 0;
        if (MATCH_CASE)
            for (const char &CHARACTER : TEXT)
                counter += CHARACTER == TARGET_CHARACTER;
        else
            for (const char &CHARACTER : TEXT)
                counter += lowercaseLetter(
                        CHARACTER
                    ) == lowercaseLetter(
                        TARGET_CHARACTER
                    ) &&
                    isalpha(
                        CHARACTER
                    );
        return counter;
    }

    static size_t countOfVowels(
        const std::string &TEXT
    ) {
        size_t counter = 0;
        for (const char &CHARACTER : TEXT)
            counter += isVowel(
                CHARACTER
            );
        return counter;
    }

    static size_t targetLetterCount(
        const std::string &TEXT,
        const char &TARGET_CHARACTER
    ) {
        size_t counter = 0;
        for (const char &CHARACTER : TEXT)
            if (CHARACTER == TARGET_CHARACTER)
                counter++;
        return counter;
    }

    static void splitText(
        std::string text,
        std::vector<std::string> &words,
        const std::string &DELIMITER
    ) {
        size_t position;
        while (
            (
                position = text.find(
                    DELIMITER
                )
            ) != std::string::npos
        ) {
            words.push_back(
                text.substr(
                    0,
                    position
                )
            );
            text.erase(
                0,
                position + DELIMITER.length()
            );
        }
        words.push_back(
            text
        );
    }

    static std::string trimLeft(
        const std::string &TEXT
    ) {
        auto start = TEXT.begin();
        const auto END = TEXT.end();

        while (
            start != END &&
            isspace(
                *start
            )
        )
            ++start;

        return {
            start,
            END + 1
        };
    }

    static std::string trimRight(
        const std::string &TEXT
    ) {
        const auto START = TEXT.begin();
        auto end = TEXT.end();

        do {
            --end;
        } while (
            end != START &&
            isspace(
                *end
            )
        );

        return {
            START,
            end + 1
        };
    }

    static std::string trim(
        const std::string &TEXT
    ) {
        auto start = TEXT.begin();
        auto end = TEXT.end();

        while (
            start != end &&
            isspace(
                *start
            )
        )
            ++start;

        do {
            --end;
        } while (
            end != start &&
            isspace(
                *end
            )
        );

        return {
            start,
            end + 1
        };
    }

    static std::string joinText(
        const std::vector<std::string> &WORDS,
        const std::string &DELIMITER
    ) {
        std::string text;
        for (const std::string &WORD : WORDS)
            text += WORD + DELIMITER;
        if (!WORDS.empty())
            text.erase(
                text.size() - DELIMITER.size()
            );
        return text;
    }

    static std::string reverseWordOrder(
        std::string text
    ) {
        std::vector<std::string> reversedText;
        const std::string &DELIMITER = " ";
        splitText(
            text,
            reversedText,
            DELIMITER
        );
        std::vector<std::string>::iterator iterator = reversedText.end();
        text.clear();
        while (iterator-- != reversedText.begin())
            text += *iterator + DELIMITER;
        if (!text.empty())
            text.erase(
                text.size() - DELIMITER.size()
            );
        return text;
    }

    static void replaceText(
        std::string &text,
        const std::string &TEXT_TO_REPLACE,
        const std::string &REPLACE_TEXT
    ) {
        size_t position = 0;
        while (
            (
                position = text.find(
                    TEXT_TO_REPLACE,
                    position
                )
            ) != std::string::npos
        ) {
            text.replace(
                position,
                TEXT_TO_REPLACE.length(),
                REPLACE_TEXT
            );
            position += REPLACE_TEXT.length();
        }
    }

    static void removeAllPunctuations(
        std::string &text
    ) {
        std::string textAfterRemoveAllPunctuations;
        for (const char &CHARACTER : text)
            if (
                !ispunct(
                    CHARACTER
                )
            )
                textAfterRemoveAllPunctuations += CHARACTER;
        text = textAfterRemoveAllPunctuations;
    }

    static void printWords(
        const std::vector<std::string> &WORDS
    ) {
        std::cout << "Words:" << std::endl;
        for (const std::string &WORD : WORDS)
            std::cout << WORD << std::endl;
    }

    static void printFirstCharacters(
        const std::string &TEXT
    ) {
        std::cout << "First Characters:" << std::endl;
        bool isStartOfWord = true;
        for (const char CHARACTER : TEXT) {
            if (
                isStartOfWord &&
                !isspace(
                    CHARACTER
                )
            ) {
                std::cout << CHARACTER << std::endl;
                isStartOfWord = false;
            }
            if (isspace(
                CHARACTER
            ))
                isStartOfWord = true;
        }
    }

    static void printFirstUppercaseLetters(
        const std::string &TEXT
    ) {
        std::cout << "First Uppercase Letters:" << std::endl;
        if (
            const size_t TEXT_LENGTH = TEXT.size();
            TEXT_LENGTH > 0
        ) {
            if (
                isupper(
                    TEXT[0]
                )
            )
                std::cout << TEXT[0] << std::endl;
            for (
                size_t firstLetterIndex = 0, secondLetterIndex = 1;
                secondLetterIndex < TEXT_LENGTH;
                ++firstLetterIndex, ++secondLetterIndex
            ) {
                const char FIRST_CHARACTER = TEXT[firstLetterIndex],
                           SECOND_CHARACTER = TEXT[secondLetterIndex];
                if (
                    isspace(
                        FIRST_CHARACTER
                    ) && isupper(
                        SECOND_CHARACTER
                    )
                )
                    std::cout << SECOND_CHARACTER << std::endl;
            }
        }
    }

    static void printFirstLowercaseLetters(
        const std::string &TEXT
    ) {
        std::cout << "First Lowercase Letters:" << std::endl;
        if (
            const size_t TEXT_LENGTH = TEXT.size();
            TEXT_LENGTH > 0
        ) {
            if (
                islower(
                    TEXT[0]
                )
            )
                std::cout << TEXT[0] << std::endl;
            for (
                size_t firstLetterIndex = 0, secondLetterIndex = 1;
                secondLetterIndex < TEXT_LENGTH;
                ++firstLetterIndex, ++secondLetterIndex
            ) {
                const char FIRST_CHARACTER = TEXT[firstLetterIndex],
                           SECOND_CHARACTER = TEXT[secondLetterIndex];
                if (
                    isspace(
                        FIRST_CHARACTER
                    ) && islower(
                        SECOND_CHARACTER
                    )
                )
                    std::cout << SECOND_CHARACTER << std::endl;
            }
        }
    }

    static void printVowelsInText(
        const std::string &TEXT
    ) {
        std::cout << "Vowels:" << std::endl;
        for (const char &CHARACTER : TEXT)
            if (
                isVowel(
                    CHARACTER
                )
            )
                std::cout << CHARACTER << std::endl;
    }

    static void printWords(
        const std::string &TEXT
    ) {
        std::cout << "Words:" << std::endl;
        size_t startPosition = 0,
               endPosition;
        while (
            (
                endPosition = TEXT.find(
                    ' ',
                    startPosition
                )
            ) != std::string::npos
        ) {
            std::cout << TEXT.substr(
                startPosition,
                endPosition - startPosition
            ) << std::endl;
            startPosition = endPosition + 1;
        }
        if (startPosition < TEXT.length())
            std::cout << TEXT.substr(
                startPosition
            ) << std::endl;
    }
};