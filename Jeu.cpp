#include "Jeu.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstdlib>

using namespace std;

/*Classe principale qui gère toute la logique du jeu*/

Jeu::Jeu() : joueur(nullptr), rng(random_device{}()) {}

/*Recherche une action ACT par son id*/
const ActAction* Jeu::findActById(const string& id) const {
    for (const auto& act : actCatalog) {
        if (act.getId() == id) return &act;
    }
    return nullptr;
}

/*Génère des dégâts aléatoires*/
int Jeu::randomDamage(int maxValue) {
    if (maxValue <= 0) return 0;
    uniform_int_distribution<int> dist(0, maxValue);
    return dist(rng);
}

/*Clone un monstre*/
unique_ptr<Monster> Jeu::cloneMonster(const Monster& m) const {

    if (m.getCategory() == Category::NormalMonster)
        return make_unique<NormalMonster>(m.getName(), m.getElement(),
            m.getHpMax(), m.getAtk(), m.getDef(),
            m.getMercyGoal(), m.getActIds());

    if (m.getCategory() == Category::MiniBoss)
        return make_unique<MiniBoss>(m.getName(), m.getElement(),
            m.getHpMax(), m.getAtk(), m.getDef(),
            m.getMercyGoal(), m.getActIds());

    return make_unique<Boss>(m.getName(), m.getElement(),
        m.getHpMax(), m.getAtk(), m.getDef(),
        m.getMercyGoal(), m.getActIds());
}

/*Charge inventaire*/
bool Jeu::chargerInv(const string& file) {
    if (!joueur) return false;

    vector<Item> items = FileLoader::loadItems(file);
    for (const auto& item : items) joueur->addItem(item);

    return true;
}

/*Charge monstres*/
bool Jeu::chargerMonstre(const string& file) {
    vector<Monster*> monstresBruts = FileLoader::loadMonstres(file);

    listeMonstre.clear();

    for (Monster* m : monstresBruts)
        listeMonstre.push_back(unique_ptr<Monster>(m));

    return !listeMonstre.empty();
}

/*Charge ACT*/
bool Jeu::chargerActs(const string& file) {
    actCatalog = FileLoader::loadActs(file);
    return !actCatalog.empty();
}

/*Inventaire*/
void Jeu::showInventory() {
    if (!joueur) return;

    cout << "\n========== INVENTAIRE ==========\n";
    joueur->getInventaire().showItems();

    if (joueur->getInventaire().isEmpty()) return;

    cout << "Choisis un item (-1 pour retour) : ";
    int choix;
    cin >> choix;

    if (choix != -1)
        joueur->useItem(choix);
}

/*Stats*/
void Jeu::showStats() const {
    if (joueur) joueur->showStats();
}

/*Bestiaire*/
void Jeu::ShowBestiaire() const {
    bestiaire.showBestiary();
}

/*Fin de partie*/
bool Jeu::checkEnding() const {

    if (!joueur) return false;

    if (!joueur->isAlive()) {
        cout << "\n=== GAME OVER ===\n";
        return true;
    }

    if (joueur->getVictories() >= 3) {  

        cout << "\n=== FIN DU JEU ===\n";

        if (joueur->getTues() > 0 && joueur->getEpargnes() == 0) {
            cout << "Fin Genocidaire : tu as tue tous les monstres.\n";
        }
        else if (joueur->getEpargnes() > 0 && joueur->getTues() == 0) {
            cout << "Fin Pacifiste : tu as epargne tous les monstres.\n";
        }
        else {
            cout << "Fin Neutre : tu as parfois tue, parfois epargne.\n";
        }

        return true;
    }

    return false;
}

/*Combat*/
void Jeu::startbattle() {

    if (!joueur || listeMonstre.empty()) return;

    uniform_int_distribution<int> dist(0, listeMonstre.size() - 1);
    int index = dist(rng);

    unique_ptr<Monster> ennemi = cloneMonster(*listeMonstre[index]);

    cout << "\n=================================\n";
    cout << "Un combat commence !\n";
    cout << "=================================\n";

    while (joueur->isAlive() && ennemi->isAlive()) {

        cout << "\n---------------------------------\n";

        cout << joueur->getName() << " | HP: "
             << joueur->getHp() << "/" << joueur->getHpMax() << "\n\n";

        cout << "Adversaire : " << ennemi->getName() << "\n";
        cout << "Type       : " << ennemi->getElement().getName() << "\n";
        cout << "Categorie  : " << CategoryToString(ennemi->getCategory()) << "\n";
        cout << "HP         : " << ennemi->getHp() << "/" << ennemi->getHpMax() << "\n";
        cout << "Mercy      : " << ennemi->getMercy() << "/" << ennemi->getMercyGoal() << "\n";

        cout << "\n=== Que veux-tu faire ? ===\n";
        cout << "1. FIGHT  - Attaquer\n";
        cout << "2. ACT    - Interagir\n";
        cout << "3. ITEM   - Utiliser un objet\n";
        cout << "4. MERCY  - Epargner\n";
        cout << "Ton choix : ";

        int choix;
        cin >> choix;

        bool combatTermine = false;

        // FIGHT
        if (choix == 1) {

            int dmg = randomDamage(ennemi->getHpMax());
            // Appliquer le boost ATK si l'element du boost est efficace contre le monstre
            if (joueur->getHasActiveBoost() && joueur->getBoostType() == "ATK_BOOST") {
                Element boostElem(joueur->getBoostElement());
                float mult = boostElem.getMultiplier(ennemi->getElement());
                if (mult > 1.0f) {
                    dmg = static_cast<int>(dmg * joueur->getBoostValue() * mult);
                    cout << "[BOOST ATK | " << joueur->getBoostElement()
                         << " efficace contre " << ennemi->getElement().getName()
                         << " x" << mult << "] Degats amplifies !\n";
                }
            }
            dmg = min(dmg, ennemi->getHp());

            if (dmg == 0)
                cout << "Ton attaque rate... Aucun degat.\n";
            else
                cout << "Tu infliges " << dmg << " degats a "
                     << ennemi->getName() << " !\n";

            ennemi->takeDamage(dmg);

            if (!ennemi->isAlive()) {

                cout << ennemi->getName() << " est vaincu !\n";

                joueur->addVictoire();
                joueur->addTue();

                bestiaire.addEntry(BestiaryEntree(
                    ennemi->getName(),
                    ennemi->getCategory(),
                    ennemi->getElement(),
                    ennemi->getHpMax(),
                    ennemi->getAtk(),
                    ennemi->getDef(),
                    false
                ));

                combatTermine = true;
            }
        }

        // ACT
        else if (choix == 2) {

            int nbActs = ennemi->getActCount();
            vector<const ActAction*> choixActs;

            vector<int> indices;
            for (int i = 0; i < actCatalog.size(); i++)
                indices.push_back(i);

            shuffle(indices.begin(), indices.end(), rng);

            for (int i = 0; i < nbActs; i++)
                choixActs.push_back(&actCatalog[indices[i]]);

            cout << "\nActions disponibles :\n";

            for (int i = 0; i < choixActs.size(); i++) {
                cout << i << ". "
                     << choixActs[i]->getId()
                     << " (Mercy " << choixActs[i]->getMercyImpact() << ")\n";
            }

            cout << "Choix : ";
            int c;
            cin >> c;

            if (c >= 0 && c < choixActs.size())
                choixActs[c]->apply(*ennemi);
        }

        // ITEM
        else if (choix == 3) {

            cout << "\n=== Items ===\n";
            joueur->getInventaire().showItems();

            cout << "Choix : ";
            int i;
            cin >> i;

            joueur->useItem(i);
        }

        // MERCY
        else if (choix == 4) {

            if (ennemi->peutEtreEpargne()) {

                cout << "Tu epargnes " << ennemi->getName()
                     << ". Le combat se termine sans violence.\n";

                joueur->addVictoire();
                joueur->addEpargne();

                bestiaire.addEntry(BestiaryEntree(
                    ennemi->getName(),
                    ennemi->getCategory(),
                    ennemi->getElement(),
                    ennemi->getHpMax(),
                    ennemi->getAtk(),
                    ennemi->getDef(),
                    true
                ));

                combatTermine = true;
            } else {
                cout << "Impossible d'epargner ce monstre pour l'instant.\n";
            }
        }

        if (combatTermine) return;

        // TOUR MONSTRE
        if (ennemi->isAlive()) {

            int dmg = randomDamage(ennemi->getAtk());
            // Appliquer le boost DEF si le monstre est du meme type que le bouclier
            if (joueur->getHasActiveBoost() && joueur->getBoostType() == "DEF_BOOST"
                && joueur->getBoostElement() == ennemi->getElement().getName()) {
                dmg = static_cast<int>(dmg / joueur->getBoostValue());
                cout << "[BOUCLIER DEF | Protection contre "
                     << joueur->getBoostElement() << "] Degats reduits !\n";
            }
            dmg = min(dmg, joueur->getHp());

            if (dmg == 0)
                cout << ennemi->getName() << " rate son attaque.\n";
            else
                cout << ennemi->getName()
                     << " t'inflige " << dmg << " degats !\n";

            joueur->takeDamage(dmg);

            if (!joueur->isAlive()) {
                cout << "Tu es tombe au combat...\n";
                return;
            }
        }
    }
}

/*Menu principal*/
void Jeu::mainMenu() {

    int choix;

    while (true) {

        if (checkEnding()) return;

        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Bestiaire\n";
        cout << "2. Demarrer un combat\n";
        cout << "3. Statistiques du joueur\n";
        cout << "4. Inventaire\n";
        cout << "5. Consulter faiblesses\n";
        cout << "6. Quitter\n";
        cout << "====================================\n";
        cout << "Ton choix : ";

        cin >> choix;

        if (choix == 1) ShowBestiaire();
        else if (choix == 2) startbattle();
        else if (choix == 3) showStats();
        else if (choix == 4) showInventory();
        else if (choix == 5) consulterFaiblesses();
        else if (choix == 6) return;
    }
}

/*Ouvre l'image des faiblesses*/
void Jeu::consulterFaiblesses() const {
    system("start \"\" \"pokemon-resistance-and-weaknesses.png\"");
}

/*Lancement*/
void Jeu::start() {

    string nom;

    cout << "=== ALTERDUNE ===\n";
    cout << "Nom du joueur : ";
    getline(cin >> ws, nom);

    joueur = make_unique<Joueur>(nom, 1000, 10, 5, Element());

    chargerInv("DataCSV/items.csv");
    chargerMonstre("DataCSV/monstres.csv");
    chargerActs("DataCSV/act.csv");

    mainMenu();
}