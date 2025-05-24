#include "functions.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\n===== FISHING FLEET MANAGEMENT SYSTEM =====\n";
    cout << "1. Manage Banks\n";
    cout << "2. Manage Trawlers\n";
    cout << "3. Manage Crew Members\n";
    cout << "4. Manage Voyages\n";
    cout << "5. Manage Catches\n";
    cout << "6. Calculate Bonuses\n";
    cout << "7. Calculate Bonuses for a single crew member\n";
    cout << "0. Exit\n";
    cout << "Select option: ";
}

// Банки (BANKS)
void manageBanksMenu(sqlite3* db) {
    int choice;
    do {
        cout << "\n=== BANKS MANAGEMENT ===\n";
        cout << "1. Add New Bank\n";
        cout << "2. Update Bank Name\n";
        cout << "3. Delete Bank\n";
        cout << "4. List All Banks\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            string name;
            cout << "Enter bank name: ";
            getline(cin, name);
            if (addBank(db, name)) {
                cout << "Bank added successfully!\n";
            }
            break;
        }
        case 2: {
            int id;
            string newName;
            cout << "Enter bank ID to update: ";
            cin >> id;
            clearInputBuffer();
            cout << "Enter new bank name: ";
            getline(cin, newName);
            if (updateBankName(db, id, newName)) {
                cout << "Bank updated successfully!\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Enter bank ID to delete: ";
            cin >> id;
            clearInputBuffer();
            if (deleteBank(db, id)) {
                cout << "Bank deleted successfully!\n";
            }
            break;
        }
        case 4: {
            auto banks = getAllBanks(db);
            cout << "\n=== LIST OF BANKS ===\n";
            for (const auto& bank : banks) {
                cout << "ID: " << bank.id << " | Name: " << bank.name << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);
}

// Траулеры (TRAWLERS)
void manageTrawlersMenu(sqlite3* db) {
    int choice;
    do {
        cout << "\n=== TRAWLERS MANAGEMENT ===\n";
        cout << "1. Add New Trawler\n";
        cout << "2. Update Trawler\n";
        cout << "3. Delete Trawler\n";
        cout << "4. List All Trawlers\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            Trawler newTrawler;
            cout << "Enter trawler name: ";
            getline(cin, newTrawler.name);
            cout << "Enter displacement: ";
            cin >> newTrawler.displacement;
            cout << "Enter build year: ";
            cin >> newTrawler.buildDate;
            clearInputBuffer();

            if (addTrawler(db, newTrawler)) {
                cout << "Trawler added successfully!\n";
            }
            break;
        }
        case 2: {
            int id;
            Trawler updatedTrawler;
            cout << "Enter trawler ID to update: ";
            cin >> id;
            clearInputBuffer();
            cout << "Enter new trawler name: ";
            getline(cin, updatedTrawler.name);
            cout << "Enter new displacement: ";
            cin >> updatedTrawler.displacement;
            cout << "Enter new build year: ";
            cin >> updatedTrawler.buildDate;
            clearInputBuffer();

            if (updateTrawler(db, id, updatedTrawler)) {
                cout << "Trawler updated successfully!\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Enter trawler ID to delete: ";
            cin >> id;
            clearInputBuffer();
            if (deleteTrawler(db, id)) {
                cout << "Trawler deleted successfully!\n";
            }
            break;
        }
        case 4: {
            auto trawlers = getAllTrawlers(db);
            cout << "\n=== LIST OF TRAWLERS ===\n";
            for (const auto& trawler : trawlers) {
                cout << "ID: " << trawler.id << " | Name: " << trawler.name
                    << " | Displacement: " << trawler.displacement
                    << " | Build year: " << trawler.buildDate << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);
}

// Члены команды (CREW_MEMBERS)
void manageCrewMenu(sqlite3* db) {
    int choice;
    do {
        cout << "\n=== CREW MANAGEMENT ===\n";
        cout << "1. Add New Crew Member\n";
        cout << "2. Update Crew Member\n";
        cout << "3. Delete Crew Member\n";
        cout << "4. List All Crew Members\n";
        cout << "5. List Crew for Trawler\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            CrewMember newMember;
            cout << "Enter last name: ";
            getline(cin, newMember.lastName);
            cout << "Enter position (crew/fisherman/captain): ";
            getline(cin, newMember.position);
            cout << "Enter hire year: ";
            cin >> newMember.hireDate;
            cout << "Enter birth year: ";
            cin >> newMember.birthYear;
            cout << "Enter trawler ID: ";
            cin >> newMember.trawlerId;
            clearInputBuffer();

            if (addCrewMember(db, newMember)) {
                cout << "Crew member added successfully!\n";
            }
            break;
        }
        case 2: {
            int id;
            CrewMember updatedMember;
            cout << "Enter crew member ID to update: ";
            cin >> id;
            clearInputBuffer();
            cout << "Enter new last name: ";
            getline(cin, updatedMember.lastName);
            cout << "Enter new position: ";
            getline(cin, updatedMember.position);
            cout << "Enter new hire year: ";
            cin >> updatedMember.hireDate;
            cout << "Enter new birth year: ";
            cin >> updatedMember.birthYear;
            cout << "Enter new trawler ID: ";
            cin >> updatedMember.trawlerId;
            clearInputBuffer();

            if (updateCrewMember(db, id, updatedMember)) {
                cout << "Crew member updated successfully!\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Enter crew member ID to delete: ";
            cin >> id;
            clearInputBuffer();
            if (deleteCrewMember(db, id)) {
                cout << "Crew member deleted successfully!\n";
            }
            break;
        }
        case 4: {
            // Для простоты выводим всех членов команды для всех траулеров
            auto trawlers = getAllTrawlers(db);
            for (const auto& trawler : trawlers) {
                cout << "\n=== CREW FOR TRAWLER: " << trawler.name << " ===\n";
                auto crew = getCrewForTrawler(db, trawler.id);
                for (const auto& member : crew) {
                    cout << "ID: " << member.id << " | Name: " << member.lastName
                        << " | Position: " << member.position
                        << " | Hire year: " << member.hireDate
                        << " | Birth year: " << member.birthYear << endl;
                }
            }
            break;
        }
        case 5: {
            int trawlerId;
            cout << "Enter trawler ID: ";
            cin >> trawlerId;
            clearInputBuffer();
            auto crew = getCrewForTrawler(db, trawlerId);
            cout << "\n=== CREW MEMBERS ===\n";
            for (const auto& member : crew) {
                cout << "ID: " << member.id << " | Name: " << member.lastName
                    << " | Position: " << member.position << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);
}

// Рейсы (VOYAGES)
void manageVoyagesMenu(sqlite3* db) {
    int choice;
    do {
        cout << "\n=== VOYAGES MANAGEMENT ===\n";
        cout << "1. Add New Voyage\n";
        cout << "2. Update Voyage\n";
        cout << "3. Delete Voyage\n";
        cout << "4. List All Voyages\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            Voyage newVoyage;
            cout << "Enter trawler ID: ";
            cin >> newVoyage.trawlerId;
            clearInputBuffer();
            cout << "Enter start date (YYYY-MM-DD): ";
            getline(cin, newVoyage.startDate);
            cout << "Enter end date (YYYY-MM-DD or leave empty if ongoing): ";
            string endDate;
            getline(cin, endDate);
            newVoyage.endDate = endDate.empty() ? "" : endDate;

            if (addVoyage(db, newVoyage)) {
                cout << "Voyage added successfully!\n";
            }
            break;
        }
        case 2: {
            int id;
            Voyage updatedVoyage;
            cout << "Enter voyage ID to update: ";
            cin >> id;
            clearInputBuffer();
            cout << "Enter new trawler ID: ";
            cin >> updatedVoyage.trawlerId;
            clearInputBuffer();
            cout << "Enter new start date (YYYY-MM-DD): ";
            getline(cin, updatedVoyage.startDate);
            cout << "Enter new end date (YYYY-MM-DD or leave empty if ongoing): ";
            string endDate;
            getline(cin, endDate);
            updatedVoyage.endDate = endDate.empty() ? "" : endDate;

            if (updateVoyage(db, id, updatedVoyage)) {
                cout << "Voyage updated successfully!\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Enter voyage ID to delete: ";
            cin >> id;
            clearInputBuffer();
            if (deleteVoyage(db, id)) {
                cout << "Voyage deleted successfully!\n";
            }
            break;
        }
        case 4: {
            // Для простоты выводим все рейсы
            auto trawlers = getAllTrawlers(db);
            for (const auto& trawler : trawlers) {
                cout << "\n=== VOYAGES FOR TRAWLER: " << trawler.name << " ===\n";
                // Здесь должна быть функция getVoyagesForTrawler (нужно добавить в functions.h/cpp)
                // Временно используем getAllVoyages (если есть)
                cout << "NOTE: Need to implement getVoyagesForTrawler function\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);
}

// Уловы (CATCHES)
void manageCatchesMenu(sqlite3* db) {
    int choice;
    do {
        cout << "\n=== CATCHES MANAGEMENT ===\n";
        cout << "1. Add New Catch\n";
        cout << "2. Update Catch\n";
        cout << "3. Delete Catch\n";
        cout << "4. List All Catches\n";
        cout << "0. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            Catch newCatch;
            cout << "Enter voyage ID: ";
            cin >> newCatch.voyageId;
            cout << "Enter bank ID: ";
            cin >> newCatch.bankId;
            clearInputBuffer();
            cout << "Enter fish type: ";
            getline(cin, newCatch.fishType);
            cout << "Enter quantity (kg): ";
            cin >> newCatch.quantityKg;
            cout << "Enter quality (high/medium/low): ";
            getline(cin, newCatch.quality);

            if (addCatch(db, newCatch)) {
                cout << "Catch added successfully!\n";
            }
            break;
        }
        case 2: {
            int id;
            Catch updatedCatch;
            cout << "Enter catch ID to update: ";
            cin >> id;
            cout << "Enter new voyage ID: ";
            cin >> updatedCatch.voyageId;
            cout << "Enter new bank ID: ";
            cin >> updatedCatch.bankId;
            clearInputBuffer();
            cout << "Enter new fish type: ";
            getline(cin, updatedCatch.fishType);
            cout << "Enter new quantity (kg): ";
            cin >> updatedCatch.quantityKg;
            cout << "Enter new quality (high/medium/low): ";
            getline(cin, updatedCatch.quality);

            if (updateCatch(db, id, updatedCatch)) {
                cout << "Catch updated successfully!\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Enter catch ID to delete: ";
            cin >> id;
            clearInputBuffer();
            if (deleteCatch(db, id)) {
                cout << "Catch deleted successfully!\n";
            }
            break;
        }
        case 4: {
            // Для простоты выводим все уловы
            cout << "\n=== ALL CATCHES ===\n";
            // Здесь должна быть функция getAllCatches (нужно добавить в functions.h/cpp)
            cout << "NOTE: Need to implement getAllCatches function\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);
}

// Премии (BONUSES)
void manageBonusesMenu(sqlite3* db) {
    std::string startDate, endDate;
    double planAmount, pricePerKg;

    std::cout << "\n=== BONUS CALCULATION ===\n";
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;
    std::cout << "Enter plan amount (kg): ";
    std::cin >> planAmount;
    std::cout << "Enter price per kg: ";
    std::cin >> pricePerKg;

    if (calculateBonuses(db, startDate, endDate, planAmount, pricePerKg)) {
        std::cout << "Bonus calculation completed successfully!\n";
    }
}

void manageSingleBonusesMenu(sqlite3* db) {
    int crewId;
    std::string startDate, endDate;
    double planAmount, pricePerKg;

    std::cout << "\n=== BONUS FOR A CREW MEMBER CALCULATION ===\n";
    std::cout << "Enter crew member ID: ";
    std::cin >> crewId;
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;
    std::cout << "Enter plan amount (kg): ";
    std::cin >> planAmount;
    std::cout << "Enter price per kg: ";
    std::cin >> pricePerKg;

    if (calculateBonusForCrewMember(db, crewId, startDate, endDate, planAmount, pricePerKg)) {
        std::cout << "Bonus calculation completed successfully!\n";
    }
}

int main() {
    sqlite3* db = initializeDatabase("bin/FishFlotilla.db");
    if (!db) {
        cerr << "Failed to initialize database!\n";
        return 1;
    }

    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            manageBanksMenu(db);
            break;
        case 2:
            manageTrawlersMenu(db);
            break;
        case 3:
            manageCrewMenu(db);
            break;
        case 4:
            manageVoyagesMenu(db);
            break;
        case 5:
            manageCatchesMenu(db);
            break;
        case 6:
            manageBonusesMenu(db);
            break;
        case 7:
            manageSingleBonusesMenu(db);
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 0);

    sqlite3_close(db);
    return 0;
}