//
// Created by Neil Connatty on 2016-11-04.
//

#include "BCCH_app.h"
#include <widget_manager.h>

BCCH_app::BCCH_app() :
    l_pedal_pressed(false)
{
}

void BCCH_app::handle_events (sf::RenderWindow &render_window, sf::Event &event)
{
    while (render_window.pollEvent(event)) {
        m_desktop.HandleEvent(event);
        if (event.type == sf::Event::Closed) {
            render_window.close();
        }
        // Handle footpedal presses
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == FOOTPEDAL_LEFT) {
                std::cout << "footpedal left pressed" << std::endl;
                l_pedal_pressed = !l_pedal_pressed;
                m_pn_interface.toggle_function();
            } else if (event.key.code == FOOTPEDAL_MIDDLE) {
                std::cout << "footpedal middle pressed" << std::endl;
                if (l_pedal_pressed) {
                    m_pn_interface.scroll_left();
                } else {
                    m_pn_interface.zoom_image();
                }
            } else if (event.key.code == FOOTPEDAL_RIGHT) {
                std::cout << "footpedal right pressed" << std::endl;
                if (l_pedal_pressed) {
                    m_pn_interface.scroll_right();
                } else {
                    m_pn_interface.hide_or_show_image();
                }
            }
        }
    }
}

void BCCH_app::render_screen (sf::RenderWindow &render_window)
{
    render_window.clear();
    m_sfgui.Display(render_window);
    render_window.display();
}

void BCCH_app::Run ()
{
    sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BCCH SmartGlasses Controller", sf::Style::Titlebar | sf::Style::Close);
    render_window.resetGLStates();
    render_window.setFramerateLimit(60);

    widget_manager w_manager;
    w_manager.init_window(m_desktop, SCREEN_WIDTH, SCREEN_HEIGHT);

    sf::Event event;
    sf::Clock clock;

    while (render_window.isOpen()) {
        handle_events(render_window, event);
        m_desktop.Update(clock.restart().asSeconds());
        render_screen(render_window);
    }
}