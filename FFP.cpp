#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

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
void R1(vector <MAR>& MAR) {
    cout << "Loading Starting Data..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Starting Data Loaded Successfully!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    R0();
}
void R2(vector <MAR> MAR) {

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

    for (const auto& Table : MAR) {
        cout << left << setw(20) << Table.MemNum;
        cout << left << setw(10) << Table.MemTier;
        cout << left << setw(20) << Table.PassNum;
        cout << left << setw(10) << Table.MRZ;
        cout << left << setw(20) << Table.MemName;
        cout << left << setw(10) << Table.MPB << endl;
    }

}



void R4(vector <MAR> MAR) {

    int acc = 0;

    cout << "Enter Member Number: ";

    cin >> acc;

    bool Found = false;

    for (const auto& Table : MAR) {
        if (Table.MemNum == acc) {
            Found = true;
            break;
        }
    }

    if (!Found) {

        cout << "such Member Number does not exist" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "returns to the Main Menu" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        R0();

    }

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
    cout << left << setw(25) << "Member Name 5" << setw(15) << "12345675" << setw(10) << "TUT01" << endl;
    cout << "================================================================" << endl;

    exit(0);
}

int main() {

    //R0

    int Selection = 0;

    int acc = 0;

    vector<MAR> MAR = { //MAR Member Account Records
        {202456734, "Gold", "A56677890",4,"WONG Claire",45000},
        {202333890, "Green", "C78678908",5,"MA Kathy",10000},
        {202067856, "Silver", "E38876890",1,"CHAN Peter",53200},
        {202211843, "Gold", "E38900078",7,"CHEUNG Alice",30000}
    };
    do {
        R0();

        cin >> Selection;

        switch (Selection) {
        case 1:
            R1(MAR);
            break;
        case 2:
            R2(MAR);
            break;
        case 3:
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
    } while (Selection != 'q');

    //R1

    //R2

    //R3

    //R4

    return 0;
}
