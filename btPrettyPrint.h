//
//  btPrettyPrint.h
//
//  Created by ritute on 2012-12-18.
//  Copyright (c) 2012 ritute. All rights reserved.
//

#ifndef __btPrettyPrint__
#define __btPrettyPrint__

namespace btPrettyPrint {

    /*
     *  Binary tree node
     */
    template <typename Comparable>
    struct BTNode {
        Comparable data;
        BTNode* left;
        BTNode* right;
        
        /*
         *  d : Comparable item representing the node's data
         *  l : pointer to node's left child
         *  r : pointer to node's right child
         */
        BTNode(Comparable d, BTNode* l = nullptr, BTNode* r = nullptr)
                : data(d), left(l), right(r) {}
    };
    
    /*
     *  Prints the binary tree to standard output, in tree-like fashion.
     *
     *  root : pointer to root of binary tree
     *
     *  eg.  (A)
     *       / \
     *      /   \
     *     /     \
     *   (B)     (C)
     *   / \     / \
     * (D) (E) (F) (G)
     */
    template <typename Comparable>
    void printBT(BTNode<Comparable>* root);
}

#endif /* defined(__btPrettyPrint__) */
