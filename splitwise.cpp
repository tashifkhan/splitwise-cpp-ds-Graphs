#include<iostream>
//#include<iomanip>
#include<bits/stdc++.h>
#include<queue>

using namespace std;

struct Account {
    int acc_no;
    string name;
    double balance;

    // Constructor to initialize account details
    Account(int acc, string n, double bal) : acc_no(acc), name(n), balance(bal) {}

    // Display account details
    void display() {
        cout << "Account Number: " << acc_no << "\n";
        cout << "Name: " << name << "\n";
        cout << "Balance: $" << balance << "\n\n";
    }
};

void create_account(queue<Account>& accounts) {
    system("cls");
    int accNo;
    string name;
    double initialBalance;

    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;

    Account newAccount(accNo, name, initialBalance);
    accounts.push(newAccount);
    cout << "Account created successfully!\n";
}

void display_all_accounts(queue<Account> accounts) {
    system("cls");
    if (accounts.empty()) {
        cout << "No accounts found!\n";
    } else {
        cout << "===== ACCOUNT DETAILS =====\n";
        while (!accounts.empty()) {
            Account currentAccount = accounts.front();
            accounts.pop();
            currentAccount.display();
        }
    }
}

void deposit(queue<Account>& accounts, int accNo, double amount) {
    system("cls");
    queue<Account> tempQueue;
    bool found = false;

    while (!accounts.empty()) {
        Account currentAccount = accounts.front();
        accounts.pop();

        if (currentAccount.acc_no == accNo) {
            currentAccount.balance += amount;
            tempQueue.push(currentAccount);
            found = true;
        } else {
            tempQueue.push(currentAccount);
        }
    }

    accounts = tempQueue;

    if (!found) {
        cout << "Account not found!\n";
    } else {
        cout << "Amount deposited successfully!\n";
    }
}

void withdraw(queue<Account>& accounts, int accNo, double amount) {
    system("cls");
    queue<Account> tempQueue;
    bool found = false;

    while (!accounts.empty()) {
        Account currentAccount = accounts.front();
        accounts.pop();

        if (currentAccount.acc_no == accNo) {
            if (currentAccount.balance >= amount) {
                currentAccount.balance -= amount;
                tempQueue.push(currentAccount);
                found = true;
            } else {
                cout << "Insufficient balance!\n";
                tempQueue.push(currentAccount);
            }
        } else {
            tempQueue.push(currentAccount);
        }
    }

    accounts = tempQueue;

    if (!found) {
        cout << "Account not found!\n";
    } else {
        cout << "Amount withdrawn successfully!\n";
    }
}

void deleteAccount(queue<Account>& accounts, int accNo)
{
    system("cls");
    queue<Account> tempQueue;

    // Search for the account to delete and enqueue other accounts to tempQueue
    while (!accounts.empty())
    {
        Account currentAccount = accounts.front();
        accounts.pop();

        if (currentAccount.acc_no != accNo)
        {
            tempQueue.push(currentAccount);
        }
        else
        {
            // Display a message indicating that the account has been deleted
            cout << "Account with Account Number " << accNo << " has been deleted.\n";
        }
    }

    // Copy back the customers from tempQueue to customerQueue
    while (!tempQueue.empty())
    {
        accounts.push(tempQueue.front());
        tempQueue.pop();
    }
}


void update_account(queue<Account>& accounts, int accNo) {
    system("cls");
    queue<Account> tempQueue;
    bool found = false;

    while (!accounts.empty()) {
        Account currentAccount = accounts.front();
        accounts.pop();

        if (currentAccount.acc_no == accNo) {
            // Assuming "update" means modifying the account name
            string newName;
            cout << "Enter new name for the account: ";
            cin >> newName;

            currentAccount.name = newName; // Updating account name
            tempQueue.push(currentAccount);
            found = true;
        } else {
            tempQueue.push(currentAccount);
        }
    }

    accounts = tempQueue; // Restoring the modified queue

    if (!found) {
        cout << "Account not found!\n";
    } else {
        cout << "Account updated successfully!\n";
    }
}


class bank
{
    public:
    string name;
    int netAmount;
    set<string> types;
};

int getMinIndex(bank listOfNetAmounts[],int numBanks)
{
    int min=INT_MAX, minIndex=-1;
    for(int i=0;i<numBanks;i++)
    {
        if(listOfNetAmounts[i].netAmount == 0)
        {
             continue;
        }

        if(listOfNetAmounts[i].netAmount < min)
        {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(bank listOfNetAmounts[],int numBanks)
{
    int max=INT_MIN, maxIndex=-1;
    for(int i=0;i<numBanks;i++)
    {
        if(listOfNetAmounts[i].netAmount == 0)
        {
            continue;
        }
        if(listOfNetAmounts[i].netAmount > max)
        {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

pair<int,string> getMaxIndex(bank listOfNetAmounts[],int numBanks,int minIndex,bank input[],int maxNumTypes)
{
    int max=INT_MIN;
    int maxIndex=-1;
    string matchingType;

    for(int i=0;i<numBanks;i++)
    {
        if(listOfNetAmounts[i].netAmount == 0)
        {
            continue;
        }


        if(listOfNetAmounts[i].netAmount < 0)
        {
            continue;
        }


        vector<string> v(maxNumTypes);
        vector<string>::iterator ls=set_intersection(listOfNetAmounts[minIndex].types.begin(),listOfNetAmounts[minIndex].types.end(), listOfNetAmounts[i].types.begin(),listOfNetAmounts[i].types.end(), v.begin());

        if((ls-v.begin())!=0 && max<listOfNetAmounts[i].netAmount )
        {
            max=listOfNetAmounts[i].netAmount;
            maxIndex=i;
            matchingType = *(v.begin());
        }
    }

    //if there is NO such max which has a common type with any remaining banks then maxIndex has -1
    // also return the common payment type
    return make_pair(maxIndex,matchingType);
}

void printAns(vector<vector<pair<int,string>>> ansGraph, int numBanks,bank input[]){

    cout<<"\nThe transactions for minimum cash flow are as follows : \n\n";
    for(int i=0;i<numBanks;i++)
        {
        for(int j=0;j<numBanks;j++)
        {

            if(i==j)
            {
                continue;
            }


            if(ansGraph[i][j].first != 0 && ansGraph[j][i].first != 0)
                {

                if(ansGraph[i][j].first == ansGraph[j][i].first)
                {
                    ansGraph[i][j].first=0;
                    ansGraph[j][i].first=0;
                }
                else if(ansGraph[i][j].first > ansGraph[j][i].first)
                {
                    ansGraph[i][j].first -= ansGraph[j][i].first;
                    ansGraph[j][i].first =0;

                    cout<<input[i].name<<" pays Rs" << ansGraph[i][j].first<< "to "<<input[j].name<<" via "<<ansGraph[i][j].second<<endl;
                }
                else
                {
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;

                    cout<<input[j].name<<" pays Rs "<< ansGraph[j][i].first<<" to "<<input[i].name<<" via "<<ansGraph[j][i].second<<endl;

                }
            }
            else if(ansGraph[i][j].first != 0)
            {
                cout<<input[i].name<<" pays Rs "<<ansGraph[i][j].first<<" to "<<input[j].name<<" via "<<ansGraph[i][j].second<<endl;

            }
            else if(ansGraph[j][i].first != 0)
            {
                cout<<input[j].name<<" pays Rs "<<ansGraph[j][i].first<<" to "<<input[i].name<<" via "<<ansGraph[j][i].second<<endl;

            }

            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    cout<<"\n";
}

void minimizeCashFlow(int numBanks,bank input[],unordered_map<string,int>& indexOf,int numTransactions,vector<vector<int>>& graph,int maxNumTypes)
{

    //Find net amount of each bank has
    bank listOfNetAmounts[numBanks];

    for(int b=0;b<numBanks;b++)
        {
        listOfNetAmounts[b].name = input[b].name;
        listOfNetAmounts[b].types = input[b].types;

        int amount = 0;
        //incoming edges
        //column traversals
        for(int i=0;i<numBanks;i++)
        {

            amount += (graph[i][b]);
        }

        //outgoing edges
        //row traverse
        for(int j=0;j<numBanks;j++)
        {
            amount += ((-1) * graph[b][j]);
        }

        listOfNetAmounts[b].netAmount = amount;
    }

    vector<vector<pair<int,string>>> ansGraph(numBanks,vector<pair<int,string>>(numBanks,{0,""}));//adjacency matrix


    //find min and max net amount
    int numZeroNetAmounts=0;

    for(int i=0;i<numBanks;i++)
    {
        if(listOfNetAmounts[i].netAmount == 0)
        {
            numZeroNetAmounts++;
        }

    }
    while(numZeroNetAmounts!=numBanks)
    {

        int minIndex=getMinIndex(listOfNetAmounts, numBanks);
        pair<int,string> maxAns = getMaxIndex(listOfNetAmounts, numBanks, minIndex,input,maxNumTypes);

        int maxIndex = maxAns.first;

        if(maxIndex == -1)
        {

            (ansGraph[minIndex][0].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[minIndex][0].second) = *(input[minIndex].types.begin());

            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            (ansGraph[0][simpleMaxIndex].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[0][simpleMaxIndex].second) = *(input[simpleMaxIndex].types.begin());

            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;

            if(listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;

            if(listOfNetAmounts[simpleMaxIndex].netAmount == 0) numZeroNetAmounts++;

        }
        else
        {
            int transactionAmount = min(abs(listOfNetAmounts[minIndex].netAmount), listOfNetAmounts[maxIndex].netAmount);

            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maxAns.second;

            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;

            if(listOfNetAmounts[minIndex].netAmount == 0)
            {
                numZeroNetAmounts++;
            }

            if(listOfNetAmounts[maxIndex].netAmount == 0)
            {
                numZeroNetAmounts++;
            }

        }

    }

    printAns(ansGraph,numBanks,input);
    // cout<<"HI\n";
}

void cashflow()
{
    system("cls");
    cout<<"\n\t\t\t\t********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n\n";
    cout<<"This system minimizes the number of transactions among multiple banks in the different corners of the world that use different modes of payment.There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment. \n\n";
    cout<<"Enter the number of banks participating in the transactions.\n";
    int numBanks;cin>>numBanks;

    bank input[numBanks];
    unordered_map<string,int> indexOf;//stores index of a bank

    cout<<"Enter the details of the banks and transactions as stated:\n";
    cout<<"Bank name ,number of payment modes it has and the payment modes.\n";
    cout<<"Bank name and payment modes should not contain spaces\n";

    int maxNumTypes;
    for(int i=0; i<numBanks;i++)
    {
        if(i==0)
        {
            cout<<"World Bank : ";
        }
        else
        {
            cout<<"Bank "<<i<<" : ";
        }
        cin>>input[i].name;
        indexOf[input[i].name] = i;
        int numTypes;
        cin>>numTypes;

        if(i==0)
        {
            maxNumTypes = numTypes;
        }


        string type;
        while(numTypes--)
        {
            cin>>type;

            input[i].types.insert(type);
        }

    }

    cout<<"Enter number of transactions.\n";
    int numTransactions;
    cin>>numTransactions;

    vector<vector<int>> graph(numBanks,vector<int>(numBanks,0));//adjacency matrix

    cout<<"Enter the details of each transaction as stated:";
    cout<<"Debtor Bank , creditor Bank and amount\n";
    cout<<"The transactions can be in any order\n";
    for(int i=0;i<numTransactions;i++)
    {
        cout<<(i)<<" th transaction : ";
        string s1,s2;
        int amount;
        cin >> s1>>s2>>amount;

        graph[indexOf[s1]][indexOf[s2]] = amount;
    }

    //settle
    minimizeCashFlow(numBanks,input,indexOf,numTransactions,graph,maxNumTypes);

}


int main() {
    queue<Account> accountQueue;

    int choice;
    do {
            system("cls");
        cout << "\n===== BANKING MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. cashflow\n";
        cout << "6. Delete\n";
        cout<<"7 update\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
           system("cls");
        switch (choice) {
            case 1:
                create_account(accountQueue);
                break;
            case 2:
                display_all_accounts(accountQueue);
                break;
            case 3:
                int depositAccNo;
                double depositAmt;
                cout << "Enter Account Number to Deposit: ";
                cin >> depositAccNo;
                cout << "Enter Amount to Deposit: $";
                cin >> depositAmt;
                deposit(accountQueue, depositAccNo, depositAmt);
                break;
            case 4:
                int withdrawAccNo;
                double withdrawAmt;
                cout << "Enter Account Number to Withdraw: ";
                cin >> withdrawAccNo;
                cout << "Enter Amount to Withdraw: $";
                cin >> withdrawAmt;
                withdraw(accountQueue, withdrawAccNo, withdrawAmt);
                break;
            case 5:
                cashflow();
            case 6:
                int account_no;
                cout<<"Enter the account number to be deleted : ";
                cin>>account_no;
                deleteAccount(accountQueue,account_no);
            case 7:
                int acco_no;
                cout<<"Enter the account no to be updated :";
                cin>>acco_no;
                update_account(accountQueue,acco_no);
            case 8:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
        cin.ignore();
        cin.get();
    } while (choice != 8);

    return 0;
}
