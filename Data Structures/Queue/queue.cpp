#include <bits/stdc++.h>

using namespace std;

class Queue {
    int front;
    int rear;
    int MAX_SIZE;
    int *queue;
    public:
    Queue(int SIZE) {
        front = -1;
        rear = -1;
        MAX_SIZE = SIZE;
        queue = new int[SIZE];
    }
    void enqueue(int x) {
        if(rear == front-1 || (front == 0 && rear == MAX_SIZE - 1)) {
            cout << "Queue is Full. Error Code -1";
            return;
        } else if(front == -1) {
            front = rear = 0;
            queue[rear] = x;
        } else if(rear == MAX_SIZE - 1 && front != 0) {
            rear = 0;
            queue[rear] = x;
        } else {
            queue[++rear] = x;
        }
    }

    int dequeue() {
        if(front == -1) {
            cout << "Queue is Empty. Error Code ";
            return 0;
        }
        int ret = queue[front];
        if(front == rear) front = rear = -1;
        else front  = (++front) % MAX_SIZE;
        return ret;
    }

    int peek() {
        if(front < 0) {
            cout << "Queue is Empty. Error Code: ";
            return 0;
        }
        return queue[front];
    }

    ~Queue() {
    }
};

int main() {
    system("clear");
    int option = 1, x;
    Queue queue(5);
    while(option) {
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Peek\n";
        cout << "0. Exit\n";
        cout << "Choose any option ";
        cin >> option;
        
        switch(option) {
            case 0:
                break;
            case 1:
                cout << "Enter any integer ";
                cin >> x;
                queue.enqueue(x);
                break;
            case 2:
                cout << queue.dequeue();
                break;
            case 3:
                cout << queue.peek();
                break;
            default:
                cout << "Enter a valid option\n";
        }
        cout << '\n';
    }
    return 0;
}