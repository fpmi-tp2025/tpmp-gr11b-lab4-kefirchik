#include "functions.h"
#include <iostream>
#include <iomanip>

// Инициализация базы данных
sqlite3* initializeDatabase(const std::string& dbPath) {
    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return db;
}

// Вывод ошибок SQLite
void printError(sqlite3* db) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
}

// Вспомогательная функция для выполнения SQL-запросов
bool executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С БАНКАМИ (BANKS) ********************/

bool addBank(sqlite3* db, const std::string& bankName) {
    std::string sql = "INSERT INTO BANKS (NAME) VALUES ('" + bankName + "');";
    return executeSQL(db, sql);
}

bool updateBankName(sqlite3* db, int bankId, const std::string& newName) {
    std::string sql = "UPDATE BANKS SET NAME = '" + newName +
        "' WHERE BANK_ID = " + std::to_string(bankId) + ";";
    return executeSQL(db, sql);
}

bool deleteBank(sqlite3* db, int bankId) {
    std::string sql = "DELETE FROM BANKS WHERE BANK_ID = " + std::to_string(bankId) + ";";
    return executeSQL(db, sql);
}

std::vector<Bank> getAllBanks(sqlite3* db) {
    std::vector<Bank> banks;
    const char* sql = "SELECT BANK_ID, NAME FROM BANKS;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        printError(db);
        return banks;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Bank b;
        b.id = sqlite3_column_int(stmt, 0);
        b.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        banks.push_back(b);
    }

    sqlite3_finalize(stmt);
    return banks;
}

Bank getBankById(sqlite3* db, int bankId) {
    Bank bank = { 0, "" };
    std::string sql = "SELECT BANK_ID, NAME FROM BANKS WHERE BANK_ID = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        printError(db);
        return bank;
    }

    sqlite3_bind_int(stmt, 1, bankId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        bank.id = sqlite3_column_int(stmt, 0);
        bank.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }

    sqlite3_finalize(stmt);
    return bank;
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С ТРАУЛЕРАМИ (TRAWLERS) ********************/

bool addTrawler(sqlite3* db, const Trawler& trawler) {
    std::string sql = "INSERT INTO TRAWLERS (NAME, DISPLACEMENT, BUILD_DATE) VALUES ('" +
        trawler.name + "', " + std::to_string(trawler.displacement) + ", " +
        std::to_string(trawler.buildDate) + ");";
    return executeSQL(db, sql);
}

bool updateTrawler(sqlite3* db, int id, const Trawler& newData) {
    std::string sql = "UPDATE TRAWLERS SET NAME = '" + newData.name +
        "', DISPLACEMENT = " + std::to_string(newData.displacement) +
        ", BUILD_DATE = " + std::to_string(newData.buildDate) +
        " WHERE TRAWLER_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

bool deleteTrawler(sqlite3* db, int id) {
    std::string sql = "DELETE FROM TRAWLERS WHERE TRAWLER_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

std::vector<Trawler> getAllTrawlers(sqlite3* db) {
    std::vector<Trawler> trawlers;
    const char* sql = "SELECT TRAWLER_ID, NAME, DISPLACEMENT, BUILD_DATE FROM TRAWLERS;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        printError(db);
        return trawlers;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Trawler t;
        t.id = sqlite3_column_int(stmt, 0);
        t.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        t.displacement = sqlite3_column_double(stmt, 2);
        t.buildDate = sqlite3_column_int(stmt, 3);
        trawlers.push_back(t);
    }

    sqlite3_finalize(stmt);
    return trawlers;
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С ЧЛЕНАМИ КОМАНД (CREW_MEMBERS) ********************/

bool addCrewMember(sqlite3* db, const CrewMember& member) {
    std::string sql = "INSERT INTO CREW_MEMBERS (LAST_NAME, POSITION, HIRE_DATE, BIRTH_YEAR, TRAWLER_ID) VALUES ('" +
        member.lastName + "', '" + member.position + "', " + std::to_string(member.hireDate) + ", " +
        std::to_string(member.birthYear) + ", " + std::to_string(member.trawlerId) + ");";
    return executeSQL(db, sql);
}

bool updateCrewMember(sqlite3* db, int id, const CrewMember& newData) {
    std::string sql = "UPDATE CREW_MEMBERS SET LAST_NAME = '" + newData.lastName +
        "', POSITION = '" + newData.position +
        "', HIRE_DATE = " + std::to_string(newData.hireDate) +
        ", BIRTH_YEAR = " + std::to_string(newData.birthYear) +
        ", TRAWLER_ID = " + std::to_string(newData.trawlerId) +
        " WHERE CREW_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

bool deleteCrewMember(sqlite3* db, int id) {
    std::string sql = "DELETE FROM CREW_MEMBERS WHERE CREW_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

std::vector<CrewMember> getCrewForTrawler(sqlite3* db, int trawlerId) {
    std::vector<CrewMember> crew;
    std::string sql = "SELECT CREW_ID, LAST_NAME, POSITION, HIRE_DATE, BIRTH_YEAR, TRAWLER_ID "
        "FROM CREW_MEMBERS WHERE TRAWLER_ID = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        printError(db);
        return crew;
    }

    sqlite3_bind_int(stmt, 1, trawlerId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        CrewMember cm;
        cm.id = sqlite3_column_int(stmt, 0);
        cm.lastName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cm.position = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        cm.hireDate = sqlite3_column_int(stmt, 3);
        cm.birthYear = sqlite3_column_int(stmt, 4);
        cm.trawlerId = sqlite3_column_int(stmt, 5);
        crew.push_back(cm);
    }

    sqlite3_finalize(stmt);
    return crew;
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С РЕЙСАМИ (VOYAGES) ********************/

bool addVoyage(sqlite3* db, const Voyage& voyage) {
    std::string sql = "INSERT INTO VOYAGES (TRAWLER_ID, START_DATE, END_DATE) VALUES (" +
        std::to_string(voyage.trawlerId) + ", '" + voyage.startDate + "', '" +
        (voyage.endDate.empty() ? "NULL" : voyage.endDate) + "');";
    return executeSQL(db, sql);
}

bool updateVoyage(sqlite3* db, int id, const Voyage& newData) {
    std::string sql = "UPDATE VOYAGES SET TRAWLER_ID = " + std::to_string(newData.trawlerId) +
        ", START_DATE = '" + newData.startDate + "'" +
        ", END_DATE = " + (newData.endDate.empty() ? "NULL" : "'" + newData.endDate + "'") +
        " WHERE VOYAGE_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

bool deleteVoyage(sqlite3* db, int id) {
    std::string sql = "DELETE FROM VOYAGES WHERE VOYAGE_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С УЛОВАМИ (CATCHES) ********************/

bool addCatch(sqlite3* db, const Catch& fishCatch) {
    std::string sql = "INSERT INTO CATCHES (VOYAGE_ID, BANK_ID, FISH_TYPE, QUANTITY_KG, QUALITY) VALUES (" +
        std::to_string(fishCatch.voyageId) + ", " + std::to_string(fishCatch.bankId) + ", '" +
        fishCatch.fishType + "', " + std::to_string(fishCatch.quantityKg) + ", '" +
        fishCatch.quality + "');";
    return executeSQL(db, sql);
}

bool updateCatch(sqlite3* db, int id, const Catch& newData) {
    std::string sql = "UPDATE CATCHES SET VOYAGE_ID = " + std::to_string(newData.voyageId) +
        ", BANK_ID = " + std::to_string(newData.bankId) +
        ", FISH_TYPE = '" + newData.fishType + "'" +
        ", QUANTITY_KG = " + std::to_string(newData.quantityKg) +
        ", QUALITY = '" + newData.quality + "'" +
        " WHERE CATCH_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

bool deleteCatch(sqlite3* db, int id) {
    std::string sql = "DELETE FROM CATCHES WHERE CATCH_ID = " + std::to_string(id) + ";";
    return executeSQL(db, sql);
}

/******************** ФУНКЦИИ ДЛЯ РАБОТЫ С ПРЕМИЯМИ (BONUSES) ********************/

bool calculateBonuses(sqlite3* db,
    const std::string& startDate,
    const std::string& endDate,
    double planAmount,
    double pricePerKg) {
    // 1. Проверка входных параметров
    if (startDate.empty() || endDate.empty() || pricePerKg <= 0) {
        std::cerr << "Invalid input parameters!" << std::endl;
        return false;
    }

    // 2. SQL-запрос для расчета премий
    std::string sql =
        "INSERT INTO BONUSES (CREW_ID, VOYAGE_ID, AMOUNT, PERIOD_START, PERIOD_END) "
        "SELECT c.CREW_ID, v.VOYAGE_ID, "
        "ROUND((SUM(ca.QUANTITY_KG) - ?) * ?, 2) AS BONUS_AMOUNT, "
        "?, ? "
        "FROM CATCHES ca "
        "JOIN VOYAGES v ON ca.VOYAGE_ID = v.VOYYAGE_ID "
        "JOIN CREW_MEMBERS c ON v.TRAWLER_ID = c.TRAWLER_ID "
        "WHERE v.START_DATE BETWEEN ? AND ? "
        "GROUP BY c.CREW_ID, v.VOYAGE_ID "
        "HAVING SUM(ca.QUANTITY_KG) > ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        printError(db);
        return false;
    }

    // 3. Привязка параметров
    sqlite3_bind_double(stmt, 1, planAmount);
    sqlite3_bind_double(stmt, 2, pricePerKg);
    sqlite3_bind_text(stmt, 3, startDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, endDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, startDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, endDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 7, planAmount);

    // 4. Выполнение запроса
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printError(db);
        sqlite3_finalize(stmt);
        return false;
    }

    // 5. Получение количества начисленных премий
    int rowsAffected = sqlite3_changes(db);
    std::cout << "Successfully calculated bonuses for " << rowsAffected << " crew members" << std::endl;

    sqlite3_finalize(stmt);
    return true;
}