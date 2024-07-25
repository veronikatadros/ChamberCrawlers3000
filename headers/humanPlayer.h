class Potion;
class Item;
class Gold;

class HumanPlayer {
    private:
        HumanPlayer();
    public:
        static HumanPlayer& getInstance();
        
        int gold;
        Potion* potionEffect; 
        void pickUp(Item& i);
        void getGoldValue(Gold& g);
        void notifyAdjacent();
};