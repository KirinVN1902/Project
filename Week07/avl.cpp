#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;   
    NODE* p_right;
    int height;
};
NODE *createNode(int data){
    NODE *p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    p->height = 1;
    return p;
}
int height(NODE *pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    return pRoot->height;
}
void updateHeight(NODE *&pRoot){
    if(pRoot == nullptr){
        return;
    }
    int leftHeight = height(pRoot->p_left);
    int rightHeight = height(pRoot->p_right);
    if(leftHeight > rightHeight){
        pRoot->height = leftHeight + 1;
    }
    else{
        pRoot->height = rightHeight + 1;
    }
}
int diffHeight(NODE *pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    return abs(height(pRoot->p_left) - height(pRoot->p_right));
}
NODE* leftRotation(NODE* pRoot){
    if(pRoot == nullptr || pRoot->p_right == nullptr){
        return pRoot;
    }
    NODE *x = pRoot->p_right;
    NODE *y = x->p_left;
    x->p_left = pRoot;
    pRoot->p_right = y;
    updateHeight(pRoot);
    updateHeight(x);
    return x;
}
NODE *rightRotation(NODE *pRoot){
    if(pRoot == nullptr || pRoot->p_left == nullptr){
        return pRoot;
    }
    NODE *x = pRoot->p_left;
    NODE *y = x->p_right;
    x->p_right = pRoot;
    pRoot->p_left = y;
    updateHeight(pRoot);
    updateHeight(x);
    return x;
}
void Insert(NODE* &pRoot, int x){
    if(pRoot == nullptr){
        NODE *p = createNode(x);
        pRoot = p;
        return;
    }
    if(pRoot->key == x){
        return;
    }
    else if(x > pRoot->key){
        Insert(pRoot->p_right, x);
    }
    else if(x < pRoot->key){
        Insert(pRoot->p_left, x);
    }
    updateHeight(pRoot);
    int dis = diffHeight(pRoot);
    if(dis >= 2){ // không phải cây AVL -> cân bằng lại
        // left left
        if(pRoot->p_left != nullptr && x < pRoot->p_left->key){
            pRoot = rightRotation(pRoot);
        }
        // right right
        else if(pRoot->p_right != nullptr && x > pRoot->p_right->key){
            pRoot = leftRotation(pRoot);
        }
        //left right
        else if(pRoot->p_left != nullptr && x > pRoot->p_left->key){
            pRoot->p_left = leftRotation(pRoot->p_left);
            pRoot = rightRotation(pRoot);
        }
        // right left
        else if(pRoot->p_right != nullptr && x < pRoot->p_right->key){
            pRoot->p_right = rightRotation(pRoot->p_right);
            pRoot = leftRotation(pRoot);
        }
    }
}
void Remove(NODE* &pRoot, int x){
    if(pRoot == nullptr){
        return;
    }
    // tìm vị trí xoá phần tử
    if(x > pRoot->key){
        Remove(pRoot->p_right, x);
    }
    else if(x < pRoot->key){
        Remove(pRoot->p_left, x);
    }
    else{
        // nốt lá
        if(pRoot->p_left == nullptr && pRoot->p_right == nullptr){
            delete pRoot;
            pRoot = nullptr;
        }
        // nốt có 1 nốt con trái
        else if(pRoot->p_left != nullptr && pRoot->p_right == nullptr){
            NODE *temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        // nốt có 1 nốt con phải
        else if(pRoot->p_left == nullptr && pRoot->p_right != nullptr){
            NODE *temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        // nốt có 2 con
        else{// xoá node phải nhất của cây con trái
            NODE *holder = pRoot;
            NODE *p = pRoot->p_left;
            while (p->p_right != nullptr){
                holder = p;
                p = p->p_right;
            }
            pRoot->key = p->key;
            if(holder == pRoot){
                pRoot->p_left = p->p_left;
            }
            else{
                holder->p_right = p->p_left;
            }
            delete p;
        }
    }
    updateHeight(pRoot);
    int dis = diffHeight(pRoot);
    if(dis >= 2){ // không phải cây AVL -> cân bằng lại
        // left left
        if(pRoot->p_left != nullptr && (height(pRoot->p_left->p_left) > height(pRoot->p_left->p_right))){
            pRoot = rightRotation(pRoot);
        }
        // right right
        else if(pRoot->p_right != nullptr && (height(pRoot->p_right->p_right) > height(pRoot->p_right->p_left))){
            pRoot = leftRotation(pRoot);
        }
        //left right
        else if(pRoot->p_left != nullptr && (height(pRoot->p_left->p_left) < height(pRoot->p_left->p_right))){
            pRoot->p_left = leftRotation(pRoot->p_left);
            pRoot = rightRotation(pRoot);
        }
        // right left
        else if(pRoot->p_left != nullptr && (height(pRoot->p_right->p_right) < height(pRoot->p_right->p_left))){
            pRoot->p_right = rightRotation(pRoot->p_right);
            pRoot = leftRotation(pRoot);
        }
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
bool isAVL(NODE* pRoot){
    if(pRoot == nullptr){
        return true;
    }
    int dis = diffHeight(pRoot);
    if(!isBST(pRoot) || dis >= 2){
        return false;
    }
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

