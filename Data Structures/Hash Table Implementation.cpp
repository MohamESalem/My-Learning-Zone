// Hash table Implementation

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename Object>
class ItemNotFoundException : public exception
{
public:
    const char *what() const throw()
    {
        return "Item not found in hash table.";
    }
};

template <typename Object>
class DuplicateItemException : public exception
{
public:
    const char *what() const throw()
    {
        return "Duplicate item found in hash table.";
    }
};


//*********************************************************************************************
template <typename Object>
class HashTable
{
public:
    HashTable();
    void makeEmpty();
    Object *find(const Object &x) const;
    void insert(const Object &x);
    void remove(const Object &x);

    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

private:
    struct HashEntry
    {
        Object element;
        EntryType info;
        HashEntry(const Object &e = Object(), EntryType i = EMPTY)
            : element(e), info(i) {}
    };
    vector<HashEntry> array;
    int occupied;
    bool isActive(int currentPos) const;
    int findPos(const Object &x) const;
    void rehash();
};
template <typename Object>
unsigned int hash(const Object &key);

// constructor

template <typename Object>
HashTable<Object>::HashTable() : array(nextPrime(101))
{
    makeEmpty();
}

template <typename Object>
void HashTable<Object>::makeEmpty()
{
    occupied = 0;
    for (int i = 0; i < array.size(); i++)
    {
        array[i].info = EMPTY;
    }
}

template <typename Object>
Object *HashTable<Object>::find(const Object &x) const
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return *array[currentPos].element;
    else
        return nullptr;
}

template <typename Object>
bool HashTable<Object>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template <typename Object>
void HashTable<Object>::remove(const Object &x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
    {
        array[currentPos].info = DELETED;
    }
    else
    {
        throw ItemNotFoundException();
    }
}

template <typename Object>
void HashTable<Object>::insert(const Object &x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
    {
        throw DuplicateItemException();
    }

    array[currentPos] = HashEntry(x, ACTIVE);
    if (++occupied > array.size() / 2)
    {
        rehash();
    }
}

template <typename Object>
void HashTable<Object>::rehash()
{
    vector<HashEntry> oldArray = array;
    array.resize(nextPrime(2 * oldArray.size()));
    for (int j = 0; j < array.size(); j++)
    {
        array[j].info = EMPTY;
    }
    makeEmpty();
    for (int i = 0; j < oldArray.size(); i++)
    {
        if (oldArray[i].info == ACTIVE)
        {
            insert(oldArray[i].element);
        }
    }
}

template <typename Object>
int HashTable<Object>::findPos(const Object &x) const
{
    int i = 0;
    int currentPos = hash(x) & array.size();
    while (array[currentPos].info != EMPTY && array[currentPos].element != x)
    {
        currentPos += 2 * ++i - 1;
        if (currentPos >= array.size())
        {
            currentPos -= array.size();
        }
    }
    return currentPos;
}

// genertic hash function
template <typename Object>
unsigned int hash(const Object &key)
{
    unsigned int hashVal = 0;
    const char *keyp = reinterpret_cast<const char *>(&key);
    for (size_t i = 0; i < sizeof(Object); i++)
    {
        hashVal = 37 * hashVal + keyp[i];
    }

    return hashVal;
}