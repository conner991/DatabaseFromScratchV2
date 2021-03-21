/* -----------------------------------------------------------------------------
FILE NAME:         
DESCRIPTION:       
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     02-21-2021         1.0  Original version
----------------------------------------------------------------------------- */
#include "Table.h"



#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])


// structs
struct Database
{
     bool inUse = false;
     std::string dbName;
     std::vector<Table> tables;
};



// Prototypes
bool inputParser(std::string inputLine, std::vector<std::string> &wordVector, bool &running);
void wordDecider(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector, int &dbCount);
void createDB(std::string dbName, std::vector<Database> &databases, int &dbCount);
void deleteDB(std::string name, std::vector<Database> &databases, int &dbCount);
void useDB(std::string name, std::vector<Database> &databases, int &dbCount);
void createTable(std::string name, std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void dropTable(std::string name, std::vector<Database> &databaseVector);
void displayTable(std::string name, std::vector<Database> &databaseVector);
void addAttribute(std::string table, std::string attName, std::string dt, std::vector<Database> &databaseVector);
/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{

     std::fstream file;


     bool running = true; 
     int dbCount = 0;
     std::string inputLine;
     std::vector<std::string> wordVector;
     std::vector<Database> databaseVector;

     // Enter SQL Mode
     while (running) {
          std::cout << "--> ";
          std::getline(std::cin, inputLine);

          // Parse our input string into vector of word strings
          running = inputParser(inputLine, wordVector, running);

          // If .exit was not entered, move forward in program
          if (wordVector.size() != 0) {
               wordDecider(wordVector, databaseVector, dbCount);
          }
          
          // clear vector of input strings after each SQL command
          wordVector.clear();
     }


     std::cout << "All done.\n\n";     
     

     // Remove an empty directory
     //int removed = rmdir("test");



}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
bool inputParser(std::string input, std::vector<std::string> &wordVector, bool &running)
{    
     std::string word, string2, string3;
     int spacePosition, numOfSpaces = 0, numOfWords; 


     // Make any letters in input string lowercase
     std::transform(input.begin(), input.end(), input.begin(), ::tolower);
     
     // Check to make sure there is a semicolon at the end of the statement
     if (input.back() == ';' || input == ".exit") {
          
          // Find the number of spaces in the input
          for(int i = 0; i < input.length(); i++) {
               if (input.at(i) == ' ')
               ++numOfSpaces;
          }
     
     
          // If there are multiple words in the input
          if (numOfSpaces != 0) {
          
               numOfWords = numOfSpaces + 1;
               
               for (int i = 0; i < numOfWords; i++) {
                    
                    // Finds the first space in a string and gives us its position number
                    spacePosition = input.find(' ', 1);

                    // Creates a string out of the first part of the input
                    word.assign(input, 0, spacePosition);
                    
                    // Adds word to the string vector
                    wordVector.push_back(word);

                    // Need to modify input string to capture the rest of the input words
                    input.erase(0, spacePosition + 1);
               }
           
          }


          
          // There is only one word in the input and it should be .EXIT
          else {

               // Add single string to vector
               wordVector.push_back(input);

               if (wordVector[0] == ".exit") {
                    wordVector.clear();
                    running = false;
                    return running;
               }

               else {
                    wordVector.clear();
                    std::cout << "Unknow Entry\n";
               }

          
          }



          
     }

     else {
          std::cout << "Input statement must end with a semicolon.\n";
     }
          

     


     return running;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void wordDecider(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector, int &dbCount) 
{    
     int oldSize, newSize;
     char frontOfString;
     



     // Make all letters in vector of string words lowercase
     for (int i = 0; i < wordVector.size(); i++){
          std::transform(wordVector[i].begin(), wordVector[i].end(), wordVector[i].begin(), ::tolower);
     }



     // Check first word in vector to see if it is one of the beginning SQL keywords
     if (wordVector[0] == "create" || wordVector[0] == "drop" || wordVector[0] == "use" || wordVector[0] == "select" || wordVector[0] == "alter") {
          
          // CREATE DATABASE or TABLE
          if (wordVector[0] == "create") {
               
               // then we're either gonna create a DATABASE or a TABLE (one of those SQL keywords will follow)
               
               // CREATE DATABASE
               if (wordVector[1] == "database") {

                    // Theres going to be a ";" at the end of our database name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);
                    
                    // Call createDB function to create DB
                    std::string dbName1 = wordVector[2];
                    createDB(dbName1, databaseVector, dbCount);

               }

               // CREATE TABLE
               else if (wordVector[1] == "table") {

                    // Check if there is a "(" following tbl_x
                    frontOfString = wordVector[3].front();
                    if (frontOfString == '(') {
                         
                         // Create tbl_x out of wordVector[2]
                         createTable(wordVector[2], wordVector, databaseVector);
                         
                    }

                    else {
                         std::cout << "parenthetical expression must follow table creation statement\n";
                    }

                    
               }

               else {
                    std::cout << "DATABASE or TABLE must follow CREATE\n";
               }
          }


          // DROP DATABASE or TABLE
          if (wordVector[0] == "drop"){
               
               // Same as "CREATE" except we're either gonna drop a created database or a table

               // DROP DATABASE
               if (wordVector[1] == "database") {
                    
                    // Theres going to be a ";" at the end of our database name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);

                    // Call deleteDB function to delete wordVector[2] database name
                    deleteDB(wordVector[2], databaseVector, dbCount);
                    
               }

               // DROP TABLE
               else if (wordVector[1] == "table") {
                    
                    // Theres going to be a ";" at the end of our table name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);
                    
                    // Now delete wordVector[2] table
                    dropTable(wordVector[2], databaseVector);
               
               }

               else {
                    std::cout << "DATABASE or TABLE must follow DROP.\n";
               }
          }


          // USE DATABASE
          if (wordVector[0] == "use") {
     
               // Next word after "USE" is a database name 
               // Theres going to be a ";" at the end of our database name that we need to get rid of
               oldSize = wordVector[1].size();
               newSize = oldSize - 1;
               wordVector[1].resize(newSize);

               // USE our database wordVector[1] and check to see if we are already using it if this happens again
               useDB(wordVector[1], databaseVector, dbCount);
               

               
          }


          // SELECT 
          if (wordVector[0] == "select") {
 
               // SELECT is always going to be followed by an action performed on a table
               
               // Next word after SELECT should be an *
               if (wordVector[1] == "*") {

                    // Here we're going to SELECT all of the attributes from our table

                    // Using FROM after *
                    if (wordVector[2] == "from") {

                         // Theres going to be a ";" at the end of our table name that we need to get rid of
                         oldSize = wordVector[3].size();
                         newSize = oldSize - 1;
                         wordVector[3].resize(newSize);
                    
                         // Call displayTable function
                         displayTable(wordVector[3], databaseVector);

                    }

                    else {
                         std::cout << "FROM must follow *\n";
                    }
               }
          
               else {
                    std::cout << wordVector[1] << " doesn't work with SELECT\n";
               }
               
          }


          // ALTER TABLE
          if (wordVector[0] == "alter"){
               
               // Next word after "alter" is only ever going to be a SQL table keyword and that must be a created table
               if (wordVector[1] == "table") {

                    // ALTER is only ever going to work with a created table
                    
                    if (wordVector[3] == "add") {

                         // Theres going to be a ";" at the end of our datatype name that we need to get rid of
                         oldSize = wordVector[5].size();
                         newSize = oldSize - 1;
                         wordVector[5].resize(newSize);
                         
                         // attribute name (wordVector[4]) and datatype (wordVector[5] with a semicolon) are entered here
                         // add attribute to tbl_x here
                         addAttribute(wordVector[2], wordVector[4], wordVector[5], databaseVector);

                    }

                    
               }

               else {
                    std::cout << "Must be TABLE keyword\n";
               }
               
          }
     }

     else {
          std::cout << "Unknown Entry\n";
     }
     

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void createDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{    
     bool inVector = false;
     struct Database db;

     // If there are more than 1 database entrys in our vector
     if (dbCount > 1) {

          for (int i = 0; i < databaseVector.size(); i++) {
                
                if (databaseVector[i].dbName == name) {
                     std::cout << "!Failed to create database " << name << " because it already exists.\n";
                     inVector = true;
                }
          }

          if (!inVector) { 
               // Now create a database with name by creating a directory in our project
               const char* dbName = name.c_str();
                    
               if (mkdir(dbName, 0777) == -1) {
                    std::cout << "Error creating Database.\n";
               }

               else {

                    // Add name of database to vector
                    db.dbName = name;
                    databaseVector.push_back(db);
                    std::cout << "Database " << name << " created.\n";
               }

               dbCount++;
          }

     }

     else if (dbCount == 1) {    

          if (databaseVector.front().dbName == name) {
               std::cout << "!Failed to create database " << name << " because it already exists.\n";
          }

          else {

               // Now create a database with name by creating a directory in our project
               const char* dbName = name.c_str();
                    
               if (mkdir(dbName, 0777) == -1) {
                    std::cout << "Error creating Database\n";
               }

               else {

                    // Add name of database to vector
                    db.dbName = name;
                    databaseVector.push_back(db);
                    std::cout << "Database " << name << " created.\n";
               }

               dbCount++;
          }
     }

     // Our database vector is empty 
     else {
          // Now create a database with name by creating a directory in our project
          const char* dbName = name.c_str();
                    
          if (mkdir(dbName, 0777) == -1) {
               std::cout << "Error creating Database\n";
          }

          else {

               // Add name of database to vector
               db.dbName = name;
               databaseVector.push_back(db);
               std::cout << "Database " << name << " created.\n";
          }

          dbCount++;
     }

     
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void deleteDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{         
     std::string tempName1, tempName2, s;
     struct Database tempDB;

     // If we have more than 1 database string in our vector
     if (dbCount > 1) {
          
          // Delete database, removes the corresponding directory string from the vector
          // by searching for it   
          for (auto i = databaseVector.begin(); i != databaseVector.end(); i++) {
               
               // Extract DB name string so we can compare it
               tempDB = *i;
               s = tempDB.dbName;
               
               if (s == name) {
                    
                    tempName1 = name;
                    databaseVector.erase(i);

                    // Delete database directory from project directory
                    std::string removalString = "rm -r " + tempName1;
                    system(removalString.c_str());
                    std::cout << "Database " << tempName1 << " deleted.\n";

                    dbCount--;     

                    break; 
              
               }
               
          }
     }

     
     // if dbCount is equal to 1
     else {
          
          if (databaseVector.front().dbName == name) {
               
               // Delete database directory from project directory
               databaseVector.clear();
               std::string removalString = "rm -r " + name;
               system(removalString.c_str());
               std::cout << "Database " << name << " deleted.\n";

               dbCount--;
          }

          else {
               std::cout << "!Failed to delete database " << name << " because it does not exist.\n";
          }
          
     }

     // else we are trying to delete an entry from an empty vector.  
     if (dbCount == 0) {
          std::cout << "!Failed to delete database " << name << " because it does not exist.\n";
     }
     
         
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void useDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{
     bool inVector = false;


     // If there are more than 1 database entrys in our vector
     if (dbCount > 1) {
     
          for (int i = 0; i < databaseVector.size(); i++) {

               // Set all database inUse booleans to false, to reset so we can swtich between them
               databaseVector[i].inUse = false;

               if (databaseVector[i].dbName == name && databaseVector[i].inUse == false) {
                    
                    std::cout << "Using database " << name << ".\n";
                    databaseVector[i].inUse = true;
                    inVector = true;
               }
               
               else if (databaseVector[i].dbName == name && databaseVector[i].inUse == true) {
                    std::cout << "!Already using database " << name << ".\n";
                    inVector = true;
               }
               

          }

          if (!inVector) {
               std::cout << "!Database " << name << " has not been created.\n";
          }


     }

     else if (dbCount == 1) {    

          if (databaseVector.front().dbName == name && databaseVector.front().inUse == false) {
               
               std::cout << "Using database " << name << ".\n";
               databaseVector.front().inUse = true;
          }

          else if (databaseVector.front().dbName == name && databaseVector.front().inUse == true) {
               std::cout << "!Already using database " << name << ".\n";
          }

          else {

               std::cout << "!Database " << name << " has not been created.\n";      
          }
     }

     // Our database vector is empty 
     else {
          std::cout << "!Database " << name << " has not been created.\n";
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void createTable(std::string tableName, std::vector<std::string> &wordVector, std::vector<Database> &databaseVector) 
{    
     int count = 0, tableExpressionSize, oldSize, newSize;
     std::string attName, attDT;
     bool used = false;
     bool inDB = false;

     // Create Attribute objects to use
     Attribute att1, att2;

     // Check for a database thats in use
     for (int i = 0; i < databaseVector.size(); i++) {
          
          if (databaseVector[i].inUse == true) {

               used = true;

               // check to make sure the table hasn't been created already
               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {
                         inDB = true;
                         std::cout << "!Failed to create table " << tableName << " because it already exists.\n";
                    }
               }

               if (!inDB) {
                    
                    // Create a table for this database by creating a table object and naming it
                    Table newTable(tableName);
               

                    // go through wordVector of strings and create attributes
                    for (int j = 0; j < wordVector.size(); j++) {

                         // Catch the first attribute in the parenthetical expression
                         if (wordVector[j].front() == '(') {
                         
                              // Need to get rid of the ( at the beginning of first attribute name
                              wordVector[j].erase(0, 1);

                              // Store in attName
                              attName = wordVector[j];

                              // Now get attribute datatype, have to take off the , at the end
                              oldSize = wordVector[j + 1].size();
                             newSize = oldSize - 1;
                              wordVector[j + 1].resize(newSize);

                              // Store in attDT
                              attDT = wordVector[j + 1];

                              // Add attribute name and datatype to Attribute object
                              att1.createAttribute(attName, attDT);

                              // Now add attribute object to the Table attribute object vector
                              newTable.addAttribute(att1);

                         }

                         // To capture other attributes in the expression
                         else if (wordVector[j].front() == 'a') {
                         
                              // Store new attribute in attName          
                              attName = wordVector[j];

                              // Get attribute datatype, either this datatype ends with a ","
                              if (wordVector[j + 1].back() == ',') {
                              
                                   oldSize = wordVector[j + 1].size();
                                   newSize = oldSize - 1;
                                   wordVector[j + 1].resize(newSize);

                                   // Store in attDT
                                   attDT = wordVector[j + 1];

                              }

                              // Or it ends with a ");"
                              else {

                                   oldSize = wordVector[j + 1].size();
                                   newSize = oldSize - 2;
                                   wordVector[j + 1].resize(newSize);

                                   // Store in attDT
                                   attDT = wordVector[j + 1];

                              }

                              // Add attribute name and datatype to Attribute object
                              att2.createAttribute(attName, attDT);

                              // Now add attribute object to the Table attribute object vector
                              newTable.addAttribute(att2);

                         }

                         // else if (wordVector[j].front() != 'a' && wordVector[j].front() != '(') {
                         //      std::cout << "Didn't recognize attribute name\n";
                         // }

                    }

                    // Add table with new attributes to the Database struct tables vector
                    databaseVector[i].tables.push_back(newTable);
                    std::cout << "Table " << tableName << " created.\n";
               }

               
          }

     }

     if (!used) {
               
          // Must be using a database in order to create a table 
          std::cout << "Failed to create table because there is no database in use.\n";
     }
     
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void dropTable(std::string tableName, std::vector<Database> &databaseVector) 
{    
     bool used = false;
     bool inDB = false;

     // Check for database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               Table tempTable;
               std::string tempName;

               for (auto it = databaseVector[i].tables.begin(); it != databaseVector[i].tables.end(); it++) {
                    
                    tempTable = *it;
                    tempName = tempTable.getTableName();

                    if (tempName == tableName) {
                         
                         databaseVector[i].tables.erase(it);
                         inDB = true;
                         std::cout << "Table " << tableName << " deleted.\n";

                         break;

                    }
               }

               

               if (!inDB) {
                    std::cout << "!Failed to delete " << tableName << " because it does not exist.\n";
               }

          }
     }

     if (!used) {
               
          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void displayTable(std::string tableName, std::vector<Database> &databaseVector)
{    
     bool used = false;
     bool inDB = false;
     int tableCount = 0;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {
                         
                         databaseVector[i].tables[j].displayAttributes();
                         inDB = true;
                         
                    }
               }

               if (!inDB) {
                    
                    std::cout << "!Failed to query table " << tableName << " because it does not exist.\n";
               }
          } 
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
     
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void addAttribute(std::string tableName, std::string attName, std::string attDT, std::vector<Database> &databaseVector) 
{
     bool used = false;
     bool inDB = false;
     int tableCount = 0;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {

                         // Create attribute to add to the table
                         Attribute att1;
                         att1.createAttribute(attName, attDT);
                         
                         databaseVector[i].tables[j].addAttribute(att1);
                         inDB = true;
                         std::cout << "Table " << tableName << " modified.\n";
                         
                    }
               }

               if (!inDB) {
                    
                    std::cout << "!Failed to modify table " << tableName << " because it does not exist.\n";
               }
          } 
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
}

