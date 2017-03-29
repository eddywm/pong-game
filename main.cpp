#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG GAME");

    window.setKeyRepeatEnabled(false);

    window.setFramerateLimit(60);

    sf::Event event;

    bool  play = true;



    //Font
    sf::Font font;
    if(!font.loadFromFile("/home/eddylloyd/CLionProjects/Gamedev/pong-game/res/Rambla-Bold.otf")){
        return 1;
    }

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setColor(sf::Color::Red);
    score.setPosition(150, 10);
    score.setString("0 : 0");

    sf::Text about;
    about.setFont(font);
    about.setCharacterSize(10);
    about.setColor(sf::Color::Blue);
    about.setPosition(400, 580);
    about.setString("Game developed by Eddy WM");

    //Images
    sf::Texture tex_pad;
    sf::Texture tex_ball;
    sf::Texture tex_background;

    if(!tex_pad.loadFromFile("/home/eddylloyd/CLionProjects/Gamedev/pong-game/res/pong-pad.png")){
        return -1;
    }

    if(!tex_ball.loadFromFile("/home/eddylloyd/CLionProjects/Gamedev/pong-game/res/kbza-Poket-Ball.png")){
        return -1;
    }

    if(!tex_background.loadFromFile("/home/eddylloyd/CLionProjects/Gamedev/pong-game/res/stars.jpg")){
        return -1;
    }

    //Sounds
    sf::SoundBuffer buffer_hit;
    if(!buffer_hit.loadFromFile("/home/eddylloyd/CLionProjects/Gamedev/pong-game/res/hit.ogg")){
        return -1;
    }
    sf::Sound hit;
    hit.setBuffer(buffer_hit);
    hit.setVolume(20);


    //Variables
    int y_velocity_pad1 = 0;
    int y_velocity_pad2 = 0;
    int x_velocity_ball = -3;
    int y_velocity_ball = -3;

    int pad1_score = 0;
    int pad2_score = 0;

    //*****************Shapes*******************//
    //Background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800, 600));
    background.setPosition(0, 0);
    background.setTexture(&tex_background);

    //Pad1
    sf::RectangleShape pad1;
    pad1.setSize(sf::Vector2f(50, 100));
    pad1.setPosition(50, 200);
    pad1.setTexture(&tex_pad);

    //Pad2
    sf::RectangleShape pad2;
    pad2.setSize(sf::Vector2f(50, 100));
    pad2.setPosition(700, 200);
    pad2.setTexture(&tex_pad);

    //Ball
    sf::RectangleShape ball;
    ball.setSize(sf::Vector2f(50, 50));
    ball.setPosition(400, 300);
    ball.setTexture(&tex_ball);

    ///States
    bool up = false, down = false;

    while (play){
        // EVENTS
        while(window.pollEvent(event)){
            if(event.type ==  sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up) up = true;
                if(event.key.code == sf::Keyboard::Down) down = true;
            }

            if(event.type ==  sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Up) up = false;
                if(event.key.code == sf::Keyboard::Down) down = false;
            }


            if(event.type == sf::Event::Closed) play = false;
        }

        ///Logic
        //Pad1
        if(up){
            y_velocity_pad1 = -5;
        }
        if(down){
            y_velocity_pad1 = 5;
        }
        if(up && down) y_velocity_pad1 = 0;
        if(!up && !down) y_velocity_pad1 = 0;

        pad1.move(0, y_velocity_pad1);

        //Out of bounds check
        if(pad1.getPosition().y < 0 ) pad1.setPosition(50, 0 );
        if(pad1.getPosition().y > 500) pad1.setPosition(50, 500);

        //Pad2


        if(ball.getPosition().y < pad2.getPosition().y) y_velocity_pad2 = -3;
        if(ball.getPosition().y > pad2.getPosition().y) y_velocity_pad2 =  3;
        pad2.move(0, y_velocity_pad2);

        //Ball
        ball.move(x_velocity_ball, y_velocity_ball);
        //Out of bounds check
        if(ball.getPosition().y < 0 ) y_velocity_ball =  -y_velocity_ball;
        if(ball.getPosition().y > 550) y_velocity_ball =  -y_velocity_ball;

        //score changing
        if(ball.getPosition().x < -50) {
            pad2_score++;
            ball.setPosition(300, 200);
        };

        if(ball.getPosition().x > 800) {
            pad2_score++;
            ball.setPosition(300, 200);
        };

        //Colision
        if(ball.getGlobalBounds().intersects(pad1.getGlobalBounds())) {
            x_velocity_ball = -x_velocity_ball;
            hit.play();
        };
        if(ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
            x_velocity_ball = -x_velocity_ball;
            hit.play();

        };

        // RENDERING
        window.clear();
        window.draw(background);

        window.draw(pad1);
        window.draw(pad2);
        window.draw(ball);

        //score
        std::stringstream sscore;
        sscore <<" USER SCORE           "<< pad1_score << " : "<<pad2_score <<"            COMPUTER SCORE " ;
        score.setString(sscore.str());
        window.draw(score);
        window.draw(about);
        window.display();
    }


    window.close();
    return 0;
}
