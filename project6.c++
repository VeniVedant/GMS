#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace std;

class alogin {
    string admin;
public:
    int adlogin() {
        cout << "Enter the admin code: ";
        cin >> admin;
        if (admin == "adminA1" || admin == "adminA2" || admin == "adminA3") {
            return getadpassword();
        } else {
            cout << "Username not found\n";
            return 0;
        }
    }

private:
    int getadpassword() {
        string pw;
        cout << "Enter the password: ";
        cin >> pw;
        if (pw == "gymadmin123") {
            cout << "WELCOME!!\n";
            return 1;
        } else {
            cout << "Incorrect password\n";
            return 0;
        }
    }
};

void allotment_gold(int& gc) {
    if (gc > 0) {
        cout << "Trainer alloted in gold class. Remaining trainers: " << --gc << "\n";
    } else {
        cout << "No trainer available\n";
    }
}

void allotment_silver(int& sc, int& gc) {
    if (sc > 0) {
        cout << "Trainer alloted in silver class. Remaining trainers: " << --sc << "\n";
    } else {
        cout << "No trainer available in silver class\n";
        if (gc > 0) {
            cout << "Allocating in gold class as backup\n";
            allotment_gold(gc);
        }
    }
}

int trainee_allotment(const char* class_type) {
    static int gold_class = 3, silver_class = 5;

    if (strcmp(class_type, "gold") == 0) {
        allotment_gold(gold_class);
    } else if (strcmp(class_type, "silver") == 0) {
        allotment_silver(silver_class, gold_class);
    } else {
        cout << "Invalid class type\n";
        return 0;
    }
    return 1;
}

class member {
    int member_number;
    char mem_name[50];
    char classs[50];
    char timings[50];
    float fee;
    long int contact;
public:
    void create_mem() {
        int class_choice;
        cout << "Enter the member number: ";
        cin >> member_number;
        cout << "Enter the name: ";
        cin.ignore();
        cin.getline(mem_name, 50);
        cout << "Enter the contact number: ";
        cin >> contact;
        
        cout << "Choose class:\n1. Gold\n2. Silver\nChoice: ";
        cin >> class_choice;
        if (class_choice == 1) {
            strcpy(classs, "gold");
            fee = 2500;
        } else if (class_choice == 2) {
            strcpy(classs, "silver");
            fee = 2000;
        }
        cout << "Monthly fee: " << fee << endl;
        trainee_allotment(classs);
        
        int timing_choice;
        cout << "Select timing:\n1. 6AM-7AM\n2. 7AM-8AM\n3. 8AM-9AM\n4. 4PM-5PM\n5. 5PM-6PM\n6. 6PM-7PM\n";
        cin >> timing_choice;
        switch (timing_choice) {
            case 1: strcpy(timings, "6AM-7AM"); break;
            case 2: strcpy(timings, "7AM-8AM"); break;
            case 3: strcpy(timings, "8AM-9AM"); break;
            case 4: strcpy(timings, "4PM-5PM"); break;
            case 5: strcpy(timings, "5PM-6PM"); break;
            case 6: strcpy(timings, "6PM-7PM"); break;
            default: strcpy(timings, "Unknown");
        }
    }

    void show_mem() const {
        cout << "Member Code: " << member_number
             << "\nName: " << mem_name
             << "\nClass: " << classs
             << "\nFee: " << fee
             << "\nContact: " << contact
             << "\nTimings: " << timings << endl;
    }

    int getmem() const {
        return member_number;
    }
};

fstream fp;
member m1;

void save_member() {
    fp.open("newdata2.dat", ios::out | ios::app);
    m1.create_mem();
    fp.write((char*)&m1, sizeof(m1));
    fp.close();
    cout << "The member has been successfully added...\n";
}

void show_all() {
    cout << "\n\t\tRECORDS:\n";
    fp.open("newdata2.dat", ios::in);
    while (fp.read((char*)&m1, sizeof(m1))) {
        m1.show_mem();
    }
    fp.close();
}

void display_record(int num) {
    bool found = false;
    fp.open("newdata2.dat", ios::in | ios::binary);
    
    if (!fp) {
        cout << "Error opening file! No data available.\n";
        return;
    }

    while (fp.read((char*)&m1, sizeof(m1))) {
        if (m1.getmem() == num) {
            m1.show_mem();
            found = true;
            break;
        }
    }

    fp.close();
    
    if (!found) {
        cout << "\nNo record found for member number: " << num << endl;
    }
}

void delete_member() {
    int num;
    cout << "Enter the member number: ";
    cin >> num;
    fp.open("newdata2.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp2.dat", ios::out);
    while (fp.read((char*)&m1, sizeof(m1))) {
        if (m1.getmem() != num) {
            fp2.write((char*)&m1, sizeof(m1));
        }
    }
    fp2.close();
    fp.close();
    remove("newdata2.dat");
    rename("Temp2.dat", "newdata2.dat");
    cout << "Record Deleted...\n";
}

void fnmanage() {
    int option;
    do {
        cout << "1. Create Member\n2. Display All Records\n3. Search Record\n4. Delete Member\n5. Exit\n";
        cin >> option;
        switch (option) {
            case 1: save_member(); break;
            case 2: show_all(); break;
            case 3: int num; cout << "Enter member number: "; cin >> num; display_record(num); break;
            case 4: delete_member(); break;
            case 5: break;
            default: cout << "Invalid option\n";
        }
    } while (option != 5);
}

int main() {
    int i;
    cout << "Select Mode\n1. USER\n2. ADMIN\n";
    cin >> i;
    if (i == 2) {
        alogin ad;
        if (ad.adlogin()) fnmanage();
        else cout << "Access Denied\n";
    } else if (i == 1) {
        cout << "User mode (Gym join/edit functionality can be added here)\n";
    }
    return 0;
}