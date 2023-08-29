#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>

std::random_device seed;
std::default_random_engine e(seed()); // Use the seed to initialize the random engine
std::normal_distribution<double> health(30.0, 5.0); // normal distribution with mean of 30 and stdev of 5
std::normal_distribution<double> strength(5.0, 1.0); // normal distribution with mean of 5 and stdev of 1
std::uniform_real_distribution<double> normal(0.0, 3.0); // uniform distribution from 0-3 (real numbers)
std::bernoulli_distribution bernoulli(0.75); // probability of true = 75%

struct Object {
    std::string name;
    int strength;
    int health;
};

Object createObject() {
    Object object;
    object.strength = 0;
    while(object.strength < 1) {
        object.strength = static_cast<int>(strength(e));
    }
    object.health = 0;
    while(object.health < 1) {
        object.health = static_cast<int>(health(e));
    }
    return object;
}

void display(std::vector<Object>& monsters, Object& player) {
    std::cout << player.name << " health: " << player.health << "; strength: " << player.strength << std::endl;
    for(Object monster: monsters) {
        std::cout << monster.name << " health: " << monster.health << "; strength: " << monster.strength << std::endl;
    }
}

void attack_player(Object& monster, Object& player) {
    if(bernoulli(e)) { // whether to attack
        if(monster.health > 0) { // monster is still alive so it attacks
            player.health -= monster.strength;
            std::cout << monster.strength << " damage received!" << std::endl;
        }
    }
}

void attack_enemy(std::vector<Object>& monsters, Object& player) {
    int choice = 0;
    while(choice<1 || choice>monsters.size()) {
        std::cout << "Choose monster to attack [1-" << monsters.size() <<  "]: ";
        std::cin >> choice;
    }
    attack_player(monsters.at(choice-1), player);
    monsters.at(choice-1).health -= player.strength;
    if(monsters.at(choice-1).health < 0){ monsters.at(choice-1).health = 0; } // reassign to 0 if health is negative
    if(monsters.at(choice-1).health == 0) { monsters.at(choice-1).name = "<DEAD>"; }
}

void heal(std::vector<Object>& monsters, Object& player) {
    player.health += player.strength*2;
}

void play(std::vector<Object>& monsters, Object& player) {
    display(monsters, player);
    int choice = 0;
    while(choice!=1 && choice!= 2) {
        std::cout << "Choose an action [1=attack, 2=heal]: ";
        std::cin >> choice;
    }
    (choice==1) ? attack_enemy(monsters, player) : heal(monsters, player);
}

int main() {
    Object player = createObject();
    player.name = "Dragon";

    std::vector<Object> monsters;
    int num = static_cast<int>(normal(e))+1;
    for(int i = 0; i<num; i++) {
        Object monster = createObject();
        monster.name = "Monster " + std::to_string(i+1);
        monsters.push_back(monster);
    }

    bool monsters_dead = false;
    while(player.health > 0 && !monsters_dead) {
        play(monsters, player);
        monsters_dead = true;
        for(Object monster: monsters) {
            if(monster.health != 0)
                monsters_dead = false;
        }
    }

    if(player.health > 0 && monsters_dead) {  // win
       std::cout << "Congratulations " << player.name << "!" << std::endl;
    }
    else if(monsters_dead){
        std::cout << "RIP monsters" << std::endl;
        std::cout << "RIP " << player.name << std::endl;
        std::cout << "Better luck next time!" << std::endl;
    }
    else {
        std:: cout << "Your enemies have defeated you " << player.name << "!" << std::endl;
    }
    return 0;
}