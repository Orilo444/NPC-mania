#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    Bullet(sf::Vector2f startPosition, sf::Vector2f moveDirection) {
        shape.setSize(sf::Vector2f(25, 10));  // Set the bullet size
        shape.setPosition(startPosition);  
        shape.setFillColor(sf::Color::Red);
        direction = moveDirection;  // Set the bullet's movement direction
    }

    // Update the bullet's position based on its direction
    void update() {
        shape.move(direction);
    }
};

int main() {
    int playerXIndex = 0;

    //---------------------update---------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(1600, 900), "RPG GAME", sf::Style::Default, settings);



    //********************ENEMY*********************
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;

    if (enemyTexture.loadFromFile("assets/skelton/textures/spritesheet.png")) {
        std::cout << "Enemy image loaded\n";
        enemySprite.setTexture(enemyTexture);
        enemySprite.setPosition(sf::Vector2f(400, 100));

        int XIndex = 0;
        int YIndex = 2;
        enemySprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        enemySprite.scale(sf::Vector2f(3, 3));


    }
    else {
        std::cout << "enemy image failed to load \n";
    }



    //**********************PLAYER*********************


    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (playerTexture.loadFromFile("assets/player/textures/spritesheet.png")) {
        std::cout << "player image loaded\n";
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 0;
        playerSprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(3, 3));
        playerSprite.setPosition(sf::Vector2f(1400, 500));


    }
    else {
        std::cout << "player image failed to load\n";
    }
    // *****************calculatendirection of bullet*******

    int frameIndex = 0;                     // Current animation frame
    const int totalFrames = 4;              // Total frames in each direction
    sf::Clock animationClock;               // Clock to control animation timing
    const float frameDuration = 0.15f;      // Time in seconds per frame

    std::vector<Bullet> bullets;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bool isMoving = false;  // Check if the player is moving

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(5, 0));
            int YIndex = 3;  // Row index for right movement
            isMoving = true;

            if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
                frameIndex = (frameIndex + 1) % totalFrames;  // Cycle through frames
                animationClock.restart();
            }
            playerSprite.setTextureRect(sf::IntRect(frameIndex * 64, YIndex * 64, 64, 64));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-5, 0));
            int YIndex = 1;  // Row index for left movement
            isMoving = true;

            if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
                frameIndex = (frameIndex + 1) % totalFrames;
                animationClock.restart();
            }
            playerSprite.setTextureRect(sf::IntRect(frameIndex * 64, YIndex * 64, 64, 64));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -5));
            int YIndex = 0;  // Row index for up movement
            isMoving = true;

            if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
                frameIndex = (frameIndex + 1) % totalFrames;
                animationClock.restart();
            }
            playerSprite.setTextureRect(sf::IntRect(frameIndex * 64, YIndex * 64, 64, 64));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, 5));
            int YIndex = 2;  // Row index for down movement
            isMoving = true;

            if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
                frameIndex = (frameIndex + 1) % totalFrames;
                animationClock.restart();
            }
            playerSprite.setTextureRect(sf::IntRect(frameIndex * 64, YIndex * 64, 64, 64));
        }

        if (!isMoving) {
            frameIndex = 0;  // Reset to idle frame if no movement
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Bullet newBullet(playerSprite.getPosition(), sf::Vector2f(5, 0));
            bullets.push_back(newBullet);
        }

        // Update bullets' positions
        for (auto& bullet : bullets) {
            bullet.update();
        }

        window.clear(sf::Color::Black);
        window.draw(enemySprite);
        window.draw(playerSprite);

        for (const auto& bullet : bullets) {
            window.draw(bullet.shape);
        }

        window.display();
    }
    return 0;
}