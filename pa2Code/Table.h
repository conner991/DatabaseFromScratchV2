/* -----------------------------------------------------------------------------
FILE NAME:         
DESCRIPTION:       
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     **-**-2020         1.0  Original version
----------------------------------------------------------------------------- */
#ifndef __TABLE_H__
#define __TABLE_H__

#include "Attribute.h"


class Table : public Attribute {
     private:
          std::string tableName;
          int numOfAttributes;
          std::vector<Attribute> attributes; 

     public:

          Table() {};
          ~Table() {};

          Table(std::string name) {
               tableName = name;
          }

          void addAttribute(Attribute a) {
               attributes.push_back(a);
          }

          int getNumOfAttributes() {
               
               numOfAttributes = attributes.size();
               
               return numOfAttributes;
          }

          std::string getAttribute(std::string attName) {

               // Cycle through vector of attributes
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {
                         return attributes[i].getName();
                    }

                    else {
                         std::cout << "Attribute not found.\n";
                    }
               }
          }

          void removeAttribute(Attribute a) {
               
               Attribute tempAtt;
               std::string tempName;

               for (auto it = attributes.begin(); it != attributes.end(); it++) {
                    
                    tempAtt = *it;
                    tempName = tempAtt.getName();

                    if (tempName == a.getName()) {
                         attributes.erase(it);
                    }
               }
          }

          void displayTableName() {
               std::cout << "Table name is: " << tableName << "\n";
          }

          void displayAttributes() {

               for (int i = 0; i < attributes.size(); i++) {
                    
                    attributes[i].displayAttribute();
                    std::cout << " | ";
               }

               std::cout << "\n";
               
          }

          void displayAttributesAndValues() {

               // Print out attributes
               for (int i = 0; i < attributes.size(); i++) {
                    
                    attributes[i].displayAttribute();
                    std::cout << " | ";
               }

               std::cout << "\n";

               for (int j = 0; j < attributes[j].getNumOfValues(); j++) {

                    // Print out related values 
                    for (int k = 0; k < attributes.size(); k++) {

                         attributes[k].displayValue(j);
                    }

                    std::cout << "\n";
               }
               
          }

          std::string getTableName() {
               return tableName;
          }

          void clearTable() {
               attributes.clear();
          }

          void addValues(std::vector<std::string> valVector) {

               // Here we add each value in valVector to it's corresponding attribute object
               // using the addValue method in the Attribute class
               for (int i = 0; i < attributes.size(); i++) {
                    attributes[i].addValue(valVector[i]);
               }

          }

          std::string getAttValue(std::string attName, std::string val) {

               // search for passed in value in attributes vector object
               // Cycle through vector of attributes
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {
                         
                         // search for specific value within the attribute object
                         for (int j = 0; j < attributes[i].getNumOfValues(); j++) {

                              if (val == attributes[i].getValue(val)) {
                                   
                                   return attributes[i].getValue(val);
                              }
                         }

                         
                    }

               }

          }




          // friend std::ostream& operator << (std::ostream &stream, Table &table) {
          

          //      for (int i = 0; i < table.attributes.size(); i++) {
                    
          //           stream << table.attributes[i].displayAttribute();
          //      }
          // }

          

};










#endif
