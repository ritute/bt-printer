//
//  btPrettyPrint.cpp
//
//  Created by ritute on 2012-12-18.
//  Copyright (c) 2012 ritute. All rights reserved.
//

#include "btPrettyPrint.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

namespace btPrettyPrint {

// <---indent--->(A)
//               / \
//              /   \
//             /     \
//            /       \
//           /         \
//          /<--intra-->\
//         /             \
//       (B)<---inter--->(C)
//       / \             / \
//      /   \           /   \
//     /     \         /     \
//   (D)     (E)     (F)     (G)
//   / \     / \     / \     / \
// (H) (I) (J) (K) (L) (M) (N) (O)

template <typename Comparable>
struct BTNodeDepth {
    BTNode<Comparable>* node;
    int depth;
    
    BTNodeDepth(BTNode<Comparable>* n, int d) : node(n), depth(d) {}
};

template <typename Comparable>
int printBranches(vector<BTNode<Comparable>*>& v, int branchLen, int indent,
                  int interSpacing) {
    
    int intraSpacing = 1;
    
    while (branchLen > 0) {
        cout << string(indent, ' ');
        for (auto itr = v.begin(); itr != v.end(); itr++) {
            if (*itr == nullptr) {
                cout << string(1+intraSpacing+1+interSpacing, ' ');
            } else {
                cout << (((*itr)->left) != nullptr ? '/' : ' ');
                cout << string(intraSpacing, ' ');
                cout << (((*itr)->right) != nullptr ? '\\' : ' ');
                cout << string(interSpacing, ' ');
            }
        }
        cout << endl;
        indent--;
        branchLen--;
        intraSpacing+=2;
        
        if (interSpacing > 0) interSpacing-=2;
    }
    
    interSpacing = (interSpacing == 0) ? intraSpacing-2 : interSpacing-2;
    
    return interSpacing;    // return last inter spacing for printing nodes
}

template <typename Comparable>
void printNodes(vector<BTNode<Comparable>*>& v, int indent, int interSpacing) {
    
    cout << string(indent, ' ');
    for (auto itr = v.begin(); itr != v.end(); itr++) {
        if (*itr == nullptr) {
            cout << string(3+interSpacing+3, ' ');
        } else {
            if ((*itr)->left != nullptr)    // print left child
                cout << "(" << (*itr)->left->data << ")";
            else cout << string(3,' ');
            
            cout << string(interSpacing, ' ');
            
            if ((*itr)->right != nullptr)   // print right child
                cout << "(" << (*itr)->right->data << ")";
            else cout << string(3,' '); 
        }
        if ((itr+1) == v.end()) interSpacing = 0;
        cout << string(interSpacing, ' ');
    }
    cout << endl;
}

template <typename Comparable>
void printRoot(vector<BTNode<Comparable>*>& v, int indent, int interSpacing) {
    
    cout << string(indent, ' ');
    cout << "(" << (v[0])->data << ")";
    cout << endl;
}

template <typename Comparable>
void printBT(BTNode<Comparable>* root) {
    
    if (root == nullptr) return;
    
    // Store entire tree in vector containing nodes and their depths
    int depth = 1;
    vector<BTNodeDepth<Comparable>> v;
    
    v.push_back(BTNodeDepth<Comparable>(root, depth));
    
    int i = 0;
    while (true) {
        bool lvlNotEmpty = false;
        depth++;
        
        int maxNodes = pow(2, depth-1);
        for (int j = 0; j < maxNodes; j += 2) {
            if (v[i].node != nullptr) {
                if (v[i].node->left != nullptr || v[i].node->right != nullptr)
                    lvlNotEmpty = true;
                v.push_back(BTNodeDepth<Comparable>(v[i].node->left, depth));
                v.push_back(BTNodeDepth<Comparable>(v[i].node->right, depth));
            } else {
                v.push_back(BTNodeDepth<Comparable>(nullptr, depth));
                v.push_back(BTNodeDepth<Comparable>(nullptr, depth));
            }
            i++;
        }
        if (!lvlNotEmpty) { depth--; break; }
    }
    
    int& maxDepth = depth;
    int currentDepth = 1;
    int interSpacing = 0;
    int branchLen = pow(2, maxDepth-currentDepth) - 1;
    vector<BTNode<Comparable>*> vv; // will contain current level's nodes
    auto itr = v.begin() + 1;

    vv.push_back(v[0].node);    // push root
    printRoot(vv, branchLen*2, interSpacing);    // indent is branchLen*2
    
    while (currentDepth < maxDepth) {
        
        // Print branches for all nodes in current level/depth
        branchLen = pow(2, maxDepth-currentDepth) - 1;
        interSpacing = printBranches(vv, branchLen, branchLen*2, interSpacing);
        
        // Print the children of all nodes in current level/depth
        branchLen = pow(2, maxDepth-(currentDepth+1)) - 1;
        printNodes(vv, branchLen*2, interSpacing);
        
        currentDepth++;
        while (vv.size()) vv.pop_back();
        while ((*itr).depth == currentDepth) {  // push nodes of next level
            vv.push_back((*itr).node);
            itr++;
        }
    }
}
    
}   // namespace btPrettyPrint

/*
int main() {
    
    using namespace btPrettyPrint;
    
    BTNode<char> a('A');
    BTNode<char> b('B');
    BTNode<char> c('C');
    BTNode<char> d('D');
    BTNode<char> e('E');
    BTNode<char> f('F');
    BTNode<char> g('G');
    BTNode<char> h('H');
    BTNode<char> i('I');
    BTNode<char> j('J');
    BTNode<char> k('K');
    BTNode<char> l('L');
    BTNode<char> m('M');
    BTNode<char> n('N');
    BTNode<char> o('O');
    BTNode<char> p('P');
    
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    d.left = &h;
    d.right = &i;
//    e.left = &j;
//    e.right = &k;
    f.left = &l;
//    f.right = &m;
//    g.left = &n;
//    g.right = &o;
//    o.left = &p;

    printBT<char>(&a);
    
    return 0;
}
*/