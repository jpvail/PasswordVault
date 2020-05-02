#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <chrono>
#include "HT.hh"
using namespace std; 

//same as other version 
string encrypt(string str){
    for(int i = 0; i < str.size(); ++i){
        str[i] -= 5; 
    }
    return str; 
}

//same as other version 
string decrypt(string str){
    for(int i = 0; i < str.size(); ++i){
        str[i] += 5; 
    }
    return str; 
}

//same as other version 
bool checkForDataBase(){
    ifstream myfile("database.txt");
    if(myfile.is_open()){
        myfile.close(); 
        return true;
    }else{
        cout << "No database in directory" << endl;
        return false; 
    }
}

//same as other version 
bool checkForAcct(){
    string password; 
    ifstream myfile("database.txt"); 
    if(myfile.is_open()){
        getline(myfile, password); 
        myfile.close(); 
        if(password.size() > 0){
            return true; 
        }else{
            return false;  
        }
    }else{
        cout << "No database file in directory" << endl; 
        return false;  
    }
}

bool interact_login(string* loginpassword, int* size){

}

//O(n)
void buildHT(HashTable* ht){

}

void insertNewPassword(HashTable* ht){
    int insert_another_password = 1;
    while(insert_another_password){
        string password_name, password, another; 
        cout << "Insert name for this password (For better preformance, use a word): ";
        cin >> password_name;   
        cout << "Insert password (will be encrypted): ";
        cin >> password;
        (*ht).insert(password_name, password);
        int y = 1; 
        while(y){
            y = 0;
            cout << "Would you like to store another (y / n)? ";
            cin >> another;
            if(another.compare("y") == 0){
                insert_another_password = 1;
            }else if(another.compare("n") == 0){
                insert_another_password = 0; 
            }else{
                y = 1;
            }
        }
    } 
}

void removePassword(HashTable* ht){

}

void updateDataBase(HashTable* ht, string loginpassword){

}


void getPassword(HashTable* ht){
    string password_name; 
    cout << "Name of password to find: ";
    cin >> password_name; 
    (*ht).search(password_name); 
}

//same as other version 
bool interact_createAcct(){ 

  
}

//same as other version 
bool interact_createAcct(){ 
}



int main(int argc, char *argv[]){
    
}
