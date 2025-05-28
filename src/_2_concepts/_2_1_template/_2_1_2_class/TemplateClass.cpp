#include<iostream>
using namespace std;

template <typename type>
class Calculator {
    enum Operator {
        Add = '+',
        Subtract = '-',
        Multiply = '*',
        Divide = '/',
        Clear = ' '
    };

    type lastValue = 0;
    Operator lastOperator = Clear;
    type lastResult = 0;
    type result = 0;

    static string checkOperator(
        const Operator &OPERATOR
    ) {
        switch (OPERATOR) {
        case Add:
            return "adding";
        case Subtract:
            return "subtracting";
        case Multiply:
            return "multiplying";
        case Divide:
            return "dividing";
        case Clear:
            return "clearing";
        default:
            return "";
        }
    }

public:
    void add(
        const type &VALUE
    ) {
        lastOperator = Add;
        lastValue = VALUE;
        lastResult = result;
        result += VALUE;
    }

    void subtract(
        const type &VALUE
    ) {
        lastOperator = Subtract;
        lastValue = VALUE;
        lastResult = result;
        result -= VALUE;
    }

    void multiply(
        const type &VALUE
    ) {
        lastOperator = Multiply;
        lastValue = VALUE;
        lastResult = result;
        result *= VALUE;
    }

    void divide(
        const type &VALUE
    ) {
        if (VALUE != 0)
            result /= VALUE;
        lastOperator = Divide;
        lastValue = VALUE;
        lastResult = result;
    }

    void clear() {
        lastValue = 0;
        lastOperator = Clear;
        result = 0;
    }

    void printResult() {
        cout << lastResult << " after " << checkOperator(
            lastOperator
        );

        if (lastOperator != Clear)
            cout << ' ' << lastValue;

        cout << " = " << to_string(
            result
        );

        if (
            lastOperator == Divide &&
            lastValue == 0
        )
            cout << ", Can't be divided by zero";

        cout << endl;
    }
};

int main() {
    Calculator<short> calculator;

    calculator.add(
        10
    );
    calculator.printResult();

    calculator.add(
        100
    );
    calculator.printResult();

    calculator.subtract(
        20
    );
    calculator.printResult();

    calculator.divide(
        0
    );
    calculator.printResult();

    calculator.divide(
        2
    );
    calculator.printResult();

    calculator.multiply(
        3
    );
    calculator.printResult();

    calculator.clear();
    calculator.printResult();
}