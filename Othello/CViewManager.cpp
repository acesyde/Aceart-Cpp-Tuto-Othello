#include "CViewManager.h"

CViewManager::CViewManager(sf::RenderWindow &App)
{
    board = &App.GetDefaultView();
    menu = new sf::View(sf::FloatRect(App.GetWidth(),0,App.GetWidth()*2,App.GetHeight()));
    etatJeux = true;
}

CViewManager::~CViewManager()
{
    delete board;
    delete menu;
}

sf::View & CViewManager::toggleMenu() {
    etatJeux = !etatJeux;
    return (etatJeux)?*board:*menu;
}

bool CViewManager::getState() {
    return etatJeux;
}

sf::Vector2f CViewManager::getMenuCenter() {
    return menu->GetCenter();
}
