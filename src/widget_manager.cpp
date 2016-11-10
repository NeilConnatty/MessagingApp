//
// Created by Neil Connatty on 2016-11-10.
//

#include "widget_manager.h"

widget_manager::widget_manager () : widgets(5)
{
}

void widget_manager::send_message ()
{
    m_pn_interface.send_message(m_message_entry->GetText());
    m_message_entry->SetText("");
}

sfg::Button::Ptr widget_manager::init_button (std::string name, std::function<void()> delegate)
{
    auto button = sfg::Button::Create(name);
    button->GetSignal(sfg::Widget::OnLeftClick).Connect(delegate);
    button->SetClass("textSet");
    return button;
}

sfg::Box::Ptr widget_manager::create_box(sfg::Box::Orientation orientation)
{
    return sfg::Box::Create(orientation, 5.0f);
}

sfg::Box::Ptr widget_manager::create_horizontal_box ()
{
    return create_box(sfg::Box::Orientation::HORIZONTAL);
}

sfg::Box::Ptr widget_manager::create_vertical_box ()
{
    return create_box(sfg::Box::Orientation::VERTICAL);
}

void widget_manager::init_widgets (sfg::Desktop &desktop, int screen_width, int screen_height)
{
    sfg::Box::Ptr box;
    sfg::Box::Ptr box_1;
    sfg::Frame::Ptr frame;

    auto label = sfg::Label::Create("Input Message: ");
    label->SetClass("textSet");

    m_message_entry = sfg::Entry::Create();
    m_message_entry->SetClass("textSet");
    m_message_entry->SetRequisition(sf::Vector2f(850.0f, 0.0f));

    box = create_vertical_box();
    box_1 = create_horizontal_box();
    box_1->Pack(label);
    box_1->Pack(m_message_entry);
    box->Pack(box_1);
    box->Pack(init_button("Send Message", std::bind(&widget_manager::send_message, this)));

    frame = sfg::Frame::Create("Messages");
    frame->SetClass("frame");
    frame->Add(box);
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Control Images");
    frame->SetClass("frame");
    box = create_vertical_box();
    box->Pack(init_button("Show Image", std::bind(&pubnub_interface::show_image, &m_pn_interface)));
    box->Pack(init_button("Hide Image", std::bind(&pubnub_interface::hide_image, &m_pn_interface)));
    box->Pack(init_button("Zoom Image", std::bind(&pubnub_interface::zoom_image, &m_pn_interface)));
    box->Pack(init_button("Reload Image", std::bind(&pubnub_interface::reload_image, &m_pn_interface)));
    box_1 = create_horizontal_box();
    box_1->Pack(init_button("Scroll Left", std::bind(&pubnub_interface::scroll_left, &m_pn_interface)));
    box_1->Pack(init_button("Scroll Right", std::bind(&pubnub_interface::scroll_right, &m_pn_interface)));
    box->Pack(box_1);
    frame->Add(box);
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Take Image");
    frame->SetClass("frame");
    frame->Add(init_button("Take and Upload Image", std::bind(&pubnub_interface::upload_image, &m_pn_interface)));
    widgets.push_back(frame);

    frame = sfg::Frame::Create("Control View");
    frame->SetClass("frame");
    frame->Add(init_button("Flip View", std::bind(&pubnub_interface::flip_view, &m_pn_interface)));
    widgets.push_back(frame);

    box = create_vertical_box();
    for (int i=0; i<widgets.size(); i++) {
        box->PackEnd(widgets[i]);
    }

    auto window = sfg::Window::Create();
    window->SetStyle(~sfg::Window::Style::RESIZE & ~sfg::Window::Style::CLOSE & sfg::Window::Style::TOPLEVEL & ~sfg::Window::Style::TITLEBAR);
    window->SetTitle("BCCH SmartGlasses Controller App");
    window->Add(box);
    window->SetRequisition(sf::Vector2f(screen_width, screen_height));
    window->SetClass("textSet");

    desktop.Add(window);
    desktop.SetProperty(".textSet", "FontSize", FONT_SIZE);
    desktop.SetProperty(".frame", "FontSize", FRAME_FONT_SIZE);
}