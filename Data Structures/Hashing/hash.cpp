#include<bits/stdc++.h>
#define M 1000000
using namespace std;

vector<long long> primes{1298963, 1298981, 1298989, 1299007, 1299013, 1299019, 1299029, 1299041, 1299059, 

 1299061, 1299079, 1299097, 1299101, 1299143, 1299169, 1299173, 1299187, 1299203,

 1299209 ,1299211, 1299223 ,1299227, 1299257 ,1299269 ,1299283 ,1299289, 1299299,

 1299317, 1299341, 1299349, 1299359 ,1299367, 1299377, 1299379,

 1299437 ,1299439, 1299449 ,1299451, 1299457 ,1299491 ,1299499, 1299533, 1299541,

 1299553, 1299583, 1299631, 1299637 ,1299647, 1299653 ,1299673 ,1299689,

 1299709 ,1299721 ,1299743 ,1299763, 1299791 ,1299811 ,1299817, 1299821, 1299827};

struct NODE {
    int key;
    string value;
    NODE* next = NULL;
};

vector<NODE*> hash_table(M, NULL);
vector<int> random_vector(100);
int PRIME;

void init() {
    srand(time(0));
    for(int i = 0; i < 100; ++i) {
        random_vector[i] = rand();
    }
    PRIME = primes[rand() % primes.size()];
}

long long hashValue(string s) {
    long long sum = 0;
    for(int i = 0; i < s.length(); ++i) {
        sum = (sum + random_vector[i]*s[i]) % PRIME;
    }
    return (sum % M + M) % M;
}

void insert(string s) {
    long long h_value = hashValue(s);
    NODE* node = new NODE;
    node->key = h_value;
    node->value = s;
    node->next = hash_table[h_value];
    hash_table[h_value] = node;
}

NODE* search(string s) {
    long long h_value = hashValue(s);
    NODE *temp = hash_table[h_value];
    while(temp) {
        if(temp->value == s) return temp;
        temp = temp->next;
    }
    return NULL;
}

void del(string s) {
    long long h_value = hashValue(s);
    NODE *temp = hash_table[h_value];
    if(temp->value == s) {
        hash_table[h_value] = temp->next;
    } else {
        while(temp->next) {
            if(temp->next->value == s) {
                temp->next = temp->next->next;
                break;
            }
            temp = temp->next;
        }
    }
}

int main() {
    init();
    int m, n;
    cin >> m >> n;
    string s;
    for(int i = 0; i < m; ++i) {
        cin >> s;
        insert(s);
    }
    bool flag = true;
    for(int i = 0; i < n; ++i) {
        cin >> s;
        auto temp = search(s);
        if(temp){
            del(s);
        } else {
            flag = false;            
            break;
        }
    }
    if(flag) printf("Yes\n");
    else printf("No\n");
    return 0;
}


/*
Harold is a kidnapper who wrote a ransom note, but now he is worried it will be traced back to him through his handwriting. He found a magazine and wants to know if he can cut out whole words from it and use them to create an untraceable replica of his ransom note. The words in his note are case-sensitive and he must use only whole words available in the magazine. He cannot use substrings or concatenation to create the words he needs.
Given the words in the magazine and the words in the ransom note, print Yes if he can replicate his ransom note exactly using whole words from the magazine; otherwise, print No.
For example, the note is "Attack at dawn". The magazine contains only "attack at dawn". The magazine has all the right words, but there's a case mismatch. The answer is .

Function Description
Complete the checkMagazine function in the editor below. It must print  if the note can be formed using the magazine, or .
checkMagazine has the following parameters:
magazine: an array of strings, each a word in the magazine
note: an array of strings, each a word in the ransom note

Input Format
The first line contains two space-separated integers,  and , the numbers of words in the  and the ..
The second line contains  space-separated strings, each .
The third line contains  space-separated strings, each .

Constraints
1 <= m, n <= 3000
1 <= |magazine[i]|, |note[i]| <= 5
Each word consists of English alphabetic letters (i.e.,  to  and  to ).

Output Format
Print Yes if he can use the magazine to create an untraceable replica of his ransom note. Otherwise, print No.

Sample Input 0
6 4
give me one grand today night
give one grand today

Sample Output 0
Yes

Sample Input 1
6 5
two times three is not four
two times two is four

Sample Output 1
No

Sample Input 2
7 4
ive got a lovely bunch of coconuts
ive got some coconuts

Sample Output 2
No
*/