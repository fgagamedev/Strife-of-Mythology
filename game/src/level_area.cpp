#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>

#include "level_area.h"

SoMTD::LevelArea::LevelArea(std::string texture_name, unsigned id, int x, int y, int p) :
    m_texture(ijengine::resources::get_texture(texture_name)),
    m_id(id),
    m_x(x),
    m_y(y),
    m_priority(p)
{
    m_start = -1;
    ijengine::event::register_listener(this);
}

SoMTD::LevelArea::~LevelArea()
{
    ijengine::event::unregister_listener(this);
}

bool
SoMTD::LevelArea::on_event(const ijengine::GameEvent&)
{
    return false;
}

void
SoMTD::LevelArea::draw_self(ijengine::Canvas *canvas, unsigned, unsigned)
{
    std::pair<int, int> p = screen_coordinates(m_x, m_y, 100, 58);
    int x_pos = p.first;
    int y_pos = p.second;

    // x0 = half of window width, the coeficient for the isometry
    int x0 = 1024/2;
    int y0 = 29;
    canvas->draw(m_texture.get(), x_pos + x0 - m_texture->w()/2, y_pos + y0);
    // printf("tile, priority: %d\n", m_priority);
}

void
SoMTD::LevelArea::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;
    if (now - m_start > 5000)
        m_done = true;
}

std::pair<int, int>
SoMTD::LevelArea::screen_coordinates(int map_x, int map_y, int tw, int th)
{
    int xs = (map_x - map_y) * (tw / 2);
    int ys = (map_x + map_y) * (th / 2);

    return std::pair<int, int>(xs, ys);
}

