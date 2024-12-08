#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
const int resolutionX = 960;
const int resolutionY = 720;
const int boxPixelsX = 48;
const int boxPixelsY = 48;
const int gameRows = resolutionX / boxPixelsX;  // Total rows on grid = 20
const int gameColumns = resolutionY / boxPixelsY;  // Total columns on grid = 15

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// Function Declarations
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void movePlayer(float& player_x, Clock&);
int showStartMenu(RenderWindow& window);
void ammoIncrease(bool& bullet_exists, int& ammo, int& nextCan, int& chance);
int nextPlayer(int& nextCan, Texture& playerTexture, Sprite& playerSprite);


void spawnBee(Sprite bees[], Texture& beeTexture, float beeSpeeds[], float beeDirections[], int& activeBeeCount, Clock& spawnClock, bool beeActive[], float Xposition[] ,int nobees);

void moveBees(Sprite bees[], float beeSpeeds[], float beeDirections[], int& activeBeeCount, Clock& beeClock,Texture& beeTexture,Texture& reverseBee, Clock animationClock, bool& bullet_exists,Sprite& bullet,bool beeActive[],float beeX[],float beeY[], int nobees, Sprite honeycombs[], Texture& honeyTexture, bool honeyActive[], float honeyX[], float honeyY[], int& activeHoneyCount, Sound& hitSound, Sprite redHoneycombs[], bool redHoneyActive[], float redHoneyX[], float redHoneyY[], int activeRedHoneyCount);

bool checkCollision(Sprite& bee, Sprite& bullet, int nobees);
void drawBee(RenderWindow& window,int& activeBeeCount,Sprite bees[],bool beeActive[], int nobees);
//void drawBees(RenderWindow &window, int gameGrid[gameRows][gameColumns], Sprite &beeSprite);


void spawnFastBee(Sprite fastBees[], Texture& fastBeeTexture, float fastBeeSpeeds[], float fastBeeDirections[], int& fastActiveBeeCount, Clock& fastSpawnClock, bool fastBeeActive[],float FastbeeX[], int noFastBees) ;
void moveFastBees(Sprite fastBees[], float fastBeeSpeeds[], float fastBeeDirections[], int& fastActiveBeeCount, Clock& fastBeeClock, Texture& fastBeeTexture, Clock animationClock, bool& bulletExists, Sprite& bullet, bool fastBeeActive[], int noFastBees, Texture& reverseFast ,float FastbeeX[],float FastbeeY[], Sprite honeycombs[], Texture& honeyTexture, bool honeyActive[], float honeyX[], float honeyY[], int& activeHoneyCount,Sprite flowerSprites[], Texture& flowerTexture,bool flowerActive[]) ;
void drawFastBees(RenderWindow& window, Sprite fastBees[], int& fastActiveBeeCount, bool fastBeeActive[], int noFastBees) ;

//           Function for Yellow Honey Comb
void drawHoneycombs(RenderWindow& window, int& activeHoneyCount, Sprite honeycombs[], bool honeyActive[],bool& bulletExists, Sprite& bullet);
// Function to spawn a honeycomb
void spawnHoneycomb(Sprite honeycombs[], Texture& honeyTexture, float honeyX[], float honeyY[], bool honeyActive[], int& activeHoneyCount, float beeX, float beeY);

void moveHoneycombs(Sprite honeycombs[], float honeyX[], float honeyY[],
                    bool honeyActive[], int& activeHoneyCount, float honeySpeed);
                   
                   void drawRedHoneycombs(RenderWindow& window, Sprite redHoneycombs[], bool redHoneyActive[], int activeRedHoneyCount,bool& bulletExists, Sprite& bullet) ;
                   




/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

int main() {
    srand(time(0));

    // Declaring RenderWindow.
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

    // Used to position your window on every launch. Use according to your needs.
    window.setPosition(Vector2i(500, 200));

    // Initializing Background Music.
    Music bgMusic;
    Music l1Music;
    if (!bgMusic.openFromFile("Music/Music3.ogg")) {
        cout << "Error: Could not load music file!" << endl;
    }
    bgMusic.setVolume(20);
    bgMusic.setLoop(true);
    bgMusic.play();
   
    SoundBuffer fire;
    if(!fire.loadFromFile("Sound Effects/fire.wav")){
    cout<<"Error: Could not load fire sound!";
    }
    Sound fireSound;
    fireSound.setBuffer(fire);
    fireSound.setVolume(30);
    fireSound.setLoop(false);
   
    SoundBuffer Hit;
    if(!Hit.loadFromFile("Sound Effects/fire.wav")){
    cout<<"Error: Could not load fire sound!";
    }
    Sound HitSound;
    HitSound.setBuffer(Hit);
    HitSound.setVolume(71);
    HitSound.setLoop(false);
   
   
    Font font;
        if (!font.loadFromFile("Fonts/arial.ttf")) {
            cerr << "Error loading font!" << endl;
            return -1;
        }

    // Show the start menu and get the selected option
    int menuSelection = showStartMenu(window);

    // If the player selects "Quit" or closes the window, end the game
    if (menuSelection == -1) {
        return 0;
    }else if(menuSelection == 0){
    // Initializing Background Music.
   
    if (!bgMusic.openFromFile("Music/level1.ogg")) {
        cout << "Error: Could not load music file!" << endl;
 }
    }
    else if(menuSelection == 1){
    if (!bgMusic.openFromFile("Music/level2.ogg")) {
        cout << "Error: Could not load music file!" << endl;
 }
    }else if(menuSelection == 2){
    if (!bgMusic.openFromFile("Music/risk.ogg")) {
        cout << "Error: Could not load music file!" << endl;
 }
    }
   
    bgMusic.play();
   
   

    // Initializing Player and Player Sprites.
    float player_x = (gameRows / 2) * boxPixelsX;
    float player_y = (gameColumns - 4) * boxPixelsY;

    Texture playerTexture;
    Sprite playerSprite;
    playerTexture.loadFromFile("spray/spray_1.png");
    playerSprite.setTexture(playerTexture);

    Texture playerTexture2;
    Sprite playerSprite2;
    playerTexture2.loadFromFile("spray/spray_1.png");
    playerSprite2.setTexture(playerTexture2);
   
    Sprite playerSprite3;
    playerSprite3.setTexture(playerTexture2);
   
         // Bee ko add karne ka leye
        Texture bee;
        //Sprite beeSprite;
        bee.loadFromFile("Sprites/regular.png");
        /*beeSprite.setTexture(bee);
        beeSprite.setPosition((gameRows / 2) * boxPixelsX, 0);
        beeSprite.setScale(1, 1);*/

    // Initializing Bullet and Bullet Sprites
    // Data for bullet / Spray pellet
    float bullet_x = player_x;
    float bullet_y = player_y;
    bool bullet_exists = false;

    Clock animationClock;
    Clock bulletClock;
    Clock smoothMovement;
    Texture bulletTexture;
    Sprite bulletSprite;
    bulletTexture.loadFromFile("Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(1, 1);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    // The ground on which player moves
    RectangleShape groundRectangle(Vector2f(960, 640));
    groundRectangle.setPosition(0, (gameColumns -2) * boxPixelsY);
    groundRectangle.setFillColor(Color::Green);
   
    playerSprite.setScale(1.5, 1.5); // Scale up player sprite
    bulletSprite.setScale(4, 4);     // Scale remains the same for bullets
    //beeSprite.setScale(1.5, 1.5);  

    // Initialize the score
    int ammo = 56;
    int score = 0;
    int nextCan = 0;
    int chance = 3;
    const int noBees=20;
    // Clock for spawning bees
    Clock beeSpawnClock;
   
    Texture reverseBee;
    reverseBee.loadFromFile("Sprites/reversed.png");
    Sprite bees[noBees];
    float beeSpeeds[noBees] = {0};
    float beeDirections[noBees] = {0};
    int activeBeeCount = 0;
    bool BeeActive[noBees]={true};
    Clock beeClock;
    Clock spawnClock;
    float beeX[noBees];  // X positions of bees
    float beeY[noBees];  // Y positions of bees
    float FastbeeX[noBees];   //X positions of Fast bees
    float FastbeeY[noBees];    //Y positions of Fast bees
   
           Texture FastTexture;
           Sprite Fastbees[noBees];
           FastTexture.loadFromFile("Sprites/fast_bee_sheet.png");
           if (!FastTexture.loadFromFile("Sprites/fast_bee_sheet.png")) {
            cerr << "Error loading " << endl;
            return -1;
        }
        Texture reversedFast;
        if(!reversedFast.loadFromFile("Sprites/reversedFastBees.png")){
        cout<<"Error loading reversed picture of Fast bees"<<endl;
        return 0;
        }
    float FastbeeSpeeds[noBees] = {0};
    float FastDirections[noBees] = {0};
    int FastactiveBeeCount = 0;
    bool FastBeeActive[noBees]={true};
    Clock FastbeeClock;
    Clock FastspawnClock;
    Clock FastanimationClock;
    const int maxHoneycombs=20;
   
    Texture YellowhoneyTexture;
if (!YellowhoneyTexture.loadFromFile("Sprites/reg_honeycomb.png")) {
    cout << "Error: Could not load honeycomb texture!" << endl;
}
           Sprite Yellowhoneycombs[maxHoneycombs];
           float YellowhoneyX[20], YellowhoneyY[20];
           bool YellowhoneyActive[maxHoneycombs] = { false };
           int YellowactiveHoneyCount = 0;
           
           Texture RedhoneyTexture;
if (!RedhoneyTexture.loadFromFile("Sprites/fast_honeycomb.png")) {
    cout << "Error: Could not load honeycomb texture!" << endl;
}
           Sprite Redhoneycombs[maxHoneycombs];
           float RedhoneyX[20], RedhoneyY[20];
           bool RedhoneyActive[maxHoneycombs] = { false };
           int RedactiveHoneyCount = 0;

           Sprite flowerSprites[30];
           bool flowerActive[30] = {false};

           // Load the flower texture
           Texture flowerTexture;
           if (!flowerTexture.loadFromFile("Sprites/obstacles.png")) {
    cout<<"Error Loading flower!";
           }
           //For background of level1 :
           Texture backgroundTexture;
           Sprite backgroundSprite;
           if (!backgroundTexture.loadFromFile("spray/Menu.jpg")) {
              cout << "Error loading background!" << endl;
           }
           backgroundSprite.setTexture(backgroundTexture);
           backgroundSprite.setScale(6.0f,6.0f);


    // Game loop starts here ---------><+++++++++++++++++++++++++++++++++++
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return 0;
            }
        }

        ///////////////////////////////////////////////////////////////
        //                                                           //
        // Call Your Functions Here. Some have been written for you. //
        // Be wary of the order you call them, SFML draws in order.  //
        //                                                           //
        ///////////////////////////////////////////////////////////////
       
           
           window.draw(backgroundSprite);
           

           
        if(menuSelection== 1){
        // Fast bees ko Zinda kar ne ka leye!
spawnFastBee(Fastbees, FastTexture, FastbeeSpeeds, FastDirections, FastactiveBeeCount, FastspawnClock, FastBeeActive,FastbeeX, 5);

moveFastBees(Fastbees, FastbeeSpeeds, FastDirections, FastactiveBeeCount, FastbeeClock, FastTexture, FastanimationClock, bullet_exists, bulletSprite, FastBeeActive, 5,reversedFast, FastbeeX, FastbeeY,Redhoneycombs,RedhoneyTexture,RedhoneyActive,RedhoneyX,RedhoneyY,RedactiveHoneyCount,flowerSprites, flowerTexture,flowerActive);
drawFastBees(window, Fastbees, FastactiveBeeCount, FastBeeActive, 5);

// New regular bees ko pada karne ka leye
       spawnBee(bees, bee, beeSpeeds, beeDirections, activeBeeCount, spawnClock, BeeActive, beeX ,15);
       
        moveBees(bees, beeSpeeds, beeDirections, activeBeeCount, beeClock, bee, reverseBee, animationClock,bullet_exists, bulletSprite, BeeActive, beeX,beeY, 20,Yellowhoneycombs,YellowhoneyTexture,YellowhoneyActive,YellowhoneyX,YellowhoneyY, YellowactiveHoneyCount,HitSound, Redhoneycombs, RedhoneyActive, RedhoneyX,RedhoneyY, RedactiveHoneyCount);
        
drawBee(window, activeBeeCount, bees, BeeActive, 15);
}else if(menuSelection == 0){
// New bees ko pada karne ka leye
       spawnBee(bees, bee, beeSpeeds, beeDirections, activeBeeCount, spawnClock, BeeActive, beeX ,20);
        // Bees ko move kar wane ka leye
          moveBees(bees, beeSpeeds, beeDirections, activeBeeCount, beeClock, bee, reverseBee, animationClock,bullet_exists, bulletSprite, BeeActive, beeX,beeY, 20,Yellowhoneycombs,YellowhoneyTexture,YellowhoneyActive,YellowhoneyX,YellowhoneyY, YellowactiveHoneyCount,HitSound, Redhoneycombs, RedhoneyActive, RedhoneyX,RedhoneyY, RedactiveHoneyCount);
        //normal bees ko banane ka leye
drawBee(window, activeBeeCount, bees, BeeActive, 20);

}else if(menuSelection == 2){
// Fast bees ko Zinda kar ne ka leye!
spawnFastBee(Fastbees, FastTexture, FastbeeSpeeds, FastDirections, FastactiveBeeCount, FastspawnClock, FastBeeActive,FastbeeX, 10);

moveFastBees(Fastbees, FastbeeSpeeds, FastDirections, FastactiveBeeCount, FastbeeClock, FastTexture, FastanimationClock, bullet_exists, bulletSprite, FastBeeActive, 5,reversedFast, FastbeeX, FastbeeY,Redhoneycombs,RedhoneyTexture,RedhoneyActive,RedhoneyX,RedhoneyY,RedactiveHoneyCount,flowerSprites, flowerTexture,flowerActive); ///////////////)
drawFastBees(window, Fastbees, FastactiveBeeCount, FastBeeActive, 10);

// New regular bees ko pada karne ka leye
       spawnBee(bees, bee, beeSpeeds, beeDirections, activeBeeCount, spawnClock, BeeActive, beeX ,15);
         moveBees(bees, beeSpeeds, beeDirections, activeBeeCount, beeClock, bee, reverseBee, animationClock,bullet_exists, bulletSprite, BeeActive, beeX,beeY, 20,Yellowhoneycombs,YellowhoneyTexture,YellowhoneyActive,YellowhoneyX,YellowhoneyY, YellowactiveHoneyCount,HitSound, Redhoneycombs, RedhoneyActive, RedhoneyX,RedhoneyY, RedactiveHoneyCount);
        drawBee(window, activeBeeCount, bees, BeeActive, 20);

}
           drawRedHoneycombs(window, Redhoneycombs, RedhoneyActive, RedactiveHoneyCount,bullet_exists,bulletSprite) ;
           drawHoneycombs(window, YellowactiveHoneyCount, Yellowhoneycombs, YellowhoneyActive,bullet_exists,bulletSprite);

       
        playerSprite2.setPosition(4,630);
        playerSprite2.setScale(1.2f,1.2f);
        playerSprite3.setPosition(90,630);
        playerSprite3.setScale(1.2f,1.2f);
       
       
        // Create a Text object for the score //--*******
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);  // Set text size
        scoreText.setFillColor(Color::White);  // Set text color
        sf::FloatRect textBounds = scoreText.getLocalBounds();   //?????? how to change this
        scoreText.setPosition(resolutionX - textBounds.width - 200, resolutionY - textBounds.height - 60);  // Position

        // Convert the score to a string and update the text
        scoreText.setString("Score: " + to_string(score));

        movePlayer(player_x, smoothMovement);

        if (Keyboard::isKeyPressed(Keyboard::Space) && !bullet_exists) {
            ammoIncrease(bullet_exists, ammo, nextCan, chance);
            bullet_exists = true;  // Bullet has been fired
            bullet_x = player_x + 18;  // bullet ke alignment ke leye
            bullet_y = player_y;  // Set bullet's starting position at the player's position
            bulletClock.restart();  // Reset the bullet clock to start the movement
            //fireSound.play();
        }

        if (bullet_exists == true) {
            moveBullet(bullet_y, bullet_exists, bulletClock);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
        } else {
            bullet_x = player_x + 8;
            bullet_y = player_y;
        }
           
           
        // yeha pe mein number of bullets se amount of spray in Cans ko display kara raha ho
        nextCan = nextPlayer(nextCan, playerTexture, playerSprite);

     

                   //drawBees(window, gameGrid, beeSprite);
           // Screen pe different Sprite ko display kar wane ka leye
        //window.draw(beeSprite);
        drawPlayer(window, player_x, player_y, playerSprite);
        // Function to display bees in the game
           
        window.draw(groundRectangle);
        window.draw(scoreText);
        if(chance== 3 || chance==2)
        window.draw(playerSprite2);
        if(chance == 3)
        window.draw(playerSprite3);
        window.display();
        window.clear();
    }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
/////////////////////////////////////////////////////////////////////////////

 void drawRedHoneycombs(RenderWindow& window, Sprite redHoneycombs[], bool redHoneyActive[], int activeRedHoneyCount, bool& bulletExists, Sprite& bullet) {
    for (int i = 0; i < activeRedHoneyCount; ++i) {
        if (!redHoneyActive[i]) continue; // Only draw active red honeycombs
        
        // Check collision with the bullet
        if (bulletExists && checkCollision(redHoneycombs[i], bullet,20)) {
            redHoneyActive[i] = false; // Deactivate the honeycomb
            bulletExists = false;  // Remove the bullet
            continue;
        }
        window.draw(redHoneycombs[i]);
    }
}


void moveHoneycombs(Sprite honeycombs[], float honeyX[], float honeyY[],
                   bool honeyActive[], int& activeHoneyCount, float honeySpeed) {
    //for (int i = 0; i < activeHoneyCount; ++i) {
        //if (!honeyActive[i]) continue; // Skip inactive honeycombs

        // Deactivate if it goes out of bounds
        //if (honeyY[i] > 960) { // Assuming 1080 is the screen height
        //    honeyActive[i] = false;
      //  }

    //    honeycombs[i].setPosition(honeyX[i], honeyY[i]);
  //  }
  
}

void spawnHoneycomb(Sprite honeycombs[], Texture& honeyTexture, float honeyX[], float honeyY[],
                    bool honeyActive[], int& activeHoneyCount, float beeX, float beeY) {
    if (activeHoneyCount >= 20) return; // Limit the number of honeycombs

    // Position the honeycomb at the location of the bee
    honeyX[activeHoneyCount] = beeX;
    honeyY[activeHoneyCount] = beeY;
    honeycombs[activeHoneyCount].setTexture(honeyTexture);
    honeycombs[activeHoneyCount].setPosition(honeyX[activeHoneyCount], honeyY[activeHoneyCount]);
    honeycombs[activeHoneyCount].setScale(1.5, 1.5); // Adjust scale if necessary
    honeyActive[activeHoneyCount] = true;
    ++activeHoneyCount;
}

void drawHoneycombs(RenderWindow& window, int& activeHoneyCount, Sprite honeycombs[], bool honeyActive[],bool& bulletExists, Sprite& bullet) {
    for (int i = 0; i < activeHoneyCount; ++i) {
        if (!honeyActive[i]) continue; // Skip inactive honeycombs

        // Check collision with the bullet
        if (bulletExists && checkCollision(honeycombs[i], bullet,20)) {
            honeyActive[i] = false; // Deactivate the honeycomb
            bulletExists = false;  // Remove the bullet
            continue;
        }

        // Draw active honeycombs
        window.draw(honeycombs[i]);
    }
}

bool checkCollision(Sprite& bee, Sprite& bullet,int nobees){
    // Bee's position and size (assuming bee size is 48x48)
    float beeX = bee.getPosition().x;
    float beeY = bee.getPosition().y;
    float beeWidth = 48;  // Example width of the bee
    float beeHeight = 48; // Example height of the bee

    // Bullet's position and size (assuming bullet size is 10x20)
    float bulletX = bullet.getPosition().x;
    float bulletY = bullet.getPosition().y;
    float bulletWidth = 48;  // Example width of the bullet
    float bulletHeight = 48; // Example height of the bullet

    // Check for overlap: If the bullet's rectangle overlaps with the bee's rectangle
    if (bulletX < beeX + beeWidth &&
        bulletX + bulletWidth > beeX &&
        bulletY < beeY + beeHeight &&
        bulletY + bulletHeight > beeY) {
        return true; // Collision detected
    }
    return 0;
}

// Function to spawn fast bees
void spawnFastBee(Sprite fastBees[], Texture& fastBeeTexture, float fastBeeSpeeds[], float fastBeeDirections[], int& fastActiveBeeCount, Clock& fastSpawnClock, bool fastBeeActive[], float FastbeeX[],int noFastBees) {
    if (fastSpawnClock.getElapsedTime().asMilliseconds() < 1000 || fastActiveBeeCount >= noFastBees) return;
   
    fastSpawnClock.restart();
    FastbeeX[fastActiveBeeCount]=rand() % (resolutionX - boxPixelsX);
    fastBees[fastActiveBeeCount].setPosition(FastbeeX[fastActiveBeeCount], 0);
    fastBees[fastActiveBeeCount].setScale(1.5, 1.5);
    fastBees[fastActiveBeeCount].setTexture(fastBeeTexture);
    fastBeeSpeeds[fastActiveBeeCount] = 10 + rand() % 20; // Faster speed range: 6 to 15
    fastBeeDirections[fastActiveBeeCount] = (rand() % 2 == 0) ? 1.0f : -1.0f;
    fastBeeActive[fastActiveBeeCount] = true;
    ++fastActiveBeeCount;
}

// Function to move fast bees
void moveFastBees(Sprite fastBees[], float fastBeeSpeeds[], float fastBeeDirections[], int& fastActiveBeeCount, Clock& fastBeeClock, Texture& fastBeeTexture, Clock animationClock, bool& bulletExists, Sprite& bullet, bool fastBeeActive[], int noFastBees, Texture& reverseFast ,float FastbeeX[],float FastbeeY[], Sprite honeycombs[], Texture& honeyTexture, bool honeyActive[], float honeyX[], float honeyY[], int& activeHoneyCount,Sprite flowerSprites[], Texture& flowerTexture,bool flowerActive[]) {
    static int frame = 0;
   
    // Change animation frame every 30ms
    if (animationClock.getElapsedTime().asMilliseconds() > 30) {
        frame = (frame + 1) % 3;  // Loop through 3 frames
        animationClock.restart();
    }

    if (fastBeeClock.getElapsedTime().asMilliseconds() < 50) return; // Faster movement interval
    fastBeeClock.restart();

    for (int i = 0; i < fastActiveBeeCount; ++i) {
        if (!fastBeeActive[i]) continue; // Only move active bees
        FastbeeX[i] += fastBeeSpeeds[i] * fastBeeDirections[i];
           
           // Dimensions of the bee and honeycomb (adjust as per your sprite dimensions)
    float beeWidth = 48;
    float beeHeight = 48;
    float honeyWidth = 48;  
    float honeyHeight = 48;
   bool collision = false;
   
        // Check for collision with bullet
        if(fastBeeActive[i])
        if (bulletExists && checkCollision(fastBees[i], bullet, noFastBees)) {
            fastBees[i].setPosition(-10000, 10000); // Remove bee from screen
            fastBeeActive[i] = false;
            bulletExists = false;
           
            // Spawn a red honeycomb at the bee's position
        if (activeHoneyCount < noFastBees) { // Ensure we don't exceed array limits
            honeyX[activeHoneyCount] = FastbeeX[i];
            honeyY[activeHoneyCount] = FastbeeY[i];
            honeycombs[activeHoneyCount].setTexture(honeyTexture);
            honeycombs[activeHoneyCount].setPosition(honeyX[activeHoneyCount], honeyY[activeHoneyCount]);
            honeycombs[activeHoneyCount].setScale(1.5, 1.5); // Adjust scale as needed
            honeyActive[activeHoneyCount] = true;
            ++activeHoneyCount;
        }  
            continue;
        }

                  if (fastBeeDirections[i] < 0) {
        fastBees[i].setTexture(fastBeeTexture);
    } else {
                   fastBees[i].setTexture(reverseFast);
    }
        
         
            if (FastbeeX[i] <= 0 || FastbeeX[i] >= resolutionX - beeWidth) {
                fastBeeDirections[i] *= -1;
                // Only move down if the bee hasn't just bounced off a honeycomb
                if (!collision) {
                    FastbeeY[i] += 48; // Move down on direction change
                }
        }
        
        // Check if bee hits the ground
        if (FastbeeY[i] >= resolutionY - 162) { // Adjust height as per your bee dimensions
            // Transfer bee to the top
            FastbeeY[i] = 0;
            FastbeeX[i] = rand() % (resolutionX - 48); // Randomize X position at the top

            // Spawn a flower at the bee's previous position
            if (!flowerActive[i]) {
                flowerSprites[i].setTexture(flowerTexture);
                flowerSprites[i].setPosition(FastbeeX[i], resolutionX -400);
                flowerSprites[i].setScale(0.5f, 0.5f); // Adjust flower size
                flowerActive[i] = true;
            }
        }
    
        fastBees[i].setTextureRect(IntRect(frame * 48, 0, 48, 48)); // Animation frame
        fastBees[i].setPosition(FastbeeX[i],FastbeeY[i]);
    }
}

// Function to draw fast bees
void drawFastBees(RenderWindow& window, Sprite fastBees[], int& fastActiveBeeCount, bool fastBeeActive[], int noFastBees) {
    for (int i = 0; i < fastActiveBeeCount; ++i) {
        if (!fastBeeActive[i]) continue; // Only draw active bees
        window.draw(fastBees[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBee(RenderWindow& window,int& activeBeeCount,Sprite bees[], bool beeActive[], int nobees){
           for (int i = 0; i < activeBeeCount; ++i) {
             if (!beeActive[i]) continue; // Only draw active bees
            window.draw(bees[i]);
        }
}



void moveBees(Sprite bees[], float beeSpeeds[], float beeDirections[], int& activeBeeCount, Clock& beeClock, Texture& beeTexture, Texture& reverseBee, Clock animationClock, bool& bullet_exists, Sprite& bullet, bool beeActive[], float beeX[], float beeY[], int nobees, Sprite honeycombs[], Texture& honeyTexture, bool honeyActive[], float honeyX[], float honeyY[], int& activeHoneyCount, Sound& HitSound, Sprite redHoneycombs[], bool redHoneyActive[], float redHoneyX[], float redHoneyY[], int activeRedHoneyCount) {
    static int frame = 0; // Frame counter

    // Change animation frame every 50ms
    if (animationClock.getElapsedTime().asMilliseconds() > 50) {
        frame = (frame + 1) % 3;  // Loop through 3 frames (0, 1, 2)
        animationClock.restart();  // Restart the animation clock for the next frame
    }

    if (beeClock.getElapsedTime().asMilliseconds() < 50) return;
    beeClock.restart();

    // Dimensions of the bee and honeycomb (adjust as per your sprite dimensions)
    float beeWidth = 48;
    float beeHeight = 48;
    float honeyWidth = 48;  
    float honeyHeight = 48;

    for (int i = 0; i < activeBeeCount; ++i) {
        if (!beeActive[i]) continue; // Skip inactive bees

        // Move bee based on its speed and direction
        beeX[i] += beeSpeeds[i] * beeDirections[i];
        // Check for collision with bullet
        if (bullet_exists && checkCollision(bees[i], bullet, nobees)) {
            HitSound.play();
            // Deactivate the bee and spawn a honeycomb
            bees[i].setPosition(10000, 10000); // Move off-screen
            beeActive[i] = false;   // Deactivate the bee
            bullet_exists = false;
            spawnHoneycomb(honeycombs, honeyTexture, honeyX, honeyY, honeyActive, activeHoneyCount, beeX[i], beeY[i]);
            continue;  // Skip further processing for this bee
        }
           
           bool collision = false;
           
        // Check for collision with honeycombs
        for (int j = 0; j < activeHoneyCount; ++j) {
            if (!honeyActive[j]) continue; // Skip inactive honeycombs

            // Custom collision detection between bee and honeycomb
            if (beeX[i] < honeyX[j] + honeyWidth &&
                beeX[i] + beeWidth > honeyX[j] &&
                beeY[i] < honeyY[j] + honeyHeight &&
                beeY[i] + beeHeight > honeyY[j]) {
                // Bounce the bee in the opposite direction
                beeDirections[i] *= -1;
                      collision = true;
                // Slightly adjust bee position to avoid "sticking"
                beeX[i] += 24 * beeDirections[i];
                break; // No need to check further honeycombs
            }
        }
        
        // Check for collision with red honeycombs
        for (int k = 0; k < activeRedHoneyCount; ++k) {
            if (!redHoneyActive[k]) continue; // Skip inactive red honeycombs

            if (beeX[i] < redHoneyX[k] + honeyWidth &&
                beeX[i] + beeWidth > redHoneyX[k] &&
                beeY[i] < redHoneyY[k] + honeyHeight &&
                beeY[i] + beeHeight > redHoneyY[k]) {
                // Bounce the bee in the opposite direction
                beeDirections[i] *= -1;
                collision = true;
                beeX[i] += 24 * beeDirections[i]; // Adjust position to avoid sticking
                break;
            }
}
            // Check for screen boundaries
        
            if (beeX[i] <= 0 || beeX[i] >= resolutionX - beeWidth) {
                beeDirections[i] *= -1;
                // Only move down if the bee hasn't just bounced off a honeycomb
                if (!collision) {
                    beeY[i] += 48; // Move down on direction change
                }
            }
        
       
        // Set the appropriate texture for bee direction
        if (beeDirections[i] < 0) {
            bees[i].setTexture(beeTexture);
        } else {
            bees[i].setTexture(reverseBee);
        }

        // Apply the animation frame
        bees[i].setTextureRect(sf::IntRect(frame * 48, 0, 48, 48));
        //Bee ke position ke leye
        bees[i].setPosition(beeX[i], beeY[i]);


    }
   
}



void spawnBee(Sprite bees[], Texture& beeTexture, float beeSpeeds[], float beeDirections[], int& activeBeeCount, Clock& spawnClock, bool beeActive[],float Xposition[], int nobees) {
if (spawnClock.getElapsedTime().asMilliseconds() < 1500 || activeBeeCount >= 20) return;

    spawnClock.restart();
    Xposition[activeBeeCount] = rand() % (resolutionX - boxPixelsX);
    bees[activeBeeCount].setPosition(Xposition[activeBeeCount], 0);
    bees[activeBeeCount].setScale(1.5, 1.5);
    beeSpeeds[activeBeeCount] = 7 + rand() % 8; // Random speed between 7 and 15
    beeDirections[activeBeeCount] = (rand() % 2 == 0) ? 1.0f : -1.0f;
    beeActive[activeBeeCount] = true;
    ++activeBeeCount;
}

int nextPlayer(int& nextCan, Texture& playerTexture, Sprite& playerSprite) {
    if (nextCan == 2 ) {
        playerTexture.loadFromFile("spray/spray_2.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    } else if (nextCan == 3) {
        playerTexture.loadFromFile("spray/spray_3.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    } else if (nextCan == 4) {
        playerTexture.loadFromFile("spray/spray_4.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    } else if (nextCan == 5) {
        playerTexture.loadFromFile("spray/spray_5.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    } else if (nextCan == 6) {
        playerTexture.loadFromFile("spray/spray_6.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    } else if (nextCan == 7) {
        playerTexture.loadFromFile("spray/spray_7.png");
        playerSprite.setTexture(playerTexture);
        return 0;
    }else if(nextCan ==1){
        playerTexture.loadFromFile("spray/spray_1.png");
        playerSprite.setTexture(playerTexture);
    }
    return 0;
}

void ammoIncrease(bool& bullet_exists, int& ammo, int& nextCan, int& chance) {
    ammo--;
    if (ammo == 48)
 {       nextCan = 2;}
    else if (ammo == 40)
{        nextCan = 3;}
    else if (ammo == 32)
{        nextCan = 4;}
    else if (ammo == 24)
        {nextCan = 5;}
    else if (ammo == 16)
        {nextCan = 6;}
    else if (ammo == 8)
       { nextCan = 7;}
    else if (ammo == 0 && chance > 0) {
    nextCan=1;
        ammo = 56;
        chance--;  // If chance becomes 0, player loses the game!
    }
}

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
}

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
    if (bulletClock.getElapsedTime().asMilliseconds() < 50) {    // ye bullet ketney time ke bad next grid pe jaye is ke leye hai
        return;
    }

    bulletClock.restart();
    bullet_y -= 48;
    if (bullet_y < -48) {
        bullet_exists = false;
    }
}

void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
    bulletSprite.setPosition(bullet_x, bullet_y);
    window.draw(bulletSprite);
}

void movePlayer(float& player_x, Clock& move) {
    if (move.getElapsedTime().asMilliseconds() < 40)
        return;

    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A) && player_x > 0) {
        player_x -= 48;
        if (player_x <= 0) player_x = 0;
        move.restart();
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D) && player_x < resolutionX - boxPixelsX) {
        player_x += 48;
        if (player_x >= 900) player_x = 900;
        move.restart();
    }
}

                                       /*Menu of the Game!*/
int showStartMenu(RenderWindow& window) {  // This is the function for the start menu
    // Font and Text setup
    Font font;
    if (!font.loadFromFile("Fonts/arial.ttf")) {  // font
        cout << "Error loading font!" << endl;
        return -1;
    }
    //For background of start menu :
Texture backgroundTexture;
Sprite backgroundSprite;
if (!backgroundTexture.loadFromFile("spray/Menu.jpg")) {
   cout << "Error loading background!" << endl;
}
backgroundSprite.setTexture(backgroundTexture);        // to adjust the background image
Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = 960.0 / textureSize.x;
    float scaleY = 720.0 / textureSize.y;
backgroundSprite.setScale(scaleX, scaleY);

    // Title text
    Text title("Buzz Bombers", font, 70);
    title.setPosition(resolutionX / 2 - title.getLocalBounds().width / 2, 50);  // resolution / 2 brings it to the middle of the page
    title.setFillColor(Color::Red);  // Sets color to white

    // Menu options
    Text level1(" Level 1", font, 30);
    level1.setPosition(resolutionX / 2 - level1.getLocalBounds().width / 2, 200);
    level1.setFillColor(Color::White);

    Text level2(" Level 2", font, 30);
    level2.setPosition(resolutionX / 2 - level2.getLocalBounds().width / 2, 250);
    level2.setFillColor(Color::White);

    Text level3(" Level 3", font, 30);
    level3.setPosition(resolutionX / 2 - level3.getLocalBounds().width / 2, 300);
    level3.setFillColor(Color::White);

    Text quit(" Exit  ", font, 30);
    quit.setPosition(resolutionX / 2 - quit.getLocalBounds().width / 2, 350);
    quit.setFillColor(Color::White);

    int selectedItem = 0;  // Track selected menu item
    bool isMenuActive = true;
   
    //Origin ko reset karne ke leye
    level1.setOrigin(30 , level1.getLocalBounds().height / 2 - 40);
    level2.setOrigin(30, level2.getLocalBounds().height / 2  - 40);
    level3.setOrigin(30, level3.getLocalBounds().height / 2 - 40) ;
    quit.setOrigin(30 , quit.getLocalBounds().height / 2 - 40);

//Green rectangle ke leye
    RectangleShape groundRectangle(Vector2f(960, 640));
    groundRectangle.setPosition(0, (gameColumns - 1.8) * boxPixelsY);
    groundRectangle.setFillColor(Color::Green);


    while (isMenuActive) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(level1);
        window.draw(level2);
        window.draw(level3);
        window.draw(quit);
        //window.draw(groundRectangle);
        window.display();

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return -1;  // Close the window if the player quits
            }

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up || e.key.code == Keyboard::W) {
                    // Move up in the menu
                    selectedItem = (selectedItem + 3 ) % 4;  // Wrap around
                } else if (e.key.code == Keyboard::Down || e.key.code == Keyboard::S) {
                    // Move down in the menu
                    selectedItem = (selectedItem + 1) % 4;  // Wrap around
                } else if (e.key.code == Keyboard::Enter) {
                    // Select the option
                    if (selectedItem == 3) {  // Quit
                        return -1;
                    } else {
                        return selectedItem;  // Return 0 for Play
                    }
                }
            }
        }

// Ye Zoom in kar ne ke leye hai
// Is section m mein size ko reset kar raha ho
level1.setScale(1.f, 1.f);
level2.setScale(1.f, 1.f);
level3.setScale(1.f, 1.f);
quit.setScale(1.f, 1.f);
//in this section, i am size of texts
if (selectedItem == 0) level1.setScale(1.5f, 1.2f);
        else if (selectedItem == 1) level2.setScale(1.5f, 1.2f);
        else if (selectedItem == 2) level3.setScale(1.5f, 1.2f);
        else if (selectedItem == 3) quit.setScale(1.5f, 1.2f);
        // This is to update the color of text as the player hovers over them
        level1.setFillColor(selectedItem == 0 ? Color::Green : Color::Black);
        level2.setFillColor(selectedItem == 1 ? Color::Yellow : Color::Black);
        level3.setFillColor(selectedItem == 2 ? Color::Red : Color::Black);
        quit.setFillColor(selectedItem == 3 ? Color::Blue : Color::Black);

    }

    return -1;
}
