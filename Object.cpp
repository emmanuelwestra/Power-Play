class Object {
    public:
        enum class Type { player, slime, orc, sprite, dragon, numTypes };
        Type name;
        int strength;
        int health;
        int level;
        std::map<Item::Type, Item> inventory;

        Object() {
            strength = 0;
            health = 0;
            level = 0;
        }
    private:
        
}