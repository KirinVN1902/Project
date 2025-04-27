#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Stack
{
    NODE *top;
};
Stack *initializeStack();
NODE *createNode(int data);
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack &s);
bool isEmpty(Stack &s);
Stack *initializeStack()
{
    Stack *st = new Stack;
    st->top = nullptr;
    return st;
}
NODE *createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->p_next = nullptr;
    return p;
}
void push(Stack &s, int key)
{
    NODE *p = createNode(key);
    p->p_next = s.top;
    s.top = p;
}
int pop(Stack &s)
{
    int val;
    if (s.top == nullptr)
    {
        return -1000000;
    }
    if (s.top->p_next == nullptr)
    {
        val = s.top->key;
        NODE *p = s.top;
        s.top = nullptr;
        delete p;
        return val;
    }
    val = s.top->key;
    NODE *p = s.top;
    s.top = s.top->p_next;
    delete p;
    return val;
}
int size(Stack &s)
{
    int n = 0;
    NODE *count = s.top;
    while (count != nullptr)
    {
        n++;
        count = count->p_next;
    }
    return n;
}
bool isEmpty(Stack &s)
{
    if (s.top == nullptr)
    {
        return true;
    }
    return false;
}
int main()
{   
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
    Stack *s;
    string line;
    while(f1 >> line){
        if(line == "init"){
            s = initializeStack();
            f2 << "EMPTY" << endl;
        }
        else if(line == "push"){
            int val;
            f1 >> val;
            push(*s, val);
            NODE *p = s->top;
            while(p != nullptr){
                f2 << p->key << " ";
                p = p->p_next;
            }
            f2 << endl;
        }
        else if(line == "pop"){
            if(isEmpty(*s)){
                f2 << "EMPTY" << endl;
            }
            else{
                pop(*s);
                if(isEmpty(*s)){
                    f2 << "EMPTY" << endl;
                }
                else{
                    NODE *p = s->top;
                    while(p != nullptr){
                        f2 << p->key << " ";
                        p = p->p_next;
                    }
                    f2 << endl;
                }
            }
        }
        else if(line == "size"){
            f2 << size(*s) << endl;
        }
        else if(line == "isEmpty"){
            if(isEmpty(*s)){
                f2 << "EMPTY" << endl;
            }
            else{
                f2 << "NOT EMPTY" << endl;
            }
        }    
    }
    return 0;
}