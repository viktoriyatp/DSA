#pragma once

#include "Allocator.h"
#include "Node.h"

#include <stdexcept>
#include <algorithm>

int height(Node<int>* rootptr) {

    if (rootptr == nullptr)
        return 0;

    return 1 + std::max(height(rootptr->left), height(rootptr->right));
}

bool isHeightBalanced(Node<int>* rootptr)
{
    if (rootptr == nullptr)
        return true;

    int leftHeight = height(rootptr->left);
    int rightHeight = height(rootptr->right);

    if (abs(leftHeight - rightHeight) <= 1
        && isHeightBalanced(rootptr->left)
        && isHeightBalanced(rootptr->right))
        return true;

    return false;
}

template <typename AllocatorType>
void free(Node<int>* rootptr, AllocatorType& allocator)
{
    if (!rootptr)
        return;

    Node<int>* toDelete = rootptr;

    free(rootptr->left,allocator);
    free(rootptr->right,allocator);

    allocator.release(toDelete);

}

template <typename AllocatorType>
Node<int>* cloneMirror(Node<int>* rootptr, AllocatorType& allocator)
{
    Node<int>* root = rootptr;

    if (!rootptr)
        return nullptr;

    Node<int>* toSwap = rootptr->left;
    rootptr->left = rootptr->right;
    rootptr->right = toSwap;

    cloneMirror(rootptr->left, allocator);
    cloneMirror(rootptr->right, allocator);

    return root;

}
