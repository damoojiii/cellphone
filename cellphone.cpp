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

request cellphone[50];
request cancel[255];
request complete[255];

buysell bns[100];
buysell sold[255];

vector<int> indexes;
vector<request> searchResults;
vector<buysell> prodResults;

//utilities & id/counter
int id = 0, canid = 0, comid = 0;
int bid = 0, sid = 0;
int key = 13;

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
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') {  // handle backspace
            if (password.length() > 0) {
                cout << "\b \b"; // move cursor back, write space, move cursor back again
                password.pop_back(); // remove last character 
            }
        } else {
            cout << '*'; // print asterisk 
            password.push_back(ch); // add character to password
        }
    }
    cout << endl;
    return password;
}
// encryption and decryption
string encrypt(string text) {
    string encrypted = ""; 
    
    for (int i = 0; i < text.length(); i++) {
        char letter = text[i];
        
        if (isupper(letter)) {
            char swap = 'A' + (letter - 'A' + key) % 26;
            encrypted += swap;
        } else if (islower(letter)) {
            char swap = 'a' + (letter - 'a' + key) % 26;
            encrypted += swap;
        } else if (isdigit(letter)) {
        char swap = '0' + (letter - '0' + key) % 10;
        encrypted += swap;
        } else {
            encrypted += letter; 
        }
    }
    
    return encrypted;
}
string decrypt(string text) {
    string decrypted = ""; 
    
    // to decrypt use the negative of the key for backward
    int inverse = 26 - (key % 26); 
    int numInverse = 10 - (key % 10);
    
    for (int i = 0; i < text.length(); i++) {
        char letter = text[i];
        
        if (isupper(letter)) {
            char swap = 'A' + (letter - 'A' + inverse) % 26;
            decrypted += swap;
        } else if (islower(letter)) {
            char swap = 'a' + (letter - 'a' + inverse) % 26;
            decrypted += swap;
        } else if (isdigit(letter)) {
            char swap = '0' + (letter - '0' + numInverse) % 10;
            decrypted += swap;
        } else {
            decrypted += letter;  
        }
    }
    
    return decrypted;
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
        cout << "\n\n\n\n";
        cout << setw(70) << "" << "=================================================\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "ID# "<< index + 1 <<"\t\t\tStatus: " << cellphone[index].status<<endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "Customer Name: " << cellphone[index].cname<<endl;
        cout << setw(70) << "" << "Brand & Model: " << cellphone[index].brand << " " << cellphone[index].model<<endl;
        cout << setw(70) << "" << "Issue: " << cellphone[index].issue <<endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "Rate of Service: " << cellphone[index].rate <<endl;
        cout << setw(70) << "" << "Tendered Amount: " << paid << endl;
        cout << setw(70) << "" << "Change: " << change << endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "\t\t "<<cellphone[index].date<<" "<<cellphone[index].time<<endl;
        cout << setw(70) << "" << "\t\tThank you, Come Again!\n";
        cout << "\n";
        cout << setw(70) << "" << "=================================================\n";
        cout << "\n\n";
        cout << setw(73) << "" << "+-------------------------------------+" << endl;
        cout << setw(73) << "" << "|       Press Enter to proceed:       |" << endl;
        cout << setw(73) << "" << "+-------------------------------------+" << endl;
        cin.get();
        cin.get();
    }
    else if(type == 'b'){
        cout << "\n\n\n\n";
        cout << setw(70) << "" << "=================================================\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "No.# "<< index + 1 <<"\t\t\tSold to: " << sold <<endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "Brand: " << bns[index].brand <<endl;
        cout << setw(70) << "" << "Model: " << bns[index].model <<endl;
        cout << setw(70) << "" << "Color: " << bns[index].color <<endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "Price: " << bns[index].price <<endl;
        cout << setw(70) << "" << "Tendered Amount: " << paid << endl;
        cout << setw(70) << "" << "Change: " << change << endl;
        cout << "\n";
        cout << setw(70) << "" << "-------------------------------------------------\n";
        cout << "\n";
        cout << setw(70) << "" << "\t\t "<<bns[index].date<<" "<<bns[index].time<<endl;
        cout << setw(70) << "" << "\t\tThank you, Come Again!\n";
        cout << "\n";
        cout << setw(70) << "" << "=================================================\n";
        cout << "\n\n";
        cout << setw(73) << "" << "+-------------------------------------+" << endl;
        cout << setw(73) << "" << "|       Press Enter to proceed:       |" << endl;
        cout << setw(73) << "" << "+-------------------------------------+" << endl;
        cin.get();
        cin.get();
    }
    
}
//function for computing the payment
void computeRate(int index, char type) {
    int serviceRate = 0, paidAmount = 0;
    string sold;

    if (type == 'p') {
        cout << "\n\n\n";
        cout << setw(70) << "" << "+------------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter rate of service for ID# " << index + 1 << "    |" << endl;
        cout << setw(70) << "" << "| > ";
        while (!(cin >> serviceRate)) {
            cin.clear();  
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "\n\n";
            cout << setw(70) << "" << "+------------------------------------+" << endl;
            cout << setw(70) << "" << "| Invalid input! Please enter a      |" << endl;
            cout << setw(70) << "" << "| number:                            |" << endl;
            cout << setw(70) << "" << "| > ";
        }
        cout << setw(70) << "" << "+------------------------------------+" << endl;

        cellphone[index].rate = serviceRate;
        while (true) {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Enter Tendered Amount:           |" << endl;
            cout << setw(70) << "" << "| > ";
            while (!(cin >> paidAmount)) {
                cin.clear();    
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
                cout << setw(70) << "" << "| number:                          |" << endl;
                cout << setw(70) << "" << "| > ";
            }
            cout << setw(70) << "" << "+----------------------------------+" << endl;

            int changeAmount = paidAmount - serviceRate;

            if (changeAmount >= 0) {
                cellphone[index].date = getCurrentDateTime("%m-%d-%Y");
                cellphone[index].time = getCurrentDateTime("%I:%M %p");
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Change amount: PHP " << changeAmount << "           |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                receipt(index, changeAmount, paidAmount, type, sold);
                return;
            } else {
                cout << "\n\n";
                cout << setw(70) << "" << "+--------------------------------------------+" << endl;
                cout << setw(70) << "" << "|            Insufficient payment.           |" << endl;
                cout << setw(70) << "" << "| Additional amount of PHP " << -changeAmount << " is required. |" << endl;
                cout << setw(70) << "" << "+--------------------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }

    } else if (type == 'b') {
        cout << "\n\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Name of Customer:                |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, sold);
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        while (true) {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Enter Tendered Amount:           |" << endl;
            cout << setw(70) << "" << "| > ";
            while (!(cin >> paidAmount)) {
                cin.clear();    
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
                cout << setw(70) << "" << "| number:                          |" << endl;
                cout << setw(70) << "" << "| > ";
            }
            cout << setw(70) << "" << "+----------------------------------+" << endl;

            int changeAmount = paidAmount - bns[index].price;

            if (changeAmount >= 0) {
                bns[index].date = getCurrentDateTime("%m-%d-%Y");
                bns[index].time = getCurrentDateTime("%I:%M %p");
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Change amount: PHP " << changeAmount << "           |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                receipt(index, changeAmount, paidAmount, type, sold);
                return;
            } else {
                cout << "\n\n";
                cout << setw(70) << "" << "+--------------------------------------------+" << endl;
                cout << setw(70) << "" << "|            Insufficient payment.           |" << endl;
                cout << setw(70) << "" << "| Additional amount of PHP " << -changeAmount << " is required. |" << endl;
                cout << setw(70) << "" << "+--------------------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
    }
}
//color
void setLimeColor() {
    cout << "\033[1;92m";
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
void searchByCname(request arr[], int size, char type);
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
        cout << "\n\n";
        cout << setw(73) << "" << "+----------------------------------+" << endl;
        cout << setw(73) << "" << "|        No results found.         |" << endl;
        cout << setw(73) << "" << "+----------------------------------+" << endl;
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
        cout << "\n\n";
        cout << setw(73) << "" << "+----------------------------------+" << endl;
        cout << setw(73) << "" << "|        No results found.         |" << endl;
        cout << setw(73) << "" << "+----------------------------------+" << endl;
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
//request counter for today
int datetoday(){
    int datecounter = 0;
    string dateNow = getCurrentDateTime("%m-%d-%Y");
    for(int i = 0; i < id; i++){  
        if(cellphone[i].date == dateNow){
            datecounter++;
        }
    }
    return datecounter;
}

int main() {
    setLimeColor();
    if (start) {
        start = false;
        welcomescreen();
    }
    //check if the database for admin is empty, if empty it will proceed to register, otherwise it will proceed to login
    ifstream empty("useradmin.txt");
    if (empty.peek() == ifstream::traits_type::eof()) {
        empty.close();
        regis();
    } else {
        empty.close();
        if (!sign) {
            signIn();
        }
    }
    
    loadpending();
    loadcancel();
    loadcomplete();
    int datecounter = datetoday();
    
    while (true) {
        system("CLS");
        cout << "\n\n\n\n\n";
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "|   No. of Ongoing Request Today:  |" << endl;
        cout << setw(65) << "" << "|                "<< left << setw(18) << datecounter << "|" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << "\n\n";
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "|            WELCOME               |" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "| Please select an option:         |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 1. Create a New Ticket           |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 2. View All Ongoing Request      |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 3. Update Ticket                 |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 4. Payment & Request History     |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 5. Buy 'n Sell                   |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 6. Settings                      |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 7. Exit                          |" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "| Enter your choice:               |" << endl;
        cout << setw(65) << "" << "| > ";
        int choice;
        while (!(cin >> choice)) {
            cin.clear();    // clear the error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            cout << "\n\n";
            cout << setw(65) << "" << "+----------------------------------+" << endl;
            cout << setw(65) << "" << "| Invalid input! Please enter a    |" << endl;
            cout << setw(65) << "" << "| number:                          |" << endl;
            cout << setw(65) << "" << "| > ";
        }
        cout << setw(65) << "" << "+----------------------------------+" << endl;

        switch (choice) {
            case 1: cticket(); break;
            case 2: cview(); break;
            case 3: cupdate(); break;
            case 4: paymenu(); break;
            case 5: buynsell(); break;
            case 6: settings(); break;
            case 7:
                cout << "\n\n";
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                cout << setw(65) << "" << "|       Thank you! Exiting..       |" << endl;
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                exit(0);
            default:
                cout << "\n\n";
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                cout << setw(65) << "" << "|         Invalid choice!          |" << endl;
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
        cout << endl;
    }
}
void printLogo(int screenWidth) {
    int logoWidth = 20;
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
}
void printLogo1(int screenWidth) {
    int logoWidth = 20;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "              ____             " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "             //\\  \\           " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "            //  \\  \\         " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "           //\\   \\  \\       " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "          //||\\   \\  \\     " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "         //||||\\   \\  \\   " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "        //||||||\\   \\  \\ " << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "       //||||||||\\   \\ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "      //||||||||||\\ / //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "     //||||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "    //||||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "   //||||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "  //||||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << " /\\||||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "/  \\||||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "\\   \\||||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << " \\   \\||||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "  \\   \\||||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "   \\   \\||/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "    \\   \\/ //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "     \\    //" << endl;
    cout << setw((screenWidth - logoWidth) / 2) << "" << "      -----" << endl;
    cout << endl;
}
void welcomescreen() {
    int screenWidth = 160;
    int titleWidth = 29;
    int welcomeWidth = 37;

    auto start_time = chrono::steady_clock::now();
    while (chrono::steady_clock::now() - start_time < chrono::seconds(3)) {
        system("CLS");
        cout<<"\n\n";
        printLogo(screenWidth);
        this_thread::sleep_for(chrono::milliseconds(800)); 
        system("CLS");
        cout<<"\n\n";
        printLogo1(screenWidth);
        this_thread::sleep_for(chrono::milliseconds(800)); 
    }

    system("CLS");
    cout<<"\n\n";
    printLogo(screenWidth);
    cout << setw((screenWidth - titleWidth) / 2) << "" << "CELLPHONE REPAIR REQUEST SYSTEM" << endl;
    cout << endl;
    cout << setw((screenWidth - welcomeWidth) / 2) << "" << "Welcome to Our Cellphone Repair Service" << endl;
    cout << endl;
    this_thread::sleep_for(chrono::seconds(3));
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
	
    if(type == 'p'){ // for pending request
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
    else if(type == 'b'){ // for product
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
    while (!(cin >> choice)) {
        
        cin.clear(); // clear the error
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        cout << "\n\n";
        cout << setw(67) << "" << "+------------------------------+" << endl;
        cout << setw(67) << "" << "| Invalid input!               |" << endl;
        cout << setw(67) << "" << "| Please enter a number:       |" << endl;
        cout << setw(67) << "" << "| > ";
    }
    cout << setw(55) << "" << "+----------------------------------------------------+" << endl;

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
    int count = 1;
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
            string temp = signup[0][1];
            temp = decrypt(temp);
            if (signup[0][0] == user && temp == pass) {
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
            cout << setw(65) << "" << "|     Hello, " << left << setw(15) << user << "|" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            main();
        } else if (count == 3) {
            cout << "\n\n\n";
            cout << setw(65) << "" << "+---------------------------+" << endl;
            cout << setw(65) << "" << "|   Too many attempts!      |" << endl;
            cout << setw(65) << "" << "|   Exiting the program...  |" << endl;
            cout << setw(65) << "" << "+---------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            exit(0);
        } else {
            cout << "\n\n\n";
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
    string pass, conpass, ans1, ans2;
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
        pass = getPassword();
        cout << endl;
        cout << setw(60) << "" << "Confirm Password: ";
        conpass = getPassword();
        cout << endl;
        if (pass != conpass) {
            cout << setw(60) << "" << "Password and Confirm Password Don't Match" << endl << endl;
        }
        else {
            signup[0][1] = encrypt(pass);
            break;
        }
    }

    cout << setw(60) << "" << "Security Question 1: What is your mother's maiden name?\n";
    cout << setw(60) << "" << "Answer: ";
    getline(cin >> ws, ans1);
    signup[0][2] = encrypt(ans1);
    cout << endl;
    cout << setw(60) << "" << "Security Question 2: What was the name of your first pet?\n";
    cout << setw(60) << "" << "Answer: ";
    getline(cin >> ws, ans2);
    signup[0][3] = encrypt(ans2);

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
    cout << setw(65) << "" << "|                           |" << endl;
    cout << setw(65) << "" << "| 2. Search by Password     |" << endl;
    cout << setw(65) << "" << "|                           |" << endl;
    cout << setw(65) << "" << "| 3. Main Menu              |" << endl;
    cout << setw(65) << "" << "+---------------------------+" << endl;
    cout << setw(65) << "" << "| Enter your choice:        |" << endl;
    cout << setw(65) << "" << "| > ";
    while (!(cin >> ch)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\n\n";
        cout << setw(65) << "" << "+---------------------------+" << endl;
        cout << setw(65) << "" << "| Invalid input! Please     |" << endl;
        cout << setw(65) << "" << "| enter a number:           |" << endl;
        cout << setw(65) << "" << "| > ";
    }
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
                    string tempans1 = signup[0][2], tempans2 = signup[0][3];
                    tempans1 = decrypt(tempans1);
                    tempans2 = decrypt(tempans2);
                    found = true;
                    cout << "\n\n\n";
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| Answer the following      |" << endl;
                    cout << setw(65) << "" << "| security questions:       |" << endl;
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| What is your mother's     |" << endl;
                    cout << setw(65) << "" << "| maiden name?:             |" << endl;
                    cout << setw(65) << "" << "| > ";
                    getline(cin >> ws, securityAns1);
                    cout << setw(65) << "" << "| What was the name of      |" << endl;
                    cout << setw(65) << "" << "| your first pet?:          |" << endl;
                    cout << setw(65) << "" << "| > ";
                    getline(cin >> ws, securityAns2);
                    cout << setw(65) << "" << "+---------------------------+" << endl;

                    if (securityAns1 == tempans1 && securityAns2 == tempans2) {
                        string temp = signup[0][1];
                        temp = decrypt(temp);
                        cout << "\n\n";
                        cout << setw(65) << "" << "+---------------------------------+" << endl;
                        cout << setw(65) << "" << "| Account recovered!              |" << endl;
                        cout << setw(65) << "" << "| Your password is: " << temp << setw(8) << " |" << endl;
                        cout << setw(65) << "" << "+---------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(3));
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
                string temp = signup[0][1];
                temp = decrypt(temp);
                if (temp == spassword) {
                    string tempans1 = signup[0][2], tempans2 = signup[0][3];
                    tempans1 = decrypt(tempans1);
                    tempans2 = decrypt(tempans2);
                    found = true;
                    cout << "\n\n\n";
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| Answer the following      |" << endl;
                    cout << setw(65) << "" << "| security questions:       |" << endl;
                    cout << setw(65) << "" << "+---------------------------+" << endl;
                    cout << setw(65) << "" << "| What is your mother's     |" << endl;
                    cout << setw(65) << "" << "| maiden name?:             |" << endl;
                    cout << setw(65) << "" << "| > ";
                    getline(cin >> ws, securityAns1);
                    cout << setw(65) << "" << "| What was the name of      |" << endl;
                    cout << setw(65) << "" << "| your first pet?:          |" << endl;
                    cout << setw(65) << "" << "| > ";
                    getline(cin >> ws, securityAns2);
                    cout << setw(65) << "" << "+---------------------------+" << endl;

                    if (securityAns1 == tempans1 && securityAns2 == tempans2) {
                        cout << "\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Account recovered!             |" << endl;
                        cout << setw(65) << "" << "| Your Username is: " << signup[0][0] << setw(7) << " |" << endl;
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(3));
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
                cout << setw(65) << "" << "|                                |" << endl;
                cout << setw(65) << "" << "| 2. Update Password             |" << endl;
                cout << setw(65) << "" << "|                                |" << endl;
                cout << setw(65) << "" << "| 3. Update All                  |" << endl;
                cout << setw(65) << "" << "|                                |" << endl;
                cout << setw(65) << "" << "| 4. Go back                     |" << endl;
                cout << setw(65) << "" << "+--------------------------------+" << endl;
                cout << setw(65) << "" << "| Enter your choice:             |" << endl;
                cout << setw(65) << "" << "| > ";
                while (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    cout << "\n\n";
                    cout << setw(65) << "" << "+--------------------------------+" << endl;
                    cout << setw(65) << "" << "| Invalid input! Please enter a  |" << endl;
                    cout << setw(65) << "" << "| number:                        |" << endl;
                    cout << setw(65) << "" << "| > ";
                }
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
                        string pass, conpass, line, updateline;
                        while (true) {
                            cout << "\n\n\n";
                            cout << setw(65) << "" << "+--------------------------------+" << endl;
                            cout << setw(65) << "" << "| Enter Updated Password:        |" << endl;
                            cout << setw(65) << "" << "| > ";
                            pass = getPassword();
                            cout << setw(65) << "" << "| Confirm Updated Password:      |" << endl;
                            cout << setw(65) << "" << "| > ";
                            conpass = getPassword();
                            cout << setw(65) << "" << "+--------------------------------+" << endl;

                            if (pass != conpass) {
                                cout << "\n\n";
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << setw(65) << "" << "| Passwords do not match.        |" << endl;
                                cout << setw(65) << "" << "| Please try again.              |" << endl;
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << endl << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                            } else {
                                signup[0][1] = encrypt(pass);
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
                        string pass, conpass, line, updateline;
                        cout << "\n\n\n";
                        cout << setw(65) << "" << "+--------------------------------+" << endl;
                        cout << setw(65) << "" << "| Enter Updated Username:        |" << endl;
                        cout << setw(65) << "" << "| > ";
                        cin >> signup[0][0];
                        while (true) {
                            cout << setw(65) << "" << "| Enter Updated Password:        |" << endl;
                            cout << setw(65) << "" << "| > ";
                            pass = getPassword();
                            cout << setw(65) << "" << "| Confirm Updated Password:      |" << endl;
                            cout << setw(65) << "" << "| > ";
                            conpass = getPassword();
                            cout << setw(65) << "" << "+--------------------------------+" << endl;

                            if (pass != conpass) {
                                cout << "\n\n";
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << setw(65) << "" << "| Passwords do not match.        |" << endl;
                                cout << setw(65) << "" << "| Please try again.              |" << endl;
                                cout << setw(65) << "" << "+--------------------------------+" << endl;
                                cout << endl << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                            } else {
                                signup[0][1]=encrypt(pass);
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
                        cout << setw(65) << "" << "|         Invalid choice!        |" << endl;
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
            cout << setw(65) << "" << "|         Invalid Choice!        |" << endl;
            cout << setw(65) << "" << "+--------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}
void settings() {
    int count = 1, max = 3;
    string pass, temp;

    while (count <= max) {
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(65) << "" << "+------------------------------------+" << endl;
        cout << setw(65) << "" << "|   Enter your password to proceed   |" << endl;
        cout << setw(65) << "" << "| > ";
        pass = getPassword();
        temp = signup[0][1];
        temp = decrypt(temp);

        if (pass != temp) {
            cout << "\n\n";
            cout << setw(65) << "" << "+----------------------------------+" << endl;
            cout << setw(65) << "" << "|        Password Incorrect        |" << endl;
            cout << setw(65) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            count++;
        } else {
            break;
        }
    }

    if (count > max) {
        cout << "\n\n";
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "|       Too many attempts!         |" << endl;
        cout << setw(65) << "" << "|      Exiting the program...      |" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        exit(0);
    }

    while (true) {
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "|            SETTINGS              |" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "| Please select an option:         |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 1. Account Settings              |" << endl;
        cout << setw(65) << "" << "|                                  |" << endl;
        cout << setw(65) << "" << "| 2. Go Back                       |" << endl;
        cout << setw(65) << "" << "+----------------------------------+" << endl;
        cout << setw(65) << "" << "| Enter your choice:               |" << endl;
        cout << setw(65) << "" << "| > ";
        int choice;
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "\n\n";
            cout << setw(65) << "" << "+----------------------------------+" << endl;
            cout << setw(65) << "" << "| Invalid input! Please enter a    |" << endl;
            cout << setw(65) << "" << "| number:                          |" << endl;
            cout << setw(65) << "" << "| > ";
        }
        cout << setw(65) << "" << "+----------------------------------+" << endl;

        switch (choice) {
            case 1: updateadmin(); return;
            case 2: main(); return;
            default:
                cout << "\n\n";
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                cout << setw(65) << "" << "|         Invalid choice!          |" << endl;
                cout << setw(65) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
//main menu
void cticket() {
    char type = 'p';
    system("CLS");

    cout << "\n\n\n\n\n\n";
    cout << setw(65) << "" << "+----------------------------------+" << endl;
    cout << setw(65) << "" << "|       Create New Ticket          |" << endl;
    cout << setw(65) << "" << "+----------------------------------+" << endl;
    cout << setw(65) << "" << "| Please Provide the following     |" << endl;
    cout << setw(65) << "" << "| details:                         |" << endl;
    cout << setw(65) << "" << "+----------------------------------+" << endl;
    cout << setw(65) << "" << "| Customer Name:                   |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].cname);
    cout << setw(65) << "" << "| Contact Number:                  |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].cnum);
    cout << setw(65) << "" << "| Device Type:                     |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].dtype);
    cout << setw(65) << "" << "| Brand:                           |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].brand);
    cout << setw(65) << "" << "| Model:                           |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].model);
    cout << setw(65) << "" << "| Issue:                           |" << endl;
    cout << setw(65) << "" << "| > ";
    getline(cin >> ws, cellphone[id].issue);

    cellphone[id].status = "Ongoing";
    cellphone[id].date = getCurrentDateTime("%m-%d-%Y");
    cellphone[id].time = getCurrentDateTime("%I:%M %p");

    id++;
    save(type);

    cout << "\n\n";
    cout << setw(65) << "" << "+----------------------------------+" << endl;
    cout << setw(65) << "" << "|           Ticket Added!          |" << endl;
    cout << setw(65) << "" << "+----------------------------------+" << endl;

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
    cout << "\n\n\n\n";
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
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|      Press Enter to Proceed      |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.get();
}
void cview() {
    char a, type = 'a';
    loadpending();
    system("CLS");
    cout << "\n\n\n";
    cout << "Request:\n";
    
    displaycustomer();
    
    while (true) {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Do you want to search?           |" << endl;
        cout << setw(70) << "" << "| [y] YES or [n] NO                |" << endl;
        cout << setw(70) << "" << "| > ";
        cin >> a;
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int opt;
            while (true) {
                system("CLS");
                cout << "\n\n\n\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|       SEARCH REQUESTS BY:        |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| 1. Customer Name                 |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 2. Device Type                   |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 3. Brand                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 4. Model                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 5. Issue                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 6. Date                          |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 7. Go Back                       |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Enter your choice:               |" << endl;
                cout << setw(70) << "" << "| > ";
                
                while (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\n\n";
                    cout << setw(70) << "" << "+----------------------------------+" << endl;
                    cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
                    cout << setw(70) << "" << "| number:                          |" << endl;
                    cout << setw(70) << "" << "| > ";
                }

                system("CLS");

                switch (opt) {
                    case 1: searchByCname(cellphone, id, type); break;
                    case 2: searchByDeviceType(cellphone, id, type); break;
                    case 3: searchByBrand(cellphone, id, type); break;
                    case 4: searchByModel(cellphone, id, type); break;
                    case 5: searchByIssue(cellphone, id, type); break;
                    case 6: searchByDate(cellphone, id, type); break;
                    case 7: cview(); return;
                    default:
                        cout << "\n\n";
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        cout << setw(70) << "" << "| Invalid input. Please try again. |" << endl;
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                }
            }
        } else if (a == 'n' || a == 'N') {
            break;
        } else {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "|          Invalid Input           |" << endl;
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|       Press Enter to Exit        |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
    main();
}
void cupdate() {
    int num = 0;
    system("CLS");
    cout << "\n\n\n";
    cout << "Requests:" << endl;
    
    displaycustomer();

    cout << setw(70) << "" << "+----------------------------+" << endl;
    cout << setw(70) << "" << "| Enter ID to be updated or  |" << endl;
    cout << setw(70) << "" << "| Enter [0] to exit:         |" << endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please      |" << endl;
        cout << setw(70) << "" << "| enter a number:            |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+----------------------------+" << endl;
    if(num == 0){
        main(); return;
    }
    int index = -1; 
    for (int i = 0; i < id; i++) {
        if (i + 1 == num) {
            index = i;
            char dis = 'p';
            displayselect(index, dis);
            break;
        }
    }

    if (index != -1) {
        char type = 'p';
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Customer Name:     |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].cname);

        cout << setw(70) << "" << "| Enter Updated Contact Number:    |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].cnum);

        cout << setw(70) << "" << "| Enter Updated Device Type:       |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].dtype);

        cout << setw(70) << "" << "| Enter Updated Brand:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].brand);

        cout << setw(70) << "" << "| Enter Updated Model:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].model);

        cout << setw(70) << "" << "| Enter Updated Issue:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, cellphone[index].issue);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Request updated successfully!    |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        save(type);
    } else {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|       Request not found!         |" << endl;
        cout << setw(70) << "" << "| >> going back to main menu...    |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
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
void buynsell() {
    loadprod();
    loadsold();
    while (true) {
        system("CLS");
        int choice = 0;
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|         Buy 'n Sell Menu         |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Please select an option:         |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 1. Add a Product to Sell         |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 2. View all Products             |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 3. Update a Product              |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 4. Delete a Product              |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 5. Buy a Product                 |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 6. Transaction History           |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 7. Back                          |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter your choice:               |" << endl;
        cout << setw(70) << "" << "| > ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
            cout << setw(70) << "" << "| number:                          |" << endl;
            cout << setw(70) << "" << "| > ";
        }
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        switch (choice) {
            case 1: addprod(); return;
            case 2: viewprod(); return;
            case 3: updateprod(); return;
            case 4: delprod(); return;
            case 5: buyprod(); return;
            case 6: viewsold(); return;
            case 7: main(); return;
            default:
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|         Invalid choice!          |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
void addprod() {
    char type = 'b';
    system("CLS");
    cout << "\n\n\n\n\n\n\n\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|           Add a Product          |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "| Please Provide the Following     |" << endl;
    cout << setw(70) << "" << "| details:                         |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;

    cout << setw(70) << "" << "| Brand:                           |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].brand);

    cout << setw(70) << "" << "| Device Type:                     |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].dtype);

    cout << setw(70) << "" << "| Model:                           |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].model);

    cout << setw(70) << "" << "| Color:                           |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].color);

    cout << setw(70) << "" << "| Display/Resolution:              |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].display);

    cout << setw(70) << "" << "| Camera:                          |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].cam);

    cout << setw(70) << "" << "| Storage:                         |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].storage);

    cout << setw(70) << "" << "| Processor:                       |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].cpu);

    cout << setw(70) << "" << "| RAM:                             |" << endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, bns[bid].ram);

    cout << setw(70) << "" << "| Price:                           |" << endl;
    cout << setw(70) << "" << "| > ";
    cin >> bns[bid].price;

    if (cin.fail()) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input. Please try again. |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return addprod();  
    }

    bns[bid].status = "Available";
    bid++;
    save(type);

    cout << "\n" << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|          Product Added!          |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    buynsell();
}
void viewprod() {
    char a, ans, type = 'a';
    loadprod(); 
    system("CLS");

    cout << "\n\n\n";
    cout << "Available Products:\n";
    
    displayprod();
    
    while (true) {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Do you want to search?           |" << endl;
        cout << setw(70) << "" << "| [y] YES or [n] NO                |" << endl;
        cout << setw(70) << "" << "| > ";
        cin >> a;
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int opt;
            while (true) {
                system("CLS");
                cout << "\n\n\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|        SEARCH PRODUCTS BY:       |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| 1. Device Type                   |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 2. Brand                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 3. Model                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 4. Color                         |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 5. Display                       |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 6. Camera Pixels                 |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 7. Storage size                  |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 8. Processor                     |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 9. RAM size                      |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 10. Price                        |" << endl;
                cout << setw(70) << "" << "|                                  |" << endl;
                cout << setw(70) << "" << "| 11. Go Back                      |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Enter your choice:               |" << endl;
                cout << setw(70) << "" << "| > ";

                while (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\n\n";
                    cout << setw(70) << "" << "+----------------------------------+" << endl;
                    cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
                    cout << setw(70) << "" << "| number:                          |" << endl;
                    cout << setw(70) << "" << "| > ";
                }

                system("CLS");

                switch (opt) {
                    case 1: searchByPDeviceType(bns, bid, type); break;
                    case 2: searchByPBrand(bns, bid, type); break;
                    case 3: searchByPModel(bns, bid, type); break;
                    case 4: searchByPColor(bns, bid, type); break;
                    case 5: searchByPDisplay(bns, bid, type); break;
                    case 6: searchByPCamera(bns, bid, type); break;
                    case 7: searchByPStorage(bns, bid, type); break;
                    case 8: searchByPCpu(bns, bid, type); break;
                    case 9: searchByPRam(bns, bid, type); break;
                    case 10:
                        cout << "\n\n";
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        cout << setw(70) << "" << "| [q] Search by Price Below        |" << endl;
                        cout << setw(70) << "" << "| [e] Search by Price Above        |" << endl;
                        cout << setw(70) << "" << "| > ";
                        cin >> ans;
                        if (ans == 'q' || ans == 'Q') {
                            searchByLowPrice(bns, bid, type);
                        } else if (ans == 'e' || ans == 'E') {
                            searchByHighPrice(bns, bid, type);
                        } else {
                            cout << "\n\n";
                            cout << setw(70) << "" << "+----------------------------------+" << endl;
                            cout << setw(70) << "" << "|          Invalid Input           |" << endl;
                            cout << setw(70) << "" << "+----------------------------------+" << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                        }
                        break;
                    case 11: viewprod(); return;
                    default:
                        cout << "\n\n";
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        cout << setw(70) << "" << "| Invalid input. Please try again. |" << endl;
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                }
            }
        } else if (a == 'n' || a == 'N') {
            break;
        } else {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "|         Invalid Input            |" << endl;
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|       Press Enter to Exit        |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.ignore();
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
    cout << "\n\n";
    cout << setw(70) << "" << "+-------------------------------------+" << endl;
    cout << setw(70) << "" << "|       Press Enter to proceed:       |" << endl;
    cout << setw(70) << "" << "+-------------------------------------+" << endl;
    cin.ignore();
    cin.get();
}
void updateprod() {
    int num = 0;
    system("CLS");
    
    cout << "\n\n\n";
    cout << "Products:\n";
    
    displayprod();
    
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------+" << endl;
    cout << setw(70) << "" << "| Enter ID to be updated or  |" << endl;
    cout << setw(70) << "" << "| Enter [0] to exit:         |" << endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please      |" << endl;
        cout << setw(70) << "" << "| enter a number:            |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+----------------------------+" << endl;

    if(num == 0){
        buynsell(); return;
    }
    

    int index = -1; 
    for (int i = 0; i < bid; i++) {
        if (i + 1 == num) {
            index = i;
            char dis = 'b';
            displayselect(index, dis);
            break;
        }
    }

    if (index != -1) {
        char type = 'b';
        
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Brand:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].brand);
        cout << setw(70) << "" << "+----------------------------------+" << endl; 
        cout << setw(70) << "" << "| Enter Updated Device Type:       |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].dtype);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Model:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].model);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Color:             |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].color);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Display/Resolution:|" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].display);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Camera:            |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].cam);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Storage:           |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].storage);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Processor:         |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].cpu);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated RAM:               |" << endl;
        cout << setw(70) << "" << "| > ";
        getline(cin >> ws, bns[index].ram);
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter Updated Price:             |" << endl;
        cout << setw(70) << "" << "| > ";
        cin >> bns[index].price;
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Invalid input. Please try again. |" << endl;
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            return updateprod();  
        }
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Product updated successfully!    |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        save(type);
    } else {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|       Product not found!         |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        updateprod();
        return;
    }
    
    buynsell();
}
void delprod() {
    int num = 0;
    system("CLS");
    
    cout << "\n\n\n";
    cout << "Products:\n";
    
    displayprod();
    
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter No. to be deleted:         |" << endl;
    cout << setw(70) << "" << "| Enter [0] to exit:               |" << endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please      |" << endl;
        cout << setw(70) << "" << "| enter a number:            |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+---------------------------------+" << endl;
    if(num == 0){
        buynsell(); return;
    }
    int index = -1;
    for (int i = 0; i < bid; i++) {
        if (i + 1 == num) {
            char dis = 'b';
            index = i;
            displayselect(index, dis);
            break;
        }
    }

    if (index != -1) {
        while (true) {
            char done;
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Are you sure you want to delete  |" << endl;
            cout << setw(70) << "" << "| this product?                    |" << endl;
            cout << setw(70) << "" << "| [y] YES or [n] NO                |" << endl;
            cout << setw(70) << "" << "| > ";
            cin >> done;
            cout << setw(70) << "" << "+----------------------------------+" << endl;

            if (done == 'y' || done == 'Y') {
                char type = 'b';
                for (int i = index; i < bid - 1; i++) {
                    bns[i] = bns[i + 1];
                }
                bid--;
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Product deleted successfully!    |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                save(type);
                break;
            } else if (done == 'n' || done == 'N') {
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Going back to buy 'n sell menu.. |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                buynsell();
                break;
            } else {
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|         Invalid Input!           |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    } else {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|        Product not found!        |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        delprod();
        return;
    }
    
    buynsell();
}
void buyprod() {
    char purchase;
    int num = 0, index = -1;
    loadprod();
    system("CLS");

    cout << "\n\n\n";
    cout << "Available Products:\n";
    
    displayprod();

    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "| Select a No. of Product or       |" << endl;
    cout << setw(70) << "" << "| Type [0] to exit:                |" << endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please      |" << endl;
        cout << setw(70) << "" << "| enter a number:            |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+----------------------------------+" << endl;

    if(num == 0){
        buynsell();
        return;
    }
    for (int i = 0; i < bid; i++) {
        if (i + 1 == num) {
            index = i;
            char dis = 'b';
            displayselect(index, dis);
            break;
        }
    }

    if (index != -1) {
        while (true) {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Type [y] to proceed to purchase  |" << endl;
            cout << setw(70) << "" << "| or [n] to cancel                 |" << endl;
            cout << setw(70) << "" << "| > ";
            cin >> purchase;
            cout << setw(70) << "" << "+----------------------------------+" << endl;

            if (purchase == 'y' || purchase == 'Y') {
                char type = 'b';
                bns[index].status = "Sold";
                computeRate(index, type);
                sid++;
                ofstream transfer("sold.txt", ios::app);
                if (transfer.is_open()) {
                    transfer << bns[index].brand << "," << bns[index].dtype << "," << bns[index].model << ","
                             << bns[index].color << "," << bns[index].display << "," << bns[index].cam << ","
                             << bns[index].storage << "," << bns[index].cpu << "," << bns[index].ram << ","
                             << bns[index].status << "," << bns[index].price << "," << bns[index].date << ","
                             << bns[index].time << endl;
                    transfer.close();
                } else {
                    cerr << "Error: Unable to open file 'sold.txt'\n";
                }
                for (int a = index; a < bid - 1; a++) {
                    bns[a] = bns[a + 1];
                }
                bid--;
                cout << "\n\n";
                cout << setw(73) << "" << "+----------------------------------+" << endl;
                cout << setw(73) << "" << "|     Product completely paid!     |" << endl;
                cout << setw(73) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                save(type);
                break;
            } else if (purchase == 'n' || purchase == 'N') {
                buyprod();
                return;
            } else {
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|         Invalid input            |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    } else {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| No. of Product not found!        |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        buyprod();
        return;
    }

    buynsell();
}
void viewsold(){
    loadsold();
    system("cls");
    cout << "\n\n";
    cout << "Sold Devices: \n";
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(8) << "Status" << " | "
         << setw(15) << "Price" << " | " << setw(10) << "Date" << " | "<< setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    
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
             << setw(8) << sold[i].status << " | "
             << setw(2) << "PHP " << setw(11) << sold[i].price << " | "
             << setw(10) << sold[i].date << " | "
             << setw(8) << sold[i].time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    }
    char a, ans, type = 'b';
    
    while (true) {
        cout << "\n\n\n";
        cout << setw(85) << "" << "+----------------------------------+" << endl;
        cout << setw(85) << "" << "| Do you want to search?           |" << endl;
        cout << setw(85) << "" << "| [y] YES or [n] NO                |" << endl;
        cout << setw(85) << "" << "| > ";
        cin >> a;
        cout << setw(85) << "" << "+----------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int opt;
            do {
                system("CLS");
                cout << "\n\n\n\n\n";
                cout << setw(85) << "" << "+----------------------------------+" << endl;
                cout << setw(85) << "" << "|       SEARCH PRODUCTS BY:        |" << endl;
                cout << setw(85) << "" << "+----------------------------------+" << endl;
                cout << setw(85) << "" << "| 1. Device Type                   |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 2. Brand                         |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 3. Model                         |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 4. Color                         |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 5. Display                       |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 6. Camera Pixels                 |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 7. Storage Size                  |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 8. Processor                     |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 9. RAM Size                      |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 10. Price                        |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 11. Date                         |" << endl;
                cout << setw(85) << "" << "|                                  |" << endl;
                cout << setw(85) << "" << "| 12. Go Back                      |" << endl;
                cout << setw(85) << "" << "+----------------------------------+" << endl;
                cout << setw(85) << "" << "| Enter your choice:               |" << endl;
                cout << setw(85) << "" << "| > ";
                
                while (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\n";
                    cout << setw(85) << "" << "+----------------------------------+" << endl;
                    cout << setw(85) << "" << "| Invalid input! Please enter a    |" << endl;
                    cout << setw(85) << "" << "| number:                          |" << endl;
                    cout << setw(85) << "" << "| > ";
                }
                
                system("CLS");
                
                switch (opt) {
                    case 1: searchByPDeviceType(sold, sid, type); break;
                    case 2: searchByPBrand(sold, sid, type); break;
                    case 3: searchByPModel(sold, sid, type); break;
                    case 4: searchByPColor(sold, sid, type); break;
                    case 5: searchByPDisplay(sold, sid, type); break;
                    case 6: searchByPCamera(sold, sid, type); break;
                    case 7: searchByPStorage(sold, sid, type); break;
                    case 8: searchByPCpu(sold, sid, type); break;
                    case 9: searchByPRam(sold, sid, type); break;
                    case 10: {
                        cout << "\n\n";
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        cout << setw(70) << "" << "| Type [q] Search by Price Below   |" << endl;
                        cout << setw(70) << "" << "| or [e] Search by Price Above     |" << endl;
                        cout << setw(70) << "" << "| > ";
                        cin >> ans;
                        cout << setw(70) << "" << "+----------------------------------+" << endl;
                        
                        if (ans == 'q' || ans == 'Q') {
                            searchByLowPrice(sold, sid, type);
                        } else if (ans == 'e' || ans == 'E') {
                            searchByHighPrice(sold, sid, type);
                        } else {
                            cout << "\n\n";
                            cout << setw(85) << "" << "+----------------------------------+" << endl;
                            cout << setw(85) << "" << "|         Invalid Input            |" << endl;
                            cout << setw(85) << "" << "+----------------------------------+" << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            continue;
                        }
                        break;
                    }
                    case 11: searchByPDate(sold, sid, type); break;
                    case 12: viewsold(); return;
                    default:
                        cout << "\n\n";
                        cout << setw(85) << "" << "+----------------------------------+" << endl;
                        cout << setw(85) << "" << "| Invalid input. Please try again. |" << endl;
                        cout << setw(85) << "" << "+----------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        continue;
                }
                
            } while (true);
        } else if (a == 'n' || a == 'N') {
            break;
        } else {
            cout << "\n\n";
            cout << setw(85) << "" << "+----------------------------------+" << endl;
            cout << setw(85) << "" << "|         Invalid Input            |" << endl;
            cout << setw(85) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    cout << "\n\n";
    cout << setw(85) << "" << "+----------------------------------+" << endl;
    cout << setw(85) << "" << "|     Press Enter to go back       |" << endl;
    cout << setw(85) << "" << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
    buynsell();
}
void displaySold(buysell arr[], int size, int* indexes, int numResults){
    // Table header
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
         
    cout << "| " << left << setw(3) << "No." << " | " << setw(13) << "Brand" << " | "
         << setw(13) << "Device Type" << " | " << setw(18) << "Model" << " | " << setw(10) << "Color" << " | "
         << setw(18) << "Display/Resolution" << " | " << setw(8) << "Camera" << " | "
         << setw(8) << "Storage" << " | " << setw(18) << "Processor" << " | "
         << setw(7) << "RAM" << " | " << setw(8) << "Status" << " | "
         << setw(15) << "Price" << " | " << setw(10) << "Date" << " | "<< setw(8) << "Time" << " |\n";
         
    cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    
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
             << setw(8) << p.status << " | "
             << setw(2) << "PHP " << setw(11) << p.price << " | "
             << setw(10) << p.date << " | "
             << setw(8) << p.time << " |\n";
             
        cout << "+" << string(5, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+"
         << string(20, '-') << "+" << string(12, '-') << "+" << string(20, '-') << "+" << string(10, '-') << "+"
         << string(10, '-') << "+" << string(20, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(17, '-') << "+" << string(12, '-') << "+" << string(10, '-')<< "+\n";
    }
    cout << "\n\n";
    cout << setw(70) << "" << "+-----------------------------------+" << endl;
    cout << setw(70) << "" << "|       Press Enter to proceed:     |" << endl;
    cout << setw(70) << "" << "+-----------------------------------+" << endl;
    cin.ignore();
    cin.get();
}
//request payment section
void paymenu() {
    while (true) {
        system("CLS");
        int choice = 0;
        cout << "\n\n\n\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|      Please select an option:    |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| 1. Payment                       |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 2. Transaction History           |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 3. View all Cancelled Requests   |" << endl;
        cout << setw(70) << "" << "|                                  |" << endl;
        cout << setw(70) << "" << "| 4. Go Back                       |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Enter your choice:               |" << endl;
        cout << setw(70) << "" << "| > ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
            cout << setw(70) << "" << "| number:                          |" << endl;
            cout << setw(70) << "" << "| > ";
        }
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        switch (choice) {
            case 1: collect(); return;
            case 2: viewcomplete(); return;
            case 3: viewcancel(); return;
            case 4: main(); return;
            default:
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|         Invalid choice!          |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(2));
        }
    }
}
void collect() {
    char done;
    int num = 0, index = -1;
    loadpending(); 
    system("CLS");

    cout << "\n\n\n";
    cout << "Requests:\n";
    displaycustomer();

    cout << "\n\n";
    cout << setw(70) << "" << "+-------------------------------------+" << endl;
    cout << setw(70) << "" << "| Select an ID or Enter [0] to exit:  |" << endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(73) << "" << "+----------------------------+" << endl;
        cout << setw(73) << "" << "| Invalid input! Please      |" << endl;
        cout << setw(73) << "" << "| enter a number:            |" << endl;
        cout << setw(73) << "" << "| > ";
    }
    cout << setw(70) << "" << "+-------------------------------------+" << endl;
    if(num == 0){
        paymenu(); return;
    }
    for (int i = 0; i < id; i++) {
        if (i + 1 == num) {
            index = i;
            char dis = 'p';
            displayselect(index, dis);
            break;
        }
    }

    if (index != -1) {
        while(true){
            cout << "\n\n";
            cout << setw(70) << "" << "+-------------------------------------+" << endl;
            cout << setw(70) << "" << "| Type [y] Completed or [n] Cancelled |" << endl;
            cout << setw(70) << "" << "| > ";
            cin >> done;
            cout << setw(70) << "" << "+-------------------------------------+" << endl;

            if (done == 'y' || done == 'Y') {
                char type = 'p';
                cellphone[index].status = "Completed";
                computeRate(index, type);
                comid++;
                ofstream transfer("completed.txt", ios::app);
                if (transfer.is_open()) {
                    transfer << cellphone[index].cname << "," << cellphone[index].cnum << "," << cellphone[index].dtype << ","
                            << cellphone[index].brand << "," << cellphone[index].model << "," << cellphone[index].issue << "," 
                            << cellphone[index].status << "," << cellphone[index].date << "," << cellphone[index].time << ","
                            << cellphone[index].rate << endl;
                    transfer.close();
                } else {
                    cerr << "Error: Unable to open file 'completed.txt'\n";
                }
                for (int a = index; a < id - 1; a++) {
                    cellphone[a] = cellphone[a + 1]; 	
                }
                id--; 
                cout << "\n\n";
                cout << setw(73) << "" << "+----------------------------------+" << endl;
                cout << setw(73) << "" << "| Ticket completed successfully!   |" << endl;
                cout << setw(73) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                save(type);
                break;
            } else if (done == 'n' || done == 'N') {
                char type = 'p';
                cellphone[index].status = "Cancelled";
                cellphone[index].date = getCurrentDateTime("%m-%d-%Y");
                cellphone[index].time = getCurrentDateTime("%I:%M %p");
                canid++;
                ofstream transfer("cancelled.txt", ios::app);
                if (transfer.is_open()) {
                    transfer << cellphone[index].cname << "," << cellphone[index].cnum << "," << cellphone[index].dtype << ","
                            << cellphone[index].brand << "," << cellphone[index].model << "," << cellphone[index].issue << "," 
                            << cellphone[index].status << "," << cellphone[index].date << "," << cellphone[index].time << endl;
                    transfer.close();
                } else {
                    cerr << "Error: Unable to open file 'cancelled.txt'\n";
                }
                for (int a = index; a < id - 1; a++) {
                    cellphone[a] = cellphone[a + 1]; 	
                }
                id--; 
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "| Ticket cancelled successfully!   |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                save(type);
                break;
            } else {
                cout << "\n\n";
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                cout << setw(70) << "" << "|         Invalid input            |" << endl;
                cout << setw(70) << "" << "+----------------------------------+" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        
    } else {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "|          ID not found!           |" << endl;
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        collect();
        return;
    }

    paymenu();
}
void viewcancel(){
    loadcancel(); 
	system("CLS");
    cout << "\n\n";
    cout << setw(3) << "" <<"Cancelled Request: \n";
    // Table header
    cout << setw(3) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
         
    cout << setw(3) << "" << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(13) << "Status" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << setw(3) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
         << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < canid; i++) {
        cout << setw(3) << "" << "| " << setw(3) << left << i+1 << " | " 
             << setw(30) << cancel[i].cname << " | "
             << setw(13) << cancel[i].cnum << " | "
             << setw(13) << cancel[i].dtype << " | "
             << setw(13) << cancel[i].brand << " | "
             << setw(18) << cancel[i].model << " | "
             << setw(30) << cancel[i].issue << " | "
             << setw(13) << cancel[i].status << " | "
             << setw(10) << cancel[i].date << " | "
             << setw(8) << cancel[i].time << " |\n";
             
        cout << setw(3) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
             << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
             << string(32, '-') << "+" << string(15, '-') << "+" << string(12, '-') << "+"
             << string(10, '-') << "+\n";
    }
    char a, type = 'b';
    
    while(true) {
        cout << "\n\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Do you want to search?           |" << endl;
        cout << setw(70) << "" << "| [y] YES or [n] NO                |" << endl;
        cout << setw(70) << "" << "| > ";
        cin >> a;
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int opt;
            do {
                system("CLS");
                cout << "\n\n\n\n";
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "|     SEARCH CANCELLED REQUESTS    |" << endl;
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "| 1. Customer Name                 |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 2. Device Type                   |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 3. Brand                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 4. Model                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 5. Issue                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 6. Date                          |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 7. Go Back                       |" << endl;
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "| Enter your choice:               |" << endl;
                cout << setw(72) << "" << "| > ";
                while (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\n";
                    cout << setw(72) << "" << "+----------------------------------+" << endl;
                    cout << setw(72) << "" << "| Invalid input! Please enter a    |" << endl;
                    cout << setw(72) << "" << "| number:                          |" << endl;
                    cout << setw(72) << "" << "| > ";
                }
                cout << setw(72) << "" << "+----------------------------------+" << endl;

                system("CLS");

                switch (opt) {
                    case 1: searchByCname(cancel, canid, type); break;
                    case 2: searchByDeviceType(cancel, canid, type); break;
                    case 3: searchByBrand(cancel, canid, type); break;
                    case 4: searchByModel(cancel, canid, type); break;
                    case 5: searchByIssue(cancel, canid, type); break;
                    case 6: searchByDate(cancel, canid, type); break;
                    case 7: viewcancel(); return;
                    default:
                        cout << "\n\n";
                        cout << setw(72) << "" << "+----------------------------------+" << endl;
                        cout << setw(72) << "" << "| Invalid input. Please try again. |" << endl;
                        cout << setw(72) << "" << "+----------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        continue;
                }

            } while (true);

            break;
        } else if (a == 'n' || a == 'N') {
            break;
        } else {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "|         Invalid Input            |" << endl;
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|       Press Enter to exit:       |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
    paymenu();
}
void viewcomplete(){
    loadcomplete(); 
	system("CLS");
    cout << "\n\n";
    cout << setw(5) << "" <<"Completed Request:\n";
    // Table header
    cout << setw(5) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
         
    cout << setw(5) << "" << "| " << left << setw(3) << "ID" << " | " << setw(30) << "Customer Name" << " | "
         << setw(13) << "Contact No." << " | " << setw(13) << "Device Type" << " | "
         << setw(13) << "Brand" << " | " << setw(18) << "Model" << " | " << setw(30) << "Issue" << " | "
         << setw(9) << "Status" << " | " << setw(13) << "Rate" << " | " << setw(10) << "Date" << " | "
         << setw(8) << "Time" << " |\n";
         
    cout << setw(5) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
         << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
         << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
         << string(12, '-') << "+" << string(10, '-') << "+\n";
    
    // Table rows
    for (int i = 0; i < comid; i++) {
        cout << setw(5) << "" << "| " << setw(3) << left << i+1 << " | " 
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
             
        cout << setw(5) << "" << "+" << string(5, '-') << "+" << string(32, '-') << "+" << string(15, '-') << "+"
            << string(15, '-') << "+" << string(15, '-') << "+" << string(20, '-') << "+"
            << string(32, '-') << "+" << string(11, '-') << "+" << string(15, '-') << "+" 
            << string(12, '-') << "+" << string(10, '-') << "+\n";
    }
    char a, type = 'c';
    
    while(true) {
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Do you want to search?           |" << endl;
        cout << setw(70) << "" << "| [y] YES or [n] NO                |" << endl;
        cout << setw(70) << "" << "| > ";
        cin >> a;
        cout << setw(70) << "" << "+----------------------------------+" << endl;

        if (a == 'y' || a == 'Y') {
            int opt;
            do {
                system("CLS");
                cout << "\n\n\n\n";
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "|     SEARCH COMPLETED REQUESTS    |" << endl;
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "| 1. Customer Name                 |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 2. Device Type                   |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 3. Brand                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 4. Model                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 5. Issue                         |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 6. Date                          |" << endl;
                cout << setw(72) << "" << "|                                  |" << endl;
                cout << setw(72) << "" << "| 7. Go Back                       |" << endl;
                cout << setw(72) << "" << "+----------------------------------+" << endl;
                cout << setw(72) << "" << "| Enter your choice:               |" << endl;
                cout << setw(72) << "" << "| > ";
                while (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\n";
                    cout << setw(72) << "" << "+----------------------------------+" << endl;
                    cout << setw(72) << "" << "| Invalid input! Please enter a    |" << endl;
                    cout << setw(72) << "" << "| number:                          |" << endl;
                    cout << setw(72) << "" << "| > ";
                }
                cout << setw(72) << "" << "+----------------------------------+" << endl;

                system("CLS");

                switch (opt) {
                    case 1: searchByCname(complete, comid, type); break;
                    case 2: searchByDeviceType(complete, comid, type); break;
                    case 3: searchByBrand(complete, comid, type); break;
                    case 4: searchByModel(complete, comid, type); break;
                    case 5: searchByIssue(complete, comid, type); break;
                    case 6: searchByDate(complete, comid, type); break;
                    case 7: viewcomplete(); return;
                    default:
                        cout << "\n\n";
                        cout << setw(72) << "" << "+----------------------------------+" << endl;
                        cout << setw(72) << "" << "| Invalid input. Please try again. |" << endl;
                        cout << setw(72) << "" << "+----------------------------------+" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        continue;
                }

            } while (true);

            break;
        } else if (a == 'n' || a == 'N') {
            break;
        } else {
            cout << "\n\n";
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            cout << setw(70) << "" << "|         Invalid Input            |" << endl;
            cout << setw(70) << "" << "+----------------------------------+" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|      Press Enter to exit:        |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
    paymenu();
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
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cout << setw(70) << "" << "|      Press Enter to Proceed      |" << endl;
    cout << setw(70) << "" << "+----------------------------------+" << endl;
    cin.get();
}
//search & sort for request system
void searchByCname(request arr[], int size, char type) {
    string search;
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the customer name to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin >> ws, search);
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << "\n";

    searchResults.clear();
    indexes.clear();

    for (int i = 0; i < size; i++) {
        if (arr[i].cname.find(search) != string::npos) {
            indexes.push_back(i); 
            searchResults.push_back(arr[i]); 
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByBrand(request arr[], int size, char type) {
    string search;
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Brand to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

    searchResults.clear();
    indexes.clear();

    for (int i = 0; i < size; i++) {
        if (arr[i].brand.find(search) != string::npos) {
            indexes.push_back(i); // store the index 
            searchResults.push_back(arr[i]); // add to searchResults
        }
    }

    displaySearchResults(arr, size, type);
}
void searchByDeviceType(request arr[], int size, char type) {
    string search;
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Device type to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------------+" << endl;
    cout << "\n";
  
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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Model to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Issue to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Date (m-d-Y) to search for:  |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Brand to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Device type to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------------+" << endl;
    cout << "\n";
  
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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Model to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Color to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(60) << "" << "+---------------------------------------------+" << endl;
    cout << setw(60) << "" << "| Enter the Display/Resolution to search for: |"<< endl;
    cout << setw(60) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(60) << "" << "+---------------------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+---------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Camera pixel to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+---------------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+---------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Storage size to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+---------------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Processor to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+------------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+-----------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the RAM size to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+-----------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Price to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> search)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
        cout << setw(70) << "" << "| number:                          |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Price to search for: |"<< endl;
    cout << setw(70) << "" << "| > ";
    while (!(cin >> search)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n";
        cout << setw(70) << "" << "+----------------------------------+" << endl;
        cout << setw(70) << "" << "| Invalid input! Please enter a    |" << endl;
        cout << setw(70) << "" << "| number:                          |" << endl;
        cout << setw(70) << "" << "| > ";
    }
    cout << setw(70) << "" << "+--------------------------------+" << endl;
    cout << "\n";

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
    cout << "\n\n";
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << setw(70) << "" << "| Enter the Date (m-d-Y) to search for:  |"<< endl;
    cout << setw(70) << "" << "| > ";
    getline(cin>>ws, search);
    cout << setw(70) << "" << "+----------------------------------------+" << endl;
    cout << "\n";

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