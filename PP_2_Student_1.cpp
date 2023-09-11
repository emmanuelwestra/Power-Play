#include <iostream>

#include <string>

#include <vector>

#include <random>

#include <algorithm>

#include <fstream>

// sorry but did it on xCode

struct Object

{

    std::string name;

    int strength{ 0 };

    int health{ 0 };

};


// Function to load monsters from a file

std::vector<Object> loadMonsters(const std::string& PP1txt) {

    std::ifstream file(PP1txt);

    if (!file.is_open()) {

        std::cerr << "Unable to open file " << PP1txt << std::endl;

        exit(1);

    }


    int numMonsters;

    file >> numMonsters;

    std::vector<Object> monsters;


    for (int i = 0; i < numMonsters; i++) {

        Object monster;

        file >> monster.name >> monster.strength >> monster.health;

        monsters.push_back(monster);

    }


    file.close();

    return monsters;

}


// Function to display the battle state

void displayBattle(const Object& player, const std::vector<Object>& monsters) {

    std::cout << player.name << ": " << player.health << std::endl

        << "Monsters:" << std::endl;


    for (int i = 0; i < monsters.size(); i++) {

        std::cout << "   " << i + 1 << ". " << monsters[i].name << ": ";

        if (monsters[i].health <= 0)

            std::cout << "<DEAD>" << std::endl;

        else

            std::cout << monsters[i].health << std::endl;

    }

}


// Function to calculate damage using a normal distribution 

int calculateDamage(const Object& attacker) {

    std::random_device seed;

    std::default_random_engine engine(seed());

    std::normal_distribution<double> damageDistribution(attacker.strength, 2.0);

    int damage = std::max(1, (int)(damageDistribution(engine)));

    return damage;

}


// Function for defending against an attack

void defend(Object& defender, int damage) {

    defender.health -= damage;

    std::cout << defender.name << " takes " << damage << " damage!" << std::endl;

}


// Function for monster attack

void monsterAttack(Object& player, const Object& monster) {

    int damage = calculateDamage(monster);

    defend(player, damage);

}


// Function for player's attack

void playerAttack(Object& monster, const Object& player) {

    int damage = calculateDamage(player);

    defend(monster, damage);

}


// Function for healing

void heal(Object& player) {

    std::random_device seed;

    std::default_random_engine engine(seed());

    std::normal_distribution<double> healDistribution(player.strength * 2, 3.0);

    int healAmount = (int)(healDistribution(engine));

    player.health += healAmount;

    std::cout << player.name << " heals for " << healAmount << " points!" << std::endl;

}


int main() {

    std::vector<Object> monsters = loadMonsters("monsters.txt");


    std::random_device seed;

    std::default_random_engine engine(seed());

    std::normal_distribution<double> randomStrength(30.0,5.0);

    std::normal_distribution<double> randomHealth(5.0,1.0);

    // Initialize player

    Object player

    {

        "Mr. Orme",

        std::max(1, (int)(randomStrength(engine))),

        std::max(1, (int)(randomHealth(engine)))

    };


    std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;


    bool allDead{ false };

    while (player.health > 0 && !allDead) {

        displayBattle(player, monsters);


        std::cout << "What do you do? (a)ttack (h)eal ";

        char command;

        std::cin >> command;


        switch (command) {

        case 'a': {

            std::cout << "Which Monster: ";

            int monsterNum;

            std::cin >> monsterNum;


            if (monsterNum > 0 && monsterNum <= monsters.size() && monsters[monsterNum - 1].health > 0) {

                playerAttack(monsters[monsterNum - 1], player);

            }

            break;

        }

        case 'h':

            heal(player);

            break;

        default:

            std::cout << "Please enter 'a' or 'h'" << std::endl;

            break;

        }


        allDead = true;

        for (const auto& monster : monsters) {

            if (monster.health > 0) {

                allDead = false;

                monsterAttack(player, monster);

            }

        }


        system("PAUSE");

        system("CLS");

    }


    if (player.health <= 0) {

        std::cout << "You Have Died" << std::endl;

    }

    if (player.health <= 0 && allDead) {
3
        std::cout << "BUT" << std::endl;

    }

    if (allDead) {

        std::cout << "You have killed the monsters!!!" << std::endl;

    }

    system("PAUSE");


    return 0;

}

