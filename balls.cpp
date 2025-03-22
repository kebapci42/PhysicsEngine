#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fare ile Çarpışma");

    // Top
    sf::CircleShape top(30.f);
    top.setFillColor(sf::Color::Green);
    top.setPosition(385.f, 300.f);

    // Fare "objesi" (isteğe bağlı görünür hale getirdik)
    sf::CircleShape fareObjesi(10.f);  // Fare çarpışma alanı
    fareObjesi.setFillColor(sf::Color(255, 255, 255, 150));  // Şeffaf beyaz
    fareObjesi.setOrigin(10.f, 10.f);  // Ortadan hizalama

    sf::Vector2f velocity(0.f, 0.f);
    float gravity = 980.f;
    float bounceFactor = 0.8f;
    float groundY = 570.f;
    float leftWall = 0.f;
    float rightWall = 770.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // Yerçekimi uygula
        velocity.y += gravity * dt;

        // Topu hareket ettir
        top.move(velocity * dt);

        sf::Vector2f pos = top.getPosition();

        // Zemin
        if (pos.y + top.getRadius() * 2 > groundY)
        {
            pos.y = groundY - top.getRadius() * 2;
            top.setPosition(pos);

            velocity.y = -velocity.y * bounceFactor;

            if (std::abs(velocity.y) < 10.f)
                velocity.y = 0.f;
        }

        // Duvarlar
        if (pos.x < leftWall)
        {
            pos.x = leftWall;
            top.setPosition(pos);
            velocity.x = -velocity.x * bounceFactor;
        }

        if (pos.x > rightWall)
        {
            pos.x = rightWall;
            top.setPosition(pos);
            velocity.x = -velocity.x * bounceFactor;
        }

        // Fare pozisyonunu al ve objeye uygula
        sf::Vector2f farePozisyonu = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        fareObjesi.setPosition(farePozisyonu);

        // Top ve fare çarpışma kontrolü
        sf::Vector2f topMerkez = top.getPosition() + sf::Vector2f(top.getRadius(), top.getRadius());
        sf::Vector2f fark = topMerkez - farePozisyonu;
        float mesafe = std::sqrt(fark.x * fark.x + fark.y * fark.y);
        float toplamYaricap = top.getRadius() + fareObjesi.getRadius();

        if (mesafe < toplamYaricap)
        {
            // Çarpışma oldu, topa kuvvet uygula
            // Yön = top merkez - fare → ters yön
            sf::Vector2f yonBirimi = fark / mesafe;
            float kuvvet = 500.f;
            velocity = yonBirimi * kuvvet;
        }

        // Sürtünme
        velocity.x *= 0.99f;

        window.clear(sf::Color::Black);
        window.draw(top);
        window.draw(fareObjesi);  // Fare objesi görünsün istersen
        window.display();
    }

    return 0;
}
