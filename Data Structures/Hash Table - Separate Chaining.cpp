#include <iostream>
#include <list>
#include <cstring>
using namespace std;

//hash table using separate chaining

class hashTable {
    private:
        static const int hashGroups = 10;
        list<pair<int, string>> table[hashGroups];
    
    public:
        bool isEmpty() const;
        int hashFunction(int key);
        void insertItem(int key, string value);
        void removeItem(int key);
        string searchItem(int key);
        void printTable();
};

bool hashTable::isEmpty() const
{
    int sum;
    for (int i = 0; i < hashGroups; i++)
    {
        sum += table[i].size();
    }
    
    return !sum;
}

int hashTable::hashFunction(int key)
{
    return key& hashGroups;
}

void hashTable::insertItem(int key, string value)
{
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++)
    {
        if (bItr->first == key)
        {
            keyExists = true;
            bItr->second = value;
            break;
        }
        
    }

    if (!keyExists)
    {
        cell.emplace_back(key, value);
    }

    return;
    
    
}

void hashTable::removeItem(int key)
{
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++)
    {
        if (bItr->first == key)
        {
            keyExists = true;
            bItr = cell.erase(bItr);
            break;
        }
        
    }

    if (!keyExists)
    {
        cout<< "Item doesn't exist." <<endl;
    }

    return;
}

void hashTable::printTable()
{
    for (int i = 0; i < hashGroups; i++)
    {
        if (table[i].size()==0) continue;

        auto bItr = table[i].begin();
        for (; bItr!=table[i].end(); bItr++)
        {
            cout<< "Key: " << bItr->first << " Value: " << bItr->second <<endl;
        }
        
        
    }
    return;
    
}

//better hash table implementation
// reference: https://www.youtube.com/watch?v=2_3fR-k-LzI