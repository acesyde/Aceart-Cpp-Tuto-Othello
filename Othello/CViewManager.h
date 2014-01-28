#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <SFML/Graphics.hpp>

class CViewManager
{
    public:
        CViewManager(sf::RenderWindow &App);
        virtual ~CViewManager();
        sf::View & toggleMenu();
        bool getState();
        sf::Vector2f getMenuCenter();
    private:
        sf::View *board;
        sf::View *menu;

        bool etatJeux;
};

#endif // CVIEWMANAGER_H
