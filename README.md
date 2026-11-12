# ALTERDUNE

A turn-based console RPG written in C++17, built for the Object-Oriented Programming course (A3, ESILV). It mixes Undertale's FIGHT / ACT / ITEM / MERCY combat with Pokémon monsters, elemental types and evolutions.

## Features

- Turn-based combat with four actions: **FIGHT**, **ACT**, **ITEM**, **MERCY**
- Elemental type system with strengths and weaknesses (see [`docs/type-chart.png`](docs/type-chart.png))
- Bestiary of monsters, inventory, and player stats
- Three endings depending on your choices: Genocide, Pacifist, Neutral
- Monsters, items and actions loaded from CSV files in [`DataCSV/`](DataCSV)

## Build and run

Requires a C++17 compiler (g++ or clang++) and `make`.

```bash
make
./alterdune
```

Run from the repository root, since the game reads `DataCSV/*.csv` with relative paths. Use `make clean` to remove build output.

## Project structure

| Area | Classes |
| --- | --- |
| Game loop | `Jeu`, `Main` |
| Entities | `Entity`, `Joueur`, `Monster`, `MonsterTypes` |
| Combat data | `Element`, `Category`, `ActAction` |
| Items | `Item`, `Inventaire` |
| Bestiary | `Bestiaire`, `BestiaryEntree` |
| Data loading | `FileLoader` |

The class diagram is in [`docs/UML.svg`](docs/UML.svg) ([PNG](docs/uml.png)).

## Authors

Luca Perkins and Benchimol — ESILV, 2026.
