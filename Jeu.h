#pragma once

#include <vector>
#include <string>
#include <memory>
#include <random>

#include "Joueur.h"
#include "MonsterTypes.h"
#include "ActAction.h"
#include "Bestiaire.h"
#include "FileLoader.h"

class Jeu {
private:
    std::unique_ptr<Joueur> joueur;
    std::vector<std::unique_ptr<Monster>> listeMonstre;
    std::vector<ActAction> actCatalog;
    Bestiaire bestiaire;

    std::mt19937 rng;

private:
    const ActAction* findActById(const std::string& id) const;
    int randomDamage(int hpMax);
    std::unique_ptr<Monster> cloneMonster(const Monster& m) const;

public:
    Jeu();

    void start();
    bool chargerInv(const std::string& file);
    bool chargerMonstre(const std::string& file);
    bool chargerActs(const std::string& file);

    void mainMenu();
    void startbattle();
    void showInventory();
    void showStats() const;
    void ShowBestiaire() const;
    bool checkEnding() const;

    
    void consulterFaiblesses() const;
};