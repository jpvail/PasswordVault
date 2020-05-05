#include <cassert> 
#include <memory> 
using namespace std;

struct Pw{
    string password_name;
    string password_real; 
    bool empty; 
    
    Pw(): empty(true), password_name(""), password_real("") {}

    Pw(string pword_name, string pword_real): 
    password_name(pword_name), password_real(pword_real), empty(true) {} 
    

    Pw& operator =(const Pw& other){
        password_name = other.password_name; 
        password_real = other.password_real;
        return *this;
    } 
}; 

class HashTable{
    private: 
        int nElements; 
        int maxSize; 
        int top; 
        Pw* array; 

        //hash function
        int hash(string password_name){
            int home = 7;
            for (int i = 0; i < password_name.size(); i++){
                home = home*31 + password_name[i];
            }
            return (home % maxSize); 
        } 

        //probe function
        int hash2(string password_name){
            int j, i; 
            for(i = 0; i < password_name.size(); i++){
                j += i * password_name[i]; 
            }
            return  (7 - j % 7); 
        }

    public: 

        HashTable(int sz){
            maxSize = sz; 
            array = new Pw [sz];
            top = maxSize-1;  
            nElements = 0; 
        }

        ~HashTable(){ delete[] array; }

        void clear(){
            delete[] array; 
            array = new Pw [maxSize]; 
            nElements = 0; 
        }

        void printAll(){
            for(int i = 0; i < maxSize; ++i ){
                cout << array[i].password_name << endl;
            }
        }

        void insert(string pword_name, string pword_real){
            assert(nElements < maxSize && "HashTable is full");
            
            int home = hash(pword_name); 

            if(array[home].empty != true){
                int i, j = 1;
                while(j < maxSize+1){
                     //double hashing
                    int i = (home + j*(hash2(pword_name)))%maxSize; 
                    if(array[i].empty == true){
                        array[i].password_name = pword_name; 
                        array[i].password_real = pword_real;
                        array[i].empty = false;
                        nElements++; 
                        return;
                    }
                    j++;
                }
            }else{
                array[home].password_name = pword_name; 
                array[home].password_real = pword_real;
                array[home].empty = false;
                nElements++; 
                return;
            }
            assert("Could not find location to insert");
        }

        //only used for updating database to allow for O(n) update
        bool pop(Pw* store){
            assert(nElements > 0 && "HashTable is empty");
            if(array[top].empty == false){
                *store = array[top];
                array[top].empty = true;
                top--;
                nElements--; 
                return true; 
            }
            top--;
            return false; 
        }

        bool remove(string name){
            assert(nElements > 0 && "HashTable is empty");
            
            int home = hash(name); 
            
            if(array[home].password_name != name){
                int i, j = 1;
                while(j < maxSize+1){
                    //double hashing
                    int i = (home + j*(hash2(name)))%maxSize; 
                    if(array[i].password_name == name){
                        array[i].empty = true; 
                        nElements--; 
                        return true;
                    }
                    j++;
                }
            }else{
                array[home].empty = true; 
                nElements--; 
                return true;
            }
            return false; 
        }


        void search(string name){
            assert( nElements > 0 && "Stack is empty");
            
            int home = hash(name); 

            if(array[home].password_name != name){
                int i, j = 1;
                while(j < maxSize+1){
                    int i = (home + j*(hash2(name)))%maxSize; 
                    if(array[i].password_name == name){
                        cout << array[i].password_real << endl; 
                        return;
                    }
                    j++;
                }
            }else{
                cout << array[home].password_real << endl;
                return;
            }
            cout << "NOT FOUND" << endl;

        }

        int count() { return nElements; }
        
};