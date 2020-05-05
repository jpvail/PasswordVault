#include <cassert> 
#include <memory> 
using namespace std; 

//used to return both password name and password itself from one function 
struct Pw{
    string password_name;  
    string password_real; 

    Pw& operator =(const Pw& other){
        password_name = other.password_name; 
        password_real = other.password_real;
        return *this;
    }
}; 

class Node{ 
    public: 
        string password_name; 
        string password; 
        Node* next; 
        Node* prev; 

        Node(string name, string pwrd, Node* prev = nullptr, Node* nxt = nullptr):
            password_name(name), password(pwrd), prev(prev), next(nxt) {}

        Node(Node* prev = nullptr, Node* nxt = nullptr):
            prev(prev), next(nxt) {}
};


class DoublyLinkedList{
    private: 
        
        int size; 
        Node* head; 
        Node* tail; 

        void initialize(){
            size = 0; 
            head = new Node(); 
            head->next = tail = new Node(head, nullptr);
        }
    
        void clearList(){
            Node* curr; 
            while(head != nullptr){
                curr = head; 
                head = head->next; 
                delete curr; 
            }
            size = 0; 
        }

    public: 

        DoublyLinkedList(){ initialize(); }

        ~DoublyLinkedList() { clearList(); }

        void clear() { clearList(); initialize(); }
       
        //O(1)
        //used whenever a password is added
        void push(string name, string pwrd){
            tail->prev = tail->prev->next = new Node(name, pwrd, tail->prev, tail);
            size++;
        }
        
        //O(1)  
        Pw pop(){
            assert(tail->prev != head && "Stack is empty");
            Pw ret = {.password_name = tail->prev->password_name,
                      .password_real = tail->prev->password}; 
            Node* temp = tail->prev; 
            tail->prev->prev->next = tail; 
            tail->prev = tail->prev->prev; 
            delete temp; 
            size--;
            return ret; 
        }


        //O(n)  
        void findPassword(string name){
            assert( size > 0 && "Stack is empty");
            bool check = true; 
            Node* curr = head; 
            for(int i = 0; i < size+1; ++i){
                if(curr->password_name == name){
                    //check = false; 
                    cout << curr->password << endl; 
                    return; 
                }
                curr = curr->next; 
            }
            if(check){
                cout << "NOT FOUND" << endl; 
            }
        }

        //O(n)
        //for removing specific passowrds 
        bool remove(string name){
            assert(size > 0 && "Stack is empty"); 
            Node* curr = head; 
            while(curr->next != tail && curr->next->password_name != name){
                curr = curr->next; 
            }
            if(curr->next == tail){
                return false; 
            }
            Node* temp = curr->next; 
            curr->next->next->prev = curr; 
            curr->next = curr->next->next; 
            delete temp; 
            size--; 
            return true; 
        }

        int length() { return size; }

};