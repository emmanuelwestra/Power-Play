#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <random>


class Object
{
public:
	static std::random_device seed;
	static std::default_random_engine engine;
	enum class Type { player, slime, orc, sprite, dragon, numTypes };

	Object() {}
	Object(Type name, int strength, int health, int level);
	virtual int attack() const = 0;
	virtual void defend(int damage) = 0;
	virtual void update(Player& player, std::vector<Monster>& monsters) = 0;
	virtual void print(std::ostream& o) const;

	bool isDead();
	Type getName() const;
	int getLevel() const;
	int getHealth() const;

protected:
	Type name{ Type::numTypes };
	int strength{ 0 };
	int health{ 0 };
	int level{ 0 };

	int damageDone(int modification) const;
	int damageTaken(int damageDone, int AC);
};

std::ostream& operator<< (std::ostream& o, const Object& src);
#endif // !OBJECT_H

