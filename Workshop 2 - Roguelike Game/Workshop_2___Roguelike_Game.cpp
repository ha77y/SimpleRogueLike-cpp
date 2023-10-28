#include <iostream>
#include <iomanip>
#include <utility>
#include <memory.h>

using namespace std;
//Starting values for player
const struct PlayerInitStats {
    int StartHealth = 50;
    int BaseDamage = 10;
};
const struct StartCoords {
    int x = 5;
    int y = 5;
};
//MapStats
const int mapWidth = 12;

class Tile
{
public:
    char identifier;

    Tile();
    ~Tile();
    /*
    Tile& operator =(Tile& Owner) {
        identifier = Owner.identifier;

        return *this;
    }
    */
};

Tile::Tile() {
    identifier = '-';
}

Tile::~Tile()
{

    cout << " Tile Distroyed"<< endl;
}

class Wall : public Tile {
public:
    Wall() : Tile() {
        this->identifier = 'x';
    }
};

class Gold : public Tile
{
public:
    int value;
    Gold(int _goldValue) :  Tile()
    {
        this->identifier = 'o';
        this->value = _goldValue;
    }
    ~Gold() {
        cout << "Gold Distroyed" << endl;
    }
};

class weapon : public Tile
{
public:
    int Damage;
    weapon(int _damage) : Tile()
    {
        identifier = '/';
        this->Damage = _damage;
    }
    weapon() : Tile()
    {
        
        identifier = '/';
        this->Damage = 0;
    }
    ~weapon() 
    {
        cout << "WeaponTile Distroyed"<< endl;

    }
};
class Enemy : Tile {
private: 
    int health;
    int damage;
public:
    void DamageEnemy(int damage) {
        health -= damage;
    }
    Enemy() {
        Tile::Tile();
        srand(time(NULL));
        // random number in range n to n+4 where n is outside the brackets 
        health =( rand() % 4)+2; //2 to 6
        damage =( rand()% 5)+1;  // 1 to 6
    }
    ~Enemy() {
        cout << "Destroyed Enemy object";
    };
};


class Player : public Tile
{
public:
    int health;// = PlayerInitStats().StartHealth;
    int damage;
    weapon usedWeapon;
    int Xpos;
    int Ypos;
    Player(weapon _weapon) : Tile()
    {
        identifier = 'Q';
        this->health = PlayerInitStats().StartHealth;
        this->usedWeapon = std::move(_weapon);
        this->damage = PlayerInitStats().BaseDamage;
        this->Xpos = StartCoords().x;
        this->Ypos = StartCoords().y;

        cout << this->health << endl;
        
    }
    ~Player() {
        cout << "PlayerTile Distroyed"<<endl;
    }
    void setWeapon(weapon newWeapon)
    {
        this->usedWeapon = std::move(newWeapon);
    }
    void changeX(int direction) {
        if (Xpos + direction < mapWidth-1 && Xpos + direction > 0) {
            Xpos += direction;
            
        }
        else {
            cout << "cannot move past this wall"<<endl;
        }
    }
    void changeY(int direction) {
        if (Ypos + direction < mapWidth-1 && Ypos + direction > 0) {
            Ypos += direction;
        }
        else {
            cout << "cannot move past this wall" << endl;
        }
    }

};


//create map
Tile *map[mapWidth][mapWidth];


void PrintMap() {
    
    for (int i = 0; i < mapWidth ; i++) {
        for (int j = 0; j < mapWidth; j++) {
            cout << map[i][j]->identifier;
        }
        cout<<endl;
    }
}

void EndProcedure() {
    
    for (int i = 0; i < mapWidth ; i++) {
        for (int j = 0; j < mapWidth; j++) {
            map[i][j]->~Tile();
        }
    }

    cout << endl;


}

void InitMap() {
    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            map[i][j] = (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) ? new Wall() : new Tile();
        }
    }
}
void initEnemy() {
    srand(time(NULL));
    
    int posx, posy;
    posx = rand()%(mapWidth-2) +1;
    posy = rand()&(mapWidth-2) +1;
    cout << posx << "   " << posy << endl;

    if (map[posx][posy]->identifier == Tile().identifier) {
        //map[posx][posy] = new Enemy();
        //Shit not working
    }
}

/// <summary>
/// 
/// 
/// 
/// </summary>

int main(int argc, char* argv[])
{
    InitMap();
    initEnemy();

    //Our Playable Character
    Player* player = new Player(weapon(5));
    //place player on the map
    map[player->Xpos][player->Ypos] = player;
    

    char input;
    //Runtime
    while (player->health>=0)
    {
        PrintMap();
        cout << endl;
        //GetplayerInput
        //seekg(0) will only give us the first inputted value and no others will be queued
        cout << "What Direction (w,a,s,d)"; cin.seekg(0) >> input;
        int changedx, changedy;
        switch (input) {
        case 'w': 
                player->changeY(-1);
            break;
        case 's':
                player->changeY(1);
            break;
        case 'd':
                player->changeX(1);
            break;
        case 'a':
                player->changeX(-1);
            break;
        default:
            cout << "invalid selection"<< endl;
        }
        map[player->Ypos][player->Xpos] = player;
        system("cls");
    }

    // end of game 
    EndProcedure();
    return 0;
}




