#include "Jeu.h"

#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

Jeu::Jeu() : joueur(nullptr), rng(random_device{}()) {}

const ActAction* Jeu::findActById(const string& id) const {
    for (const auto& act : actCatalog) {
        if (act.getId() == id) {
            return &act;
        }
    }
    return nullptr;
}

int Jeu::randomDamage(int hpMax) {
    if (hpMax <= 0) return 0;
    uniform_int_distribution<int> dist(0, hpMax);
    return dist(rng);
}

unique_ptr<Monster> Jeu::cloneMonster(const Monster& m) const {
    if (m.getCategory() == Category::NormalMonster) {
        return make_unique<NormalMonster>(
            m.getName(),
            m.getElement(),
            m.getHpMax(),
            m.getAtk(),
            m.getDef(),
            m.getMercyGoal(),
            m.getActIds()
        );
    }

    if (m.getCategory() == Category::MiniBoss) {
        return make_unique<MiniBoss>(
            m.getName(),
            m.getElement(),
            m.getHpMax(),
            m.getAtk(),
            m.getDef(),
            m.getMercyGoal(),
            m.getActIds()
        );
    }

    return make_unique<Boss>(
        m.getName(),
        m.getElement(),
        m.getHpMax(),
        m.getAtk(),
        m.getDef(),
        m.getMercyGoal(),
        m.getActIds()
    );
}

bool Jeu::chargerInv(const string& file) {
    if (!joueur) return false;

    vector<Item> items = FileLoader::loadItems(file);

    for (const auto& item : items) {
        joueur->addItem(item);
    }

    return true;
}

bool Jeu::chargerMonstre(const string& file) {
    vector<Monster*> monstresBruts = FileLoader::loadMonstres(file);

    listeMonstre.clear();

    for (Monster* m : monstresBruts) {
        listeMonstre.push_back(unique_ptr<Monster>(m));
    }

    return !listeMonstre.empty();
}

bool Jeu::chargerActs(const string& file) {
    actCatalog = FileLoader::loadActs(file);
    return !actCatalog.empty();
}

void Jeu::showInventory() {
    if (!joueur) return;

    cout << "\n=== Inventaire ===\n";
    joueur->getInventaire().showItems();

    if (joueur->getInventaire().isEmpty()) return;

    cout << "Entrer l'index d'un item a utiliser hors combat (-1 pour retour) : ";
    int choix;
    cin >> choix;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (choix == -1) return;

    joueur->useItem(choix);
}

void Jeu::showStats() const {
    if (!joueur) return;
    joueur->showStats();
}

void Jeu::ShowBestiaire() const {
    bestiaire.showBestiary();
}

bool Jeu::checkEnding() const {
    if (!joueur) return false;

    if (!joueur->isAlive()) {
        cout << "\n=== GAME OVER ===\n";
        cout << "Tu as ete vaincu.\n";
        return true;
    }

    if (joueur->getVictories() >= 10) {
        cout << "\n=== FIN DE PARTIE ===\n";

        if (joueur->getTues() > 0 && joueur->getEpargnes() == 0) {
            cout << "Fin Genocidaire : tu as tue tous les monstres vaincus.\n";
        }
        else if (joueur->getEpargnes() > 0 && joueur->getTues() == 0) {
            cout << "Fin Pacifiste : tu as epargne tous les monstres vaincus.\n";
        }
        else {
            cout << "Fin Neutre : tu as parfois tue, parfois epargne.\n";
        }

        return true;
    }

    return false;
}

void Jeu::startbattle() {
    if (!joueur) return;

    if (listeMonstre.empty()) {
        cout << "Aucun monstre disponible.\n";
        return;
    }

    uniform_int_distribution<int> dist(0, static_cast<int>(listeMonstre.size()) - 1);
    int index = dist(rng);

    unique_ptr<Monster> ennemi = cloneMonster(*listeMonstre[index]);

    cout << "\n=== Un combat commence ===\n";
    ennemi->displayStatus();

    while (joueur->isAlive() && ennemi->isAlive()) {
        cout << "\n---------------------------------\n";
        cout << joueur->getName() << " HP: " << joueur->getHp() << "/" << joueur->getHpMax() << "\n";
        cout << ennemi->getName() << " HP: " << ennemi->getHp() << "/" << ennemi->getHpMax()
             << " | Mercy: " << ennemi->getMercy() << "/" << ennemi->getMercyGoal() << "\n";

        cout << "\n1. FIGHT\n2. ACT\n3. ITEM\n4. MERCY\n";
        cout << "Choix : ";

        int choix;
        cin >> choix;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide.\n";
            continue;
        }

        bool combatTermine = false;

        if (choix == 1) {
            int dmg = randomDamage(ennemi->getHpMax());
            dmg = min(dmg, ennemi->getHp());

            cout << "\nTu attaques " << ennemi->getName() << " !\n";

            if (dmg == 0) {
                cout << "L'attaque ne fait aucun degat.\n";
            } else {
                ennemi->takeDamage(dmg);
                cout << "Tu infliges " << dmg << " degats.\n";
            }

            if (!ennemi->isAlive()) {
                cout << ennemi->getName() << " est vaincu.\n";
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
        else if (choix == 2) {
            vector<const ActAction*> actionsDisponibles;

            const vector<string>& ids = ennemi->getActIds();

            if (!ids.empty()) {
                int maxActs = min(static_cast<int>(ids.size()), ennemi->getActCount());

                for (int i = 0; i < maxActs; ++i) {
                    const ActAction* action = findActById(ids[i]);
                    if (action) {
                        actionsDisponibles.push_back(action);
                    }
                }
            }
            else {
                int maxActs = min(static_cast<int>(actCatalog.size()), ennemi->getActCount());

                for (int i = 0; i < maxActs; ++i) {
                    actionsDisponibles.push_back(&actCatalog[i]);
                }
            }

            if (actionsDisponibles.empty()) {
                cout << "Aucune action ACT disponible.\n";
            } else {
                cout << "\nActions ACT disponibles :\n";
                for (int i = 0; i < static_cast<int>(actionsDisponibles.size()); ++i) {
                    cout << i << ". " << actionsDisponibles[i]->getId() << "\n";
                }

                cout << "Choisis une action : ";
                int actChoice;
                cin >> actChoice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choix invalide.\n";
                    continue;
                }

                if (actChoice < 0 || actChoice >= static_cast<int>(actionsDisponibles.size())) {
                    cout << "Choix invalide.\n";
                    continue;
                }

                actionsDisponibles[actChoice]->apply(*ennemi);
                cout << "Mercy actuel : " << ennemi->getMercy()
                     << "/" << ennemi->getMercyGoal() << "\n";
            }
        }
        else if (choix == 3) {
            cout << "\n=== Items ===\n";
            joueur->getInventaire().showItems();

            if (!joueur->getInventaire().isEmpty()) {
                cout << "Choisis l'index d'un item : ";
                int itemIndex;
                cin >> itemIndex;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choix invalide.\n";
                    continue;
                }

                joueur->useItem(itemIndex);
            }
        }
        else if (choix == 4) {
            if (ennemi->peutEtreEpargne()) {
                cout << "\nTu epargnes " << ennemi->getName() << ".\n";
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
                cout << "La mercy est insuffisante pour epargner ce monstre.\n";
            }
        }
        else {
            cout << "Choix invalide.\n";
            continue;
        }

        if (combatTermine) {
            return;
        }

        if (ennemi->isAlive()) {
            int dmg = randomDamage(joueur->getHpMax());
            dmg = min(dmg, joueur->getHp());

            cout << "\n" << ennemi->getName() << " attaque !\n";

            if (dmg == 0) {
                cout << "L'attaque du monstre rate.\n";
            } else {
                joueur->takeDamage(dmg);
                cout << "Tu subis " << dmg << " degats.\n";
            }

            if (!joueur->isAlive()) {
                cout << "Tu as ete vaincu...\n";
                return;
            }
        }
    }
}

void Jeu::mainMenu() {
    if (!joueur) return;

    int choix = 0;

    while (true) {
        if (checkEnding()) return;

        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Bestiaire\n";
        cout << "2. Demarrer un combat\n";
        cout << "3. Statistiques du personnage\n";
        cout << "4. Items\n";
        cout << "5. Quitter\n";
        cout << "Choix : ";

        cin >> choix;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide.\n";
            continue;
        }

        switch (choix) {
        case 1:
            ShowBestiaire();
            break;
        case 2:
            startbattle();
            break;
        case 3:
            showStats();
            break;
        case 4:
            showInventory();
            break;
        case 5:
            cout << "Fin du jeu.\n";
            return;
        default:
            cout << "Choix invalide.\n";
            break;
        }
    }
}

void Jeu::start() {
    string nom;

    cout << "=== ALTERDUNE ===\n";
    cout << "Entre le nom de ton personnage : ";
    getline(cin >> ws, nom);

    joueur = make_unique<Joueur>(nom, 100, 10, 5, Element());

    if (!chargerInv("DataCSV/items.csv")) {
        cout << "Chargement des items echoue.\n";
        return;
    }

    if (!chargerMonstre("DataCSV/monstres.csv")) {
        cout << "Chargement des monstres echoue.\n";
        return;
    }

    if (!chargerActs("DataCSV/act.csv")) {
        cout << "Chargement des actions ACT echoue.\n";
        return;
    }

    cout << "\n=== Resume initial ===\n";
    cout << "Nom : " << joueur->getName() << "\n";
    cout << "HP  : " << joueur->getHp() << "/" << joueur->getHpMax() << "\n";
    cout << "Inventaire :\n";
    joueur->getInventaire().showItems();

    mainMenu();
}