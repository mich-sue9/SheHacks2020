#include "TextComponent.h"
#include "Game/GameBoard.h"
#include <iostream>


GameEngine::TextComponent::TextComponent()
{

}

GameEngine::TextComponent::~TextComponent()
{

}

void GameEngine::TextComponent::Update()
{

}

void GameEngine::TextComponent::Render(sf::RenderTarget* target)
{
	__super::Render(target);

	if (!target)
	{
		return;
	}

	//After the values are set, render itself is pretty simple
	text.setPosition(GetEntity()->GetPos());
	text.setRotation(GetEntity()->GetRot());

	target->draw(text);
}

void GameEngine::TextComponent::SetFont(std::string fontName_)
{
	if (!font.loadFromFile("Resources/fonts/arial.ttf"))
	{
		//error
		return;
	}

	// select the font
	text.setFont(font); // font is a sf::Font
}

void GameEngine::TextComponent::SetText(std::string text_, int size_, sf::Color color_)
{
	SetText(text_);
	SetSize(size_);
	SetColor(color_);

}

void GameEngine::TextComponent::SetText(std::string text_)
{
	// set the string to display
	text.setString(text_);
}

void GameEngine::TextComponent::SetSize(int size_)
{
	// set the character size
	text.setCharacterSize(size_); // in pixels, not points!
}

void GameEngine::TextComponent::SetColor(sf::Color color_)
{
	// set the color
	text.setFillColor(color_);
}