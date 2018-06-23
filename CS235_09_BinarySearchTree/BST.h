/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *
 *    This will contain the class definition of:
 *       BST             : similar to std::BST
 *       BST :: iterator : an iterator through the BST
 * Author
 *
 ************************************************************************/



#ifndef BST_H
#define BST_H

#include <cassert>  // because I am paranoid
#include <string>
#include "BNode.h"
#include "stack.h"    // for Stack

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG


namespace custom
{
    
/************************************************
 * BST
 * A class that holds stuff
 ***********************************************/
template <class T>
class BST
{
private:
    int numElements = 0;
    BNode<T> *root;
        
public:
        
    //Constructor
    BST(): numElements(0), root(NULL) {}
        
        
    //Copy Constructor
    BST(const BST <T> & rhs)        throw (const char *) {
        
        try {
            this->numElements = 0;
            this->root = NULL;
            *this = rhs;
        } catch (std::bad_alloc) {
            throw "ERROR: Unable to allocate buffer";
        }
    }
        
        
    //Destructor
    ~BST() {}
        
        
    //operator=
    BST & operator = (const BST & rhs) throw (const char *) {
        
    
    }
    
    
    //empty()
    bool empty() {
        if (numElements > 0) {
            return false;
        }
        return true;
    }
    
    
    //size()
    int  size()     const { return numElements;                 }
    
    
    //clear()
    void clear()          {}
    
    
    //insert()
    void insert(T t) {
        
    }
    
    
    //erase()
    void erase(BSTIterator it) {
        
    }
    
    //find()
    BSTIterator find(T t) {
        
    }
        
    //begin(): Iterator
    BSTIterator <T> begin() const {
        Stack < BNode <T> * > nodes;
        
        nodes.push(NULL);
        nodes.push(root);
        while (nodes.top() != NULL && nodes.top()->pLeft)
            nodes.push(nodes.top()->pLeft);
        
        return BSTIterator<T>(nodes);
        
    }
    
    //end()
    BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
    
    //rbegin()
    BSTIterator <T> rbegin() const {
        BSTIterator <T> BST <T> :: rbegin() const
        {
            Stack < BinaryNode <T> * > nodes;
            
            nodes.push(NULL);
            nodes.push(root);
            while (nodes.top() != NULL && nodes.top()->pRight)
                nodes.push(nodes.top()->pRight);
            
            return BSTIterator<T>(nodes);
        }
    }
    
    //rend()
    BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
    
    
    
  
    
class BSTIterator
{
public:
    // constructors
    BSTIterator(BNode <T> * p = NULL)    { nodes.push(p);  }
    
    BSTIterator(Stack < BNode <T> *> & s) { nodes = s;         }
    
    BSTIterator(const BSTIterator <T> & rhs)  {
        nodes = rhs.nodes;
        
    }
    
    // assignment
    BSTIterator <T> & operator = (const BSTIterator <T> & rhs) {
        // need an assignment operator for the Stack class.
        nodes = rhs.nodes;
        return *this;
    }
    
    // compare
    bool operator == (const BSTIterator <T> & rhs) const
    {
        // only need to compare the leaf node
        return rhs.nodes.const_top() == nodes.const_top();
    }
    bool operator != (const BSTIterator <T> & rhs) const
    {
        // only need to compare the leaf node
        return rhs.nodes.const_top() != nodes.const_top();
    }
    
    // de-reference. Cannot change because it will invalidate the BST
    T & operator * ()
    {
        return nodes.top()->data;
    }
    
    // iterators
    BSTIterator <T> & operator ++ () {
        // do nothing if we have nothing
        if (nodes.top() == NULL)
            return *this;
        
        // if there is a right node, take it
        if (nodes.top()->pRight != NULL)
        {
            nodes.push(nodes.top()->pRight);
            
            // there might be more left-most children
            while (nodes.top()->pLeft)
                nodes.push(nodes.top()->pLeft);
            return *this;
        }
        
        // there are no right children, the left are done
        assert(nodes.top()->pRight == NULL);
        BinaryNode <T> * pSave = nodes.top();
        nodes.pop();
        
        // if the parent is the NULL, we are done!
        if (NULL == nodes.top())
            return *this;
        
        // if we are the left-child, got to the parent.
        if (pSave == nodes.top()->pLeft)
            return *this;
        
        // we are the right-child, go up as long as we are the right child!
        while (nodes.top() != NULL && pSave == nodes.top()->pRight)
        {
            pSave = nodes.top();
            nodes.pop();
        }
        
        return *this;

    }
    
    BSTIterator <T>   operator ++ (int postfix) {
        BSTIterator <T> itReturn = *this;
        ++(*this);
        return itReturn;
    }
    
    BSTIterator <T> & operator -- () {
        // do nothing if we have nothing
        if (nodes.top() == NULL)
            return *this;
        
        // if there is a left node, take it
        if (nodes.top()->pLeft != NULL)
        {
            nodes.push(nodes.top()->pLeft);
            
            // there might be more right-most children
            while (nodes.top()->pRight)
                nodes.push(nodes.top()->pRight);
            return *this;
        }
        
        // there are no left children, the right are done
        assert(nodes.top()->pLeft == NULL);
        BinaryNode <T> * pSave = nodes.top();
        nodes.pop();
        
        // if the parent is the NULL, we are done!
        if (NULL == nodes.top())
            return *this;
        
        // if we are the right-child, got to the parent.
        if (pSave == nodes.top()->pRight)
            return *this;
        
        // we are the left-child, go up as long as we are the left child!
        while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
        {
            pSave = nodes.top();
            nodes.pop();
        }
        
        return *this;
    }
    
    BSTIterator <T>   operator -- (int postfix) {
        BSTIterator <T> itReturn = *this;
        --(*this);
        return itReturn;
    }
    
    // must give friend status to remove so it can call getNode() from it
    friend void BST <T> :: remove(BSTIterator <T> & it);
    
private:
    
    // get the node pointer
    BNode <T> * getNode() { return nodes.top(); }
    
    // the stack of nodes
    Stack < BNode <T> * > nodes;
};
    
    
  
};

    
    
} // namespace custom

#endif // BST_H





