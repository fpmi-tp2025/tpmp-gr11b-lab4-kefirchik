#ifndef FISH_FLOTILLA_FUNCTIONS_H
#define FISH_FLOTILLA_FUNCTIONS_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct CrewMember {
    int id;
    std::string lastName;
    std::string position;
    int hireDate;
    int birthYear;
    int trawlerId;
};

struct Trawler {
    int id;
    std::string name;
    double displacement;
    int buildDate;
};

struct Bank {
    int id;
    std::string name;
};

struct Voyage {
    int id;
    int trawlerId;
    std::string startDate;
    std::string endDate;
};

struct Catch {
    int id;
    int voyageId;
    int bankId;
    std::string fishType;
    double quantityKg;
    std::string quality;
};

struct Statistics {
    int trawlerId;
    double totalCatch;
};

// Инициализация базы данных
sqlite3* initializeDatabase(const std::string& dbPath);

// Функции для работы с таблицами
bool addTrawler(sqlite3* db, const Trawler& trawler);
bool updateTrawler(sqlite3* db, int id, const Trawler& newData);
bool deleteTrawler(sqlite3* db, int id);

bool addCrewMember(sqlite3* db, const CrewMember& member);
bool updateCrewMember(sqlite3* db, int id, const CrewMember& newData);
bool deleteCrewMember(sqlite3* db, int id);

bool addVoyage(sqlite3* db, const Voyage& voyage);
bool updateVoyage(sqlite3* db, int id, const Voyage& newData);
bool deleteVoyage(sqlite3* db, int id);

bool addCatch(sqlite3* db, const Catch& fishCatch);
bool updateCatch(sqlite3* db, int id, const Catch& newData);
bool deleteCatch(sqlite3* db, int id);

bool addBank(sqlite3* db, const std::string& bankName);
bool updateBankName(sqlite3* db, int bankId, const std::string& newName);
bool deleteBank(sqlite3* db, int bankId);

bool calculateBonuses(sqlite3* db,
    const std::string& startDate,
    const std::string& endDate,
    double planAmount,
    double pricePerKg);

bool calculateBonusForCrewMember(
    sqlite3* db,
    int crewId,
    const std::string& startDate,
    const std::string& endDate,
    double planAmount,
    double pricePerKg
);

std::vector<Bank> getAllBanks(sqlite3* db);
Bank getBankById(sqlite3* db, int bankId);

// Вспомогательные функции
void printError(sqlite3* db);
std::vector<Trawler> getAllTrawlers(sqlite3* db);
std::vector<CrewMember> getCrewForTrawler(sqlite3* db, int trawlerId);

#endif // FISH_FLOTILLA_FUNCTIONS_H