#include <iostream>
#include "Stack.h"
#include "LimitedStack.h"
#include "Queue.h"
#include "LimitedQueue.h"

bool checkBalanceBrackets(const char* string, const int maxDeep);

int main() {
    size_t lenght = 0;
    int i = 0;
    
    std::cout << "Enter the size of stack: ";
    std::cin >> lenght;

    LimitedStack<int> steck(lenght);

    std::cout << "Enter " << lenght << " ints: " << std::endl;
    try {
        while (i != lenght) {
            int element;
            std::cin >> element;

            steck.push(element);
            i++;
        }
    }
    catch (const LimitedStack<int>::StackOverflow& e) {
        std::cerr << "Error: " << e.getMessage() << "\n";
        return 1;
    }

    if (!steck.isEmpty()) std::cout << "Stack is not empty" << std::endl;

    try {
        char answer = 'Y';
        while (answer != 'N' && answer != 'n') {
            std::cout << "Do you want to pick up an item from the stack? (Y/N): ";
            std::cin >> answer;
            if (answer == 'Y' || answer == 'y') std::cout << "Taken: " << steck.pop() << std::endl;
            else if (answer == 'N' || answer == 'n') std::cout << "Ok. End of the test... " << std::endl;
            else std::cout << "Unknown character!" << std::endl;
        }
    }
    catch (const LimitedStack<int>::StackUnderflow& e) {
        std::cerr << "Error: " << e.getMessage() << "\n";
        return 1;
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
    int j = 0;

    std::cout << std::endl << "Enter the size of queue: ";
    std::cin >> qlenght;

    LimitedQueue<int> queue(qlenght);

    std::cout << "Enter " << qlenght << " ints: " << std::endl;
    try {
        while (j != qlenght) {
            int element;
            std::cin >> element;

            queue.enQueue(element);
            j++;
        }
    }
    catch (const LimitedQueue<int>::QueueOverflow& e) {
        std::cerr << "Error: " << e.getMessage() << "\n";
        return 1;
    }

    if (!queue.isEmpty()) std::cout << "Queue is not empty" << std::endl;

    try {
        char answer = 'Y';
        while (answer == 'Y' || answer == 'y') {
            std::cout << "Do you want to pick up an item from the queue? (Y/N): ";
            std::cin >> answer;
            if (answer == 'Y' || answer == 'y') std::cout << "Taken: " << queue.deQueue() << std::endl;
            else if (answer == 'N' || answer == 'n') std::cout << "Ok. End of the test... " << std::endl;
            else std::cout << "Unknown character!" << std::endl;
        }
    }
    catch (const LimitedQueue<int>::QueueUnderflow& e) {
        std::cerr << "Error: " << e.getMessage() << "\n";
        return 1;
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