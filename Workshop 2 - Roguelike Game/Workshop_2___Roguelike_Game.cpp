#include <iostream>
#include <utility>

using namespace std ;



class Tile
{
public:
    string Type;
    int value{};
    char identifier{};

    Tile(string _type , int _value);
    Tile() = default;
    ~Tile();
};

Tile::Tile(string _type, int _value)
{
    this->Type = std::move(_type);
    this->value = _value;
    identifier = '-';
}

Tile::~Tile()
{
    cout << " Destructor called";
}

class Gold : public Tile
{
public:
    Gold(int _goldValue) :  Tile("Gold",_goldValue)
    {
        identifier = 'o';
    }
};

class weapon : public Tile
{
public:
    int Damage;
    weapon(int _damage) : Tile("Weapon",0)
    {
        identifier = '/';
        this->Damage = _damage;
    }
    weapon() : Tile("Empty Weapon",0)
    {
        identifier = '/';
    }
};

class player : public Tile
{
public:
    int health;
    weapon usedWeapon;
    player(int _health, int _damage, weapon _weapon) : Tile("Player",0)
    {
        identifier = 'x';
        this->health = _health;
        this->usedWeapon = std::move(_weapon);
        
    }
    void setWeapon(weapon newWeapon)
    {
        this->usedWeapon = std::move(newWeapon);
    }
};
Tile map[8][8] = {Tile(0,0)}; 

int main(int argc, char* argv[])
{
    for(int i = 0 ; i<= 8 ; i++)
    {
        for(int j = 0 ; j<=8 ; j++)
        {
            cout<< map[i][j].identifier ;
        }
        cout<< endl;
    }

    for(int i = 0 ; i<= 8 ; i++)
    {
        for(int j = 0 ; j<=8 ; j++)
        {
            delete &map[i][j];
        }
        cout<< endl;
    }

    //return 0;
}
