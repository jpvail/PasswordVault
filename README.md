# Password Vault Documentation 

Password Vault is a unique comamnd line application that stores your passwords in an encrypted format within a secure efficient database that is directly on your computer and only accessible by you. Unlike other applications which may store your data on a remote server, all of your data is saved locally so there are no privacy concerns. 

Users create an account after opening the application for the first time which involves creating a password that is used to log into the application in the future. After logging in, the user has the option to either add one or multiple  passwords to the their account, or remove an already existing password from their account, or get an existing password by simply typing in the password's name that was specified when the password was first added. 

Password Vault is unique in that it stores all of your information in a textfile located in the same directory as the application executable itself. However, all of the private data within the textfile is encrypted using a secret formula. 

## The application is available in two versions: 
- One which uses a doubly linked list for constant time insertion capabilities. 
- One which uses a hash table for faster search and remove capabilities. 

