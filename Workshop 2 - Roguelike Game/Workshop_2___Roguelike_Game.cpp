#include <iostream>
#include <utility>

using namespace std ;



class Tile
{
public:
    string Type;
    int value{};
    char identifier{};

    Tile(string _type);
    Tile();
    ~Tile();
};

Tile::Tile(string _type)
{
    this->Type = std::move(_type);
    identifier = '-';
}
Tile::Tile() {
    identifier = '-';
}

Tile::~Tile()
{
    cout << " Destructor called";
}

class Wall : public Tile {
public:
    Wall() : Tile("Wall") {
        this->identifier = 'x';
    }
};

class Gold : public Tile
{
public:
    Gold(int _goldValue) :  Tile("Gold")
    {
        identifier = 'o';
    }
};

class weapon : public Tile
{
public:
    int Damage;
    weapon(int _damage) : Tile("Weapon")
    {
        identifier = '/';
        this->Damage = _damage;
    }
    weapon() : Tile("Empty Weapon")
    {
        
        identifier = '/';
        this->Damage = 0;
    }
};

const struct PlayerInitStats {
    int StartHealth = 50;
    int BaseDamage = 10;
};

class Player : public Tile
{
public:
    int health = PlayerInitStats().StartHealth;
    int damage;
    weapon usedWeapon;
    Player(weapon _weapon) : Tile("Player")
    {
        identifier = 'Q';
        //this->health = PlayerInitStats().StartHealth;
        this->usedWeapon = std::move(_weapon);
        this->damage = PlayerInitStats().BaseDamage;

        cout << this->health << endl;
        
    }
    void setWeapon(weapon newWeapon)
    {
        this->usedWeapon = std::move(newWeapon);
    }
};

const int mapWidth = 12;
const struct StartCoords {
    int x = 5;
    int y = 5;
};


Tile* map[mapWidth][mapWidth] = {};


void PrintMap() {

}



int main(int argc, char* argv[])
{
    for(int i = 0 ; i< mapWidth ; i++)
    {
        for(int j = 0 ; j<mapWidth ; j++)
        {
            map[i][j] = (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) ? new Wall() : new Tile();

            cout<<  map[i][j]->identifier;
            // cout<< "Test"<< endl;
        }
        cout<< endl;
    }
    Player* PlayerPointer = new Player(weapon(5));

    map[StartCoords().x][StartCoords().y] = PlayerPointer;
    
/*
    for(int i = 0 ; i<= 8 ; i++)
        {
            for(int j = 0 ; j<=8 ; j++)
            {
                delete &map[i][j];
            }
            cout<< endl;
        }
*/
    

    //return 0;
}
