# Глоссарий

## Таблицы базы данных 

### TRAWLER
   - id - уникальный айди для определения вхождения в таблицу;
   - name - имя траулера;
   - displacement - объем траулера;
   - buildDate - дата постройки;
### BANK
   - id - уникальный айди;
   - name - имя банки;
### CREW MEMBER
   - id - уникальный айди;
   - lastName - фамилия члена экипажа;
   - position - позиция члена экипажа; (crew, fisherman, captain)
   - hireDate - дата наема на работу;
   - birthYear - год рождения;
   - trawlerID - указатель на айди траулера, за которым закреплён член экипажа;
### VOYAGE
   - id - уникальный айди;
   - trawlerID - указатель на айди; ;траулера, который на этом задании;
   - startDate - дата начала задания;
   - endDate - дата окончания;
### CATCH
   - id - уникальный айди;
   - voyageID - указатель на айди задания;
   - bankID - указатель на айди банки, где был взят улов;
   - fishType - вид рыбы;
   - quantityKg - количество в килограммах;
   - quality - качество (low, medium, high);
### STATISTICS
   - trawlerID - указатель на айди траулера, которого статистика;
   - totalCatch - количество всей выловленной рыбы в килограммах.

## Функции

- sqlite3* initializeDatabase(const std::string& dbPath) - подключение базы данных по заданному пути;
- bool addX(sqlite3* db, const X& x) - добавление вхождения в таблицу Х;
- bool updateX(sqlite3* db, int id, const X& newData) - обновление вхождения (ищется по айди) в таблице Х;
- bool deleteX(sqlite3* db, int id) - удаление вхождения (ищется по айди) в таблице Х;
- bool calculateBonuses(sqlite3* db, const std::string& startDate, const std::string& endDate, double planAmount, double pricePerKg) - функция для расчета премий;
- bool calculateBonusForCrewMember(sqlite3* db, int crewId, const std::string& startDate, const std::string& endDate, double planAmount, double pricePerKg) - функция расчета премий конкретному члену экипажа;
- std::vector<Bank> getAllBanks(sqlite3* db) - функция получения всех банков в таблице;
- Bank getBankById(sqlite3* db, int bankId) - функция получения банки по ее айди;
- void printError(sqlite3* db) - функция вывода ошибки при работе с БД;
- std::vector<Trawler> getAllTrawlers(sqlite3* db) - функция получения всех траулеров в таблице;
- std::vector<CrewMember> getCrewForTrawler(sqlite3* db, int trawlerId) - функция нахождения всех членов экипажа, приписанных к траулеру.