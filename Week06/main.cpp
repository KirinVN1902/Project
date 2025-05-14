#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#define p 31
#define m 2000
using namespace std;
struct Company
{
    string name;
    string profit_tax;
    string address;
};
struct Node
{
    Company data;
    Node *p_next;
};
typedef Node* HashTable[2000];
void readFile(ifstream &f1, string s1, vector<Company> &readCompanyList, int &count)
{
    f1.open(s1);
    if (!f1.is_open())
    {
        cout << "Cannot open file to read!";
        return;
    }
    string line;
    while(getline(f1, line)){
        stringstream ss(line);
        Company com;
        getline(ss, com.name, '|');
        getline(ss, com.profit_tax, '|');
        getline(ss, com.address);
        readCompanyList.push_back(com);
        count++;
    }
    f1.close();
}
long long hashString(string company_name)
{
    int len = company_name.size();
    long long sum = 0;
    if (len > 20)
    {
        int j = 0;
        for (int i = len - 20; i < len; i++)
        {
            sum += int(company_name[i]) * pow(p, j);
            j++;
        }
    }
    else
    {
        int j = 0;
        for (int i = 0; i < len; i++)
        {
            sum += int(company_name[i]) * pow(p, j);
            j++;
        }
    }
    return (sum % m);
}
Node *createNode(Company data){
    Node *temp = new Node;
    temp->data = data;
    temp->p_next = nullptr;
    return temp;
}
void createHashTable(HashTable &h, vector<Company> &list_company, int count){
    for (int i = 0; i < m; i++){
        h[i] = nullptr;
    }
    for (int i = 0; i < count; i++){
        Company com = list_company[i];
        Node* temp = createNode(com);
        long long location = hashString(com.name);
        temp->p_next = h[location];
        h[location] = temp;
    }
}
void insert(HashTable &hash_table, Company company){
    Node *temp = createNode(company);
    long long index = hashString(company.name);
    temp->p_next = hash_table[index];
    hash_table[index] = temp;
}
Company* search(HashTable hash_table, string company_name){
    Company com;
    long long location = hashString(company_name);
    Node *find = hash_table[location];
    while(find != nullptr){
        if(find->data.name == company_name){
            return &(find->data);
        }
        find = find->p_next;
    }
    return nullptr;
}
void writeFile(ifstream &f1, string s1, ofstream &f2, string s2, HashTable h){
    f1.open(s1);
    if(!f1.is_open()){
        cout << "Cannot open file to read!";
        return;
    }
    f2.open(s2);
    if(!f2.is_open()){
        cout << "Cannot open file to write!";
        return;
    }
    string line;
    while(getline(f1, line)){
        Company *com = search(h, line);
        if(com != nullptr){
            f2 << com->name << "|" << com->profit_tax << "|" << com->address << endl;
        }
        else{
            f2 << "Not found!" << endl;
        }
    }
    f1.close();
    f2.close();
}
int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "Error in command line!";
        return -1;
    }
    ifstream f1, f2;
    ofstream f3;
    string s1 = argv[1];
    string s2 = argv[2];
    string s3 = argv[3];
    vector<Company> v;
    int count  = 0;
    readFile(f1, s1, v, count);
    HashTable h;
    createHashTable(h, v, count);
    writeFile(f2, s2, f3, s3, h);
    return 0;
}