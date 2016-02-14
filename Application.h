#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>

class State;

/** 
 * \brief Main class for application. Contains window and pointer to current state
 */
class Application{
public:
	/** 
	 * \brief Construct new Application.
	 * 
	 * Creates application and its window with parameters passed to constructor.
	 * 
	 * \param width	Width of the window
	 * \param height	Height of the window
	 * \param title	Title of the window
	 * \param fps		Maximum frames per second
	 */ 
	Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);

	/**
	 * \brief Default constructor
	 *
	 * Creates application with with window parameters:
	 * size 800x600, title "Game", fps 60
	 */
	Application();

	/**
	 * \brief Default destructor
	 *
	 * Destroys application
	 */
	~Application();

	/**
	 * \brief Run main game loop
	 * 
	 * This is a method you call when you create your application
	 */
	void run();

	/**
	 * \brief Get Reference to the application's window
	 *
	 * Allows you to manipulate properties of the window like
	 * current view, its size and so on
	 *
	 * \return reference to application's window
	 */
	sf::RenderWindow& getWindow();

	/**
	 * \brief Change game state
	 *  
	 * This method changes current state. It also destoys previous one
	 * 
	 * \param state Pointer to new game state
	 */
	void changeState(State* state);

	/*
	 * \brief Get application's console
	 * 
	 * This method allows you to display additional information in upper
	 * left corner of the window
	 *
	 * \return Reference to application's output string stream
	 */
	std::ostringstream& getConsole();

private:
	/**
	 * \brief Process events
	 * 
	 * Processes events and delegates theem to game state
	 */
	void processEvents();

	/**
	 * \brief Update the application
	 *
	 * This method is called at constant interval of time. It updates 
	 * application's logic
	 *
	 * \param dt time since last update
	 */
	void update(const sf::Time& dt);

	/**
	 * \brief Render window
	 * 
	 * Renders window on the screen.
	 */
	void render();

	sf::RenderWindow window_;		/**< Application's window */
	bool hasFocus_;					/**< Indicates wether window has focus */
	std::unique_ptr<State> state_;	/**< Pointer to current game state */

	/** 
	 * Console displaying useful information like frames per second
	 * and updates per second. You can show more information with
	 * getConsole() method
	 */
	struct Console{
		Console();
		void update(const sf::Time& dt);

		bool up_;
		sf::Time timeSinceFpsUpdate_;
		const sf::Time TimePerFpsUpdate_;
		unsigned int frameCounter_;
		unsigned int updateCounter_;
		float currentFps_;
		float currentUps_;
		sf::Font font_;
		std::ostringstream stream_;
		sf::Text text_;
	} console_;
};

