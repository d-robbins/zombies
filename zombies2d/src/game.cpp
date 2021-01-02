#include "game.h"


Game::Game(const int& w, const int& h, const std::string& title) :
	width_(w),
	height_(h),
	name_(title)
{
	window_.create(sf::VideoMode(width_, height_), name_);
	intialize_game();
}

void Game::intialize_game() {
	player_ = sf::CircleShape(50.0f);
	player_.setFillColor(sf::Color::Red);
	player_.setPosition(sf::Vector2f(static_cast<float>(width_) / 2, static_cast<float>(height_) / 2));

	//
	border_.resize(4);
	for (auto& wall : border_) {
		wall.setFillColor(sf::Color::Red);
	}

	border_[0] = sf::RectangleShape(sf::Vector2f(static_cast<float>(width_), 30.f));
	border_[1] = sf::RectangleShape(sf::Vector2f(static_cast<float>(width_), 30.f));
	border_[2] = sf::RectangleShape(sf::Vector2f(static_cast<float>(height_ - 60), 30.f));
	border_[3] = sf::RectangleShape(sf::Vector2f(static_cast<float>(height_ - 60), 30.f));
	
	border_[0].setFillColor(sf::Color::Green);
	
	border_[1].setPosition(sf::Vector2f(0.0f, static_cast<float>(height_) - 30.0f));
	border_[1].setFillColor(sf::Color::Green);
	
	border_[2].rotate(90.0f);
	border_[3].rotate(90.0f);
	border_[2].setFillColor(sf::Color::Green);
	border_[3].setFillColor(sf::Color::Green);

	border_[2].setPosition(sf::Vector2f(30.0f, 30.0f));
	border_[3].setPosition(sf::Vector2f(static_cast<float>(width_), 30.0f));

}

void Game::process_input(const sf::Event& e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player_.move(sf::Vector2f(0.0f, -MOVE_SCALE));
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player_.move(sf::Vector2f(0.0f, MOVE_SCALE));
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player_.move(sf::Vector2f(-MOVE_SCALE, 0.0f));
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player_.move(sf::Vector2f(MOVE_SCALE, 0.0f));
	}
}

Game::~Game() {

}

void Game::play()
{
	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			process_input(event);
		}

		window_.clear();
		window_.draw(player_);

		for (const auto& wall : border_) {
			window_.draw(wall);
		}

		window_.display();
	}
}