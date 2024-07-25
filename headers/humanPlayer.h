class Potion;
class Item;
class Gold;

class HumanPlayer {
    public:
    int gold;
    Potion* potionEffect; 
    void pickUp(Item& i);
    void getGoldValue(Gold& g);
    void notifyAdjacent();
    
};