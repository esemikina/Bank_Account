//Author: Yelizaveta Semikina, UIC, Spring 2021
//Assignment: Project 02

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void printAccBal(int acct, double balance) {
    cout << "Account " << acct << ":" << " balance" << " $" << balance << endl;
}



void checkArrays(int accounts[], double balances[], int N)
{
   cout << std::fixed;
   cout << std::setprecision(2);

   cout << "** Checking arrays..." << endl;
   cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
   cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}

int search(int accounts[], int N,int acct){
    for(int i = 0; i < N; i++) {
        
        if(accounts[i] == acct) {       
            return i; 
        }
    }
    
    return -1; 
}

int maxBalance(double balances[], int N){
    int index = 0;
    double highest = balances[0];
    for(int i = 0; i < N; i++) {
        if(balances[i] > highest){
            highest = balances[i]; 
            index = i;
        }
    }

    return index; 
}



int main() {

    cout << std::fixed;
    cout << std::setprecision(2); 
    
    string filename;
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    cout << "Enter bank filename> " << endl;
    cin >> filename;
    
    cout << "** Inputting account data..." << endl;
    
    ifstream infile; 
    infile.open(filename);
    if (!infile.good()) {
        cout << "**Error: unable to open input file '" << filename << "'" << endl;
        return 0;
    }
    int account, N;
    double balance;

    infile >> N;
    // Declare arrays: accounts and balances
    int* accounts = new int[N];
    double* balances = new double[N];
 
    for(int i = 0; i < N; i++) {
        infile >> accounts[i] >> balances[i];  
    }
    

    infile.close();


    checkArrays(accounts, balances, N);
    
    cout << "** Processing user commands..." << endl; 
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
 
    string com;
    cin >> com; 
   
    
    
    while(com != "x"){
        if(com == "+"){
         
            cin >> account;
            cin >> balance; 
            // Search for the account
            int idx = search(accounts, N, account);
            // Add balance to that account
            if(idx != -1) { 
                balances[idx] += balance;
                // output account info
                printAccBal(accounts[idx], balances[idx]);
            } else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if(com == "-"){
        
            cin >> account;
            cin >> balance; 
            // Search for the account
            int idx = search(accounts, N, account);
            // Substract balance to that account
            if(idx != -1) {
                balances[idx] -= balance;
                printAccBal(accounts[idx], balances[idx]);
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if(com == "?"){
        
            int account;
            cin >> account;
            // search the account and get the index
            int idx = search(accounts, N, account);
            if(idx != -1) {
                printAccBal(accounts[idx], balances[idx]);
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if(com == "^"){
       
            // get the index of the max balance account
            int idx = maxBalance(balances, N);
   
            printAccBal(accounts[idx], balances[idx]);
        }
        else if(com == "*"){
            // From low to high
            int acc1, acc2;
            cin >> acc1;
            cin >> acc2;
            for(int i = 0; i < N; i++) {
                if(accounts[i] >= acc1 && accounts[i] <= acc2) {
                    printAccBal(accounts[i], balances[i]);
                }
            }
        }
         else if(com == "<"){//List of accounts with negative balance
            
             for(int i= 0; i < N; i++){
                 if (balances[i] < 0 ){
                    printAccBal(accounts[i], balances[i]);
                 }
             }   
         }
        else if(com == "$"){
            //Total of all positive balances 
            // declaring sum
            double sum = 0; 
             
            // Iterating through all elements, finding positive and adding them up
            for (int i = 0; i < N; i++) {
  
                if(balances[i] > 0){
                     sum += balances[i];
                } 
             }
            cout << "Total deposits: $" << sum << endl;
        }
        else if(com == "add"){
            // update N to new_size     
            N = N + 1;      
            // create new array
            int *new_accounts = new int[N];     
            double *new_balances = new double[N]; 
            // coping from original to new ones

                                     
            for(int i = 0; i < N-1; i++){ 
                new_accounts[i] = accounts[i]; 
                new_balances[i] = balances[i];
            }
            
            // delete old ptrs values
            delete [] accounts; 
            delete [] balances; 


            

            // getting the largest acc
            int largest_account_number = new_accounts[N-2]; 
            // store the new acc number with it's balance
                                    
            new_accounts[N-1] = largest_account_number + 1; 
            new_balances[N-1] = 0.0;
            
            accounts = new_accounts; 
            balances = new_balances;
            cout << "Added account " << accounts[N-1] << ":" << " balance" << " $" << balances[N-1] << endl;
        } 
        
        else if(com == "del") { 
            int delete_account;
            cin >> delete_account;
            // search for account index
            int idx = search(accounts, N, delete_account);
            if (idx != -1) {
                // create new arrays of a new size N - 1
                int* new_accounts = new int[N-1];
                double* new_balances = new double[N-1];
                // shift elemets to the left 
                for(int i = idx; i < N-1; i++) {
                    accounts[i] = accounts[i+1]; 
                    balances[i] = balances[i+1]; 
                }
                // copy until N-1
                for(int i = 0; i < N-1; i++) {
                    new_accounts[i] = accounts[i]; 
                    new_balances[i] = balances[i]; 
                }
                delete [] accounts;
                delete [] balances;
                // fix pointers
                accounts = new_accounts; 
                balances = new_balances; 
                // decrease size by 1
                N = N - 1;
                cout << "Deleted account " << delete_account << endl;
            } else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
       }

        else {
            cout << "** Invalid command, try again..." << endl; 
        }
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
        cin >> com;
    }

   
    cout << "** Saving account data..." << endl;
    cout << "** Done **" << endl; 
   
     // file output
    ofstream outfile; 
    outfile.open(filename);
    outfile << N << endl;
    outfile << fixed << setprecision(2);
    for(int i = 0; i < N; i++) {
        outfile << accounts[i] << " " << balances[i]  << endl;
    }
    outfile.close();
    
    delete [] accounts;
    delete [] balances;
    
    return 0;
}
