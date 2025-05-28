#include<iostream>
using namespace std;

template <typename type>
void swapValues(
    type &firstValue,
    type &secondValue
) {
    type temporaryValue = firstValue;
    firstValue = secondValue;
    secondValue = temporaryValue;
}

void printValues(
    const string &VALUES_TITLE,
    const string &FIRST_VALUE,
    const string &SECOND_VALUE
) {
    cout << VALUES_TITLE << endl;
    cout << "First Value: " << FIRST_VALUE << endl;
    cout << "Second Value: " << SECOND_VALUE << endl << endl;
}

int main() {
    string firstValue = "Aa";
    string secondValue = "Mm";

    printValues(
        "Before Swap",
        firstValue,
        secondValue
    );

    swapValues(
        firstValue,
        secondValue
    );

    printValues(
        "After Swap",
        firstValue,
        secondValue
    );
}