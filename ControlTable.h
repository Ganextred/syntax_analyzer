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
//    const map<char, vector<string>> grammar = {
//            {'S', {"BA"}},
//            {'A', {"+BA", "e"}},
//            {'B', {"DC"}},
//            {'C', {"*DC", "e"}},
//            {'D', {"(S)", "a"}}
//    };
//
    const map<char, vector<string>> grammar = {
            {'S', {"i+D","(S*R)", "e"}},
            {'D', {"V*S", "L!S"}},
            {'R', {"V!S", "L*S"}},
            {'V', {"Z", "n"}},
            {'L', {"(S)", "Z"}},
            {'Z', {"e"}}
    };

    static bool isNotTerminal(char c) {
        return (c >= 'A' && c <= 'Z');
    }

//    bool isEpsilon(char c) {
//        return isNotTerminal(c) &&
//        (c == 'A' ||  c == 'C');
//    }
    bool isEpsilon(char c) {
        return isNotTerminal(c)
        && first1[c].count('e') > 0;
    }

//        bool isEpsilon(char c) {
//        return isNotTerminal(c) &&
//               (c == 'S' || c == 'Z' || c == 'L' || c == 'V');
//    }
    map<char, set<char>> first1;

    map<char, set<char>> findFirst1() {
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
                    if (value == "Z")
                        cout<<"";
                    do {
                        currentC = value[i];
                        if (!isNotTerminal(currentC)) {
                            if (currentC == 0)
                                cout<<"here1";
                            changesFlag |= first1[key].insert(currentC).second;
                        } else {
                            for (char c: first1[currentC]) {
                                if (c == 0)
                                    cout<<"here2";
                                if(c != 'e')
                                    changesFlag |= first1[key].insert(c).second;
                                }
                        }
                        i++;
                    } while (isEpsilon(currentC) && i<value.size());
                    if (isEpsilon(value[i-1]) && i == value.size()){
                        changesFlag |= first1[key].insert('e').second;
                    }
                }
            }
        }
        return first1;
    }
    map<char, set<char>> follow1;

    map<char, set<char>> findFollow1() {
        follow1['S'].insert('e');
        bool changesFlag = true;
        while (changesFlag) {
            changesFlag = false;
            // ітерація по символам в алфавіті, це символ який ми оновлюємо
            for (const auto &itToUpdate: grammar) {
                char cToUpdate = itToUpdate.first;
                // ітерація по символам в алфавіті
                for (const auto &it: grammar) {
                    char key = it.first;
                    const vector<string> &values = it.second;
                    // ітерація по правилам для певного символа
                    for (string value: values) {
                        // ітерація по символамв пошуках символу який зараз обробляємо
                        for (int i = 0; i < value.size(); i++) {
                            if (value[i] == cToUpdate) {// знайшли символ який зараз обновляємо справа
                                if (i == value.size() - 1) {
                                    for (char c: follow1[key])
                                        changesFlag |= follow1[cToUpdate].insert(c).second;
                                } else {
                                    int j = i+1;
                                    do{
                                        if (!isNotTerminal(value[j]))
                                            changesFlag |= follow1[cToUpdate].insert(value[j]).second;
                                        else{
                                            for (char c: first1[value[j]])
                                                if (c != 'e')
                                                    changesFlag |= follow1[cToUpdate].insert(c).second;
                                        }
                                        j++;
                                    }while (isEpsilon(value[j-1]) && j<value.size());
                                    if (isEpsilon(value[j-1]) && j == value.size()){
                                        for (char c: follow1[key])
                                            changesFlag |= follow1[cToUpdate].insert(c).second;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return follow1;
    };

};


#endif //SYNTAX_ANALYZER_CONTROLTABLE_H
