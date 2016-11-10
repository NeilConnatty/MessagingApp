//
// Created by Neil Connatty on 2016-11-04.
//

#include "BCCH_app.h"
#include <SFML/Graphics.hpp>

void BCCH_app::send_message ()
{
    m_pn_interface.send_message(m_message_entry->GetText());
    m_message_entry->SetText("");
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
    sfg::Box::Ptr box;
    sfg::Box::Ptr box_1;
    sfg::Frame::Ptr frame;

    auto label = sfg::Label::Create("Input Message: ");
    label->SetClass("textSet");

    m_message_entry = sfg::Entry::Create();
    m_message_entry->SetClass("textSet");
    m_message_entry->SetRequisition(sf::Vector2f(850.0f, 0.0f));

    box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    box_1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    box_1->Pack(label);
    box_1->Pack(m_message_entry);
    box->Pack(box_1);
    box->Pack(init_button("Send Message", std::bind(&BCCH_app::send_message, this)));

    frame = sfg::Frame::Create("Messages");
    frame->SetClass("frame");
    frame->Add(box);
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Control Images");
    frame->SetClass("frame");
    box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    box->Pack(init_button("Show Image", std::bind(&pubnub_interface::show_image, &pn_interface)));
    box->Pack(init_button("Hide Image", std::bind(&pubnub_interface::hide_image, &pn_interface)));
    box->Pack(init_button("Zoom Image", std::bind(&pubnub_interface::zoom_image, &pn_interface)));
    box->Pack(init_button("Reload Image", std::bind(&pubnub_interface::reload_image, &pn_interface)));
    box_1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    box_1->Pack(init_button("Scroll Left", std::bind(&pubnub_interface::scroll_left, &pn_interface)));
    box_1->Pack(init_button("Scroll Right", std::bind(&pubnub_interface::scroll_right, &pn_interface)));
    box->Pack(box_1);
    frame->Add(box);
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Take Image");
    frame->SetClass("frame");
    frame->Add(init_button("Take and Upload Image", std::bind(&pubnub_interface::upload_image, &pn_interface)));
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Control View");
    frame->SetClass("frame");
    frame->Add(init_button("Flip View", std::bind(&pubnub_interface::flip_view, &pn_interface)));
    widgets.push_back(frame);

    box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    for (int i=0; i<widgets.size(); i++) {
        box->PackEnd(widgets[i]);
    }

    auto window = sfg::Window::Create();
    window->SetStyle(~sfg::Window::Style::RESIZE & ~sfg::Window::Style::CLOSE & sfg::Window::Style::TOPLEVEL & ~sfg::Window::Style::TITLEBAR);
    window->SetTitle("BCCH SmartGlasses Controller App");
    window->Add(box);
    window->SetRequisition(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    window->SetClass("textSet");

    m_desktop.Add(window);
    m_desktop.SetProperty(".textSet", "FontSize", FONT_SIZE);
    m_desktop.SetProperty(".frame", "FontSize", FRAME_FONT_SIZE);
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
    sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BCCH SmartGlasses Controller", sf::Style::Titlebar | sf::Style::Close);
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