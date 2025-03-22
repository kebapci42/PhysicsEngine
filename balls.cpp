#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Collision");

    // Create the ball with a radius of 30 pixels
    sf::CircleShape top(30.f);
    top.setFillColor(sf::Color::Green); // Set the ball color to green
    top.setPosition(385.f, 300.f); // Set the initial position of the ball

    // Create the mouse object (visible collision area)
    sf::CircleShape fareObjesi(10.f); // Create a circle with radius 10 pixels for the mouse collision area
    fareObjesi.setFillColor(sf::Color(255, 255, 255, 150)); // Set a transparent white color
    fareObjesi.setOrigin(10.f, 10.f); // Set the origin to the center of the circle

    // Initialize the ball's velocity vector (initially zero)
    sf::Vector2f velocity(0.f, 0.f);
    float gravity = 980.f; // Gravity acceleration in pixels per second squared
    float bounceFactor = 0.8f; // Bounce damping factor (reduces speed after collision)
    float groundY = 570.f; // Y-coordinate of the ground (bottom boundary)
    float leftWall = 0.f;  // X-coordinate for the left wall
    float rightWall = 770.f; // X-coordinate for the right wall (800 - ball width)

    // Clock to measure the time elapsed (delta time)
    sf::Clock clock;

    // Main loop: runs until the window is closed
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Check if the window is requested to close
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time since the last frame (in seconds)
        float dt = clock.restart().asSeconds();

        // Apply gravity to the ball's vertical velocity
        velocity.y += gravity * dt;

        // Move the ball according to its velocity scaled by delta time
        top.move(velocity * dt);

        // Get the current position of the ball (top-left corner of its bounding box)
        sf::Vector2f pos = top.getPosition();

        // Ground collision check:
        // If the bottom of the ball is below the ground level, adjust its position and reverse the y-velocity
        if (pos.y + top.getRadius() * 2 > groundY)
        {
            pos.y = groundY - top.getRadius() * 2;
            top.setPosition(pos);
            // Reverse the vertical velocity and apply the bounce factor (damping)
            velocity.y = -velocity.y * bounceFactor;
            // If the vertical velocity is very small, set it to zero to stop jittering
            if (std::abs(velocity.y) < 10.f)
                velocity.y = 0.f;
        }

        // Left wall collision check:
        // If the ball goes beyond the left wall, adjust its position and reverse the x-velocity
        if (pos.x < leftWall)
        {
            pos.x = leftWall;
            top.setPosition(pos);
            velocity.x = -velocity.x * bounceFactor;
        }

        // Right wall collision check:
        // If the ball goes beyond the right wall, adjust its position and reverse the x-velocity
        if (pos.x > rightWall)
        {
            pos.x = rightWall;
            top.setPosition(pos);
            velocity.x = -velocity.x * bounceFactor;
        }

        // Get the mouse position relative to the window and update the mouse object position
        sf::Vector2f farePozisyonu = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        fareObjesi.setPosition(farePozisyonu);

        // Collision detection between the ball and the mouse object:
        // Calculate the center of the ball
        sf::Vector2f topMerkez = top.getPosition() + sf::Vector2f(top.getRadius(), top.getRadius());
        // Calculate the difference vector between the ball center and the mouse position
        sf::Vector2f fark = topMerkez - farePozisyonu;
        // Calculate the distance between the two centers using the Pythagorean theorem
        float mesafe = std::sqrt(fark.x * fark.x + fark.y * fark.y);
        // Calculate the sum of the radii (ball radius + mouse object radius)
        float toplamYaricap = top.getRadius() + fareObjesi.getRadius();

        // If the distance is less than the sum of the radii, a collision is occurring
        if (mesafe < toplamYaricap)
        {
            // Collision occurred: apply a force to the ball in the direction away from the mouse object.
            // Normalize the difference vector to get the direction (unit vector)
            sf::Vector2f yonBirimi = fark / mesafe;
            float kuvvet = 500.f; // Magnitude of the force to be applied
            velocity = yonBirimi * kuvvet; // Set the ball's velocity to this new vector
        }

        // Apply friction to the horizontal (x-axis) velocity to gradually slow down horizontal movement
        velocity.x *= 0.99f;

        // Clear the window with a black background
        window.clear(sf::Color::Black);
        // Draw the ball
        window.draw(top);
        // Draw the mouse object (collision area)
        window.draw(fareObjesi);
        // Display the rendered frame on the screen
        window.display();
    }

    return 0;
}
