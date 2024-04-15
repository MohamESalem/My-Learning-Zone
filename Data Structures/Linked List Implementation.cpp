
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

//exception
class BadIterator : public std::exception {
public:
    const char* what() const throw() {
        return "Invalid iterator";
    }
};

// this incomplete declaration is for the friend class
template <typename Object>
class linkedList;

template <typename Object>
class linkedListItr;

// Node class
template <typename Object>
class linkedListNode
{
    linkedListNode(const Object &theElement = Object(), linkedListNode *n = NULL) : element(theElement), next(n) {}
    Object element;
    linkedListNode *next;
    friend class linkedList<Object>;
    friend class linkedListItr<Object>;
};

// Iterator classs
template <typename Object>
class linkedListItr
{
public:
    linkedListItr() : current(NULL) {}
    bool isValid() const
    {
        return current != NULL;
    }

    void advance()
    {
        if (isValid())
            current = current->next;
    }

    const Object &retrieve() const
    {
        if (!isValid())
            throw BadIterator();
        return current->element;
    }

private:
    linkedListNode<Object> *current;
    linkedListItr(linkedListNode<Object> *theNode) : current(theNode) {}

    friend class linkedList<Object>;
};

// linked list class
template <typename Object>
class linkedList
{
public:
    linkedList();
    linkedList(const linkedList &rhs);
    ~linkedList();

    bool isEmpty() const;
    void makeEmpty();
    linkedListItr<Object> zeroth() const;
    linkedListItr<Object> first() const;
    void insert(const Object &x, const linkedListItr<Object> &p);
    linkedListItr<Object> find(const Object &x) const;
    linkedListItr<Object> findPrevious(const Object &x) const;
    void remove(const Object &x);
    const linkedList &operator=(const linkedList &rhs);

private:
    linkedListNode<Object> *header;
};

template <typename Object>
linkedList<Object>::linkedList()
{
    header = new linkedListNode<Object>;
}

template <typename Object>
bool linkedList<Object>::isEmpty() const
{
    return header->next == NULL;
}

template <typename Object>
linkedListItr<Object> linkedList<Object>::zeroth() const
{
    return linkedListItr<Object>(header);
}

template <typename Object>
linkedListItr<Object> linkedList<Object>::first() const
{
    return linkedListItr<Object>(header->next);
}

template <typename Object>
void printList(const linkedList<Object> &theList)
{
    if (theList.isEmpty())
        cout << "Empty List:" << endl;
    else
    {
        linkedListItr<Object> itr = theList.first();
        for (; itr.isValid(); itr.advance())
        {
            cout << itr.retrieve() << " ";
        }
    }
    cout << endl;
}

template <typename Object>
linkedListItr<Object> linkedList<Object>::find(const Object &x) const
{

    linkedListNode<Object> *p = header->next;

    while (p != NULL && p->element != x)
        p = p->next;

    return linkedListItr<Object>(p);
}

template <typename Object>
void linkedList<Object>::remove(const Object &x)
{

    linkedListNode<Object> *p = findPrevious(x).current;

    if (p->next != NULL)
    {

        linkedListNode<Object> *oldNode = p->next;
        p->next = p->next->next; // Bypass
        delete oldNode;
    }
}

template <typename Object>
linkedListItr<Object> linkedList<Object>::findPrevious(const Object &x) const
{

    linkedListNode<Object> *p = header;

    while (p->next != NULL && p->next->element != x)
        p = p->next;

    return linkedListItr<Object>(p);
}

template <typename Object>

void linkedList<Object>::insert(const Object &x, const linkedListItr<Object> &p)
{

    if (p.current != NULL)
        p.current->next = new linkedListNode<Object>(x, p.current->next);
}

// Make the list logically empty.
template <typename Object>
void linkedList<Object>::makeEmpty()
{
    while (!isEmpty())
        remove(first().retrieve());
}

// Destructor.
template <typename Object>
linkedList<Object>::~linkedList()
{
    makeEmpty();
    delete header;
}

template <typename Object>
linkedList<Object>::linkedList(const linkedList<Object> &rhs)
{
    header = new linkedListNode<Object>;
    *this = rhs;
}

// Deep copy of linked lists.
template <typename Object>
const linkedList<Object> &
linkedList<Object>::operator=(const linkedList<Object> &rhs)
{

    if (this != &rhs)
    {
        makeEmpty();
        linkedListItr<Object> ritr = rhs.first();
        linkedListItr<Object> itr = zeroth();
        for (; ritr.isValid(); ritr.advance(), itr.advance())
            insert(ritr.retrieve(), itr);
    }
    return *this;
}