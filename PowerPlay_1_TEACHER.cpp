#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
 
struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};
 
int main()
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> randomHealth(30.0, 5.0);
	std::normal_distribution<double> randomStrength(5.0, 1.0);
 
	Object player;
	player.name = "Mr. Orme";
	player.strength = std::max(1, (int)randomStrength(engine));
	player.health = std::max(1, (int)randomHealth(engine));
 
	std::vector<Object> monsters;
	std::uniform_int_distribution<int> randomNumMonsters(1, 3);
 
	int numMonsters{ std::max(1, randomNumMonsters(engine)) };
 
	for (int i{ 0 }; i < numMonsters; i++)
	{
		monsters.push_back({
			"monster " + std::to_string(i + 1),
			std::max(1, (int)randomStrength(engine)),
			std::max(1, (int)randomHealth(engine))
			});
	}
	
	std::cout << "A monster approaches!!" << std::endl;
	while (player.health> 0 && monsters.size()> 0)
	{
		
		std::cout << player.name << ": " << player.health << std::endl
			<< "  Monsters: " << std::endl;
		for (int i{ 0 }; i < monsters.size(); i++)
		{
			std::cout << "   " << i + 1 << ". " << monsters[i].name << ": " << monsters[i].health << std::endl;
		}
		
		std::cout << "What do you do? (a)ttack (h)eal ";
		char command{ 'x' };
		std::cin >> command;
		switch (command)
		{
		case 'a':
		{
			std::cout << "Which Monster: ";
			int monsterNum{ 0 };
			std::cin >> monsterNum;
			if (monsterNum > 0 && monsterNum <= monsters.size())
			{
				monsters[monsterNum - 1].health -= player.strength;
			}
			break;
		}
		case 'h':
			player.health += player.strength *2 ;
			break;
		default:
			std::cout << "please enter a or h" << std::endl;
			break;
		}
		for (auto monsterIter{ monsters.begin() }; monsterIter != monsters.end(); )
		{
			if (monsterIter->health <= 0)
			{
				monsterIter = monsters.erase(monsterIter);
			}
			else
			{
				monsterIter++;
			}
		}
		std::bernoulli_distribution willAttack(.75);
		for (const auto& monster : monsters)
		{
			if (willAttack(engine))
			{
				std::cout << monster.name << " attacks!" << std::endl;
				player.health -= monster.strength;
			}
			else
			{
				std::cout << monster.name << " twiddles its thumbs" << std::endl;
			}
		}
		
		system("PAUSE");
		system("CLS");
	}
 
	if (player.health <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.health <= 0 && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");
}