#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <chrono>
#include "HT.hh"
using namespace std; 

string encrypt(string str){
    for(int i = 0; i < str.size(); ++i){
        str[i] -= 5; 
    }
    return str; 
}

string decrypt(string str){
    for(int i = 0; i < str.size(); ++i){
        str[i] += 5; 
    }
    return str; 
}

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
    string inputpassword, stored_password, prevSize;
    cout << "Insert login password: "; 
    cin >> inputpassword;  
    fstream myfile("database.txt");
    if(myfile.is_open()){
        myfile >> stored_password >> prevSize;  
        if(decrypt(stored_password).compare(inputpassword) == 0){
            myfile.close();
            try{ 
                *size = stoi(prevSize);
            }catch(...){
                cout << "Database Error: No number indicating size of database" << endl;
                exit(1); 
            }
            *loginpassword = stored_password; 
            return true; 
        }else{
            return false; 
        }
    }else{
        cout << "No database file in directory" << endl; 
        return false;
    }
}

void buildHT(HashTable* ht){
    ifstream myfile("database.txt"); 
    string passw_name, passw_real, oldstoredpassword; 
    int size; 
    myfile >> oldstoredpassword >> size;
    while (true){
        myfile >> passw_name >> passw_real;
        if(myfile.eof()) break; 
#if ADD_TESTING
        
        auto start = chrono::high_resolution_clock::now(); 
#endif 
        (*ht).insert(passw_name, decrypt(passw_real)); 
#if ADD_TESTING
        auto end = chrono::high_resolution_clock::now(); 
        double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-9; 
        cout << fixed  
        << time_taken << setprecision(9); 
        cout << endl; 
#endif
    }
    myfile.close(); 
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
    string password_name; 
    cout << "Name of password to be removed: ";
    cin >> password_name; 
#if REMOVE_TESTING
    cout << "Time taken to remove element from database with " << ht->count() << " elements: " << endl;     
    auto start = chrono::high_resolution_clock::now(); 
#endif
    if((*ht).remove(password_name)){
#if REMOVE_TESTING
        auto end = chrono::high_resolution_clock::now(); 
        double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-9; 
        cout << fixed  
        << time_taken << setprecision(9); 
        cout << endl; 
#endif
        cout << password_name << " was successfully removed\n";
    }else{
        cout << "No password with name: " << password_name << endl;
    }
}

void updateDataBase(HashTable* ht, string loginpassword){
    ofstream myfile("database.txt", std::ofstream::trunc);
    myfile << loginpassword + " " + to_string((*ht).count()) + "  " << endl;
    while((*ht).count() > 0){
        Pw temp; 
        if((*ht).pop(&temp)){
            myfile << temp.password_name << " " << encrypt(temp.password_real) << "\n"; 
        }
    }
    myfile.close();
}


void getPassword(HashTable* ht){
    string password_name; 
    cout << "Name of password to find: ";
    cin >> password_name; 
#if GET_TESTING
    auto start = chrono::high_resolution_clock::now(); 
#endif
    (*ht).search(password_name); 
#if GET_TESTING
    cout << "Time taken to get element from database with " << ht->count() << " elements: " << endl;
    auto end = chrono::high_resolution_clock::now(); 
    double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; 
    cout << fixed  
    << time_taken << setprecision(9); 
    cout << endl; 
#endif
}

bool interact_createAcct(){ 
    string pwrd1, pwrd2, quitorcont; 
    while((pwrd1.size() == 0 && pwrd2.size() == 0) || pwrd1.compare(pwrd2) != 0){
        cout << "Welcome. Create a password: "; 
        cin >> pwrd1; 
        cout << "Confirm new password: "; 
        cin >> pwrd2; 
        if(pwrd1.compare(pwrd2) != 0){
            cout  << "Passwords must match." << endl; 
        }
    }
    fstream myfile("database.txt"); 
    if(myfile.is_open()){
        myfile << encrypt(pwrd1) << " t\n";
        int errorcheck = 1; 
        int counter = 0; 
        while(errorcheck){
            errorcheck = 0; 
            cout << "Would you like to store new passwords (y / n)? ";
            cin >> quitorcont;
            if(quitorcont.compare("y") == 0){
                int insert_another_password = 1;
                while(insert_another_password){
                    counter++;
                    string password_name, password, another; 
                    cout << "Insert name for this password (Must start with a letter): ";
                    cin >> password_name;   
                    cout << "Insert password (will be encrypted): ";
                    cin >> password;
                    myfile << password_name << " " << encrypt(password) << " \n"; 
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
                myfile.seekp(pwrd2.size()+1);
                myfile << to_string(counter);
                myfile.close(); 
                return true; 
            }else if(quitorcont.compare("n") == 0){
                myfile.close(); 
                return true; 
            }else{
                errorcheck = 1; 
            }
        }
        return false;
    }else{
        cout << "No database file in directory" << endl; 
        return false;
    }
}


int main(int argc, char *argv[]){
    if(checkForDataBase()){
        if(checkForAcct()){
            bool loggedin = false; 
            string loginpassword; 
            int size; 

            while(!(loggedin)){
                loggedin = interact_login(&loginpassword, &size); 
            }
            int newsz = size*2 + 10; 
            HashTable* ht = new HashTable(newsz); 
            buildHT(ht);
            string addorget; 
            cout << "Would you like to add, get, or remove a password (a / g / r)? "; 
            cin >> addorget; 
            if(addorget.compare("a") == 0){
                insertNewPassword(ht);
                updateDataBase(ht, loginpassword); 
            }else if(addorget.compare("g") == 0){
#if SHOW_HT
                (*ht).printAll();
#endif
                getPassword(ht);
            }else if(addorget.compare("r") == 0){
                removePassword(ht);
                updateDataBase(ht, loginpassword);
            }else{
                cout << "Only respond, a r or g\n"; 
            }
            delete ht; 
        }else{
            interact_createAcct(); 
        }
    }
    return 0;
}


