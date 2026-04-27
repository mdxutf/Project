#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>   
#include <ctime>     
#include <cctype>
#include <sstream>
#include <regex>

using namespace std;

//class

class MAR {
public:
    int MemNum = 0;
    string MemTier = "";
    string PassNum = "";
    int MRZ = 0;
    string MemName = "";
    int MPB = 0;
};

class FLR {
public:
    int MemNum = 0;
    string Origin = "";
    string Destination = "";
    string FlightNum = "";
    string CabinClass = "";
    string DepartureDate = "";
    string CreationDate = "";
    bool Updated = false;
};

class TXN {
public:
    int MemNum = 0;
    string Type = "";
    int Points = 0;
    string Desc = "";
};
vector<MAR> gMember;
vector<FLR> gFlights;
vector<TXN> gTransactions;
string gSystemDate = "";


//func

int calculateMRZ(const string& passport) {
    if (passport.length() != 9) return 0;
    if (!isupper(passport[0])) return 0;

    int weights[9] = {7, 3, 1, 7, 3, 1, 7, 3, 1};
    int sum = 0;
    for (int i = 0; i < 9; ++i) {
        char c = passport[i];
        int val;
        if (i == 0) {
            val = 10 + (c - 'A');
        } else {
            if (!isdigit(c)) return 0;
            val = c - '0';
        }
        sum += val * weights[i];
    }
    return sum % 10;
}

bool checkFormat(const string& dateStr) {
    if (dateStr.length() != 10) {

        return false;

    }
    regex pattern("\\d{2}-\\d{2}-\\d{4}");
    int LastD[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int month = stoi(dateStr.substr(3, 2));
    int day = stoi(dateStr.substr(0, 2));
    int year = stoi(dateStr.substr(6, 10));
    if (month > 12 || month < 1 || year != 2025) {
        return false;
    }
    else if (regex_match(dateStr, pattern) && day <= LastD[month - 1] && day >= 1) {
        return true;
    }

    return false;
}

void delay(int sec){
    this_thread::sleep_for(chrono::seconds(sec));
}

//R0 - R5

void R0() {

    cout << "Welcome Message designed by your group" << endl;
    cout << "*** FFP Main Menu ***" << endl;
    cout << "[1] Load Starting Data" << endl;
    cout << "[2] Show All Member Accounts" << endl;
    cout << "[3] Open or Close Member Account" << endl;
    cout << "[4] Member Account Operations" << endl;
    cout << "[5] Generate Daily Statement" << endl;
    cout << "[6] Credits and Exit" << endl;
    cout << "********************************" << endl;
    cout << "Option (1 - 6):";

}

int R1(vector <MAR>& MAR){

    gMember = {
        {202456734, "Gold", "A56677890", 4, "WONG Claire", 45000},
        {202333890, "Green", "C78678908", 5, "MA Kathy", 10000},
        {202067856, "Silver", "E38876890", 1, "CHAN Peter", 53200},
        {202211843, "Gold", "E38900078", 7, "CHEUNG Alice", 30000}
    };
    gFlights = {
        {202211843, "Hong Kong", "London", "CC81", "First", "28-05-2025", "01-05-2025", 0},
        {202211843, "London", "Hong Kong", "CC82", "First", "10-06-2025", "01-05-2025", 0},
        {202333890, "London", "Dubai", "CC61", "Economy", "12-06-2025", "10-06-2025", 0},
        {202067856, "Hong Kong", "Dubai", "CC31", "Business", "05-07-2025", "20-06-2025", 0},
        {202067856, "Dubai", "London", "CC62", "Business", "08-07-2025", "20-06-2025", 0},
        {202456734, "Dubai", "Hong Kong", "CC32", "Business", "05-08-2025", "02-08-2025", 0}
    };

    string SetDate;
    int chance = 3;

    cout<<"Starting data loaded successfully!"<<endl;
    cout<<"*** Set System Date for updating Mileage Points ***"<<endl;
    while(chance >0){

        chance--;

        cout<<"Please enter system date (DD-MM-YYYY):";

        cin>>SetDate;

        if (checkFormat(SetDate)){

            char confirm;
            cout << "Confirmation (Y/N): ";
            cin >> confirm;
        
            if(toupper(confirm) == 'Y'){
               cout<<"The date is set"<<endl;
               delay(1);
               cout << "returns to the Main Menu" << endl;
               delay(1);
               return 0;
            }else{

                chance = 3;
            }

            
        }else{
            cout<<"invalid format or out-of-range dates"<<endl;
            delay(1);
            cout<<"Please prompt again"<<endl;
        }

    }

    cout<<"Since you have entered THREE consecutive invalid inputs"<<endl;
    delay(1);
    cout<<"the system should set a default date of 30-06-2025"<<endl;
    delay(1);
    cout << "returns to the Main Menu" << endl;
    return 0;

}


void R2() {
    cout << endl;
    cout << left << setw(20) << "Member";
    cout << left << setw(10) << "Member";
    cout << left << setw(20) << "Passport";
    cout << left << setw(10) << "MRZ";
    cout << left << setw(20) << "Member";
    cout << left << setw(10) << "Mileage Points" << endl;
    cout << left << setw(20) << "Number";
    cout << left << setw(10) << "Tier";
    cout << left << setw(20) << "Number";
    cout << left << setw(10) << "  ";
    cout << left << setw(20) << "Name";
    cout << left << setw(10) << "Balance" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;

    for (const auto& Table : gMember) {
        cout << left << setw(20) << Table.MemNum;
        cout << left << setw(10) << Table.MemTier;
        cout << left << setw(20) << Table.PassNum;
        cout << left << setw(10) << Table.MRZ;
        cout << left << setw(20) << Table.MemName;
        cout << left << setw(10) << Table.MPB << endl;
    }
    cout << endl;
    cout << left << setw(20) << "Member";
    cout << left << setw(10) << "Origin";
    cout << left << setw(20) << "Destination";
    cout << left << setw(10) << "Flight";
    cout << left << setw(10) << "Cabin";
    cout << left << setw(20) << "Departure";
    cout << left << setw(20) << "Creation";
    cout << left << setw(10) << "Updated" << endl;
    cout << left << setw(50) << "Number";
    cout << left << setw(10) << "Number";
    cout << left << setw(10) << "Class";
    cout << left << setw(20) << "Date";
    cout << left << setw(10) << "Date" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& Table : gFlights) {
        cout << left << setw(20) << Table.MemNum;
        cout << left << setw(10) << Table.Origin;
        cout << left << setw(20) << Table.Destination;
        cout << left << setw(10) << Table.FlightNum;
        cout << left << setw(10) << Table.CabinClass;
        cout << left << setw(20) << Table.DepartureDate;
        cout << left << setw(20) << Table.CreationDate;
        cout << left << setw(10) << Table.Updated << endl;
    }

}

void R3() {
    int acc = 0;
    cout << "Enter Member Number: ";
    cin >> acc;
    cin.ignore();

    bool exists = false;
    size_t idx = 0;
    for (size_t i = 0; i < gMember.size(); ++i) {
        if (gMember[i].MemNum == acc) {
            exists = true;
            idx = i;
            break;
        }
    }

    if (exists) {
        // Close account
        const MAR& m = gMember[idx];
        cout << endl << "Member Information:" << endl;
        cout << left << setw(20) << "Member Number" << ": " << m.MemNum << endl;
        cout << left << setw(20) << "Member Tier" << ": " << m.MemTier << endl;
        cout << left << setw(20) << "Passport Number" << ": " << m.PassNum << endl;
        cout << left << setw(20) << "MRZ" << ": " << m.MRZ << endl;
        cout << left << setw(20) << "Member Name" << ": " << m.MemName << endl;
        cout << left << setw(20) << "Mileage Points Balance" << ": " << m.MPB << endl << endl;

        char confirm;
        cout << "Confirm to close this account? (Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
            int closedNum = gMember[idx].MemNum;
            gMember.erase(gMember.begin() + idx);
            for (int i = static_cast<int>(gFlights.size()) - 1; i >= 0; --i) {
                if (gFlights[i].MemNum == closedNum) {
                    gFlights.erase(gFlights.begin() + i);
                }
            }
            cout << "Member account and related flight records closed successfully." << endl;
        } else {
            cout << "Close operation cancelled." << endl;
        }
    } else {
        // Open new account 
        cout << endl << "--- Open New Member Account ---" << endl;
        bool opened = false;
        for (int attempt = 0; attempt < 3; ++attempt) {
            string name, passport, tier;

            cout << "Attempt " << (attempt + 1) << "/3" << endl;
            cout << "Enter Member Name: ";
            getline(cin, name);

            cout << "Enter Passport Number (e.g. A12345678): ";
            cin >> passport;

            cout << "Enter Member Tier (Green/Silver/Gold/Diamond): ";
            cin >> tier;
            cin.ignore();

            // Validate passport
            bool validPassport = (passport.length() == 9 && isupper(passport[0]));
            if (validPassport) {
                for (size_t j = 1; j < 9; ++j) {
                    if (!isdigit(passport[j])) {
                        validPassport = false;
                        break;
                    }
                }
            }
            if (validPassport) {
                for (const auto& m : gMember) {
                    if (m.PassNum == passport) {
                        validPassport = false;
                        break;
                    }
                }
            }

            bool validTier = (tier == "Green" || tier == "Silver" || tier == "Gold" || tier == "Diamond");

            if (validPassport && validTier && !name.empty()) {
                int mrz = calculateMRZ(passport);

                string yearStr = "2025";
                if (!gSystemDate.empty() && gSystemDate.length() >= 10) {
                    yearStr = gSystemDate.substr(6, 4);
                }
                int year = stoi(yearStr);
                int rand5 = 10000 + (rand() % 90000);
                int newMemNum = year * 100000 + rand5;

                MAR newMember;
                newMember.MemNum = newMemNum;
                newMember.MemTier = tier;
                newMember.PassNum = passport;
                newMember.MRZ = mrz;
                newMember.MemName = name;
                newMember.MPB = 0;
                gMember.push_back(newMember);

                cout << "\nNew member account opened successfully!" << endl;
                cout << "Generated Member Number: " << newMemNum << endl;
                cout << "MRZ: " << mrz << endl;
                opened = true;
                break;
            } else {
                cout << "Invalid input. " << (2 - attempt) << " attempt(s) left." << endl;
            }
        }
        if (!opened) {
            cout << "Failed to open new member account after 3 attempts." << endl;
        }
    }
    cout << "\nOperation completed. Returning to Main Menu." << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void R4(vector <MAR> MAR) {

    int acc = 0;

    cout << "Enter Member Number: ";

    cin >> acc;

    bool Found = false;
    
    for (size_t i = 0; i < gMember.size(); ++i) {
        if (gMember[i].MemNum == acc) {
            Found = true;
            break;
        }
    }

    if (Found) {

        cout << "such Member Number does not exist" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "returns to the Main Menu" << endl;
        this_thread::sleep_for(chrono::seconds(2));

    }
    else{
        cout << "Action for Member Number: " << acc << endl;
        cout << "***** Member Account Operations Menu ***********************" << endl;
        cout << "[1] Edit Member Information" << endl;
        cout << "[2] Update Mileage Points Balance according to Flight Records" << endl;
        cout << "[3] Create Flight Records" << endl;
        cout << "[4] Redeem Mileage Points for a Gift & Transfer" << endl;
        cout << "[5] Return to Main Menu" << endl;
        cout << "***********************************************************" << endl;
        cout << "Option (1 - 5):";
    }
    
    int Sel = 0;
    cin>>Sel;
    if((Sel>0)&&(Sel<6)){
        
        
        
        char confirm;
        cout << "Confirm to edit this account? (Y/N): ";
        cin >> confirm;
        
        if(toupper(confirm) == 'Y'){
            
        }
        
    }

}
//R5: Generate Daily Statement
void R5(vector<MAR> MAR) {

    int acc = 0;
    cout << "Enter Member Number: ";
    cin >> acc;

    bool Found = false;
    int idx = 0;

    for (int i = 0; i < MAR.size(); i++) {
        if (MAR[i].MemNum == acc) {
            Found = true;
            idx = i;
            break;
        }
    }

    if (!Found) {
        cout << "Such Member Number does not exist." << endl;
        return;
    }

    cout << "Member Name: " << MAR[idx].MemName << endl;
    cout << "Member Number: " << MAR[idx].MemNum << endl;
    cout << "Statement Date: " << gSystemDate << endl;
    cout << "----------------------------------------------------------------" << endl;

    cout << "Transaction Summary:" << endl;
    cout << left << setw(16) << "Type"
        << setw(10) << "Mileage"
        << setw(30) << "Description" << endl;

    bool anyTxn = false;
    for (int i = 0; i < gTransactions.size(); i++) {
        if (gTransactions[i].MemNum == acc) {
            cout << left << setw(16) << gTransactions[i].Type
                << setw(10) << gTransactions[i].Points
                << setw(30) << gTransactions[i].Desc << endl;
            anyTxn = true;
        }
    }

    if (!anyTxn) {
        cout << "(No transactions recorded)" << endl;
    }

    cout << "----------------------------------------------------------------" << endl;

    cout << "Upcoming Itinerary:" << endl;
    cout << left << setw(14) << "Origin"
        << setw(14) << "Destination"
        << setw(10) << "Flight"
        << setw(12) << "Cabin"
        << setw(12) << "Departure" << endl;
    cout << "(No flight record vector available yet)" << endl;
    cout << "----------------------------------------------------------------" << endl;

    int bonusPct = 0;
    if (MAR[idx].MemTier == "Silver") {
        bonusPct = 2;
    }
    else if (MAR[idx].MemTier == "Gold") {
        bonusPct = 4;
    }
    else if (MAR[idx].MemTier == "Diamond") {
        bonusPct = 6;
    }

    cout << "Member Account Summary:" << endl;
    cout << left << setw(40) << "Total Mileage Points Balance" << ": " << MAR[idx].MPB << endl;
    cout << left << setw(40) << "Member Tier" << ": " << MAR[idx].MemTier << endl;
    cout << left << setw(40) << "Bonus Mileage Points" << ": " << bonusPct << "%" << endl;
}
//R6: Credits and Exit
void R6() {

    char confirm;

    do {
        cout << "Exit the program? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
            cout << "Invalid input. Please enter Y or N." << endl;
        }

    } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

    if (confirm == 'N' || confirm == 'n') {
        cout << "Exit cancelled. Returning to Main Menu." << endl;
        return;
    }
    // Display group member particulars, changing the details below to your actual group member particulars
    cout << "================================================================" << endl;
    cout << "                         Credits                                " << endl;
    cout << "================================================================" << endl;
    cout << left << setw(25) << "Student Name"
        << setw(15) << "Student No."
        << setw(10) << "Tutorial" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << left << setw(25) << "Member Name 1" << setw(15) << "12345671" << setw(10) << "TUT01" << endl;
    cout << left << setw(25) << "Member Name 2" << setw(15) << "12345672" << setw(10) << "TUT01" << endl;
    cout << left << setw(25) << "Member Name 3" << setw(15) << "12345673" << setw(10) << "TUT01" << endl;
    cout << left << setw(25) << "Member Name 4" << setw(15) << "12345674" << setw(10) << "TUT01" << endl;
    cout << left << setw(25) << "Hui Ho Chun Oscar" << setw(15) << "24048710A" << setw(10) << "B06" << endl;
    cout << "================================================================" << endl;

    exit(0);
}

//Main

int main() {

    int Selection = 0;

    int acc = 0;

    bool lock = true;

    vector<MAR> MAR = { //MAR Member Account Records
        {202456734, "Gold", "A56677890",4,"WONG Claire",45000},
        {202333890, "Green", "C78678908",5,"MA Kathy",10000},
        {202067856, "Silver", "E38876890",1,"CHAN Peter",53200},
        {202211843, "Gold", "E38900078",7,"CHEUNG Alice",30000}
    };
    do {
        R0();

        cin >> Selection;

        if((lock&&Selection!=1)&&(Selection != 6)){

            cout<<"***Error***"<<endl;

            cout<<"Options 2 to 5 on the Main Menu are enabled only after the system is loaded with the starting data"<<endl;

            this_thread::sleep_for(chrono::seconds(2));
            cout << "returns to the Main Menu" << endl;
            this_thread::sleep_for(chrono::seconds(2));

            continue;

        }
        

        switch (Selection) {
        case 1:
            R1(MAR);
            lock = false;
            break;
        case 2:
            R2();
            break;
        case 3:
            R3();
            break;
        case 4:
            R4(MAR);
            break;
        case 5:
            R5(MAR);
            break;
        case 6:
            R6();
            break;
        default:
            cout << "No Such Selection";
            break;
        }
    } while (Selection != 7);
    cout << "Program terminates. Good bye!" << endl;
    srand(static_cast<unsigned>(time(NULL)));

    return 0;
}
