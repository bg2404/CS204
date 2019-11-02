#include<bits/stdc++.h>
using namespace std;

class Stack {
    int top;
    int MAX_SIZE;
    int *stack;
    public:
    Stack(int SIZE) {
        top = -1;
        MAX_SIZE = SIZE;
        stack = new int[SIZE];
    };

    void push(int x) {
        if(top == MAX_SIZE - 1) {
            cout << "Stack is full" << '\n';
            return;
        }
        stack[++top] = x;
    }

    int pop() {
        if(top < 0) {
            cout << "Stack Empty. Error Code: ";
            top = 0;
        }
        return stack[top--];
    }

    int peek() {
        if(top < 0) {
            cout << "Stack Empty. Error Code: ";
        }
        return stack[top];
    }

    int length() {
        return top + 1;
    }

    ~Stack() {
    }
};

int main() {
    system("clear");
    int option = 1, x;
    Stack stack(5);
    while(option) {
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Length\n";
        cout << "0. Exit\n";
        cout << "Choose any option ";
        cin >> option;
        
        switch(option) {
            case 0:
                break;
            case 1:
                cout << "Enter any integer ";
                cin >> x;
                stack.push(x);
                break;
            case 2:
                cout << stack.pop();
                break;
            case 3:
                cout << stack.peek();
                break;
            case 4:
                cout << stack.length();
                break;
            default:
                cout << "Enter a valid option\n";
        }
        cout << '\n';
    }
    return 0;
}