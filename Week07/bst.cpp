#include <iostream>
#include <vector>
using namespace std;
struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};
NODE *createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}
NODE *search(NODE *pRoot, int x){
    if(pRoot == nullptr){
        return nullptr;
    }
    else{
        if(x > pRoot->key){
            return search(pRoot->p_right, x);
        }
        else if(x < pRoot->key){
            return search(pRoot->p_left, x);
        }
    }
    return pRoot;
}
void Insert(NODE* &pRoot, int x){
    if(pRoot == nullptr){
        NODE *p = createNode(x);
        pRoot = p;
        return;
    }
    else{
        if(x > pRoot->key){
            Insert(pRoot->p_right, x);
        }
        else if(x < pRoot->key){
            Insert(pRoot->p_left, x);
        }
    }
}
void Remove(NODE* &pRoot, int x){
    if(pRoot == nullptr){
        return;
    }
    else{
        if(x > pRoot->key){
            Remove(pRoot->p_right, x);
        }
        else if(x < pRoot->key){
            Remove(pRoot->p_left, x);
        }
        else{
            // nếu là lá
            if(pRoot->p_left == nullptr && pRoot->p_right == nullptr){
                delete pRoot;
                pRoot = nullptr;
                return;
            }
            // nếu có 1 nốt con phải
            else if((pRoot->p_left == nullptr && pRoot->p_right != nullptr)){
                NODE *temp = pRoot;
                pRoot = pRoot->p_right;
                delete temp;
                return;
            }
            // nếu có 1 nốt con trái
            else if((pRoot->p_left != nullptr && pRoot->p_right == nullptr)){
                NODE * temp = pRoot;
                pRoot = pRoot->p_left;
                delete temp;
                return;
            }
            // nếu có cả 2 nốt, xoá nút phải nhất của cây con trái
            else{
                NODE *holder = pRoot;
                NODE *temp = pRoot->p_left;
                while(temp->p_right != nullptr){
                    holder = temp;
                    temp = temp->p_right;
                }
                pRoot->key = temp->key;
                if(holder == pRoot){
                    pRoot->p_left = temp->p_left;
                    delete temp;
                }
                else{
                    holder->p_right = temp->p_left;
                    delete temp;
                }
            }
        }
    }
}
NODE* createTree(int a[], int n){
    NODE *pRoot = createNode(a[0]);
    for (int i = 1; i < n; i++){
        Insert(pRoot, a[i]);
    }
    return pRoot;
}
void removeTree(NODE *&pRoot){
    if(pRoot == nullptr){
        return;
    }
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    NODE *p = pRoot;
    delete p;
    pRoot = nullptr;
}
void insertTree(NODE *&tree, int data){
    if(tree == nullptr){
        NODE *p = createNode(data);
        tree = p;
    }
    else{
        if(data < tree->key){
            insertTree(tree->p_left, data);
        }
        else if(data > tree->key){
            insertTree(tree->p_right, data);
        }
    }
}
int Height(NODE *pRoot){
    if(pRoot == nullptr){
        return -1;
    }
    int LeftHeight = Height(pRoot->p_left);
    int RightHeight = Height(pRoot->p_right);
    if(LeftHeight > RightHeight){
        return 1 + LeftHeight;
    }
    else{
        return 1 + RightHeight;
    }
}
int countLess(NODE* pRoot, int x){
    if(pRoot == nullptr){
        return 0;
    }
    if(x <= pRoot->key){
        return countLess(pRoot->p_left, x);
    }
    else{
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    }
}
int countGreater(NODE* pRoot, int x){
    if(pRoot == nullptr){
        return 0;
    }
    if(x >= pRoot->key){
        return countGreater(pRoot->p_right, x);
    }
    else{
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    }
}
vector<int> LNR(NODE *pRoot)
{
    vector<int> v;
    NODE *p = pRoot;
    if (p == nullptr)
    {
        return v;
    }
    else
    {
        vector<int> left = LNR(p->p_left);
        v.insert(v.end(), left.begin(), left.end());
        v.push_back(p->key);
        vector<int> right = LNR(p->p_right);
        v.insert(v.end(), right.begin(), right.end());
    }
    return v;
}
bool isBST(NODE *pRoot){
    if(pRoot == nullptr){
        return true;
    }
    vector<int> v = LNR(pRoot);
    int comp = -1000000;
    for (int x : v){
        if(x <= comp){
            return false;
        }
        comp = x;
    }
    return true;
}
bool isFullBinaryTree(NODE *pRoot){
    if(pRoot == nullptr){
        return true;
    }
    if ((pRoot->p_left == nullptr && pRoot->p_right != nullptr) || (pRoot->p_left != nullptr && pRoot->p_right == nullptr)){
        return false;
    }
    if(isFullBinaryTree(pRoot->p_left) && isFullBinaryTree(pRoot->p_right)){
        return true;
    }
    return false;
}
bool isFullBST(NODE *pRoot){
    if(pRoot == nullptr){
        return true;
    }
    return isBST(pRoot) && isFullBinaryTree(pRoot);
}
