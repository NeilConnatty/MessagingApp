//
// Created by Neil Connatty on 2016-11-04.
//

#include "BCCH_app.h"
#include <SFML/Graphics.hpp>

void BCCH_app::send_message ()
{
    m_pn_interface.send_message(m_entry->GetText());
    m_entry->SetText("");
}

sfg::Button::Ptr BCCH_app::init_button (std::string name, std::function<void()> delegate)
{
    auto button = sfg::Button::Create(name);
    button->GetSignal(sfg::Widget::OnLeftClick).Connect(delegate);
    button->SetClass("textSet");
    return button;
}

void BCCH_app::init_widgets (pubnub_interface &pn_interface)
{
    m_label = sfg::Label::Create("Input Message: ");
    m_label->SetClass("textSet");

    m_entry = sfg::Entry::Create();
    m_entry->SetClass("textSet");
    m_entry->SetRequisition(sf::Vector2f(800.0f, 0.0f));

    auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    box->Pack(m_label);
    box->Pack(m_entry);

    buttons.push_back(init_button("Send Message", std::bind(&BCCH_app::send_message, this)));
    buttons.push_back(init_button("Show Image", std::bind(&pubnub_interface::show_image, &pn_interface)));
    buttons.push_back(init_button("Hide Image", std::bind(&pubnub_interface::hide_image, &pn_interface)));
    buttons.push_back(init_button("Zoom Image", std::bind(&pubnub_interface::zoom_image, &pn_interface)));
    buttons.push_back(init_button("Reload Image", std::bind(&pubnub_interface::reload_image, &pn_interface)));
    buttons.push_back(init_button("Upload Image", std::bind(&pubnub_interface::upload_image, &pn_interface)));
    buttons.push_back(init_button("Scroll Left", std::bind(&pubnub_interface::scroll_left, &pn_interface)));
    buttons.push_back(init_button("Scroll Right", std::bind(&pubnub_interface::scroll_right, &pn_interface)));
    buttons.push_back(init_button("Flip View", std::bind(&pubnub_interface::flip_view, &pn_interface)));

    m_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    m_box->Pack(box);
    for (int i=0; i<buttons.size(); i++) {
        m_box->Pack(buttons[i]);
    }

    m_window = sfg::Window::Create();
    m_window->SetStyle(~sfg::Window::Style::RESIZE & ~sfg::Window::Style::CLOSE & sfg::Window::Style::TOPLEVEL & ~sfg::Window::Style::TITLEBAR);
    m_window->SetTitle("BCCH SmartGlasses Controller App");
    m_window->Add(m_box);
    m_window->SetRequisition(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    m_window->SetClass("textSet");

    m_desktop.Add(m_window);
    m_desktop.SetProperty(".textSet", "FontSize", FONT_SIZE);
}

void BCCH_app::handle_events (sf::RenderWindow &render_window, sf::Event &event)
{
    while (render_window.pollEvent(event)) {
        m_desktop.HandleEvent(event);
        if (event.type == sf::Event::Closed) {
            render_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == FOOTPEDAL_LEFT) {
                std::cout << "footpedal left pressed" << std::endl;
                m_pn_interface.show_image();
            } else if (event.key.code == FOOTPEDAL_MIDDLE) {
                std::cout << "footpedal middle pressed" << std::endl;
                m_pn_interface.zoom_image();
            } else if (event.key.code == FOOTPEDAL_RIGHT) {
                std::cout << "footpedal right pressed" << std::endl;
                m_pn_interface.reload_image();
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
    sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BCCH SmartGlasses Controller App", sf::Style::Titlebar | sf::Style::Close);
    render_window.resetGLStates();
    render_window.setFramerateLimit(60);

    init_widgets(m_pn_interface);

    sf::Event event;
    sf::Clock clock;

    while (render_window.isOpen()) {
        handle_events(render_window, event);
        m_desktop.Update(clock.restart().asSeconds());
        render_screen(render_window);
    }
}