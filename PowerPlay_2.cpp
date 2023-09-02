#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

struct Object {
    std::string name;
    int strength;
    int health;
};

// definitions
std::vector<Object> loadMonsters();

// global
std::random_device seed;
std::default_random_engine e(seed());

int main() {
    Object player;
    std::cout << "Enter name: ";
    std:: cin >> player.name;
    std::vector<Object> monsters = loadMonsters();
    while(player.health > 0 && monsters.size() > 0) {
        displayBattle();
        std::cin >> fish;
    }
    return 0;
}

// This function loads the monsters from the passed in file and returns the vector. You’ll need a for loop.
std::vector<Object> loadMonsters() {
    std::ifstream fin;
    fin.open("monsters.txt");
    if(!fin.is_open()) { exit(EXIT_FAILURE); }
    int num;
    fin >> num;
    std::vector<Object> monsters(num);
    for(auto& monster: monsters) {
        fin >> monster.name;
        fin >> monster.health;
        fin >> monster.strength;
    }
    return monsters;
}

// Almost a copy and paste from PP1
void displayBattle() {

}

// Almost a copy and paste from PP1
// monsterAttack();

// // Almost a copy and paste from PP1
// playerAttack();

// // returns damage done using normal distribution and the passed in object’s strength. I also output the object’s name, along with “ deals “ mean: attacker.strength, stdev: 2.0
// attack();

// // takes the defending object and the damage being done. subtracts the damage from the defender’s health. outputs: damage << " damage to " << object.name << "!!!" << std::endl;
// // The code for a fight looks like this for the player attacking a monster:
//  defend(monsters[monsterNum - 1], attack(player));
// defend();

// // uses a normal distribution with median of strength*2 and standard deviation of 3. adds random amount to object’s health.
// heal();
