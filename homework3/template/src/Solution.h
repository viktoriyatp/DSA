#pragma once 

#include <cmath>
#include <vector>
#include <stack>
#include "Node.h"

template <typename T>
int findWeigth(Node<T>* rootptr) {

    if (!rootptr)
        return 0;

    return 1 + findWeigth(rootptr->left) + findWeigth(rootptr->right);
}

template <typename T>
bool helperIsBalanced(Node<T>* rightTree, Node<T>* leftTree) {

    int rightTreeWeight = findWeigth(rightTree);
    int leftTreeWeight = findWeigth(leftTree);

    if (abs(rightTreeWeight - leftTreeWeight) > 1)
        return false;
    else
        return true;

    return  helperIsBalanced(rightTree->left, leftTree->right) &&
            helperIsBalanced(rightTree->right, leftTree->left);
}

template<typename T>
bool isBalanced(const Node<T>* rootptr) {

    if (!rootptr)
        return true;

    if (!rootptr->left && !rootptr->right)
        return true;
    
    return helperIsBalanced(rootptr->left, rootptr->right);
}

template<typename T>
void treeToVectorInOrder(const Node<T>* rootptr, std::vector<T>& data) {

    if (!rootptr)
        return;

    treeToVectorInOrder(rootptr->left, data);
    data.push_back(rootptr->data);
    treeToVectorInOrder(rootptr->right, data);
}

template<typename T>
bool isBst(const Node<T>* rootptr) {

    if (rootptr == nullptr)
        return true;

    std::vector<T> data;
    treeToVectorInOrder(rootptr, data);
    
    for (size_t i = 0; i < data.size() - 1; i++)
    {
        if (data.at(i) > data.at(i+1))
           return false;
    }

    return true;
}

template<typename T>
void release(Node<T>* rootptr) {

    if (rootptr == nullptr)
        return;

    release(rootptr->left);
    release(rootptr->right);

    delete rootptr;
}

template<typename T>
Node<T>* helperToBalanced(std::vector<T> data, int start, int end) {

    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;

    Node<T>* rootptr = new Node<T>(data[mid], nullptr, nullptr);

    rootptr->left = helperToBalanced(data, start, mid - 1);
    rootptr->right = helperToBalanced(data, mid + 1, end);

    return rootptr;
}

template<typename T>
Node<T>* toBalanced(std::vector<T> data) {

     if (data.empty())
        return nullptr;

     Node<T>* rootptr = nullptr;

     try {
        rootptr = helperToBalanced(data, 0, data.size() - 1);
     }
     catch (std::bad_alloc &ba) {
         release(rootptr);
         rootptr = nullptr;
         throw;
     }

     return rootptr;
}

template<typename T>
std::vector<T> toVector(const Node<T>* rootptr) {

    std::vector<T> data;
    treeToVectorInOrder(rootptr, data);
    return data;
}

template<typename T> 
void helperLevel(const Node<T>* rootptr, unsigned int level, std::vector<T>& data) {

    if (!rootptr)
        return;

    helperLevel(rootptr->left, level - 1, data);
    if(level == 0) 
        data.push_back(rootptr->data);
    helperLevel(rootptr->right, level - 1, data);
}

template<typename T>
std::vector<T> level(const Node<T>* rootptr, int level) {

    std::vector<T> data;

    if (!rootptr) {
        return data;
    }

    if (!level) {
        data.push_back(rootptr->data);
        return data;
    }

    helperLevel(rootptr, level, data);

    return data;
}
