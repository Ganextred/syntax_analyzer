//
// Created by User on 12.11.2023.
//

#ifndef SYNTAX_ANALYZER_CONTROLTABLE_H
#define SYNTAX_ANALYZER_CONTROLTABLE_H


#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class ControlTable {
public:
    const map<char, vector<string>> inputGrammar = {
            {'S', {"BA"}},
            {'A', {"+BA", "e"}},
            {'B', {"DC"}},
            {'C', {"*DC", "e"}},
            {'D', {"(S)", "a"}}
    };

    static bool isNotTerminal(char c) {
        return (c >= 'A' && c <= 'Z');
    }

    bool isEpsilon(char c) {
        return isNotTerminal(c) &&
        (c == 'A' ||  c == 'C');
    }

    map<char, set<char>> findFirst1(const map<char, vector<string>> &grammar) {
        map<char, set<char>> first1;
        bool changesFlag = true;
        while (changesFlag) {
            changesFlag = false;
            // ітерація по символам
            for (const auto &it: grammar) {
                char key = it.first;
                const vector<string> &values = it.second;
                // ітерація по правилам для певного символа
                for (string value: values) {
                    // ітерація по символам, поки попередні - епсілон
                    int i = 0;
                    char currentC;
                    do {
                        currentC = value[i];
                        if (!isNotTerminal(currentC)) {
                            changesFlag = first1[key].insert(currentC).second;
                        } else {
                            for (char c: first1[currentC])
                                if (c != 'e'){
                                    changesFlag = first1[key].insert(c).second;
                                }
                        }
                        i++;
                    } while (isEpsilon(currentC));
                }
            }
        }
        cout<<"f";
        return first1;
    }


};


#endif //SYNTAX_ANALYZER_CONTROLTABLE_H
