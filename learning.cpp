#include <iostream>
#include <list>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

class BST {
private:
    struct Node{
        int data;
        Node* left;
        Node* right;
    };

    Node* root = nullptr;



public:
    void add(int value){
        Node* newNode = new Node;
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right= nullptr;

        if (root=nullptr)
        {
            root = newNode;
            return;
        }

        Node* temp = root;
        Node* parent = nullptr;
        while (temp!=nullptr)
        {
            parent = temp;
            if (value<=temp->data)
            {
                temp = temp->left;
            }

            else
            {
                temp=temp->right;
            }
            
            
        }

        if (value<=parent->data)
        {
            parent->left = newNode;
        }

        else
        {
            parent->right = newNode;
        }
        
    }


};