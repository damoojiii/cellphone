#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>  //to manipulate string or convert into string
#include <thread> //thread & ctime for retrieving the date/time and use for sleep
#include <ctime>
#include <iomanip> //design
#include <sstream> //converting string to int in filestream
#include <conio.h> //hashpassword
#include <vector> //storing searches ps: trying to use 

using namespace std;

struct request{
    //long long int cnum; for phone number but I chose to use string
    string cname,cnum, brand, model, issue, dtype, status, date, time;
    int rate;
};
struct buysell{
    string dtype, brand, model, color, display, cam, cpu, storage, ram, status, issue, date, time;
    int price;
};

//arrays & vectors
string signup[1][4];//admin

request cellphone[100];
request cancel[100];
request complete[100];

buysell bns[100];
buysell sold[100];

vector<int> indexes;
vector<request> searchResults;
vector<buysell> prodResults;

//utilities & id/counter
int id = 0, canid = 0, comid = 0;
int bid = 0, sid = 0;

bool sign = false, start = true;


//current time function
string getCurrentDateTime(const char* format) {
    time_t now = time(nullptr);  //get time/date computer format
    char buffer[80];  //array to be able to convert the format into string
    strftime(buffer, sizeof(buffer), format, localtime(&now));   //converting the time/date format into string
    return string(buffer);  //return the result
}
//hashpassword
string getPassword(){
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // Loop until Enter is pressed
        if (ch == '\b') {  // Handle Backspace (ASCII code 8)
            if (password.length() > 0) {
                cout << "\b \b"; // Move cursor back, write space, move cursor back again
                password.pop_back(); // Remove last character from password
            }
        } else {
            cout << '*'; // Print asterisk 
            password.push_back(ch); // Add character to password
        }
    }
    cout << endl; // Newline after entering password
    return password;
}
// function for table to column width
string fitColumn(const string& str, size_t width) {
    if (str.length() > width)
        return str.substr(0, width - 3) + "...";
    return str + string(width - str.length(), ' ');
}
//receipt or invoice
void receipt(int index, int change, int paid, char type, string sold){
    system("CLS");
    if(type == 'p'){
        cout << "=================================================\n";
        cout << "-------------------------------------------------\n";
        cout << "ID# "<< index + 1 <<"\t\t\tStatus: " << cellphone[index].status<<endl;
        cout << "-------------------------------------------------\n";
        cout << "Customer Name: " << cellphone[index].cname<<endl;
        cout << "Brand & Model: " << cellphone[index].brand << " " << cellphone[index].model<<endl;
        cout << "Issue: " << cellphone[index].issue <<endl;
        cout << "-------------------------------------------------\n";
        cout << "Rate of Service: " << cellphone[index].rate <<endl;
        cout << "Tendered Amount: " << paid << endl;
        cout << "Change: " << change << endl;
        cout << "-------------------------------------------------\n";
        cout << "\t\t"<<cellphone[index].date<<" "<<cellphone[index].time<<endl;
        cout<< "\t\tThank you, Come Again!\n";
        cout << "=================================================\n";
        cout<<"\nPress Enter to proceed\n";
        cin.get();
        cin.get();
    }
    else if(type == 'b'){
        cout << "=================================================\n";
        cout << "-------------------------------------------------\n";
        cout << "No.# "<< index + 1 <<"\t\t\tSold to: " << sold <<endl;
        cout << "-------------------------------------------------\n";
        cout << "Brand: " << bns[index].brand <<endl;
        cout << "Model: " << bns[index].model <<endl;
        cout << "Color: " << bns[index].color <<endl;
        cout << "-------------------------------------------------\n";
        cout << "Price: " << bns[index].price <<endl;
        cout << "Tendered Amount: " << paid << endl;
        cout << "Change: " << change << endl;
        cout << "-------------------------------------------------\n";
        cout << "\t\t"<<bns[index].date<<" "<<bns[index].time<<endl;
        cout<< "\t\tThank you, Come Again!\n";
        cout << "=================================================\n";
        cout<<"\nPress Enter to proceed\n";
        cin.get();
        cin.get();
    }
    
}
//function for computing the payment
void computeRate(int index, char type){
    int serviceRate = 0, paidAmount = 0;
    string sold;
    if(type == 'p'){
        cout << "Enter rate of service for ID# " << index + 1 << ": ";
        cin >> serviceRate;

        cellphone[index].rate = serviceRate;
        while(true){
            cout << "Enter Tendered Amount: ";
            cin >> paidAmount;

            int changeAmount = paidAmount - serviceRate;

            if (changeAmount >= 0) {
                cellphone[index].date = getCurrentDateTime("%m-%d-%Y");
                cellphone[index].time = getCurrentDateTime("%I:%M %p");
                cout << "Change amount: PHP " << changeAmount << endl;
                this_thread::sleep_for(chrono::seconds(3));
                receipt(index,changeAmount,paidAmount,type,sold);
                return;
            } else {
                cout << "Insufficient payment. Additional amount of PHP " << -changeAmount << " is required." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }  
        }

    }else if(type == 'b'){  
        cout << "Name of Customer: ";
        getline(cin>>ws,sold);
        while(true){
            cout << "Enter Tendered Amount: ";
            cin >> paidAmount;

            int changeAmount = paidAmount - bns[index].price;

            if (changeAmount >= 0) {
                bns[index].date = getCurrentDateTime("%m-%d-%Y");
                bns[index].time = getCurrentDateTime("%I:%M %p");
                cout << "Change amount: PHP " << changeAmount << endl;
                this_thread::sleep_for(chrono::seconds(3));
                receipt(index,changeAmount,paidAmount,type,sold);
                return;
            } else {
                cout << "Insufficient payment. Additional amount of PHP " << -changeAmount << " is required." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }  
        }
    }
    
}
//color
void setLimeColor() {
    cout << "\033[1;92m"; // Set the text color to lime
}

void welcomescreen();

void loadpending();
void loadcomplete();
void loadcancel();
void loadprod();
void loadsold();
void save(char type);

void signIn();
void login();
void regis();
void forgot();
void updateadmin();
void settings();

void cticket();
void displaycustomer();
void displayselect(int index, char dis);
void cview();
void cupdate();

void buynsell();
void addprod();
void viewprod();
void displayprod();
void updateprod();
void delprod();
void buyprod();
void viewsold();

void paymenu();
void collect();
void viewcancel();
void viewcomplete();
//working

//considerations
void delmenu();
void specdel();
void alldel();
//search & sort for request
void searchByBrand(request arr[], int size, char type);
void searchByDeviceType(request arr[], int size, char type);
void searchByModel(request arr[], int size, char type);
void searchByIssue(request arr[], int size, char type);
void searchByDate(request arr[], int size, char type);
void displayRequest(request arr[], int size, int* indexes, int numResults);
void displayComplete(request arr[], int size, int* indexes, int numResults);
//search & sort for products
void searchByPBrand(buysell arr[], int size, char type);
void searchByPDeviceType(buysell arr[], int size, char type);
void searchByPModel(buysell arr[], int size, char type);
void searchByPColor(buysell arr[], int size, char type);
void searchByPDisplay(buysell arr[], int size, char type);
void searchByPCamera(buysell arr[], int size, char type);
void searchByPStorage(buysell arr[], int size, char type);
void searchByPCpu(buysell arr[], int size, char type);
void searchByPRam(buysell arr[], int size, char type);
void searchByLowPrice(buysell arr[], int size, char type);
void searchByHighPrice(buysell arr[], int size, char type);
void searchByPDate(buysell arr[], int size, char type);
void displayProduct(buysell arr[], int size, int* indexes, int numResults);
void displaySold(buysell arr[], int size, int* indexes, int numResults);
//search results
void displaySearchResults(request arr[], int size, char type) {
    if (searchResults.empty()) {
        cout << "No results found." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        if (type == 'a'){
            cview();
        }else if (type == 'b'){
            viewcancel();
        }
        else if (type == 'c'){
            viewcomplete();
        }
        
        return;
    }

    cout << "Search Results:" << endl;
    if (type == 'a' || type == 'b'){
        displayRequest(arr, size, indexes.data(), indexes.size());
        searchResults.clear();
        indexes.clear();
    }
    else if(type == 'c'){
        displayComplete(arr, size, indexes.data(), indexes.size());
        searchResults.clear();
        indexes.clear();
    }
    
}
void displayProdResults(buysell arr[], int size, char type) {
    if (prodResults.empty()) {
        cout << "No results found." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        if (type == 'a'){
            viewprod();
        }else if (type == 'b'){
            viewsold();
        }
        
        return;
    }

    cout << "Search Results:" << endl;
    if (type == 'a'){
        displayProduct(arr, size, indexes.data(), indexes.size());
        prodResults.clear();
        indexes.clear();
    }
    else if(type == 'b'){
        displaySold(arr, size, indexes.data(), indexes.size());
        prodResults.clear();
        indexes.clear();
    }
    
}

int main(){
    setLimeColor();
    if(start){
        start = false;
        welcomescreen();
    }
    ifstream empty("useradmin.txt");
    if (empty.peek() == ifstream::traits_type::eof()) {
        empty.close();
        regis();
    } else {
        empty.close();
        if(sign == false){
            signIn();        
        }
    }
    loadpending();
    loadcancel();
    loadcomplete();
    while(true){
        system("CLS");
        int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"****************** WELCOME *****************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Create a New Ticket\n";
        cout<<"2. View All Request Tickets\n";
        cout<<"3. Update Ticket\n";
        cout<<"4. Payment & Request History\n";
        cout<<"5. Buy 'n Sell\n";
        cout<<"6. Settings\n";
        cout<<"7. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: cticket(); break;
            case 2: cview(); break;
            case 3: cupdate(); break;
            case 4: paymenu(); break;
            case 5: buynsell(); break;
            case 6: settings(); break;
            case 7: 
                cout<< "\nThank you! Exiting..\n";
                this_thread::sleep_for(chrono::seconds(1));
                exit(0);
            default: 
                cout << "\nInvalid choice!\n";
                this_thread::sleep_for(chrono::seconds(1));
        }
        cout<<endl;
    }
    
}
void welcomescreen() {
    system("CLS");

    int screenWidth = 150;
    int logoWidth = 20;
    int titleWidth = 30;
    int welcomeWidth = 35;
    cout << "\n\n\n";
    cout << setw((screenWidth - logoWidth) / 2) << "" << "              ____             " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "             //\\  \\           " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "            //  \\  \\         " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "           //\\   \\  \\       " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "          //  \\   \\  \\     " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "         //    \\   \\  \\   " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "        //      \\   \\  \\ " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "       //        \\   \\ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "      //          \\ / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "     //            / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "    //            / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "   //            / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "  //            / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << " /\\            / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "/  \\          / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "\\   \\        / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << " \\   \\      / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "  \\   \\    / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "   \\   \\  / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "    \\   \\/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "     \\    //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "      -----" << endl;
    cout << endl;

    cout << setw((screenWidth - titleWidth) / 2) << "" << "CELLPHONE REPAIR REQUEST SYSTEM" << endl;
    cout << endl;

    cout << setw((screenWidth - welcomeWidth) / 2) << "" << "Welcome to Our Cellphone Repair Service" << endl;
    cout << endl;

    this_thread::sleep_for(chrono::seconds(5));
}
// save & load file for customer request
void loadpending()
{
    ifstream read;
    read.open("customerticket.txt");
    if(!read){
        cerr<<"Error opening file for reading"<<endl;
        return;
    }
    read >> id;
    read.ignore(); 

    for (int i = 0; i < id; i++)
    {
        getline(read>>ws, cellphone[i].cname, ',');    
        getline(read>>ws, cellphone[i].cnum, ',');
        getline(read>>ws, cellphone[i].dtype , ',');
        getline(read>>ws, cellphone[i].brand, ',');
        getline(read>>ws, cellphone[i].model, ',');
        getline(read>>ws, cellphone[i].issue,',');
        getline(read>>ws, cellphone[i].status,',');
        getline(read>>ws, cellphone[i].date,',');
        getline(read>>ws, cellphone[i].time);

    }
    
    read.close();
}
void save(char type){
	
    if(type == 'p'){
        ofstream write ("customerticket.txt");
        if(!write){
            cerr<<"Error opening file for writing"<<endl;
            return;
        }
        write << id <<endl;
        for(int i = 0; i < id ;i++)
        {
            write << cellphone[i].cname << "," << cellphone[i].cnum << "," << cellphone[i].dtype << ","
                << cellphone[i].brand << "," << cellphone[i].model << "," << cellphone[i].issue << "," 
                << cellphone[i].status << "," << cellphone[i].date << "," << cellphone[i].time<<endl;
        }
        write.close();
    }
    else if(type == 'b'){
        ofstream write ("buyprod.txt");
        if(!write){
            cerr<<"Error opening file for writing"<<endl;
            return;
        }
        write << bid <<endl;
        for(int i = 0; i < bid ;i++)
        {
            write << bns[i].brand << "," << bns[i].dtype << "," << bns[i].model << "," 
                << bns[i].color << "," << bns[i].display << "," << bns[i].cam << "," 
                << bns[i].storage << "," << bns[i].cpu << "," << bns[i].ram<< ","
                << bns[i].status << "," << bns[i].price << endl;
        }
        write.close();
    }

}
//load file for completed & cancelled request
void loadcancel(){
    ifstream read;
    read.open("cancelled.txt");
    if(!read){
        cerr<<"Error opening file for reading"<<endl;
        return;
    }
    int count = 0;
    while(!read.eof())
    {
        getline(read>>ws, cancel[count].cname, ',');    
        getline(read>>ws, cancel[count].cnum, ',');
        getline(read>>ws, cancel[count].dtype , ',');
        getline(read>>ws, cancel[count].brand, ',');
        getline(read>>ws, cancel[count].model, ',');
        getline(read>>ws, cancel[count].issue,',');
        getline(read>>ws, cancel[count].status,',');
        getline(read>>ws, cancel[count].date,',');
        getline(read>>ws, cancel[count].time);
        
        count++;
    }
    canid = count-1;
    
    read.close();
}
void loadcomplete(){
    ifstream read;
    read.open("completed.txt");
    if(!read){
        cerr<<"Error opening file for reading"<<endl;
        return;
    }
    int count = 0;
    while(!read.eof())
    {
        string strRate;
        int tempRate;
        getline(read>>ws, complete[count].cname, ',');    
        getline(read>>ws, complete[count].cnum, ',');
        getline(read>>ws, complete[count].dtype , ',');
        getline(read>>ws, complete[count].brand, ',');
        getline(read>>ws, complete[count].model, ',');
        getline(read>>ws, complete[count].issue,',');
        getline(read>>ws, complete[count].status,',');
        getline(read>>ws, complete[count].date,',');
        getline(read>>ws, complete[count].time, ',');
        getline(read, strRate); 
		stringstream ss(strRate);
        if (ss >> tempRate) {
            complete[count].rate = tempRate;
        }

        count++;
    }
    comid = count-1;
    read.close();
}
//load for buy n sell
void loadprod(){
    ifstream read;
    read.open("buyprod.txt");
    if(!read){
        cerr<<"Error opening file for reading"<<endl;
        return;
    }
    read >> bid;
    read.ignore(); 

    for (int i = 0; i < bid; i++)
    {
        string strPrice;
        int tempPrice;
        getline(read>>ws, bns[i].brand, ',');    
        getline(read>>ws, bns[i].dtype, ',');
        getline(read>>ws, bns[i].model, ',');
        getline(read>>ws, bns[i].color, ',');
        getline(read>>ws, bns[i].display, ',');
        getline(read>>ws, bns[i].cam, ',');
        getline(read>>ws, bns[i].storage,',');
        getline(read>>ws, bns[i].cpu,',');
        getline(read>>ws, bns[i].ram,',');
        getline(read>>ws, bns[i].status, ',');
        getline(read, strPrice); 
		stringstream ss(strPrice);
        if (ss >> tempPrice) {
            bns[i].price = tempPrice;
        }

    }
    
    read.close();
}
void loadsold(){
    ifstream read;
    read.open("sold.txt");
    if(!read){
        cerr<<"Error opening file for reading"<<endl;
        return;
    }
    int count = 0;
    while(!read.eof())
    {
        string strPrice;
        int tempPrice;
        getline(read>>ws, sold[count].brand, ',');    
        getline(read>>ws, sold[count].dtype, ',');
        getline(read>>ws, sold[count].model , ',');
        getline(read>>ws, sold[count].color, ',');
        getline(read>>ws, sold[count].display, ',');
        getline(read>>ws, sold[count].cam,',');
        getline(read>>ws, sold[count].storage,',');
        getline(read>>ws, sold[count].cpu,',');
        getline(read>>ws, sold[count].ram, ',');
        getline(read>>ws, sold[count].status, ',');
        getline(read, strPrice, ','); 
		stringstream ss(strPrice);
        if (ss >> tempPrice) {
            sold[count].price = tempPrice;
        }
        getline(read>>ws, sold[count].date, ',');
        getline(read>>ws, sold[count].time);

        count++;
    }
    sid = count-1;
    read.close();
}
//security
void signIn() {
    system("CLS");
    int choice;

    cout << "\n\n\n\n\n\n\n\n\n";
    cout << setw(55) << "" << "+----------------------------------------------------+" << endl;
    cout << setw(55) << "" << "|            CELLPHONE REPAIR REQUEST SYSTEM         |" << endl;
    cout << setw(55) << "" << "+----------------------------------------------------+" << endl;
    cout << setw(55) << "" << "| 1. Login                                           |" << endl;
    cout << setw(55) << "" << "| 2. Forgot Username or Password                     |" << endl;
    cout << setw(55) << "" << "| Enter your choice: ";
    cin >> choice;
    cout << setw(50) << "" << "+----------------------------------------------------+" << endl;

    switch (choice) {
    case 1: login(); return;
    case 2: forgot(); return;
    default:
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(55) << "" << "+----------------------------------------------------+" << endl;
        cout << setw(55) << "" << "|               Invalid Input                        |" << endl;
        cout << setw(55) << "" << "+----------------------------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        signIn();
    }
}
void login() {
    int count = 0;
    bool found = false;
    string user, pass;

    while (true) {
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(65) << "" << "+---------------------------+" << endl;
        cout << setw(65) << "" << "|        Login Menu         |" << endl;
        cout << setw(65) << "" << "+---------------------------+" << endl;
        cout << setw(65) << "" << "| Enter your username:      |" << endl;
        cout << setw(65) << "" << "| > ";
        cin >> user;
        cout << setw(65) << "" << "| Enter your password:      |" << endl;
        cout << setw(65) << "" << "| > ";
        pass = getPassword();
        cout << setw(65) << "" << "+---------------------------+" << endl;

        ifstream input("useradmin.txt");
        while (input >> signup[0][0] >> signup[0][1] >> signup[0][2] >> signup[0][3]) {
            if (signup[0][0] == user && signup[0][1] == pass) {
                found = true;
                system("cls");
            }
        }
        input.close();

        if (found == true) {
            sign = true;
            cout << "\n\n\n\n\n\n\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "|     LOGIN SUCCESSFUL!     |" << endl;
            cout << setw(65) << "" << "|     Hello, " << left << setw(14) << user << "|" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            main();
        } else if (count == 5) {
            cout << "\n\n\n\n\n\n\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "|   Too many attempts!      |" << endl;
            cout << setw(65) << "" << "|    Exiting the program... |" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            exit(0);
        } else {
            cout << "\n\n\n\n\n\n\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "| Invalid Username or       |" << endl;
            cout << setw(65) << "" << "| Password. Please try      |" << endl;
            cout << setw(65) << "" << "| again.                    |" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            count++;
        }
    }
}
void regis() {
    string conpass;
    system("CLS");

    cout << endl << endl << endl;
    cout << setw(60) << "" << "+---------------------------------------+" << endl;
    cout << setw(60) << "" << "|           User Registration           |" << endl;
    cout << setw(60) << "" << "+---------------------------------------+" << endl;
    cout << setw(60) << "" << "| Please register before you use the    |" << endl;
    cout << setw(60) << "" << "| system.                               |" << endl;
    cout << setw(60) << "" << "|                                       |" << endl;
    cout << setw(60) << "" << "| Note: Think thoroughly for the        |" << endl;
    cout << setw(60) << "" << "| credentials you have to input.        |" << endl;
    cout << setw(60) << "" << "+-------------------------------------- +" << endl;
    cout << endl << endl;

    cout << setw(60) << "" << "Enter the Username: ";
    cin >> signup[0][0];
    cout << endl;

    while (true) {
        cout << setw(60) << "" << "Enter the Password: ";
        signup[0][1] = getPassword();
        cout << endl;
        cout << setw(60) << "" << "Confirm Password: ";
        conpass = getPassword();
        cout << endl;
        if (signup[0][1] != conpass) {
            cout << setw(60) << "" << "Password and Confirm Password Don't Match" << endl << endl;
        }
        else {
            break;
        }
    }

    cout << setw(60) << "" << "Security Question 1: What is your mother's maiden name?\n";
    cout << setw(60) << "" << "Answer: ";
    cin >> signup[0][2];
    cout << endl;
    cout << setw(60) << "" << "Security Question 2: What was the name of your first pet?\n";
    cout << setw(60) << "" << "Answer: ";
    cin >> signup[0][3];

    ofstream reg("useradmin.txt", ios::app);
    reg << signup[0][0] << " " << signup[0][1] << " " << signup[0][2] << " " << signup[0][3] << endl;
    system("CLS");
    cout << "\n\n\n\n\n";
    cout << setw(60) << "" << "Registration Successful." << endl;
    reg.close();
    this_thread::sleep_for(chrono::seconds(2));
    main();
}
void forgot() {
    int ch;
    system("CLS");

    cout << "\n\n\n\n\n\n\n\n\n";
    cout << setw(65) << "" << "+---------------------------+" << endl;
    cout << setw(65) << "" << "|         Forgot Menu       |" << endl;
    cout << setw(65) << "" << "+---------------------------+" << endl;
    cout << setw(65) << "" << "| 1. Search by Username     |" << endl;
    cout << setw(65) << "" << "| 2. Search by Password     |" << endl;
    cout << setw(65) << "" << "| 3. Main Menu              |" << endl;
    cout << setw(65) << "" << "+---------------------------+" << endl;
    cout << setw(65) << "" << "| Enter your choice:        |" << endl;
    cout << setw(65) << "" << "| > ";
    cin >> ch;
    cout << setw(65) << "" << "+---------------------------+" << endl;

    switch (ch) {
        case 1: {
            string susername, securityAns1, securityAns2;
            system("CLS");

            cout << "\n\n\n\n\n\n\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "| Enter remembered username |" << endl;
            cout << setw(65) << "" << "| > ";
            cin >> susername;
            cout << setw(65) << "" << "+---------------------------+" << endl;

            ifstream check("useradmin.txt");
            bool found = false;

            while (check >> signup[0][0] >> signup[0][1] >> signup[0][2] >> signup[0][3]) {
                if (signup[0][0] == susername) {
                    found = true;
                    cout << "\n\n\n";
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| Answer the following      |" << endl;
                    cout << setw(65) << "" << "| security questions:       |" << endl;
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| What is your mother's     |" << endl;
                    cout << setw(65) << "" << "| maiden name?:             |" << endl;
                    cout << setw(65) << "" << "| > ";
                    cin >> securityAns1;
                    cout << setw(65) << "" << "| What was the name of      |" << endl;
                    cout << setw(65) << "" << "| your first pet?:          |" << endl;
                    cout << setw(65) << "" << "| > ";
                    cin >> securityAns2;
                    cout << setw(65) << "" << "+---------------------------+" << endl;

                    if (securityAns1 == signup[0][2] && securityAns2 == signup[0][3]) {
                        cout << "\n\n";
                        cout << setw(65) << "" << "+---------------------------------+" << endl;
                        cout << setw(65) << "" << "| Account recovered!              |" << endl;
                        cout << setw(65) << "" << "| Your password is: " << signup[0][1] << setw(8) << " |" << endl;
                        cout << setw(65) << "" << "+---------------------------------+" << endl;
                        updateadmin();
                    } else {
                        cout << "\n\n";
                        cout << setw(65) << "" << "+---------------------------+" << endl;
                        cout << setw(65) << "" << "| Security answers do not   |" << endl;
                        cout << setw(65) << "" << "| match. Recovery failed.   |" << endl;
                        cout << setw(65) << "" << "+---------------------------+" << endl;
                    }
                    break;
                }
            }
            check.close();

            if (!found) {
                cout << "\n\n";
                cout << setw(65) << "" << "+---------------------------+" << endl;
                cout << setw(65) << "" << "| Username not found in     |" << endl;
                cout << setw(65) << "" << "| the database.             |" << endl;
                cout << setw(65) << "" << "+---------------------------+" << endl;
            }

            this_thread::sleep_for(chrono::seconds(3));
            signIn();
            return;
        }
        case 2: {
            string spassword, securityAns1, securityAns2;
            system("CLS");

            cout << "\n\n\n\n\n\n\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "| Enter remembered password |" << endl;
            cout << setw(65) << "" << "| > ";
            cin >> spassword;
            cout << setw(65) << "" << "+---------------------------+" << endl;

            ifstream check("useradmin.txt");
            bool found = false;

            while (check >> signup[0][0] >> signup[0][1] >> signup[0][2] >> signup[0][3]) {
                if (signup[0][1] == spassword) {
                    found = true;
                    cout << "\n\n\n";
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| Answer the following      |" << endl;
                    cout << setw(65) << "" << "| security questions:       |" << endl;
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| What is your mother's     |" << endl;
                    cout << setw(65) << "" << "| maiden name?:             |" << endl;
                    cout << setw(65) << "" << "| > ";
                    cin >> securityAns1;
                    cout << setw(65) << "" << "| What was the name of      |" << endl;
                    cout << setw(65) << "" << "| your first pet?:          |" << endl;
                    cout << setw(65) << "" << "| > ";
                    cin >> securityAns2;
                    cout << setw(65) << "" << "+---------------------------+" << endl;

                    if (securityAns1 == signup[0][2] && securityAns2 == signup[0][3]) {
                        cout << "\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Account recovered!             |" << endl;
                        cout << setw(65) << "" << "| Your Username is: " << signup[0][0] << setw(7) << " |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        updateadmin();
                    } else {
                        cout << "\n\n";
                        cout << setw(65) << "" << "+---------------------------+" << endl;
                        cout << setw(65) << "" << "| Security answers do not   |" << endl;
                        cout << setw(65) << "" << "| match. Recovery failed.   |" << endl;
                        cout << setw(65) << "" << "+---------------------------+" << endl;
                    }
                    break;
                }
            }
            check.close();

            if (!found) {
                cout << "\n\n";
                cout << setw(65) << "" << "+---------------------------+" << endl;
                cout << setw(65) << "" << "| Password not found in     |" << endl;
                cout << setw(65) << "" << "| the database.             |" << endl;
                cout << setw(65) << "" << "+---------------------------+" << endl;
            }

            this_thread::sleep_for(chrono::seconds(3));
            signIn();
            return;
        }
        case 3: {
            signIn();
            return;
        }
        default: {
            cout << "\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "| Invalid Input. Kindly     |" << endl;
            cout << setw(65) << "" << "| try again.                |" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            forgot();
        }
    }
}
void updateadmin() {
    char a;
    while (true) {
        system("CLS");

        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(65) << "" << "+--------------------------------+" << endl;
        cout << setw(65) << "" << "| Do you want to update your     |" << endl;
        cout << setw(65) << "" << "| account? [y] YES or [n] NO     |" << endl;
        cout << setw(65) << "" << "| > ";
        cin >> a;
        cout << setw(65) << "" << "+--------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int choice;
            while (true) {
                system("CLS");

                cout << "\n\n\n\n\n\n\n\n\n";
                cout << setw(65) << "" << "+--------------------------------+" << endl;
                cout << setw(65) << "" << "|        Update Account Menu     |" << endl;
                cout << setw(65) << "" << "+--------------------------------+" << endl;
                cout << setw(65) << "" << "| 1. Update Username             |" << endl;
                cout << setw(65) << "" << "| 2. Update Password             |" << endl;
                cout << setw(65) << "" << "| 3. Update All                  |" << endl;
                cout << setw(65) << "" << "| 4. Go back                     |" << endl;
                cout << setw(65) << "" << "+--------------------------------+" << endl;
                cout << setw(65) << "" << "| Enter your choice:             |" << endl;
                cout << setw(65) << "" << "| > ";
                cin >> choice;
                cout << setw(65) << "" << "+--------------------------------+" << endl;

                switch (choice) {
                    case 1: {
                        ifstream file("useradmin.txt");
                        string line, updateline;

                        // Read the first line
                        getline(file, line);

                        cout << "\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Enter Updated Username:        |" << endl;
                        cout << setw(65) << "" << "| > ";
                        cin >> signup[0][0];
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt");
                        reg << updateline << endl;

                        system("CLS");
                        cout << "\n\n\n\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Username Updated Successfully  |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 2: {
                        string conpass, line, updateline;
                        while (true) {
                            cout << "\n\n\n";
                            cout << setw(65) << "" << "+--------------------------------+" << endl;
                            cout << setw(65) << "" << "| Enter Updated Password:        |" << endl;
                            cout << setw(65) << "" << "| > ";
                            signup[0][1] = getPassword();
                            cout << setw(65) << "" << "| Confirm Updated Password:      |" << endl;
                            cout << setw(65) << "" << "| > ";
                            conpass = getPassword();
                            cout << setw(65) << "" << "+--------------------------------+" << endl;

                            if (signup[0][1] != conpass) {
                                cout << "\n\n";
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << setw(65) << "" << "| Passwords do not match.        |" << endl;
                                cout << setw(65) << "" << "| Please try again.              |" << endl;
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << endl << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                            } else {
                                break;
                            }
                        }
                        ifstream file("useradmin.txt");
                        getline(file, line);
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt", ios::trunc);
                        reg << updateline << endl;
                        system("CLS");
                        cout << "\n\n\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Password Updated Successfully  |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 3: {
                        string conpass, line, updateline;
                        cout << "\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Enter Updated Username:        |" << endl;
                        cout << setw(65) << "" << "| > ";
                        cin >> signup[0][0];
                        while (true) {
                            cout << setw(65) << "" << "| Enter Updated Password:        |" << endl;
                            cout << setw(65) << "" << "| > ";
                            signup[0][1] = getPassword();
                            cout << setw(65) << "" << "| Confirm Updated Password:      |" << endl;
                            cout << setw(65) << "" << "| > ";
                            conpass = getPassword();
                            cout << setw(65) << "" << "+--------------------------------+" << endl;

                            if (signup[0][1] != conpass) {
                                cout << "\n\n";
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << setw(65) << "" << "| Passwords do not match.        |" << endl;
                                cout << setw(65) << "" << "| Please try again.              |" << endl;
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << endl << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                            } else {
                                break;
                            }
                        }
                        ifstream file("useradmin.txt");
                        getline(file, line);
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt");
                        reg << updateline << endl;
                        system("CLS");
                        cout << "\n\n\n\n\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Account Updated Successfully   |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 4: {
                        main();
                        return;
                    }
                    default: {
                        cout << "\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Invalid choice!                |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                }
            }
            break;
        } else if (a == 'n' || a == 'N') {
            main();
            return;
        } else {
            cout << "\n\n";
            cout << setw(65) << "" << "+--------------------------------+" << endl;
            cout << setw(65) << "" << "| Invalid Choice                 |" << endl;
            cout << setw(65) << "" << "+--------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}
void settings(){
    int count = 0, max = 5;
    string pass;
    while(true){
        cout<<"Enter your password before you proceed: ";
        pass = getPassword();
        if(pass != signup[0][1]){
            cout << "Password Incorrect\n";
            count++;
        }
        else if(count == max){
            cout<<"\nToo many attempts! Exiting the program...\n";  //nabuang na ata to, hindi napasok dito kahit nagana yung count
            this_thread::sleep_for(chrono::seconds(2));
            exit(0);
        }
        else{
            break;
        }
    }
    while(true){
        system("CLS");
        int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"****************** Settings *****************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Account Settings\n";
        cout<<"2. Di mo shore\n";
        cout<<"3. Go Back\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: updateadmin(); return;
            case 2: cview(); return;
            case 3: main(); return;
            default: 
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    } 
}
//main menu
void cticket(){
    char type = 'p';
    system("CLS");
    cout<<"Create New Ticket/Request"<<endl;
    cout<<"Please Provide the Following details"<<endl;
    cout<<"Customer Name: ";
    getline(cin >> ws, cellphone[id].cname);
    cout<<"Contact Number: ";
    getline(cin >> ws, cellphone[id].cnum);
    cout<<"Device Type: ";
    getline(cin>>ws, cellphone[id].dtype);
    cout<<"Brand: ";
    getline(cin>>ws, cellphone[id].brand);
    cout<<"Model: ";
    getline(cin>>ws, cellphone[id].model);
    cout<<"Issue: ";
    getline(cin>>ws, cellphone[id].issue);
    cellphone[id].status = "Pending..";
    cellphone[id].date = getCurrentDateTime("%m-%d-%Y");
    cellphone[id].time = getCurrentDateTime("%I:%M %p");
    id++;
    save(type);
    cout<<"\nTicket Added!\n"<<endl;
    this_thread::sleep_for(chrono::seconds(3));
    main();
}
void displaycustomer(){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(13) << "Status" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < id; i++) {
        cout << "| " << setw(3) << left << i+1 << " | " 
             << setw(30) << cellphone[i].cname << " | "
             << setw(13) << cellphone[i].cnum << " | "
             << setw(13) << cellphone[i].dtype << " | "
             << setw(13) << cellphone[i].brand << " | "
             << setw(18) << cellphone[i].model << " | "
             << setw(30) << cellphone[i].issue << " | "
             << setw(13) << cellphone[i].status << " | "
             << setw(10) << cellphone[i].date << " | "
             << setw(8) << cellphone[i].time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
             << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
             << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
             << string(10, '-') << "+\n";
    }
}
void displayselect(int index, char dis) {
    system("CLS");
    if(dis == 'p'){
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
        cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
            << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
            << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
            << setw(13) << "Status" << " | " << setw(10) << "Date" << " | "
            << setw(8) << "Time" << " |\n";
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
            << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
            << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
            << string(10, '-') << "+\n";

        // Display selected request
        cout << "| " << setw(3) << left << index + 1<< " | " 
            << setw(30) << cellphone[index].cname << " | "
            << setw(13) << cellphone[index].cnum << " | "
            << setw(13) << cellphone[index].dtype << " | "
            << setw(13) << cellphone[index].brand << " | "
            << setw(18) << cellphone[index].model << " | "
            << setw(30) << cellphone[index].issue << " | "
            << setw(13) << cellphone[index].status << " | "
            << setw(10) << cellphone[index].date << " | "
            << setw(8) << cellphone[index].time << " |\n";
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
            << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
            << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
            << string(10, '-') << "+\n";
    }
    else if(dis == 'b'){
        // Table header
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
            << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" 
            << string(10, '-') << "+" << string(10, '-') << "+" << string(20, '-') << "+" 
            << string(9, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+\n";
            
        cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
            << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
            << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
            << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
            << setw(7) << "RAM" << " | " << setw(15) << "Status" << " | "
            << setw(15) << "Price" << " |\n";
            
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
            << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" 
            << string(10, '-') << "+" << string(10, '-') << "+" << string(20, '-') << "+" 
            << string(9, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+\n";
        
        // Table rows
        cout << "| " << setw(3) << left << index+1 << " | " 
                << setw(13) << bns[index].brand << " | "
                << setw(13) << bns[index].dtype << " | "
                << setw(18) << bns[index].model << " | "
                << setw(10) << bns[index].color << " | "
                << setw(18) << bns[index].display << " | "
                << setw(8) << bns[index].cam << " | "
                << setw(8) << bns[index].storage << " | "
                << setw(18) << bns[index].cpu << " | "
                << setw(7) << bns[index].ram << " | "
                << setw(15) << bns[index].status << " | "
                << setw(2) << "PHP " << setw(11) << bns[index].price << " |\n";
                
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
            << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" 
            << string(10, '-') << "+" << string(10, '-') << "+" << string(20, '-') << "+" 
            << string(9, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+\n";
    }
    
}
void displayRequest(request arr[], int size, int* indexes, int numResults){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";

    cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(13) << "Status" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";

    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";

    // Table rows
     for (int i = 0; i < numResults; i++) {
        int index = indexes[i];
        const request& r = arr[index];
        cout << "| " << setw(3) << left << index+1 << " | " 
             << setw(30) << r.cname << " | "
             << setw(13) << r.cnum << " | "
             << setw(13) << r.dtype << " | "
             << setw(13) << r.brand << " | "
             << setw(18) << r.model << " | "
             << setw(30) << r.issue << " | "
             << setw(13) << r.status << " | "
             << setw(10) << r.date << " | "
             << setw(8) << r.time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
             << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
             << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
             << string(10, '-') << "+\n";
    }
    cout << "\nPress Enter to continue: " << endl;
    cin.get();
}
void displayComplete(request arr[], int size, int* indexes, int numResults){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(9) << "Status" << " | " << setw(13) << "Price" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < numResults; i++) {
        int index = indexes[i];
        const request& r = arr[index];
        cout << "| " << setw(3) << left << index+1 << " | " 
             << setw(30) << r.cname << " | "
             << setw(13) << r.cnum << " | "
             << setw(13) << r.dtype << " | "
             << setw(13) << r.brand << " | "
             << setw(18) << r.model << " | "
             << setw(30) << r.issue << " | "
             << setw(9) << r.status << " | "
             << setw(2) << "PHP " << setw(9)<< r.rate << " | "
             << setw(10) << r.date << " | "
             << setw(8) << r.time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
            << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
            << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
            << string(12, '-') << "+" << string(10, '-') << "+\n";
    }
    cout << "\nPress Enter to continue: " << endl;
    cin.get();
}
void cview() {
    char a, type='a';
    loadpending();
    system("CLS");
    cout << "Request:" << endl;
    displaycustomer();
    while(true){
        cout << "Do you want to search? [y] YES or [N] NO:  ";
        cin>>a;
        if(a == 'y'|| a == 'Y'){
            int opt;
            do {
                cout << "Search requests by:" << endl;
                cout << "1. Device Type" << endl;
                cout << "2. Brand" << endl;
                cout << "3. Model" << endl;
                cout << "4. Issue" << endl;
                cout << "5. Date" << endl;
                cout << "6. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                system("CLS");
                

                switch (opt) {
                case 1: searchByDeviceType(cellphone, id, type);
                        break;
                case 2: searchByBrand(cellphone, id, type);
                        break;
                case 3: searchByModel(cellphone, id, type);
                        break;
                case 4: searchByIssue(cellphone, id, type);
                        break;
                case 5: searchByDate(cellphone, id, type);
                        break;
                case 6: cview(); return;
                default:
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }

            } while (true);
        }
        else if(a == 'n' || a == 'N'){
            break;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
    cout << endl;
    cout << "Press Enter to Exit" << endl;
    cin.get();
    cin.get();
    main();
    
}
void cupdate()
{
	int num = 0;
	system("CLS");
	cout << "Records:" << endl;
	displaycustomer();
	cout << "Enter ID to be updated: ";
	cin >> num;
	int index = -1; 
	for (int i = 0; i < id; i++) 
	{
		if (i + 1 == num) 
		{
			index = i;
            char dis = 'p';
            displayselect(index, dis);
			break;
		}
	}
	if (index != -1)
	{
        char type = 'p';
		cout<<"Enter Updated Customer Name: ";
        getline(cin >> ws, cellphone[index].cname);
        cout<<"Enter Updated Contact Number: ";
        getline(cin >> ws, cellphone[index].cnum);
        cout<<"Enter Updated Device Type: ";
        getline(cin>>ws, cellphone[index].dtype);
        cout<<"Enter Updated Brand: ";
        getline(cin>>ws, cellphone[index].brand);
        cout<<"Enter Updated Model: ";
        getline(cin>>ws, cellphone[index].model);
        cout<<"Enter Updated Issue: ";
        getline(cin>>ws, cellphone[index].issue);
		cout << "Request updated successfully!" << endl;
        this_thread::sleep_for(chrono::seconds(3));
		save(type);
	}
	else
	{
		cout << "Request not found!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
	}
	main();
}
void delmenu(){
    system("CLS");
    int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Specifically Delete a Ticket\n";
        cout<<"2. Delete All Ticket Record\n";
        cout<<"3. Go Back\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: specdel(); return;
            case 2: alldel(); return;
            case 3: main(); return;
            default:
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                delmenu();
        }
}
void specdel(){
    int num = 0;
	system("CLS");
	cout << "Records:" << endl;
	displaycustomer();
	cout << "Enter ID to be deleted: ";
	cin >> num; 
	int index = -1;  
	for (int i = 0; i < id; i++) 
	{
		if (i + 1 == num) 
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
        char type = 'p';
		for (int i = index; i < id - 1; i++) 
		{
			cellphone[i] = cellphone[i + 1]; 	
		}
		id--; 
		cout << "Ticket deleted successfully!" << endl;
        this_thread::sleep_for(chrono::seconds(3));
		save(type);
	}
	else
	{
		cout << "Ticket not found!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
	}
	main();
}
void alldel(){
    
}
//buy n sell section
void buynsell(){
    loadprod();
    loadsold();
    while(true){
        system("CLS");
        int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Add a Product to Sell\n";
        cout<<"2. View all Products\n";
        cout<<"3. Update a Product\n";
        cout<<"4. Delete a Product\n";
        cout<<"5. Buy a Product\n";
        cout<<"6. Transaction History\n";
        cout<<"7. Back\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: addprod(); return;
            case 2: viewprod(); return;
            case 3: updateprod(); return;
            case 4: delprod(); return;
            case 5: buyprod(); return;
            case 6: viewsold(); return;
            case 7: main(); return;
            default:
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    } 
}
void addprod(){
    char type = 'b';
    system("CLS");
    cout<<"Add a Product"<<endl;
    cout<<"Please Provide the Following details"<<endl;
    cout<<"Brand: ";
    getline(cin >> ws, bns[bid].brand);
    cout<<"Device Type: ";
    getline(cin >> ws, bns[bid].dtype);
    cout<<"Model: ";
    getline(cin>>ws, bns[bid].model);
    cout<<"Color: ";
    getline(cin>>ws, bns[bid].color);
    cout<<"Display/Resolution: ";
    getline(cin>>ws, bns[bid].display);
    cout<<"Camera: ";
    getline(cin>>ws, bns[bid].cam);
    cout<<"Storage: ";
    getline(cin>>ws, bns[bid].storage);
    cout<<"Processor: ";
    getline(cin>>ws, bns[bid].cpu);
    cout<<"RAM: ";
    getline(cin>>ws, bns[bid].ram);
    cout<<"Price: ";
    cin>>bns[bid].price;
    bns[bid].status = "Available";
    bid++;
    save(type);
    cout<<"\nProduct Added!\n"<<endl;
    this_thread::sleep_for(chrono::seconds(3));
    buynsell();
}
void viewprod(){
    char a, ans, type = 'a';
    loadprod(); 
	system("CLS");
	cout<<"Available Products:"<<endl;
	displayprod();
    while(true){
        cout << "Do you want to search? [y] YES or [N] NO:  ";
        cin>>a;
        if(a == 'y'|| a == 'Y'){
            int opt;
            do {
                cout << "Search Products by:" << endl;
                cout << "1. Device Type" << endl;
                cout << "2. Brand" << endl;
                cout << "3. Model" << endl;
                cout << "4. Color" << endl;
                cout << "5. Display" << endl;
                cout << "6. Camera Pixels" << endl;
                cout << "7. Storage size" << endl;
                cout << "8. Processor" << endl;
                cout << "9. RAM size" << endl;
                cout << "10. Price" << endl;
                cout << "11. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                system("CLS");
                
                switch (opt) {
                case 1: searchByPDeviceType(bns, bid, type);
                        break;
                case 2: searchByPBrand(bns, bid, type);
                        break;
                case 3: searchByPModel(bns, bid, type);
                        break;
                case 4: searchByPColor(bns, bid, type);
                        break;
                case 5: searchByPDisplay(bns, bid, type);
                        break;
                case 6: searchByPCamera(bns, bid, type);
                        break;
                case 7: searchByPStorage(bns, bid, type);
                        break;
                case 8: searchByPCpu(bns, bid, type);
                        break;
                case 9: searchByPRam(bns, bid, type);
                        break;
                case 10:
                {
                    cout<<"\nType [q] Search by Price Below or [e] Search by Price Above \n";
                    cin>>ans;
                    if(ans == 'q' || ans == 'Q'){
                        searchByLowPrice(bns, bid, type);
                        break;
                    }
                    else if(ans == 'e' || ans == 'E'){
                        searchByHighPrice(bns, bid, type);
                        break;
                    }
                    else{
                        cout<<"\nInvalid Input\n";
                        continue;
                    }

                }
                case 11: viewprod(); return;
                default: 
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }

            } while (true);
        }
        else if(a == 'n' || a == 'N'){
            break;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
    cout<<endl;
    cout<<"Press Enter to Exit\n";
    cin.get();
    cin.get();
	buynsell();
}
void displayprod() {
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(15) << "Status" << " | "
         << setw(15) << "Price" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < bid; i++) {
        cout << "| " << setw(3) << left << i+1 << " | " 
             << setw(13) << bns[i].brand << " | "
             << setw(13) << bns[i].dtype << " | "
             << setw(18) << bns[i].model << " | "
             << setw(10) << bns[i].color << " | "
             << setw(18) << bns[i].display << " | "
             << setw(8) << bns[i].cam << " | "
             << setw(8) << bns[i].storage << " | "
             << setw(18) << bns[i].cpu << " | "
             << setw(7) << bns[i].ram << " | "
             << setw(15) << bns[i].status << " | "
             << setw(2) << "PHP " << setw(11) << bns[i].price << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
            << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
            << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
            << string(17, '-') << "+" << string(17, '-') << "+\n";
    }
}
void displayProduct(buysell arr[], int size, int* indexes, int numResults){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(15) << "Status" << " | "
         << setw(15) << "Price" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < numResults; i++) {
        int index = indexes[i];
        const buysell& p = arr[index];
        cout << "| " << setw(3) << left << index+1 << " | " 
             << setw(13) << p.brand << " | "
             << setw(13) << p.dtype << " | "
             << setw(18) << p.model << " | "
             << setw(10) << p.color << " | "
             << setw(18) << p.display << " | "
             << setw(8) << p.cam << " | "
             << setw(8) << p.storage << " | "
             << setw(18) << p.cpu << " | "
             << setw(7) << p.ram << " | "
             << setw(15) << p.status << " | "
             << setw(2) << "PHP " << setw(11) << p.price << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
            << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
            << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
            << string(17, '-') << "+" << string(17, '-') << "+\n";
    }
    cout << "\nPress Enter to continue: " << endl;
    cin.get();
    cin.get();
}
void updateprod(){
    int num = 0;
	system("CLS");
	cout << "Products:" << endl;
	displayprod();
	cout << "Enter ID to be updated: ";
	cin >> num;
	int index = -1; 
	for (int i = 0; i < bid; i++) 
	{
		if (i + 1 == num) 
		{
			index = i;
            char dis = 'b';
            displayselect(index, dis);
			break;
		}
	}
	if (index != -1)
	{
        char type = 'b';
		cout<<"Enter Updated Brand: ";
        getline(cin >> ws, bns[index].brand);
        cout<<"Enter Updated Device Type: ";
        getline(cin >> ws, bns[index].dtype);
        cout<<"Enter Updated Model: ";
        getline(cin>>ws, bns[index].model);
        cout<<"Enter Updated Color: ";
        getline(cin>>ws, bns[index].color);
        cout<<"Enter Updated Display/Resolution: ";
        getline(cin>>ws, bns[index].display);
        cout<<"Enter Updated Camera: ";
        getline(cin>>ws, bns[index].cam);
        cout<<"Enter Updated Storage: ";
        getline(cin>>ws, bns[index].storage);
        cout<<"Enter Updated Processor: ";
        getline(cin>>ws, bns[index].cpu);
        cout<<"Enter Updated RAM: ";
        getline(cin>>ws, bns[index].ram);
        cout<<"Enter Updated Price: ";
        cin>>bns[index].price;
		cout << "Product updated successfully!" << endl;
        this_thread::sleep_for(chrono::seconds(3));
		save(type);
	}
	else
	{
		cout << "Product not found!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
	}
	buynsell();
}
void delprod(){
    int num = 0;
	system("CLS");
	cout << "Products:" << endl;
	displayprod();
	cout << "Enter No. to be deleted: ";
	cin >> num; 
	int index = -1;  
	for (int i = 0; i < bid; i++) 
	{
		if (i + 1 == num) 
		{
            char dis = 'b';
			index = i;
            displayselect(index,dis);
			break;
		}
	}
        
	if (index != -1)
	{
        while(true){
            char done;
            cout<<"Are you sure you want to delete this product?\n [y] YES or [n] NO: ";
            cin>>done;
            if(done == 'y'||done == 'Y'){
                char type = 'b';
                for (int i = index; i < bid - 1; i++) 
                {
                    bns[i] = bns[i + 1]; 	
                }
                bid--; 
                cout << "Product deleted successfully!" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                save(type);
                break;
            }else if(done == 'n'||done=='N'){
                cout<<">> going back to buy 'n sell menu...";
                this_thread::sleep_for(chrono::seconds(2));
                buynsell();
                break;
            }else{
                cout<<"Invalid Input!\n";
                this_thread::sleep_for(chrono::seconds(1));
            }
        }    
	}
	else
	{
		cout << "Product not found!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
	}
	buynsell();
}
void buyprod(){
    char purchase;
    int num = 0, index = -1;
    loadprod(); 
	system("CLS");
	cout<<"Available Products: "<<endl;
	displayprod();
    cout << "Select a No. : ";
	cin >> num;
    for (int i = 0; i < bid; i++){
		if (i + 1 == num){
            index = i;
            char dis = 'b';
			displayselect(index,dis);
            break;
		}
	}
    if(index != -1){
        while(true){
            cout<<"Type [y] to proceed to purchase or [n] to cancel ";
            cin>>purchase;

            if(purchase == 'y'|| purchase == 'Y'){
                char type = 'b';
                bns[index].status = "Sold";
                computeRate(index, type);
                sid++;
                ofstream transfer("sold.txt", ios::app);
                if (transfer.is_open()) {
                    transfer << bns[index].brand << "," << bns[index].dtype << "," << bns[index].model << ","
                            << bns[index].color << "," << bns[index].display << "," << bns[index].cam << "," 
                            << bns[index].storage << "," << bns[index].cpu << "," << bns[index].ram << "," 
                            << bns[index].status<< "," << bns[index].price << "," << bns[index].date<< "," 
                            << bns[index].time <<endl;
                    transfer.close();
                } else {
                    cerr << "Error: Unable to open file 'sold.txt'\n";
                }
                for (int a = index; a < bid - 1; a++) {
                bns[a] = bns[a + 1]; 	
                }
                bid--; 
                cout << "Product completely paid!" << endl;
                save(type);
                break;
            }
            else if(purchase == 'n'||purchase == 'N'){
                cout<<">> going back to buy 'n sell menu...";
                this_thread::sleep_for(chrono::seconds(2));
                buynsell();
                break;
            }else{
                cout << "Invalid input\n";
            }
        }
        
    }else{
        cout << "No.# not found!" << endl;
    }
    this_thread::sleep_for(chrono::seconds(3));
    buynsell();
}
void viewsold(){
    loadsold();
    system("cls");
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(15) << "Status" << " | "
         << setw(15) << "Price" << " | " << setw(10) << "Date" << " | "<< setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    
    // Table rows
    for (int i = 0; i < sid; i++) {
        cout << "| " << setw(3) << left << i+1 << " | " 
             << setw(13) << sold[i].brand << " | "
             << setw(13) << sold[i].dtype << " | "
             << setw(18) << sold[i].model << " | "
             << setw(10) << sold[i].color << " | "
             << setw(18) << sold[i].display << " | "
             << setw(8) << sold[i].cam << " | "
             << setw(8) << sold[i].storage << " | "
             << setw(18) << sold[i].cpu << " | "
             << setw(7) << sold[i].ram << " | "
             << setw(15) << sold[i].status << " | "
             << setw(2) << "PHP " << setw(11) << sold[i].price << " | "
             << setw(10) << sold[i].date << " | "
             << setw(8) << sold[i].time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    }
    char a, ans, type = 'b';
    while(true){
        cout << "Do you want to search? [y] YES or [N] NO:  ";
        cin>>a;
        if(a == 'y'|| a == 'Y'){
            int opt;
            do {
                cout << "Search Products by:" << endl;
                cout << "1. Device Type" << endl;
                cout << "2. Brand" << endl;
                cout << "3. Model" << endl;
                cout << "4. Color" << endl;
                cout << "5. Display" << endl;
                cout << "6. Camera Pixels" << endl;
                cout << "7. Storage size" << endl;
                cout << "8. Processor" << endl;
                cout << "9. RAM size" << endl;
                cout << "10. Price" << endl;
                cout << "11. Date" << endl;
                cout << "12. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                system("CLS");
                
                switch (opt) {
                case 1: searchByPDeviceType(sold, sid, type);
                        break;
                case 2: searchByPBrand(sold, sid, type);
                        break;
                case 3: searchByPModel(sold, sid, type);
                        break;
                case 4: searchByPColor(sold, sid, type);
                        break;
                case 5: searchByPDisplay(sold, sid, type);
                        break;
                case 6: searchByPCamera(sold, sid, type);
                        break;
                case 7: searchByPStorage(sold, sid, type);
                        break;
                case 8: searchByPCpu(sold, sid, type);
                        break;
                case 9: searchByPRam(sold, sid, type);
                        break;
                case 10:
                {
                    cout<<"\nType [q] Search by Price Below or [e] Search by Price Above \n";
                    cin>>ans;
                    if(ans == 'q' || ans == 'Q'){
                        searchByLowPrice(sold, sid, type);
                        break;
                    }
                    else if(ans == 'e' || ans == 'E'){
                        searchByHighPrice(sold, sid, type);
                        break;
                    }
                    else{
                        cout<<"\nInvalid Input\n";
                        continue;
                    }

                }
                case 11: searchByPDate(sold, sid, type); break;
                case 12: viewsold(); return;
                default: 
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }

            } while (true);
        }
        else if(a == 'n' || a == 'N'){
            break;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
    cout<<endl;
    cout<<"Press Enter to go back\n";
    cin.get();
    cin.get();
	buynsell();
}
void displaySold(buysell arr[], int size, int* indexes, int numResults){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(15) << "Status" << " | "
         << setw(15) << "Price" << " | " << setw(10) << "Date" << " | "<< setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    
    // Table rows
    for (int i = 0; i < numResults; i++) {
        int index = indexes[i];
        const buysell& p = arr[index];
        cout << "| " << setw(3) << left << index+1 << " | " 
             << setw(13) << p.brand << " | "
             << setw(13) << p.dtype << " | "
             << setw(18) << p.model << " | "
             << setw(10) << p.color << " | "
             << setw(18) << p.display << " | "
             << setw(8) << p.cam << " | "
             << setw(8) << p.storage << " | "
             << setw(18) << p.cpu << " | "
             << setw(7) << p.ram << " | "
             << setw(15) << p.status << " | "
             << setw(2) << "PHP " << setw(11) << p.price << " | "
             << setw(10) << p.date << " | "
             << setw(8) << p.time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(17, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    }
    cout << "\nPress Enter to continue: " << endl;
    cin.get();
    cin.get();
}
//request payment section
void paymenu(){
    while(true){
        system("CLS");
        int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Payment\n";
        cout<<"2. Transaction History\n";
        cout<<"3. View all Cancelled Request\n";
        cout<<"4. Go Back\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: collect(); return;
            case 2: viewcomplete(); return;
            case 3: viewcancel(); return;
            case 4: main(); return;
            default:
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
    
}
void collect(){
    char done;
    int num = 0, index = -1;
    loadpending(); 
	system("CLS");
	cout<<"Request:"<<endl;
	displaycustomer();
    cout << "Select an ID: ";
	cin >> num;
    for (int i = 0; i < id; i++){
		if (i + 1 == num){
            index = i;
            char dis = 'p';
			displayselect(index,dis);
            break;
		}
	}

    if(index != -1){
        cout<<"Type [y] Completed or [n] Cancelled ";
        cin>>done;

        if(done == 'y'|| done == 'Y'){
            char type = 'p';
            cellphone[index].status = "Completed";
            computeRate(index,type);
            comid++;
            ofstream transfer("completed.txt", ios::app);
            if (transfer.is_open()) {
                transfer << cellphone[index].cname << "," << cellphone[index].cnum << "," << cellphone[index].dtype << ","
                        << cellphone[index].brand << "," << cellphone[index].model << "," << cellphone[index].issue << "," 
                        << cellphone[index].status << "," << cellphone[index].date << "," << cellphone[index].time<< ","
                        << cellphone[index].rate<<endl;
                transfer.close();
            } else {
                cerr << "Error: Unable to open file 'completed.txt'\n";
            }
            for (int a = index; a < id - 1; a++) {
            cellphone[a] = cellphone[a + 1]; 	
            }
            id--; 
            cout << "Ticket completely paid!" << endl;
            save(type);
        }
        else if(done == 'n'||done == 'N'){
            char type = 'p';
            cellphone[index].status = "Cancelled";
            cellphone[index].date = getCurrentDateTime("%m-%d-%Y");
            cellphone[index].time = getCurrentDateTime("%I:%M %p");
            canid++;
            ofstream transfer("cancelled.txt", ios::app);
            if (transfer.is_open()) {
                transfer<< cellphone[index].cname << "," << cellphone[index].cnum << "," << cellphone[index].dtype << ","
                        << cellphone[index].brand << "," << cellphone[index].model << "," << cellphone[index].issue << "," 
                        << cellphone[index].status << "," << cellphone[index].date << "," << cellphone[index].time<<endl;
                transfer.close();
            } else {
                cerr << "Error: Unable to open file 'cancelled.txt'\n";
            }
            for (int a = index; a < id - 1; a++) {
            cellphone[a] = cellphone[a + 1]; 	
            }
            id--; 
            cout << "Ticket cancelled successfully!" << endl;
            save(type);
        }else{
            cout << "Invalid input\n";
        }
    }else{
        cout << "ID not found!" << endl;
    }
    this_thread::sleep_for(chrono::seconds(3));
    paymenu();
}
void viewcancel(){
    loadcancel(); 
	system("CLS");
    cout<<"Cancelled Request: \n";
    // Table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(13) << "Status" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < canid; i++) {
        cout << "| " << setw(3) << left << i+1 << " | " 
             << setw(30) << cancel[i].cname << " | "
             << setw(13) << cancel[i].cnum << " | "
             << setw(13) << cancel[i].dtype << " | "
             << setw(13) << cancel[i].brand << " | "
             << setw(18) << cancel[i].model << " | "
             << setw(30) << cancel[i].issue << " | "
             << setw(13) << cancel[i].status << " | "
             << setw(10) << cancel[i].date << " | "
             << setw(8) << cancel[i].time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
             << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
             << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
             << string(10, '-') << "+\n";
    }
    char a, type = 'b';
    while(true){
        cout << "Do you want to search? [y] YES or [N] NO:  ";
        cin>>a;
        if(a == 'y'|| a == 'Y'){
            int opt;
            do {
                cout << "Search cancelled requests by:" << endl;
                cout << "1. Device Type" << endl;
                cout << "2. Brand" << endl;
                cout << "3. Model" << endl;
                cout << "4. Issue" << endl;
                cout << "5. Date" << endl;
                cout << "6. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                system("CLS");
                

                switch (opt) {
                case 1: searchByDeviceType(cancel, canid, type);
                        break;
                case 2: searchByBrand(cancel, canid, type);
                        break;
                case 3: searchByModel(cancel, canid, type);
                        break;
                case 4: searchByIssue(cancel, canid, type);
                        break;
                case 5: searchByDate(cancel, canid, type);
                        break;
                case 6: viewcancel();
                        return;
                default:
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }

            } while (true);
            break;
        }
        else if(a == 'n' || a == 'N'){
            break;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
    cout << "\nPress Enter to exit: " << endl;
    cin.get();
    cin.get();
    paymenu();
    return;
}
void viewcomplete(){
    loadcomplete(); 
	system("CLS");
    cout<<"Completed Request:\n";
    // Table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
         
    cout << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(9) << "Status" << " | " << setw(13) << "Rate" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < comid; i++) {
        cout << "| " << setw(3) << left << i+1 << " | " 
             << setw(30) << complete[i].cname << " | "
             << setw(13) << complete[i].cnum << " | "
             << setw(13) << complete[i].dtype << " | "
             << setw(13) << complete[i].brand << " | "
             << setw(18) << complete[i].model << " | "
             << setw(30) << complete[i].issue << " | "
             << setw(9) << complete[i].status << " | "
             << setw(2) << "PHP " << setw(9)<< complete[i].rate << " | "
             << setw(10) << complete[i].date << " | "
             << setw(8) << complete[i].time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
            << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
            << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
            << string(12, '-') << "+" << string(10, '-') << "+\n";
    }
    char a, type = 'c';
    while(true){
        cout << "Do you want to search? [y] YES or [N] NO:  ";
        cin>>a;
        if(a == 'y'|| a == 'Y'){
            int opt;
            do {
                cout << "Search completed requests by:" << endl;
                cout << "1. Device Type" << endl;
                cout << "2. Brand" << endl;
                cout << "3. Model" << endl;
                cout << "4. Issue" << endl;
                cout << "5. Date" << endl;
                cout << "6. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                system("CLS");
                
                switch (opt) {
                case 1: searchByDeviceType(complete, comid, type);
                        break;
                case 2: searchByBrand(complete, comid, type);
                        break;
                case 3: searchByModel(complete, comid, type);
                        break;
                case 4: searchByIssue(complete, comid, type);
                        break;
                case 5: searchByDate(complete, comid, type);
                        break;
                case 6: viewcomplete();
                        return;
                default:
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }

            } while (true);
            break;
        }
        else if(a == 'n' || a == 'N'){
            break;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
    cout << "\nPress Enter to exit: " << endl;
    cin.get();
    cin.get();
    paymenu();
    return;
}
//search & sort for request system
void searchByBrand(request arr[], int size, char type) {
    string search;
    cout << "Enter the brand to search for: ";
    getline(cin>>ws, search);

    searchResults.clear();
    indexes.clear();

    for (int i = 0; i < size; i++) {
        if (arr[i].brand.find(search) != string::npos) {
            indexes.push_back(i); // Store the index 
            searchResults.push_back(arr[i]); // Add to searchResults
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByDeviceType(request arr[], int size, char type) {
    string search;
    cout << "Enter the device type to search for: ";
    getline(cin>>ws, search);
  
    searchResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].dtype.find(search) != string::npos) {
            indexes.push_back(i);
            searchResults.push_back(arr[i]);
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByModel(request arr[], int size, char type) {
    string search;
    cout << "Enter the Model to search for: ";
    getline(cin>>ws, search);

    searchResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].model.find(search) != string::npos) {
            indexes.push_back(i);
            searchResults.push_back(arr[i]);
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByIssue(request arr[], int size, char type) {
    string search;
    cout << "Enter the issue to search for: ";
    getline(cin>>ws, search);

    searchResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].issue.find(search) != string::npos) {
            indexes.push_back(i);
            searchResults.push_back(arr[i]);
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByDate(request arr[], int size, char type) {
    string search;
    cout << "Enter the date (m-d-Y) to search for: ";
    getline(cin>>ws, search);

    searchResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].date == search) {
            indexes.push_back(i);
            searchResults.push_back(arr[i]);
        }
    }

    displaySearchResults(arr, size, type);
}
//buy & sell search
void searchByPBrand(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the brand to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();

    for (int i = 0; i < size; i++) {
        if (arr[i].brand.find(search) != string::npos) {
            indexes.push_back(i); // Store the index 
            prodResults.push_back(arr[i]); // Add to searchResults
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPDeviceType(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the device type to search for: ";
    getline(cin>>ws, search);
  
    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].dtype.find(search) != string::npos) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPModel(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Model to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].model.find(search) != string::npos) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPColor(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Color to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].color.find(search) != string::npos) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPDisplay(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Display/Resolution to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].display == search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPCamera(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Camera Pixels to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].cam == search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPStorage(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Storage size to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].storage == search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPCpu(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the Processor to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].cpu.find(search) != string::npos) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPRam(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the RAM size to search for: ";
    getline(cin>>ws, search);

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].ram == search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByLowPrice(buysell arr[], int size, char type) {
    int search;
    cout << "Enter the Price to search for: ";
    cin>>search;

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].price <= search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByHighPrice(buysell arr[], int size, char type) {
    int search;
    cout << "Enter the Price to search for: ";
    cin>>search;

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].price >= search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}
void searchByPDate(buysell arr[], int size, char type) {
    string search;
    cout << "Enter the date (m-d-Y) to search for: ";
    cin>>search;

    prodResults.clear();
    indexes.clear();
    for (int i = 0; i < size; i++) {
        if (arr[i].date == search) {
            indexes.push_back(i);
            prodResults.push_back(arr[i]);
        }
    }

    displayProdResults(arr, size, type);
}