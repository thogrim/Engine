#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>

class State;

////////////////////////////////////////////////////////////////////////////
/// \brief Class containing application's window and pointer to current state
///
////////////////////////////////////////////////////////////////////////////
class Application{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Construct new Application
	///
	/// This constructor creates application and its window with parameters 
	/// passed to constructor
	///
	/// \param width	Width of the window
	/// \param height	Height of the window
	/// \param title	Title of the window
	/// \param fps		Maximum frames per second
	///////////////////////////////////////////////////////////////////////////
	Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// This constructor creates application with with window parameters:
	/// size 800x600, title "Game", fps 60
	///////////////////////////////////////////////////////////////////////////
	Application();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Destroys application
	///////////////////////////////////////////////////////////////////////////
	~Application();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Run main game loop
	///
	/// This is a method you call when you create your application
	///////////////////////////////////////////////////////////////////////////
	void run();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Get Reference to the application's window
	///
	/// Method that allows you to manipulate properties of the window like
	/// current view, its size and so on
	///
	/// \return reference to application's window
	///////////////////////////////////////////////////////////////////////////
	sf::RenderWindow& getWindow();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Change game state
	/// 
	/// This method changes current state. It also destoys previous one
	///
	/// \param state Pointer to new game state
	///////////////////////////////////////////////////////////////////////////
	void changeState(State* state);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Get application's console
	/// 
	/// This method allows you to display additional information in upper
	/// left corner of the window
	///
	/// \return Reference to application's output string stream
	///////////////////////////////////////////////////////////////////////////
	std::ostringstream& getConsole();

private:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Process events
	/// 
	/// This method processes events and delegates them to game state
	///////////////////////////////////////////////////////////////////////////
	void processEvents();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Update the application
	///
	/// This method is called at constant interval of time. It updates 
	/// application's logic
	///
	/// \param dt time since last update
	///////////////////////////////////////////////////////////////////////////
	void update(const sf::Time& dt);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Render window
	/// 
	/// This method renders window on the screen.
	///////////////////////////////////////////////////////////////////////////
	void render();

	// Application's window
	sf::RenderWindow window_;

	// Indicates wether window has focus
	bool hasFocus_;

	// Pointer to current game state
	std::unique_ptr<State> state_;

	// Console displaying useful information like frames per second
	// and updates per second. You can show more information with
	// getConsole() method
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

