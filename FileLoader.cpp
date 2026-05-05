#include "FileLoader.h"
#include "MonsterTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/*Cette classe sert à charger les différents fichiers csv*/
// Utilitaires 

string FileLoader::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

string FileLoader::toUpper(const string& s) {
    string result = s;
    for (char& c : result) c = toupper(c);
    return result;
}

// Chargement items.csv 
// Format : name,type,value,quantity,element
vector<Item> FileLoader::loadItems(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERREUR] Fichier introuvable : " << path << "\n";
        exit(1);
    }

    vector<Item> items;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty()) continue;
        if (lineNum == 1) continue;  // skip header

        istringstream ss(line);
        string name, type, valueStr, qtyStr, elementStr;

        if (!getline(ss, name,       ',') ||
            !getline(ss, type,       ',') ||
            !getline(ss, valueStr,   ',') ||
            !getline(ss, qtyStr,     ',') ||
            !getline(ss, elementStr, ',')) {
            cerr << "[AVERTISSEMENT] Ligne " << lineNum
                 << " mal formee dans " << path << " (ignoree)\n";
            continue;
        }

        try {
            Element elem(toUpper(trim(elementStr)));
            items.emplace_back(trim(name), toUpper(trim(type)),
                               stoi(trim(valueStr)),
                               stoi(trim(qtyStr)),
                               elem);
        } catch (...) {
            cerr << "[AVERTISSEMENT] Erreur ligne " << lineNum << " (ignoree)\n";
        }
    }
    cout << "[OK] " << items.size() << " items charges.\n";
    return items;
}

// Chargement monstres.csv 
// Format : n°Id,pokemon,type,Categorie,evolution,hp,hpMax,atk,def
vector<Monster*> FileLoader::loadMonstres(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERREUR] Fichier introuvable : " << path << "\n";
        exit(1);
    }

    vector<Monster*> monstres;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty()) continue;
        if (lineNum == 1) continue;  // skip header

        istringstream ss(line);
        string idStr, name, typeStr, catStr, evolution,
               hpStr, hpMaxStr, atkStr, defStr;

        if (!getline(ss, idStr,     ',') ||
            !getline(ss, name,      ',') ||
            !getline(ss, typeStr,   ',') ||
            !getline(ss, catStr,    ',') ||
            !getline(ss, evolution, ',') ||
            !getline(ss, hpStr,     ',') ||
            !getline(ss, hpMaxStr,  ',') ||
            !getline(ss, atkStr,    ',') ||
            !getline(ss, defStr,    ',')) {
            cerr << "[AVERTISSEMENT] Ligne " << lineNum
                 << " mal formee dans " << path << " (ignoree)\n";
            continue;
        }

        try {
            name    = trim(name);
            catStr  = trim(catStr);
            typeStr = toUpper(trim(typeStr));

            int hpMax = stoi(trim(hpMaxStr));
            int atk   = stoi(trim(atkStr));
            int def   = stoi(trim(defStr));

            Element elem(typeStr);

            // actIds vide pour l'instant — sera rempli via act.csv si besoin
            vector<string> actIds;

            Monster* m = nullptr;
            if      (catStr == "1") m = new NormalMonster(name, elem, hpMax, atk, def, 30, actIds);
            else if (catStr == "2") m = new MiniBoss     (name, elem, hpMax, atk, def, 30, actIds);
            else if (catStr == "3") m = new Boss         (name, elem, hpMax, atk, def, 30, actIds);
            else {
                cerr << "[AVERTISSEMENT] Categorie inconnue '"
                     << catStr << "' ligne " << lineNum << " (ignoree)\n";
                continue;
            }
            monstres.push_back(m);
        } catch (...) {
            cerr << "[AVERTISSEMENT] Erreur ligne " << lineNum << " (ignoree)\n";
        }
    }
    cout << "[OK] " << monstres.size() << " monstres charges.\n";
    return monstres;
}

// Chargement act.csv 
// Format : id,text,mercy_impact
vector<ActAction> FileLoader::loadActs(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERREUR] Fichier introuvable : " << path << "\n";
        exit(1);
    }

    vector<ActAction> acts;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty()) continue;
        if (lineNum == 1) continue;  // skip header

        istringstream ss(line);
        string id, text, mercyStr;

        if (!getline(ss, id,       ',') ||
            !getline(ss, text,     ',') ||
            !getline(ss, mercyStr, ',')) {
            cerr << "[AVERTISSEMENT] Ligne " << lineNum
                 << " mal formee dans " << path << " (ignoree)\n";
            continue;
        }

        try {
            acts.emplace_back(toUpper(trim(id)),
                              trim(text),
                              stoi(trim(mercyStr)));
        } catch (...) {
            cerr << "[AVERTISSEMENT] Erreur ligne " << lineNum << " (ignoree)\n";
        }
    }
    cout << "[OK] " << acts.size() << " actions ACT chargees.\n";
    return acts;
}