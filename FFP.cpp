#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class MAR{
    public:
    int MemNum = 0;
    string MemTier = "";
    string PassNum = "";
    int MRZ = 0;
    string MemName = "";
    int MPB = 0;
};

void R0(){

    cout<<"Welcome Message designed by your group" <<endl;
    cout<<"*** FFP Main Menu ***"<<endl;
    cout<<"[1] Load Starting Data"<<endl;
    cout<<"[2] Show All Member Accounts"<<endl;
    cout<<"[3] Open or Close Member Account"<<endl;
    cout<<"[4] Member Account Operations"<<endl;
    cout<<"[5] Generate Daily Statement"<<endl;
    cout<<"[6] Credits and Exit"<<endl;
    cout<<"********************************"<<endl;
    cout<<"Option (1 - 6):";

}

void R1(vector <MAR> MAR){
    
    cout << left << setw(20) << "Member";
    cout << left << setw(10) << "Member";
    cout << left << setw(20) << "Passport";
    cout << left << setw(10) << "MRZ";
    cout << left << setw(20) << "Member";
    cout << left << setw(10) << "Mileage Points"<<endl;
    cout << left << setw(20) << "Number";
    cout << left << setw(10) << "Tier";
    cout << left << setw(20) << "Number";
    cout << left << setw(10) << "  ";
    cout << left << setw(20) << "Name";
    cout << left << setw(10) << "Balance"<<endl;
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

void R4(vector <MAR> MAR){

    int acc = 0;

    cout<<"Enter Member Number: ";

    cin>>acc;

    bool Found = false;

    for (const auto& Table : MAR) {
        if (Table.MemNum == acc){
            Found = true;
            break;
        }
    }

    if(!Found){

        cout<<"such Member Number does not exist"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout<<"returns to the Main Menu"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        R0();

    }

    cout<<"Action for Member Number: "<<acc<<endl;
    cout<<"***** Member Account Operations Menu ***********************" <<endl;
    cout<<"[1] Edit Member Information"<<endl;
    cout<<"[2] Update Mileage Points Balance according to Flight Records"<<endl;
    cout<<"[3] Create Flight Records"<<endl;
    cout<<"[4] Redeem Mileage Points for a Gift & Transfer"<<endl;
    cout<<"[5] Return to Main Menu"<<endl;
    cout<<"***********************************************************"<<endl;
    cout<<"Option (1 - 5):";

}

int main(){

    //R0

    int Selection = 0;

    int acc = 0;

    vector<MAR> MAR = { //MAR Member Account Records
        {202456734, "Gold", "A56677890",4,"WONG Claire",45000},
        {202333890, "Green", "C78678908",5,"MA Kathy",10000},
        {202067856, "Silver", "E38876890",1,"CHAN Peter",53200},
        {202211843, "Gold", "E38900078",7,"CHEUNG Alice",30000}
    };

    R0();

    cin>>Selection;

    switch(Selection){
        case 1:
        R1(MAR);
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        R4(MAR);
        break;
        case 5:
        break;
        default:
        cout<<"No Such Selection";
    }

    //R1

    //R2

    //R3

    //R4

    return 0;
}