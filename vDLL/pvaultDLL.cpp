#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <chrono> 
#include "DLL.hh"
using namespace std; 


string encrypt(string str){
����for(int i = 0; i < str.size(); ++i){
��������str[i] -= 5; 
����}
����return str; 
}

string decrypt(string str){
����for(int i = 0; i < str.size(); ++i){
��������str[i] += 5; 
����}
����return str; 
}

bool checkForDataBase(){
����ifstream myfile("database.txt");
����if(myfile.is_open()){
��������myfile.close(); 
��������return true;
����}else{
��������cout << "No database in directory" << endl;
��������return false; 
����}
}

bool checkForAcct(){
����string password; 
����ifstream myfile("database.txt"); 
����if(myfile.is_open()){
��������getline(myfile, password); 
��������myfile.close(); 
��������if(password.size() > 0){
������������return true; 
��������}else{
������������return false;��
��������}
����}else{
��������cout << "No database file in directory" << endl; 
��������return false;��
����}
}


bool interact_login(string* loginpassword){
    string inputpassword, stored_password;
    cout << "Insert login password: "; 
    cin >> inputpassword;  
    fstream myfile("database.txt");
    if(myfile.is_open()){
        getline(myfile, stored_password);
        if(decrypt(stored_password).compare(inputpassword) == 0){
            myfile.close();
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

void buildDLLStack(DLLStack* dlls){
    ifstream myfile("database.txt"); 
    string passw_name, passw_real, oldstoredpassword; 
    myfile >> oldstoredpassword;
    while (true){
        myfile >> passw_name;
        myfile >> passw_real;
        if(myfile.eof()) break; 
        //auto start = chrono::high_resolution_clock::now();
        (*dlls).push(passw_name, decrypt(passw_real));
        /*auto end = chrono::high_resolution_clock::now();
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-9; 
        cout << fixed  
        << time_taken << setprecision(9); 
        cout << endl; */
    }
    myfile.close(); 
}

void insertNewPassword(DLLStack* dlls){
    int insert_another_password = 1;
    while(insert_another_password){
        string password_name, password, another; 
        cout << "Insert name for this password: ";
        cin >> password_name;   
        cout << "Insert password (will be encrypted): ";
        cin >> password;
        (*dlls).push(password_name, password);
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

void removePassword(DLLStack* dlls){
����string password_name; 
����cout << "Name of password to be removed: ";
����cin >> password_name; 
���// auto start = chrono::high_resolution_clock::now();
����if((*dlls).remove(password_name)){
�������// auto end = chrono::high_resolution_clock::now();
��������//double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
��������/*time_taken *= 1e-9; 
��������cout << fixed��
��������<< time_taken << setprecision(9); 
��������cout << endl; 
��������cout << password_name << " was successfully removed\n";*/
����}else{
��������cout << "No password with name: " << password_name << endl;
����}
}

void updateDataBase(DLLStack* dlls, string loginpassword){
    ofstream myfile("database.txt", std::ofstream::trunc);
    myfile << loginpassword << endl;
    while((*dlls).length() > 0){
        Pw temp = (*dlls).pop();
        myfile << temp.password_name << " " << encrypt(temp.password_real) << "\n"; 
    }
    myfile.close();
}

void getPassword(DLLStack* dlls){
    string password_name; 
    cout << "Name of password to find: ";
    cin >> password_name; 
    //auto start = chrono::high_resolution_clock::now();
    (*dlls).findPassword(password_name); 
   /* auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; 
    cout << fixed  
    << time_taken << setprecision(9); 
    cout << endl; */
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
        myfile << encrypt(pwrd1) << "\n";
        int errorcheck = 1; 
        while(errorcheck){
            errorcheck = 0; 
            cout << "Would you like to store new passwords (y / n)? ";
            cin >> quitorcont;
            if(quitorcont.compare("y") == 0){
                int insert_another_password = 1;
                while(insert_another_password){
                    string password_name, password, another; 
                    cout << "Insert name for this password: ";
                    cin >> password_name;   
                    cout << "Insert password (will be encrypted): ";
                    cin >> password;
                    myfile << password_name << " " << encrypt(password) << '\n'; 
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
                myfile.close(); 
                return true; 
            }else if(quitorcont.compare("n") == 0){
                myfile.close(); 
                return true; 
            }else{
                errorcheck = 1; 
            }
        }
    }else{
        cout << "No database file in directory" << endl; 
        return false;
    }
}


int main(int argc, char *argv[]){
    if(checkForDataBase()){
        if(checkForAcct()){
            bool loggedin = false; 
            //need password for updating database
            string loginpassword; 
            while(!(loggedin)){
                loggedin = interact_login(&loginpassword); 
            }
            DLLStack dlls; 
            buildDLLStack(&dlls);
            string addorget; 
            cout << "Would you like to add, get, or remove a password (a / g / r)? "; 
            cin >> addorget; 
            if(addorget.compare("a") == 0){
                insertNewPassword(&dlls);
                updateDataBase(&dlls, loginpassword); 
            }else if(addorget.compare("g") == 0){
                getPassword(&dlls);
            }else if(addorget.compare("r") == 0){
                removePassword(&dlls);
                //auto start = chrono::high_resolution_clock::now(); 
                updateDataBase(&dlls, loginpassword);
                /*auto end = chrono::high_resolution_clock::now(); 
                double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
                time_taken *= 1e-9; 
                cout << fixed  
                << time_taken << setprecision(9); 
                cout << endl; */
            }else{
                cout << "Only respond, a r or g\n"; 
            }
        }else{
            interact_createAcct(); 
        }
    }
    return 0;
}


