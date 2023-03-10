#include <iostream>
#include "Stack.h"
#include "LimitedStack.h"
#include "Queue.h"
#include "LimitedQueue.h"

bool checkBalanceBrackets(const char* string, const int maxDeep);

int main() {
    size_t lenght = 0;
    
    std::cout << "Enter the size of a stack: ";
    std::cin >> lenght;

    LimitedStack<int> stack(lenght);
    
    char answer = 'Y';
    while (answer != 'q' && answer != 'Q') {
        std::cout << "What do you want to do with the stack? (P - push / G - get / Q - quit): ";
        std::cin >> answer;

        if (answer == 'G' || answer == 'g') {
            try {
                std::cout << "Taken: " << stack.pop() << std::endl;
            }
            catch (const LimitedStack<int>::StackUnderflow& e) {
                std::cerr << "Error: " << e.getMessage() << "\n";
                return 1;
            }
        }
        else if (answer == 'P' || answer == 'p') {
            try {
                std::cout << "How many elements do you want to push: ";
                int j = 0;
                std::cin >> j;
                for (int i = 0; i < j; i++) {
                    int element;
                    std::cin >> element;
                    stack.push(element);
                }
            }
            catch (const LimitedStack<int>::StackOverflow& e) {
                std::cerr << "Error: " << e.getMessage() << "\n";
                return 1;
            }
        }
        else if (answer == 'Q' || answer == 'q') { std::cout << "Ok. End of the test... " << std::endl; }
        else { std::cout << "Unknown character!" << std::endl; }
    }
    
    std::cout << std::endl << "BRACKETS CHECK" << std::endl;

    char* string = new char[100];

    while (true) {
        std::cout << "Enter the string (Q to quit): ";
        std::cin >> string;

        if (*string == 'q' || *string == 'Q')
            break;
        
        bool result = checkBalanceBrackets(string, 10);

        if (result) {
            std::cout << "The brackets are correct" << std::endl;
        }
        else {
            std::cout << "The brackets are wrong" << std::endl;
        }
    }

    size_t qlenght = 0;

    std::cout << std::endl << "Enter the size of a queue: ";
    std::cin >> qlenght;

    LimitedQueue<int> queue(qlenght);
    
    answer = 'Y';
    while (answer != 'q' && answer != 'Q') {
        std::cout << "What do you want to do with the queue? (A - add / G - get / Q - quit): ";
        std::cin >> answer;

        if (answer == 'G' || answer == 'g') {
            try {
                std::cout << "Taken: " << queue.deQueue() << std::endl;
            }
            catch (const LimitedQueue<int>::QueueUnderflow& e) {
                std::cerr << "Error: " << e.getMessage() << "\n";
                return 1;
            }
        }
        else if (answer == 'A' || answer == 'a') {
            try {
                std::cout << "How many elements do you want to add: ";
                int j = 0;
                std::cin >> j;
                for (int i = 0; i < j; i++) {
                    int element;
                    std::cin >> element;
                    queue.enQueue(element);
                }
            }
            catch (const LimitedQueue<int>::QueueOverflow& e) {
                std::cerr << "Error: " << e.getMessage() << "\n";
                return 1;
            }
        }
        else if (answer == 'Q' || answer == 'q') { std::cout << "Ok. End of the test... " << std::endl; }
        else { std::cout << "Unknown character!" << std::endl; }
    }

    return 0;
}

bool checkBalanceBrackets(const char* string, const int maxDeep) {
    LimitedStack<char> steck(maxDeep);
    int i = 0;
    int brackets = 0;
    char bracket = ' ';

    while (string[i] != '\0') {
        if (string[i] == '(' || string[i] == '[' || string[i] == '{') {
            brackets++;
            if (brackets > maxDeep) {
                std::cerr << "The limit of nesting brackets has been exceeded!" << std::endl;
                exit(-1);
            }
            steck.push(string[i]);
        }
        else if (string[i] == ')' || string[i] == ']' || string[i] == '}') {
            if (steck.isEmpty())
                return false;

            bracket = steck.pop();
            brackets--;

            if ((string[i] == ')' && bracket != '(') ||
                (string[i] == '}' && bracket != '{') ||
                (string[i] == ']' && bracket != '['))
            { return false; }
        }
        i++;
    }
    return brackets == 0;
}