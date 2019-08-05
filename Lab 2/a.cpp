#include<iostream>

using namespace std;

struct node {
    int x;
    int y;
    struct node* next;
};

class LinkedList{
    private:
        struct node* top_node;      
    
    public:
        LinkedList() {
            top_node = NULL;
        }

        void AddFirst(int x, int y) {
            struct node* new_node = (struct node*) malloc(sizeof(struct node));
            new_node->x = x;
            new_node->y = y;
            new_node->next = top_node;
            top_node = new_node;
        }

        int DelFirst() {
            if(top_node == NULL) {
                return -1;
            }
            struct node* temp_node = top_node;
            top_node = top_node->next;
            temp_node->next = NULL;
            free(temp_node);
            return 0;
        }

        int Del(int x, int y) {
            if(top_node == NULL) {
                return -1;
            }
            
            if(top_node->x == x && top_node->y == y) {
                return DelFirst();
            }

            struct node* temp_node = top_node;
            
            while(temp_node->next != NULL) {
                if(temp_node->next->x == x && temp_node->next->y == y) {
                    struct node* del_node = temp_node->next;
                    temp_node->next = temp_node->next->next;
                    del_node->next = NULL;
                    free(del_node);
                    return 0;
                }
                temp_node = temp_node->next;
            }
            return -1;
        }

        void Search(double d) {
            struct node* temp_node = top_node;
            bool found = false;
            while(temp_node != NULL) {
                if(d*d >= temp_node->x*temp_node->x + temp_node->y*temp_node->y) {
                    cout << "(" << temp_node->x << ", " << temp_node->y << ") ";
                    found = true;
                }
                temp_node = temp_node->next;
            }
            if(!found) {
                cout << "-1";
            }
            cout << '\n';
        }

        void Search(int x, int y) {
            struct node* temp_node = top_node;
            bool found = false;
            while(temp_node != NULL) {
                if(temp_node->x == x && temp_node->y == y) {
                    found = true;
                    cout << "True\n";
                }
                temp_node = temp_node->next;
            }
            if(!found) {
                cout << "False\n";
            }
        }

        void Length() {
            struct node* temp_node = top_node;
            int len = 0;
            while(temp_node != NULL) {
                len++;
                temp_node = temp_node->next;
            }
            cout << len << '\n';
        }
};

int main() {
    LinkedList ll;
    int q;
    cin >> q;
    int o, x, y, d;
    while(q--) {
        cin >> o;
        if(o == 1) {
            cin >> x >> y;
            ll.AddFirst(x,y);
        } else if(o == 2) {
            cout << ll.DelFirst() << '\n';
        } else if(o == 3) {
            cin >> x >> y;
            cout << ll.Del(x,y) << '\n';
        } else if(o == 4) {
            cin >> d;
            ll.Search(d);
        } else if(o == 5) {
            cin >> x >> y;
            ll.Search(x,y);
        } else if(o == 6) {
            ll.Length();
        } else {
            break;
        }
    }
    return 0;
}