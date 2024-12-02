#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

double extractNumeric(const std::string &input) {
    bool hasSign = false, hasDecimal = false;
    int decimalPos = -1;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (i == 0 && (c == '+' || c == '-')) {
            hasSign = true;
        } else if (c == '.') {
            if (hasDecimal) return -999999.99; // more than one decimal point
            hasDecimal = true;
            decimalPos = i;
        } else if (!isdigit(c)) {
            return -999999.99; // invalid
        }
    }

    if (input.empty() || (hasSign && input.size() == 1)) return -999999.99;

    // convert to double
    try {
        double value = 0.0;
        size_t start = hasSign ? 1 : 0;
        for (size_t i = start; i < input.size(); ++i) {
            if (input[i] == '.') break;
            value = value * 10 + (input[i] - '0');
        }
        if (hasDecimal) {
            double fractional = 0.0, divisor = 10.0;
            for (size_t i = decimalPos + 1; i < input.size(); ++i) {
                fractional += (input[i] - '0') / divisor;
                divisor *= 10.0;
            }
            value += fractional;
        }
        return input[0] == '-' ? -value : value;
    } catch (...) {
        return -999999.99;
    }
}

int main() {
    std::string input;
    while (true) {
        std::cout << "Enter a string (or 'END' to quit): ";
        std::getline(std::cin, input);
        if (input == "END") break;
        double result = extractNumeric(input);
        if (result == -999999.99) {
            std::cout << "The input is invalid.\n";
        } else {
            std::cout << "The input is: " << std::fixed << std::setprecision(4) << result << "\n";
        }
    }
    return 0;
}
