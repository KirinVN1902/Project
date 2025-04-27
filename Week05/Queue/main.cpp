#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Queue
{
    NODE *head;
    NODE *tail;   
};
Queue* initializeQueue();
NODE *createNode(int x);
void enqueue (Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);
void printTheResult(Queue q, ofstream &f);
Queue* initializeQueue(){
    Queue *q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}
NODE *createNode(int x){
    NODE *p = new NODE;
    p->key = x;
    p->p_next = nullptr;
    return p;
}
void enqueue (Queue &q, int key){ //addTail
    NODE *p = createNode(key);
    if(q.tail == nullptr){
        q.head = p;
        q.tail = p;
    }
    else{
        q.tail->p_next = p;
        q.tail = p;
    }
}
int dequeue(Queue &q){ // removeHead
    int val = -1000000;
    if(q.head == nullptr){
        return -1000000;
    }
    else if(q.head == q.tail && q.tail != nullptr){
        NODE *p = q.head;
        val = p->key;
        q.head = nullptr;
        q.tail = nullptr;
        delete p;
    }
    else{
        NODE *p = q.head;
        val = p->key;
        q.head = q.head->p_next;
        delete p;
    }
    return val;
}
int size(Queue q){
    int n = 0;
    if(q.head == nullptr){
        return n;
    }
    NODE *p = q.head;
    while(p != nullptr){
        n++;
        p = p->p_next;
    }
    return n;
}
bool isEmpty(Queue q){
    return q.head == nullptr;
}
void printTheResult(Queue q, ofstream &f){
    if(isEmpty(q) == 1){
        f << "EMPTY";
    }
    else{
        NODE *p = q.head;
        while (p != nullptr){
            f << p->key << " ";
            p = p->p_next;
        }
    }
    f << endl;
}
int main(){
    ifstream f1;
    ofstream f2;
    f1.open("input.txt");
    if(!f1.is_open()){
        cout << "Cannot open file to read!";
        return -1;
    }
    f2.open("output.txt");
    if(!f2.is_open()){
        cout << "Cannot open file to write!";
        return -1;
    }
    Queue *q;
    string line;
    while(f1 >> line){
        if(line == "init"){
            q = initializeQueue();
            f2 << "EMPTY" << endl;
        }
        else if(line == "enqueue"){
            int val;
            f1 >> val;
            enqueue(*q, val);
            printTheResult(*q, f2);
        }
        else if(line == "dequeue"){
            dequeue(*q);
            printTheResult(*q, f2);
        }
        else if(line == "size"){
            f2 << size(*q) << endl;
        }
        else if(line == "isEmpty"){
            if(isEmpty(*q)){
                f2 << "EMPTY" << endl;
            }
            else{
                f2 << "NOT EMPTY" << endl;
            }
        }
    }
    return 0;
}