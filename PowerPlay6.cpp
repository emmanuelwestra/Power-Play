#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

class Object;
class Player;
class Monster;
class Item;

std::vector<Monster> createMonsters(const Object& player);
void monsterAttack(Object& player, const std::vector<Monster>& monsters);
void bringOutYourDead(std::vector<Monster>& monsters);
void playerAttack(const Object& player, std::vector<Monster>& monsters);
void levelUp(Object& player);
int calculateAC(const Object& object);
void displayBattle(const Object& player, const std::vector<Monster>& monsters);
void printItem(const Item & item);
int attack(const Object& object);
void defend(Object& object, int damage);
std::random_device seed;
std::default_random_engine engine(seed());

class Item {
	public:
		enum class Type {sword, armor, shield, numTypes};
		Type clasification;
		int bonusValue;
		Item(int bonusValue=0) { // default constructor
			this->bonusValue = bonusValue;
		}
		Item(Type clasification, int bonusValue=0) {
			this->clasification = clasification;
			this->bonusValue = bonusValue;
		}
	friend std::ostream& operator<<(std::ostream& o, const Item& src);
	friend bool operator<(const Item& first, const Item& second);
	friend int operator+=(const Item& src, int val);
};
std::ostream& operator<<(std::ostream& o, const Item& src) {
	o << "Type: " << src.clasification << "; bonusValue: " << src.bonusValue << std::endl;
	return o;
}
bool operator<(const Item& first, const Item& second) {
	return first.bonusValue < second.bonusValue;
}
int operator+=(const Item& src, int val) {
	return src.bonusValue+val;
}
class Object {
    public:
        enum class Type { player, slime, orc, sprite, dragon, numTypes };
        Type name;
        int strength;
        int health;
        int level;
        std::map<Item::Type, Item> inventory;
		Object(Type type, int strength=0, int health=0, int level=0) {
			this->strength = strength;
            this->health = health;
            this->level = level;
			name = type;
		}
		void printName() const {
			std::cout  << "L:" << level  << " ";
			switch (name) {
				case Type::player:
				std::cout  << "Player";
				break;
				case Type::slime:
				std::cout  << "Slime";
				break;
				case Type::orc:
				std::cout  << "Orc";
				break;
				case Type::sprite:
				std::cout  << "Sprite";
				break;
				case Type::dragon:
				std::cout  << "Dragon";
				break;
				}
		}
		friend std::ostream& operator<<(std::ostream&, const Object&);
};
std::ostream& operator<<(std::ostream& o, const Object& src) {
			o<<"Type: " << src.name << "; strength: " << src.strength << "; health: " << src.health << "; level: " << src.level << std::endl;
			return o;
}
class Player : public Object {
	public:
		int spell_points;
		Player(int strength=0, int health=0, int level=0) : Object(Type::player, strength, health, level){
			spell_points = 0;
		}
		void heal() {
			std::normal_distribution<double> randomHeal(strength, 3.0);
			int amountHealed{ std::max(1, (int)randomHeal(engine)) };
			printName();
			std::cout  << " is healed by " << amountHealed  << "hp!" << std::endl;
			health  += amountHealed;
		}
};
class Monster : public Object {
	public:
		int AC;
		Monster(Type type, int strength=0, int health=0, int level=0, int AC=0) : Object(type, strength, health, level){
			this->AC = AC;
		}
};

int main()
{
	Player player(0,1,0);
	std::vector<Monster> monsters;
	while (player.health  > 0)
	{
		levelUp(player);
		monsters  = createMonsters(player);
		std::cout  << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");
		while (player.health  > 0 && monsters.size() > 0)
		{
			displayBattle(player, monsters);
			std::cout  << "What do you do? (a)ttack (h)eal ";
			char command{ 'x' };
			std::cin  >> command;
			switch (command)
			{
				case 'a':
				{
					playerAttack(player, monsters);
					break;
				}
				case 'h' :
					player.heal();
				break;
			default:
				std::cout  << "please enter a or h" << std::endl;
				break;
			}
			bringOutYourDead(monsters);
			monsterAttack(player, monsters);
			system("PAUSE");
			system("CLS");
		}
	}
	if (player.health  <= 0)
	{
		std::cout  << "You Have Died" << std::endl;
	}
	if (player.health  <= 0 && monsters.size() == 0)
	{
		std::cout  << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout  << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");
}
void displayBattle(const Object& player, const std::vector<Monster>& monsters)
{
	player.printName();
	std::cout  << " h:" << player.health  << std::endl;
	std::for_each(player.inventory.begin(), player.inventory.end(), [](const std::pair<Item::Type, Item> item){
		std::cout  << "  ";
		printItem(item.second);
		std::cout  << std::endl;
	});
	std::cout  << std::endl  << "  Monsters: " << std::endl;
	size_t index{0};
	std::for_each(monsters.begin(), monsters.end(), [&index](const auto &monster){
		std::cout  << "   " << index+1 << ". ";
		monster.printName();
		std::cout  << " h:" << monster.health  << std::endl;
		++index;
	});
}
std::vector<Monster> createMonsters(const Object& player)
{
	
	std::normal_distribution<double> randomNumMonsters((double)player.level, player.level  / 2.0);
	int numMonsters{ std::max(1, (int)randomNumMonsters(engine)) };
	std::vector<Monster> monsters(numMonsters);

	std::normal_distribution<double> monsterLevel((float)player.level, player.level  / 4.0);
	std::uniform_int_distribution<int> monsterType(1, (int)Object::Type::numTypes  - 1);

	std::generate(monsters.begin(), monsters.end(), [&monsterLevel, &monsterType](){
		//set level based on player level
		int level{ std::max(1, (int)monsterLevel(engine)) };
		
		Object::Type name{ (Object::Type)monsterType(engine) };
		double strengthVariance{ 0.0 };
		double healthVariance{ 0.0 };
		switch (name)
		{
			case Object::Type::slime:
				strengthVariance  = level  * 1.5;
				healthVariance  = level  * 1.25;
				break;
			case Object::Type::orc:
				strengthVariance  = level  * 2;
				healthVariance  = level  * level  * 1.25;
				break;
			case Object::Type::sprite:
				strengthVariance  = level  * 1.75;
				healthVariance  = level;
				break;
			case Object::Type::dragon:
				strengthVariance  = level  * 6;
				healthVariance  = level  * level  * 3;
				break;
		}
		std::normal_distribution<double> randomStrength(strengthVariance, level  / 4.0);
		std::normal_distribution<double> randomHealth(healthVariance * 5, level  / 2.0);
		return Monster{
				name,
				std::max(1, (int)randomStrength(engine)),
				std::max(1, (int)randomHealth(engine)),
				level,
				{}
			};
	});
	return monsters;
}
void monsterAttack(Object& player, const std::vector<Monster>& monsters)
{
	std::bernoulli_distribution willAttack(.75);
	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&willAttack, &player](const auto & monster){
		if (willAttack(engine))
		{
			monster.printName();
			std::cout << " attacks!" << std::endl;
			defend(player, attack(monster));
		}
		else
		{
			monster.printName();
			std::cout  << " twiddles its thumbs" << std::endl;
		}
	});

}
void playerAttack(const Object& player, std::vector<Monster>& monsters)
{
	std::cout  << "Which Monster: ";
	int monsterNum{ 0 };
	std::cin  >> monsterNum;
	if (monsterNum  > 0 && monsterNum  <= monsters.size())
	{
		defend(monsters[monsterNum  - 1], attack(player));
	}
}
void levelUp(Object& player)
{
	player.level++;

	std::normal_distribution<double> randomHealth(20.0 + player.level  * 5, 5.0);
	player.health  += std::max(1, (int)randomHealth(engine));
	std::normal_distribution<double> randomStrength(3.0 + player.level, 1.0);
	player.strength  += std::max(1, (int)randomStrength(engine));
	
	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes  - 1);
	std::normal_distribution<double> randomBonus((double)player.level, (double)player.level  / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };
	
	std::cout  << "You found a ";
	printItem(found);
	std::cout  << "!!!!" << std::endl;
	
	if (
		auto haveOne{ player.inventory.find(found.clasification) };
	haveOne  == player.inventory.end()
		|| player.inventory[found.clasification].bonusValue  < found.bonusValue
		)
	{
		std::cout  << "You keep the shiny new toy!" << std::endl;
		player.inventory[found.clasification] = found;
	}
	else
	{
	std::cout  << "You toss aside the ugly old thing!" << std::endl;
	}
}
int calculateAC(const Object& object)
{
	int AC{ 0 };
	if (auto armor{ object.inventory.find(Item::Type::armor) }; 
		armor  != object.inventory.end())
	{
		AC  += armor->second.bonusValue;
	}
	if (auto shield{ object.inventory.find(Item::Type::shield) }; 
		shield != object.inventory.end())
	{
		AC  += shield->second.bonusValue;
	}
	return AC;
}
void printItem(const Item& item)
{
	switch (item.clasification)
	{
		case Item::Type::armor:
		std::cout  << "Armor";
		break;
		case Item::Type::shield:
		std::cout  << "Shield";
		break;
		case Item::Type::sword:
		std::cout  << "Sword";
		break;
	}
	std::cout  << "+" << item.bonusValue;
}
int attack(const Object& object)
{
	int potentialDamage{ object.strength  };
	if (auto sword{ object.inventory.find(Item::Type::sword) }; 
		sword  != object.inventory.end())
	{
		potentialDamage  += sword->second.bonusValue;
	}
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);
	object.printName();
	std::cout  << " deals ";
	return std::max(1, (int)damageDealt(engine));
}
void defend(Object& object, int damage)
{
	std::normal_distribution<double> defense(calculateAC(object), 1.0 / object.level);
	damage  = std::max(0, damage - (int)defense(engine));
	std::cout  << damage  << " damage to ";
	object.printName();
	std::cout   << "!!!" << std::endl;
	object.health  -= damage;
}
void bringOutYourDead(std::vector<Monster>& monsters)
{
	std::remove_if(monsters.begin(), monsters.end(), [](const Object &monster){
		if (monster.health  <= 0)
		{
			monster.printName();
			std::cout  << " has died!!!" << std::endl  << std::endl;
			return true; // delete monster
		}
		return false; // keep monster
	});
}