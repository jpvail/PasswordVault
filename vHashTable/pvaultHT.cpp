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

}

void removePassword(HashTable* ht){

}

void updateDataBase(HashTable* ht, string loginpassword){

}


void getPassword(HashTable* ht){

}

//same as other version 
bool interact_createAcct(){ 

  
}


int main(int argc, char *argv[]){
    
}


