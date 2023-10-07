#include <iostream>
#include <utility>
#include <memory.h>

using namespace std ;





class Tile
{
public:
    string Type;
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
    free(&identifier);
    free(&Type);

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
    ~weapon() 
    {
        Tile::~Tile();
        free(&Damage);

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


/// <summary>
/// 
/// 
/// 
/// </summary>

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
    
    

    //return 0;
}



void EndProcedure() {

    delete map;

    cout << endl;

    
}