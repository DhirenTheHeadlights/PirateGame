#include "UI/Menu/OptionsMenu.h"
#include "World/Architecture/GameState.h"

using namespace PirateGame;

// Set up the options menu
void OptionsMenu::setUpMenu() {
	// Set up the menu sprite
	menu.setTexture(Textures::optionsMenuTextures.getBackground());
	menu.setPosition(static_cast<float>(window->getSize().x / 2u) - menu.getGlobalBounds().getSize().x / 2, 
				     static_cast<float>(window->getSize().y / 2u) - menu.getGlobalBounds().getSize().y / 2);

	interactableTextSize = 30;

	// Set up the title text
	titleText = sf::Text("Options", font, textSize);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(menu.getPosition().x + menu.getGlobalBounds().getSize().x / 2 - titleText.getGlobalBounds().getSize().x / 2, 
						  menu.getPosition().y - titleText.getGlobalBounds().getSize().y - padding);

	// Add the interactables to the menu and set their positions
	addInteractablesToMenu();
	setInteractablePositions();
}

void OptionsMenu::setInteractablePositions() {
	// Set the positions of the tabs
	sf::Vector2f tabPosition = sf::Vector2f(menu.getPosition() + tabButtonPosition);
	for (auto& tab : tabButtons) {
		tab.setPosition(tabPosition);
		tabPosition.x += tab.getSprite().getGlobalBounds().getSize().x;
	}

	setTabInteractablePositions(generalTabInteractables);
	setTabInteractablePositions(graphicsTabInteractables);
	setTabInteractablePositions(audioTabInteractables);
	setTabInteractablePositions(controlsTabInteractables);
}

void OptionsMenu::setTabInteractablePositions(std::vector<std::unique_ptr<Interactable>>& tabInteractables) const {
	// Set the positions of the interactables to be under the menu
	sf::Vector2f leftPosition = sf::Vector2f(menu.getPosition() + leftColumnPosition);
	sf::Vector2f rightPosition = sf::Vector2f(menu.getPosition() + rightColumnPosition);

	for (const auto& interactable : tabInteractables) {
		interactable->setPosition(rightPosition);
		interactable->getText().setPosition(leftPosition + sf::Vector2f(leftBounds.x / 2, leftBounds.y / 2)
											- sf::Vector2f(interactable->getText().getGlobalBounds().getSize().x / 2,
											interactable->getText().getGlobalBounds().getSize().y / 2));
		const float offset = interactable->getSprite().getGlobalBounds().getSize().y;
		leftPosition.y += offset;
		rightPosition.y += offset;
	}
}

/// Tabs

void OptionsMenu::addInteractablesToMenu() {
	// Add the tabs to the menu
	addButton(sf::Text("General", font, interactableTextSize), Textures::optionsMenuTextures.getTab(), tabButtons, std::function([this] { currentTab = Tab::General; }));
	addButton(sf::Text("Graphics", font, interactableTextSize), Textures::optionsMenuTextures.getTab(), tabButtons, std::function([this] { currentTab = Tab::Graphics; }));
	addButton(sf::Text("Audio", font, interactableTextSize), Textures::optionsMenuTextures.getTab(), tabButtons, std::function([this] { currentTab = Tab::Audio; }));
	addButton(sf::Text("Controls", font, interactableTextSize), Textures::optionsMenuTextures.getTab(), tabButtons, std::function([this] { currentTab = Tab::Controls; }));

	// Create the back button
	const std::function backFunc = [this] {
		// Grab the global game state manager
		if (GameState::gameStarted) {
			GameState::changeGameState(GameState::State::GameLoop);
		} // Enter the game loop again if the game has started
		else {
			GameState::changeGameState(GameState::State::Start);
		}
		};
	addButton(sf::Text("Exit", font, interactableTextSize), Textures::optionsMenuTextures.getTab(), tabButtons, backFunc);

	addGeneralTabInteractables();
	addGraphicsTabInteractables();
	addAudioTabInteractables();
	addControlsTabInteractables();
}

/// Set up the interactables for the tabs

void OptionsMenu::addGeneralTabInteractables() {
	// Add the interactables to the general tab
	std::vector<std::pair<std::function<void()>, std::string>> screenPair;

	screenPair.push_back(std::make_pair(std::function([this] {
		// Set the game to fullscreen
		window->create(sf::VideoMode::getDesktopMode(), "Pirate Game", sf::Style::Fullscreen);
		}), "Fullscreen"));

	screenPair.push_back(std::make_pair(std::function([this] {
		// Set the game to windowed
		window->create(sf::VideoMode(1920, 1080), "Pirate Game", sf::Style::Default);
		}), "Windowed"));

	addDropDown(sf::Text("Screen", font, interactableTextSize), Textures::optionsMenuTextures.getDropDown(), generalTabInteractables, screenPair);

	std::vector<std::pair<std::function<void()>, std::string>> resolutionPair;

	resolutionPair.push_back(std::make_pair(std::function([this] {
		window->setSize(sf::Vector2u(1920, 1080));
		}), "1920x1080"));
	resolutionPair.push_back(std::make_pair(std::function([this] {
		window->setSize(sf::Vector2u(1600, 900));
		}), "1600x900"));
	resolutionPair.push_back(std::make_pair(std::function([this] {
		window->setSize(sf::Vector2u(1280, 720));
		}), "1280x720"));
	resolutionPair.push_back(std::make_pair(std::function([this] {
		window->setSize(sf::Vector2u(640, 480));
		}), "640x480"));

	addDropDown(sf::Text("Resolution", font, interactableTextSize), Textures::optionsMenuTextures.getDropDown(), generalTabInteractables, resolutionPair);
}

void OptionsMenu::addGraphicsTabInteractables() {
	// Add the interactables to the graphics tab
	addSlider(sf::Text("Brightness", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), graphicsTabInteractables,
		std::function([this](float value) { /*Implement later*/ }));

	addSlider(sf::Text("Gamma", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), graphicsTabInteractables,
		std::function([this](float value) { /*Implement later*/ }));

	std::vector<std::pair<std::function<void()>, std::string>> qualityPair;

	qualityPair.push_back(std::make_pair(std::function([this] {}), "Low"));
	qualityPair.push_back(std::make_pair(std::function([this] {}), "Medium"));
	qualityPair.push_back(std::make_pair(std::function([this] {}), "High"));

	addDropDown(sf::Text("Quality", font, interactableTextSize), Textures::optionsMenuTextures.getDropDown(), graphicsTabInteractables, qualityPair);

	std::vector<std::pair<std::function<void()>, std::string>> vsyncToggle;

	vsyncToggle.push_back(std::make_pair(std::function([this] {
		window->setVerticalSyncEnabled(true);
		}), "On"));
	vsyncToggle.push_back(std::make_pair(std::function([this] {
		window->setVerticalSyncEnabled(false);
		}), "Off"));

	addDropDown(sf::Text("VSync", font, interactableTextSize), Textures::optionsMenuTextures.getDropDown(), graphicsTabInteractables, vsyncToggle);
}

void OptionsMenu::addAudioTabInteractables() {
	// Add the interactables to the audio tab
	addSlider(sf::Text("Master Volume", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), audioTabInteractables,
		std::function([this](float value) { /*Implement later*/ }));

	addSlider(sf::Text("Music Volume", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), audioTabInteractables,
		std::function([this](float value) { /*Implement later*/ }));

	addSlider(sf::Text("SFX Volume", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), audioTabInteractables,
		std::function([this](const float value) { context.gsm->setSoundVolume(value); }));
}

void OptionsMenu::addControlsTabInteractables() {
	// Add the interactables to the controls tab
	addButton(sf::Text("Rebind", font, interactableTextSize), Textures::optionsMenuTextures.getRightInteractable(), controlsTabInteractables,
		std::function([this] { /*Implement later*/ }));
}

/// Draw/Interact with the menu

void OptionsMenu::interactWithMenuItems() {
	// Interact with the tabs
	for (auto& tab : tabButtons) {
		tab.interact(window,  context.gsm.get());
	}

	// Interact with the interactables for the current tab
	switch (currentTab) {
	case Tab::General:
		for (const auto& interactable : generalTabInteractables) {
			interactable->interact(window,  context.gsm.get());
		}
		break;
	case Tab::Graphics:
		for (const auto& interactable : graphicsTabInteractables) {
			interactable->interact(window,  context.gsm.get());
		}
		break;
	case Tab::Audio:
		for (const auto& interactable : audioTabInteractables) {
			interactable->interact(window,  context.gsm.get());
		}
		break;
	case Tab::Controls:
		for (const auto& interactable : controlsTabInteractables) {
			interactable->interact(window,  context.gsm.get());
		}
		break;
	default: ;
	}
}

void OptionsMenu::update() {
	interactWithMenuItems();
}

// Draw the menu
void OptionsMenu::draw() {
	// Draw the menu background
	window->draw(menu);
	window->draw(titleText);

	// Draw the tabs
	for (auto& tab : tabButtons) {
		tab.getText().setFillColor(sf::Color::White);
		tab.draw(window);
	}

	// Draw the interactables for the current tab
	switch (currentTab) {
	case Tab::General:
		drawTabInteractables(generalTabInteractables);
		break;
	case Tab::Graphics:
		drawTabInteractables(graphicsTabInteractables);
		break;
	case Tab::Audio:
		drawTabInteractables(audioTabInteractables);
		break;
	case Tab::Controls:
		drawTabInteractables(controlsTabInteractables);
		break;
	case Tab::Extra:
		break;
	default: ;
	}
}

// General function to draw the tab interactables
void OptionsMenu::drawTabInteractables(std::vector<std::unique_ptr<Interactable>>& tabInteractables) {
	// Draw the interactables in reverse order so that the top interactable is draw last
	// This means that the drop down menu will be drawn on top of the other interactables and will
	// be visible
	for (auto it = tabInteractables.rbegin(); it != tabInteractables.rend(); ++it) {
		(*it)->getText().setFillColor(sf::Color::Black);
		(*it)->draw(window);
	}
}
