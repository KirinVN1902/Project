#include <iostream>
#include <vector>
#include <string>

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
vector<int> NLR(NODE *pRoot)
{
    vector<int> v;
    NODE *p = pRoot;
    if (p == nullptr)
    {
        return v;
    }
    else
    {
        v.push_back(p->key);
        vector<int> left = NLR(p->p_left);
        v.insert(v.end(), left.begin(), left.end());
        vector<int> right = NLR(p->p_right);
        v.insert(v.end(), right.begin(), right.end());
    }
    return v;
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
vector<int> LRN(NODE *pRoot)
{
    vector<int> v;
    NODE *p = pRoot;
    if (p == nullptr)
    {
        return v;
    }
    else
    {
        vector<int> left = LRN(p->p_left);
        v.insert(v.end(), left.begin(), left.end());
        vector<int> right = LRN(p->p_right);
        v.insert(v.end(), right.begin(), right.end());
        v.push_back(p->key);
    }
    return v;
}
void LevelOrderTemp(NODE* pRoot, int level, vector<vector<int>> &res){
    if(pRoot == nullptr){
        return;
    }
    if(level >= res.size()){
        res.push_back({});
    }
    res[level].push_back(pRoot->key);
    LevelOrderTemp(pRoot->p_left, level + 1, res);
    LevelOrderTemp(pRoot->p_right, level + 1, res);
}
vector<vector<int>> LevelOrder(NODE *pRoot){
    vector<vector<int>> v;
    LevelOrderTemp(pRoot, 0, v);
    return v;
}
int countNode(NODE *pRoot){
    vector<int> v = NLR(pRoot);
    return v.size();
}
int sumNode(NODE *pRoot){
    int sum = 0;
    vector<int> v = NLR(pRoot);
    for (int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum;
}
int heightNode(NODE *pRoot, int value){
    if(pRoot == nullptr){
        return -1;
    }
    if(pRoot->key == value){
        int leftHeight = 0, rightHeight = 0;
        if(pRoot->p_left != nullptr){
            leftHeight = heightNode(pRoot->p_left, pRoot->p_left->key);
        }
        else{
            leftHeight = -1;
        }
        if(pRoot->p_right != nullptr){
            rightHeight = heightNode(pRoot->p_right, pRoot->p_right->key);
        }
        else{
            rightHeight = -1;
        }
        if(leftHeight > rightHeight){
            return 1 + leftHeight;
        }
        else{
            return 1 + rightHeight;
        }
    }
    int left = heightNode(pRoot->p_left, value);
    if(left != -1){
        return left;
    }
    int right = heightNode(pRoot->p_right, value);
    return right;
}
int level(NODE *pRoot, NODE *p){
    vector<vector<int>> v = LevelOrder(pRoot);
    int value = p->key;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v[i].size(); j++){
            if(value ==  v[i][j]){
                return i;
            }
        }
    }
    return -1;
}
int countLeaf(NODE *pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    if(pRoot->p_left == nullptr && pRoot->p_right == nullptr){
        return 1;
    }
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}