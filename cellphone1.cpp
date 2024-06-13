#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>  //to manipulate string or convert into string
#include <thread> //thread & ctime for retrieving the date/time and use for sleep
#include <ctime>
#include <iomanip> //design
#include <sstream> //converting string to int in filestream
#include <conio.h>

using namespace std;

struct request{
    //long long int cnum;
    string cname,cnum, brand, model, issue, dtype, status, date, time;
    int rate;
};
struct buysell{
    string dtype, brand, model, color, display, cam, cpu, storage, ram, status, issue, condition, date, time;
    int price;
};

//arrays
string signup[1][4];//admin

request cellphone[100];
request cancel[100];
request complete[100];

buysell bns[100];
buysell sold[100];

buysell sangla[100];

//utilities & id/counter
int id = 0, canid = 0, comid = 0;
int bid = 0, sid = 0;

bool sign = false;

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
void sanglamenu();
void sanglaan();
void sanglahistory();
void settings();
//considerations
void delmenu();
void specdel();
void alldel();


int main(){
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
        cout<<"6. Sangla\n";
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
            case 6: sanglaan(); break;
            case 7: exit(0);
            default: 
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
        cout<<endl;
    }
    
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
void signIn(){
    system("CLS");
    int choice;
    cout<<"*********************************************"<<endl;
    cout<<"*******CELLPHONE REPAIR REQUEST SYSTEM*******"<<endl;
    cout<<"1. Login \n";
    cout<<"2. Forgot Username or Password\n";
    cout<<"Enter your choice: ";
    cin >> choice;
    cout<<endl;

    switch (choice)
    {
    case 1: login(); return;
    case 2: forgot(); return;
    default:
        system("CLS");
        cout<<"Input Invalid\n";
        this_thread::sleep_for(chrono::seconds(2));
        signIn();
    }
};
void login(){
    int count;
    string user,pass;
    system("CLS");
    cout<<"Enter your username:";
    cin>>user;
    cout<<"Enter your password:";
    pass = getPassword();

    ifstream input("useradmin.txt");
    while(input>>signup[0][0]>>signup[0][1]>>signup[0][2]>>signup[0][3]){
        if(signup[0][0]==user && signup[0][1]==pass){
            count=1;
            sign = true;
            system("cls");
        }
    }
    input.close();
    if(count==1){
        cout<<"\nHello "<<user<<"\n\nLOGIN SUCCESSFUL...\n";
        this_thread::sleep_for(chrono::seconds(3));
        main();
    }
    else{
        cout<<"\nInvalid Username or Password\nPlease Try Again..\n";
        this_thread::sleep_for(chrono::seconds(2));
        main();
    }
}
void regis(){
    string conpass;
    system("CLS");
    cout << "Note: Think throughly for credentials you have to input\n\n";
    cout << "Enter the Username: ";
    cin >> signup[0][0];
    while(true){
        cout << "Enter the Password: ";
        signup[0][1]=getPassword();
        cout << "Confirm Password: ";
        conpass=getPassword();
        if (signup[0][1]!=conpass){
            cout << "Password and Confirm Password Doesnt Match\n";
        }
        else{
            break;
        }
    }
    cout << "Security Question 1: What is your mother's maiden name?" << endl;
    cout << "Answer: ";
    cin >> signup[0][2];
    cout << "Security Question 2: What was the name of your first pet?" << endl;
    cout << "Answer: ";
    cin >> signup[0][3];
    
    ofstream reg("useradmin.txt", ios::app);
    reg << signup[0][0] << " " << signup[0][1] << " " << signup[0][2] << " " << signup[0][3] << endl;
    system("CLS");
    cout << "\nRegistration Successful." << endl;
    reg.close();
    this_thread::sleep_for(chrono::seconds(2));
    main();
    
}
void forgot()
{
        int ch;
        system("cls");
        cout<<"Forgot?\n";
        cout<<"1.Search by Username"<<endl;
        cout<<"2.Search by Password"<<endl;
        cout<<"3.Main menu"<<endl;
        cout<<"Enter your choice :";
        cin>>ch;
        switch(ch)
        {
                case 1:
                {
                    string susername, securityAns1, securityAns2;
                    cout << "Enter remembered username: ";
                    cin >> susername;

                    ifstream check("useradmin.txt");
                    bool found = false;

                    while (check >> signup[0][0] >> signup[0][1] >> signup[0][2] >> signup[0][3]) {
                        if (signup[0][0] == susername) {
                            found = true;
                            cout<< "Answer the following questions" << endl;
                            cout << "What is your mother's maiden name?: ";
                            cin >> securityAns1;
                            cout << "What was the name of your first pet?: ";
                            cin >> securityAns2;

                            if (securityAns1 == signup[0][2] && securityAns2 == signup[0][3]) {
                                cout << "\nAccount recovered!\nYour password is: " << signup[0][1] << endl;
                                updateadmin();
                                
                            } else {
                                cout << "Security answers do not match. Recovery failed." << endl;
                            }
                            break;
                        }
                    }
                    check.close();

                    if (!found) {
                        cout << "Username not found in the database." << endl;
                    }

                    this_thread::sleep_for(chrono::seconds(3));
                    signIn();
                    return;
                }
                case 2:
                {
                    string spassword, securityAns1, securityAns2;
                    cout << "Enter remembered password: ";
                    cin >> spassword;

                    ifstream check("useradmin.txt");
                    bool found = false;

                    while (check >> signup[0][0] >> signup[0][1] >> signup[0][2] >> signup[0][3]) {
                        if (signup[0][1] == spassword) {
                            found = true;
                            cout<< "Answer the following questions" << endl;
                            cout << "What is your mother's maiden name?: ";
                            cin >> securityAns1;
                            cout << "What was the name of your first pet?: ";
                            cin >> securityAns2;

                            if (securityAns1 == signup[0][2] && securityAns2 == signup[0][3]) {
                                cout << "\nAccount recovered!\nYour Username is: " << signup[0][0] << endl;
                                updateadmin();
                            } else {
                                cout << "Security answers do not match. Recovery failed." << endl;
                            }
                            break;
                        }
                    }
                    check.close();

                    if (!found) {
                        cout << "Password not found in the database." << endl;
                    }

                    this_thread::sleep_for(chrono::seconds(3));
                    signIn();
                    return;
                }

                case 3:
                {
                    signIn();
                    return;
                }
                default:
                    cout<<"Invalid Input. Kindly try again"<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    forgot();
        }
}
//main menu
void updateadmin(){
    char a;
    while(true){
        cout << "Do you want to update your account? [y] YES or [n] NO :";
        cin >> a;
        if(a == 'y'|| a == 'Y'){
            int choice;
            system("CLS");
            while(true){
                cout<<"*********************************"<<endl;
                cout<<"Please select an option: \n";
                cout<<"1. Update Username\n";
                cout<<"2. Update Password\n";
                cout<<"3. Update All\n";
                cout<<"4. Go back\n";
                cout<<"Enter your choice: ";
                cin>>choice;
                switch(choice)
                {
                    case 1:
                    {
                        ifstream file("useradmin.txt");
                        string line, updateline;

                        // Read the first line
                        getline(file, line);

                        cout << "Enter Updated Username: ";
                        cin >> signup[0][0];
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt");
                        reg << updateline << endl;

                        system("CLS");
                        cout << "\nUsername Updated Successfully." << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 2:
                    {
                        string conpass, line, updateline;
                        while(true){
                            cout << "Enter Updated Password: ";
                            signup[0][1]=getPassword();
                            cout << "Confirm Updated Password: ";
                            conpass=getPassword();
                            if(signup[0][1]!=conpass){
                                cout << "Password and Confirm Password Doesnt Match.\n";
                            }
                            else{
                                break;
                            }
                        }
                        ifstream file("useradmin.txt");
                        getline(file, line); 
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt", ios::trunc);
                        reg << updateline << endl;
                        system("CLS");
                        cout << "\nPassword Updated Successfully." << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 3:
                    {
                        string conpass, line, updateline;
                        cout << "Enter Updated Username: ";
                        cin >> signup[0][0];
                        while(true){
                            cout << "Enter Updated Password: ";
                            signup[0][1]=getPassword();
                            cout << "Confirm Updated Password: ";
                            conpass=getPassword();
                            if(signup[0][1]!=conpass){
                                cout << "Password and Confirm Password Doesnt Match.\n";
                            }
                            else{
                                break;
                            }
                        }
                        ifstream file("useradmin.txt");
                        getline(file, line); 
                        updateline = signup[0][0] + " " + signup[0][1] + " " + signup[0][2] + " " + signup[0][3];

                        ofstream reg("useradmin.txt");
                        reg << updateline << endl;
                        system("CLS");
                        cout << "\nAccount Updated Successfully." << endl;
                        reg.close();
                        this_thread::sleep_for(chrono::seconds(2));
                        main();
                        return;
                    }
                    case 4: main(); return;
                    default:
                        cout << "Invalid choice!" << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                }
            }
            break;
        }
        else if (a == 'n' || a == 'N'){
            main(); return;
        }
        else{
            cout << "Invalid Choice\n";
        }
    }

    
}
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
void cview(){
    loadpending(); 
	system("CLS");
	cout<<"Request:"<<endl;
	displaycustomer();
    cout<<endl;
    cout<<"Press Enter to go back\n";
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
    loadprod(); 
	system("CLS");
	cout<<"Available Products:"<<endl;
	displayprod();
    cout<<endl;
    cout<<"Press Enter to go back\n";
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
         << setw(15) << "Price" << setw(10) << "Date" << " | "<< setw(8) << "Time" << " |\n";
         
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
    cout<<endl;
    cout<<"Press Enter to go back\n";
    cin.get();
    cin.get();
	buynsell();
}
void sanglamenu(){
    while(true){
        system("CLS");
        int choice = 0;
        cout<<"********************************************"<<endl;
        cout<<"Please select an option: \n";
        cout<<"1. Sangla\n";
        cout<<"2. Sangla History\n";
        cout<<"3. Go Back\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: sanglaan(); return;
            case 2: sanglahistory(); return;
            case 3: main(); return;
            default:
                cout << "Invalid choice!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
void sanglaan(){
    char type = 'b';
    system("CLS");
    cout<<"Sangla"<<endl;
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
void sanglahistory(){

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
    cout<<endl;
    cout<<"Press Enter to go back\n";
    cin.get();
    cin.get();
	paymenu();
}
void viewcomplete(){
    loadcomplete(); 
	system("CLS");
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
    cout<<endl;
    cout<<"Press Enter to go back\n";
    cin.get();
    cin.get();
	paymenu();
}