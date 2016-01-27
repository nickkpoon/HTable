/*
 * CS130A Proj1
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;
const int TSIZE = 5;
 
/*
 * HashNode Class Declaration
 */
class HashNode
{
    public:
        int key;
        int value;
        HashNode(int key, int value)
        {
            this->key = key;
            this->value = value;
        }
};
 
/*
 * DeletedNode Class Declaration
 */
class DeletedNode:public HashNode
{
    private:
        static DeletedNode *entry;
        DeletedNode():HashNode(-1, -1)
        {}
    public:
        static DeletedNode *getNode()
        {
            if (entry == NULL)
                entry = new DeletedNode();
            return entry;
        }
};
DeletedNode *DeletedNode::entry = NULL;
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        HashNode **htable;
    public:
        HashMap()
        {
            htable = new HashNode* [TSIZE];
            for (int i = 0; i < TSIZE; i++)
            {
                htable[i] = NULL;
            }
        }
 
        ~HashMap()
        {
            for (int i = 0; i < TSIZE; i++)
            {
                if (htable[i] != NULL && htable[i] != DeletedNode::getNode())
                    delete htable[i];
            }
            delete[] htable;
        }
        /*
         * Hash Function
         */
        int HashFunc(int key)
        {
            return key % TSIZE;
        }
        /*
         * Insert Element at a key
         */
        void Insert(int key, int value)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            int deletedindex = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                if (htable[hash_val] == DeletedNode::getNode())
                    deletedindex = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (htable[hash_val] == NULL || hash_val == init)
            {
                if(deletedindex != -1)
                    htable[deletedindex] = new HashNode(key, value);
                else
                    htable[hash_val] = new HashNode(key, value);
            }
            if(init != hash_val)
            {
                if (htable[hash_val] != DeletedNode::getNode())
                {
                    if (htable[hash_val] != NULL)
                    {
                        if (htable[hash_val]->key == key)
                            htable[hash_val]->value = value;
                    }
                }
                else
                    htable[hash_val] = new HashNode(key, value);
            }
        }
        /*
         * Search Element at a key
         */
        int Search(int key)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (htable[hash_val]==NULL || hash_val==init)
                return -1;
            else
                return htable[hash_val]->value;
        }
        /*
         * Remove Element at a key
         */
        void Remove(int key)
        {
            int hash_val = HashFunc(key);
            int init = -1;
            while (hash_val != init&&(htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL&&htable[hash_val]->key!=key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hash_val != init && htable[hash_val] != NULL)
            {
                delete htable[hash_val];
                htable[hash_val] = DeletedNode::getNode();
            }
        }
};
 
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash;
    int key, value;
    double gpa;
    int choice;
    string input;
    string operation;
    string name;
    //double gpa;
    while(1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        //cin>>choice;
        getline (cin,input);
        stringstream stream(input);

        stream >> operation;
        stream >> value;
        //stream >> name;
        
        //stream >> gpa;
        stream >> key;

        if(operation == "insert")
            choice = 1;
        else if (operation == "lookup")
            choice = 2;
        else if (operation == "remove")
            choice = 3;



        switch(choice)
        {
        case 1:
            /*
            cout<<"Enter element to be inserted: ";
            cin>>value;
            cout<<"Enter key at which element to be inserted: ";
            cin>>key;
            */

            hash.Insert(key, value);
            cout<<"item successfully inserted"<<endl;
            break;
        case 2:
            /*
            cout<<"Enter key of the element to be searched: ";
            cin>>key;
            */
            if(hash.Search(key) == -1)
            {
                cout<<"No element found at key "<<key<<endl;
                continue;
            }
            else
            {
                cout<<"Element at key "<<key<<" : ";
                cout<<hash.Search(key)<<endl;
            }
            break;
        case 3:
            
            hash.Remove(key);
            cout<<"item successfully deleted"<<endl;
            break;

        case 4:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}