#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "RenderComponent.h"

namespace  GameEngine
{
	class TextComponent : public RenderComponent
	{
	public:
		TextComponent();
		virtual ~TextComponent();

		virtual void Update() override;
		virtual void Render(sf::RenderTarget* target) override;

		void SetFont(std::string fontName_);
		void SetText(std::string text_, int size_, sf::Color color_);
		void SetText(std::string text_);
		void SetSize(int size_);
		void SetColor(sf::Color color_);

	private:
		sf::Text text;
		sf::Font font;

	};
}
#endif /