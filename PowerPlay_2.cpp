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

// function prototypes
std::vector<Object> loadMonsters();
void displayBattle(Object player, std::vector<Object> monsters);
void monsterAttack(Object player, std::vector<Object> monsters);
void playerAttack(Object player, std::vector<Object> monsters);
void attack(Object player, std::vector<Object> monsters);
void defend(Object player, std::vector<Object> monsters);
void heal(Object player, std::vector<Object> monsters);

// global
std::random_device seed;
std::default_random_engine e(seed());

int main() {
    Object player;
    std::cout << "Enter name: ";
    std:: cin >> player.name;
    std::vector<Object> monsters = loadMonsters();
    while(player.health > 0 && monsters.size() > 0) {
        displayBattle(player, monsters);
		char command{' '};
        while(command!= 'a' && command!='h') {
            std::cout << "What do you do? (a)ttack (h)eal ";
            std::cin >> command;
        }
		if(command == 'a')
            monsterAttack(player, monsters);
        else
            defend();
        attack();
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
void displayBattle(Object player, std::vector<Object> monsters) {
    std::cout << player.name << ": " << player.health << std::endl;
    std::cout << "Monsters: " << std::endl;
    for (int i{ 0 }; i < monsters.size(); i++){
        std::cout << i + 1 << ". " << monsters[i].name << ": " << monsters[i].health << std::endl;
    }
}

// Almost a copy and paste from PP1
void monsterAttack(Object player, std::vector<Object> monsters) {
    std::cout << "Which Monster: ";
    int monsterNum{ 0 };
    std::cin >> monsterNum;
    if (monsterNum > 0 && monsterNum <= monsters.size())
    {
        monsters[monsterNum - 1].health -= player.strength;
    }
}

// // Almost a copy and paste from PP1
void playerAttack(Object player, std::vector<Object> monsters) {

}

// // returns damage done using normal distribution and the passed in object’s strength. I also output the object’s name, along with “ deals “ mean: attacker.strength, stdev: 2.0
void attack(Object player, std::vector<Object> monsters) {

}

// // takes the defending object and the damage being done. subtracts the damage from the defender’s health. outputs: damage << " damage to " << object.name << "!!!" << std::endl;
// // The code for a fight looks like this for the player attacking a monster:
//  defend(monsters[monsterNum - 1], attack(player));
void defend(Object player, std::vector<Object> monsters) {

}

// // uses a normal distribution with median of strength*2 and standard deviation of 3. adds random amount to object’s health.
void heal(Object player, std::vector<Object> monsters) {

}
