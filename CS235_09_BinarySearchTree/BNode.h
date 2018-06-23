//
//  Node.cpp
//  CS235_07_List
//
//  Created by Mauricio Takashi Kiyama on 6/1/18.
//  Copyright © 2018 Marcio Kazuo Kiyama. All rights reserved.
//

#include <stdio.h>

template <class T>
class BNode {
        
public:
    T data;
    BNode<T>* pLeft;
    BNode<T>* pRight;
    BNode<T>* pParent;
    bool isRed;
    
    // default constructor
    BNode() : data(0), pLeft(NULL), pRight(NULL), pParent(NULL){}
        
    //non-default constructor
    BNode(T nData): pLeft(NULL), pRight(NULL), pParent(NULL) {
        data = nData;
    }
    
    //verifyRB(depth: integer)
    
    //verifyBST
    
    //balance()
    
};
