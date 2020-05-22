
// COS30008, Tutorial 10, 2020

#pragma once

#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"

#include <stdexcept>

#include "Stages.h"

template<class T> 
class List
{
private:
	// auxiliary definition to simplify node usage
	typedef DoublyLinkedNode<T> Node;

	Node* fTop;		// the first element in the list
	Node* fLast;	// the last element in the list
	int fCount;		// number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
    typedef DoublyLinkedNodeIterator<T> Iterator;

#ifdef A
    List()
    {
        fTop = &Node::NIL;
        fLast = &Node::NIL;
        fCount = 0;
    }// default constructor - creates empty list
#endif
    
	~List() 						        // destructor - frees all nodes
    {
        while ( fTop != &Node::NIL )
        {
            Node* temp = (Node *)&fTop->getNext();  // get next node (to become top)
            fTop->remove();                         // move first node
            delete fTop;                            // free node memory
            fTop = temp;                            // make temp the new top
        }
    }
    
	bool isEmpty() const	                // Is list empty?
    {
        return fTop == &Node::NIL;
    }
    
	int size() const                		// list size
    {
        return fCount;
    }

	void push_front( const T& aElement )	// adds a node initialized with aElement at front
    {
        Node* lNewElement = new Node( aElement );    // create a new node

        if ( fTop == &Node::NIL )                    // Is this the first node?
        {
            fTop = lNewElement;                        // make lNewNode first node
            fLast = lNewElement;                    // make lNewNode last node as well
        }
        else
        {
            fTop->push_front( *lNewElement );       // make lNewElement previous of top
            fTop = lNewElement;                        // make lNewNode first node
        }

        fCount++;                                    // increment count
    }
    
#ifdef B
    void push_back(const T& aElement)
    {
        Node* lNewElement = new Node(aElement);
        if (fLast == &Node::NIL)                    // Is this the first node?
        {
            fTop = lNewElement;                        // make lNewNode first node
            fLast = lNewElement;                    // make lNewNode last node as well
        }
        else
        {
            fLast->push_back(*lNewElement);         // make lNewElement next from last
            fLast = lNewElement;                        // make lNewNode last node
        }

        fCount++;
    }// adds a node initialized with aElement at back
#endif
	
#ifdef C
    void remove(const T& aElement)
    {
        Node* lNode = fTop;
        while (lNode != &Node::NIL)
        {
            if (lNode->getValue() == aElement) 
            {
                break;
            }
            lNode = (Node*)&lNode->getNext();
        }// Position lNode on node matching aElement or Node::NIL

        if (lNode != &Node::NIL)
        {
            if (lNode == fTop)
            {
                fTop = (Node*)&fTop->getNext();
            }
            if (lNode == fLast)
            {
                fLast = (Node*)&fLast->getPrevious();
            }
            lNode->remove();
            delete lNode;
            fCount--;
        }
    }// remove node, if fTop/fLast adjust the list accordingly.
#endif

#ifdef D
    const T& operator[](size_t aIndex) const
    {
        if (aIndex + 1 > fCount)
        {
            throw std::range_error("Index out of range.");
        }
        
        Node* temp = fTop;
        while (aIndex) 
        {
            temp = (Node*)&temp->getNext();
            aIndex--;
        }
        return temp->getValue();
    }// list indexer
#endif

#ifdef A
    Iterator begin() const
    {
        return Iterator(*fTop);
    }// return a forward iterator
    Iterator end() const  
    {
        return begin().end();
    }// return a forward end iterator
    Iterator rbegin() const
    {
        return begin().rbegin();
    }// return a backwards iterator
    Iterator rend() const
    {
        return begin().rend();
    }// return a backwards end iterator
#endif
};
