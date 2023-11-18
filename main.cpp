
#include <iostream>
#include "ControlTable.h"


int main() {
    ControlTable ct;
    auto first1 = ct.findFirst1();
    auto follow1 = ct.findFollow1();
    auto table = ct.create_table();

    for (const auto &entry : first1) {
        std::cout << "Key: " << entry.first << ", Values: ";

        // Print the set associated with the key
        for (const auto &value : entry.second) {

            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
    cout<<"Follow1:"<<endl;
    for (const auto &entry : follow1) {
        std::cout << "Key: " << entry.first << ", Values: ";

        // Print the set associated with the key
        for (const auto &value : entry.second) {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }

    cout<<"table"<<endl;
    for (const auto& entry : table) {
        std::cout << "Key: " << entry.first.first << ", Value: (" << entry.first.second << "->" << ct.grammar.at(entry.first.second)[entry.second] << ")\n";
    }

    ct.analyzeInput("(a+a)*a!");

    return 0;
}
