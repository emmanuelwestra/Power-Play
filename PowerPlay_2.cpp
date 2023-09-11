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
void game();
void displayBattle(const Object& player, const std::vector<Object>& monsters);
void monsterAttack(Object& player, const std::vector<Object>& monsters, std::default_random_engine& e);
void playerAttack(const Object& player, std::vector<Object>& monsters, std::default_random_engine& e);
int attack(const Object& attackObject, std::default_random_engine& e);
void defend(Object& player, const int damage);
void heal(Object& player, std::vector<Object>& monsters, std::default_random_engine& e);
void displayEnding(Object& player, std::vector<Object> monsters);

int main() {
    bool repeat = true;
    while(repeat) {
        game();
        std::cout << "\033[2J"; // clear the console (system("CLS") only works on Windows, but this is known to be multi-platform)
        std::cout << "Want to play again? (y/n)" << std::endl;
        std::string choice;
        std::cin >> choice;
        repeat = choice=="y";
    }
    return 0;
}

void game() {
    // random
    std::random_device seed;
    std::default_random_engine e(seed());
    std::normal_distribution<double> randomHealth(30.0, 5.0);
    std::normal_distribution<double> randomStrength(5.0, 1.0);
    std::bernoulli_distribution willAttack(.75); // chance that a monster will attack when healing

    std::cout << "\033[2J"; // clear the console (system("CLS") only works on Windows, but this is known to be multi-platform)

    Object player;
    std::cout << "Enter name: ";
    std:: cin >> player.name;
    player.health = std::max(1, (int)randomHealth(e));
    player.strength = std::max(1, (int)randomStrength(e));
    std::vector<Object> monsters = loadMonsters();

    while(player.health > 0 && monsters.size() > 0) {
        displayBattle(player, monsters);
		char command{' '};
        while(command!= 'a' && command!='h') {
            std::cout << "What do you do? (a)ttack (h)eal ";
            std::cin >> command;
        }
		if(command == 'a'){
            playerAttack(player, monsters, e);
            monsterAttack(player, monsters, e);
        }
        else {
            heal(player, monsters, e);
            defend(player, willAttack(e) ? attack(monsters.at(monsters.size()-1), e) : 0);
        }
    }

    displayEnding(player, monsters);
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
        fin >> monster.strength;
        fin >> monster.health;
    }
    return monsters;
}

// Almost a copy and paste from PP1
void displayBattle(const Object& player, const std::vector<Object>& monsters) {
    std::cout << player.name << ": " << player.health << std::endl;
    std::cout << "Monsters: " << std::endl;
    for (int i{ 0 }; i < monsters.size(); i++){
        std::cout << i + 1 << ". " << monsters[i].name << ": " << monsters[i].health << std::endl;
    }
}

// a monster attacks the player
void monsterAttack(Object& player, const std::vector<Object>& monsters, std::default_random_engine& e) {
    std::bernoulli_distribution willAttack(.50); // the chance has been reduced for fairness
    for (const auto& monster : monsters) { // auto determines type and the & means it is a pointer
        if (willAttack(e)) {
            std::cout << monster.name << " attacks!" << std::endl;
            player.health -= attack(monster, e);
        }
        else {
            std::cout << monster.name << " twiddles its thumbs" << std::endl;
        }
    }
}

// the player attacks a monster
void playerAttack(const Object& player, std::vector<Object>& monsters, std::default_random_engine& e) {
    std::cout << "Which Monster: ";
    int monsterNum{ 0 };
    std::cin >> monsterNum;
    if (monsterNum > 0 && monsterNum <= monsters.size()) {
        monsters.at(monsterNum - 1).health -= attack(player, e);
    }
    if(monsters.at(monsterNum - 1).health<1) {
        monsters.erase(monsters.begin()+monsterNum-1); // the monster is deleted from the monsters list
    }
}

// returns damage done using normal distribution and the passed in object’s strength. I also output the object’s name, along with “ deals “ mean: attacker.strength, stdev: 2.0
int attack(const Object& attackObject, std::default_random_engine& e) {
    std::normal_distribution<double> calc((double)attackObject.strength, 2.0);
    int damage = std::max(1, (int)calc(e));
    std::cout << attackObject.name << " deals " << damage << std::endl;
    return damage;
}

// takes the defending object and the damage being done. subtracts the damage from the defender’s health. outputs: damage << " damage to " << object.name << "!!!" << std::endl;
// The code for a fight looks like this for the player attacking a monster:
//  defend(monsters[monsterNum - 1], attack(player));
void defend(Object& player, const int damage) {
    player.health -= damage;
    std::cout << damage << " damage to " << player.name << "!!!" << std::endl;
}

// // uses a normal distribution with median of strength*2 and standard deviation of 3. adds random amount to object’s health.
void heal(Object& player, std::vector<Object>& monsters, std::default_random_engine& e) {
    std::normal_distribution<double> calc((double)player.strength*2, 3.0);
    int amount = (int)calc(e);
    player.health += std::max(1, amount);
}

void displayEnding(Object& player, std::vector<Object> monsters) {
    if (player.health <= 0)
		std::cout << "You Have Died" << std::endl;
	if (player.health <= 0 && monsters.size() == 0)
		std::cout << "BUT" << std::endl;
	if (monsters.size() == 0)
		std::cout << "You have killed the monsters!!!" << std::endl;
}
