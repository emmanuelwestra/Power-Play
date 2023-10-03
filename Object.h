#ifndef Object_H
#define Object_H
class Object {
    double AC;
    struct Item;
    enum class Type;
	int strength, health, level;
	std::map<Item::Type, Item> inventory;
    private:
}
#endif