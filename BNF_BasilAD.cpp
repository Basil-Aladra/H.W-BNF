#include <iostream>
using namespace std;
// lexical analysis program . BASIL ADRA
char input[100];  
int pos = 0;

void advance() {
    pos++;
}

char current_char() {
    return input[pos];
}

void skip_whitespace() {
    while (current_char() == ' ') {
        advance();
    }
}

int number() {
    int result = 0;
    while (current_char() >= '0' && current_char() <= '9') {
        result = result * 10 + (current_char() - '0');
        advance();
    }
    return result;
}

int base();
int factor();
int term();
int expr();

int power_manual(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int power() {
    int result = base();
    
    if (current_char() == '^') {
        advance();
        int exp = factor();
        result = power_manual(result, exp);  
    }

    return result;
}

int base() {
    int result;
    skip_whitespace();

    if (current_char() >= '0' && current_char() <= '9') {
        result = number();
    } else if (current_char() == '(') {
        advance();  
        result = expr();
        advance();  
    } else {
        cout << "Error: Unexpected token in base: " << current_char() << endl;
        exit(1);
    }

    return result;
}

int factor() {
    return power();
}

int term() {
    int result = factor();

    while (current_char() == '*' || current_char() == '/') {
        if (current_char() == '*') {
            advance();
            result *= factor();
        } else if (current_char() == '/') {
            advance();
            int divisor = factor();
            if (divisor == 0) {
                cout << "Error: Division by zero" << endl;
                exit(1);
            }
            result /= divisor;
        }
    }

    return result;
}

int expr() {
    int result = term();

    while (current_char() == '+' || current_char() == '-') {
        if (current_char() == '+') {
            advance();
            result += term();
        } else if (current_char() == '-') {
            advance();
            result -= term();
        }
    }

    return result;
}

int main() {
    int choice;
    cout << "Menu:\n";
    cout << "1. BNF for Code\n";
    cout << "2. Enter an expression to evaluate\n";
    cout << "Enter your choice - 1 or 2 -: ";
    cin >> choice;

    if (choice == 1) {
       cout << "<expr> ? <term> {(+ | -) <term>}\n"
            "<term> ? <factor> {(* | /) <factor>}\n"
            "<factor> ? <power>\n"
            "<power> ? <base> {^ <factor>}\n" 
            "<base> ? id | int_constant | (<expr>)\n";
        
        
    } else if (choice == 2) {
        cout << "Enter an arithmetic expression: ";
        cin.ignore();  
        cin.getline(input, 100);  

        pos = 0;

        int result = expr();
        cout << "Result: " << result << endl;
    } else {
        cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}
