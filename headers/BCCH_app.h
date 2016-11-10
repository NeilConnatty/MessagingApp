//
// Created by Neil Connatty on 2016-11-04.
//

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "pubnub_interface.h"

#ifndef NITTY_BCCH_WINDOW_H
#define NITTY_BCCH_WINDOW_H

#define FOOTPEDAL_LEFT 12
#define FOOTPEDAL_MIDDLE 74
#define FOOTPEDAL_RIGHT 63

class BCCH_app
{
public:
    void Run ();

private:
    void handle_events (sf::RenderWindow &render_window, sf::Event &event);
    void render_screen (sf::RenderWindow &render_window);

private:
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 1280;

    sfg::SFGUI m_sfgui;
    sfg::Desktop m_desktop;
    pubnub_interface m_pn_interface;
};


#endif //NITTY_BCCH_WINDOW_H
