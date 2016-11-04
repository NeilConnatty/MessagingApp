//
// Created by Neil Connatty on 2016-11-04.
//

#include "BCCH_app.h"
#include <SFML/Graphics.hpp>

void BCCH_app::send_message ()
{
    m_pn_interface.send_message(m_label->GetText());
}

void BCCH_app::init_widgets (pubnub_interface &pn_interface)
{
    m_label = sfg::Label::Create("Input Message");
    m_label->SetClass("textSet");

    m_send_message_button = sfg::Button::Create("Send Message");
    m_send_message_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&BCCH_app::send_message, this));
    m_send_message_button->SetClass("textSet");

    m_show_image_button = sfg::Button::Create("Show Image");
    m_show_image_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&pubnub_interface::show_image, &pn_interface));
    m_show_image_button->SetClass("textSet");

    m_hide_image_button = sfg::Button::Create("Hide Image");
    m_hide_image_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&pubnub_interface::hide_image, &pn_interface));
    m_hide_image_button->SetClass("textSet");

    m_zoom_image_button = sfg::Button::Create("Zoom Image");
    m_zoom_image_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&pubnub_interface::zoom_image, &pn_interface));
    m_zoom_image_button->SetClass("textSet");

    m_reload_image_button = sfg::Button::Create("Reload Image");
    m_reload_image_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&pubnub_interface::reload_image, &pn_interface));
    m_reload_image_button->SetClass("textSet");

    m_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    m_box->Pack(m_label);
    m_box->Pack(m_send_message_button);
    m_box->Pack(m_show_image_button);
    m_box->Pack(m_hide_image_button);
    m_box->Pack(m_zoom_image_button);
    m_box->Pack(m_reload_image_button);

    m_window = sfg::Window::Create();
    m_window->SetTitle("BCCH SmartGlasses Controller App");
    m_window->Add(m_box);
    m_window->SetRequisition(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    m_window->SetClass("textSet");

    m_desktop.Add(m_window);
    m_desktop.SetProperty(".textSet", "FontSize", FONT_SIZE);
}

void BCCH_app::Run ()
{
    sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BCCH", sf::Style::Titlebar | sf::Style::Close);
    render_window.resetGLStates();

    init_widgets(m_pn_interface);

    sf::Event event;
    sf::Clock clock;

    while (render_window.isOpen()) {
        while (render_window.pollEvent(event)) {
            m_desktop.HandleEvent(event);
            if (event.type == sf::Event::Closed) {
                render_window.close();
            }

            m_desktop.Update(clock.restart().asSeconds());

            render_window.clear();
            m_sfgui.Display(render_window);
            render_window.display();
        }
    }
}