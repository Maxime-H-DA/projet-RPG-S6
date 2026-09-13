# Alterdune

Jeu de rôle en console développé en C++, dans le cadre d'un projet de Programmation Orientée Objet.

L'objectif était de construire un vrai système de combat tour par tour avec une architecture propre derrière (héritage, classes abstraites, polymorphisme), plutôt qu'un script avec des `if` partout.

## Architecture

Player et Monster héritent tous les deux d'Entity, qui porte les attributs de base (nom, HP, attaque, défense) et déclare `attack()` en pure virtuelle. Ni Entity ni Monster ne sont instanciables directement.

Monster est ensuite décliné en 3 catégories, NormalMonster, MiniBoss et Boss, qui héritent de Monster et redéfinissent `attack()` et `getMaxActions()` chacune avec son propre comportement (2, 3 ou 4 actions disponibles, fourchette de dégâts différente).

Les monstres sont stockés dans un `vector<Monster*>`. Quand le GameManager appelle `enemy->attack(player)`, c'est la vtable qui décide quelle version est exécutée : aucun `switch` sur la catégorie dans la logique de combat. Le même appel `attack()` produit donc des résultats radicalement différents selon le vrai type de l'entité.

Chaque dégât est tiré dans une fourchette via un générateur Mersenne Twister (`mt19937`) plutôt que `rand()`, pour une meilleure qualité statistique, avec une seed unique partagée par toutes les entités (`static`). Le tirage est refait à chaque attaque, donc deux combats contre le même ennemi ne se déroulent jamais exactement pareil.

## Combat et progression

Le combat repose sur 4 actions : FIGHT (dégâts), ACT (catalogue de 8 actions textuelles, dont 2 à impact négatif), ITEM (soin) et MERCY (épargner l'ennemi).

Chaque monstre a une jauge `mercyGauge` bornée entre 0 et son `mercyGoal`, MERCY n'est disponible que si la jauge est pleine. Le joueur gagne de l'XP différenciée selon l'ennemi vaincu (+2 / +3 / +5) et monte de niveau automatiquement.

La difficulté progresse dans le temps : les MiniBoss n'apparaissent qu'après 3 combats, les Boss qu'à partir de 7 victoires. La partie se termine sur une des 3 fins possibles (Pacifiste, Neutre, Génocidaire) selon le style de jeu.

## Données

Les monstres et objets sont chargés depuis des fichiers CSV (`monsters.csv`, `items.csv`) avec `ifstream` et `stringstream`, avec gestion des lignes mal formées via `try/catch`. Le fichier fourni contient 45 monstres uniques (26 normaux, 13 mini-boss, 6 boss).

Chaque combat est archivé dans un journal (`history.txt`) via une structure légère `BestiaryEntry`, plutôt qu'en manipulant plusieurs listes parallèles.

## Tests

4 tests unitaires s'exécutent automatiquement au lancement (`runUnitTests`) avant le menu principal : dégâts reçus, système Mercy, level up, et réinitialisation du joueur à un état propre.

## Outils utilisés

C++, STL (`vector`, `map`), `<random>` (Mersenne Twister), `ifstream` / `stringstream`, POO (héritage, classes abstraites, polymorphisme)
