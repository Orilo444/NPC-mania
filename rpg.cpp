#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    //---------------------update---------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG GAME", sf::Style::Default, settings);

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (playerTexture.loadFromFile("assets/player/textures/spritesheet.png")) {
        std::cout << "player image loaded\n";
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 0;
        playerSprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(3, 3));


    }
    else {
        std::cout << "player image failed to load\n";
    }



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            /*if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D) {
                    sf::Vector2f position = playerSprite.getPosition();
                    playerSprite.setPosition(position + sf::Vector2f(10, 0));
                }
                
            }*/
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, 1));
        }

        //--------------------draw---------------
        window.clear(sf::Color::Black);
        window.draw(playerSprite);


        window.display();
    }
    return 0;
}