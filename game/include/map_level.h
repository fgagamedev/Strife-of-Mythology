#ifndef SOMTD_MAP_LEVEL_H
#define SOMTD_MAP_LEVEL_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/level.h>
#include <ijengine/texture.h>

#include <string>
#include <memory>
#include <fstream>

#include "player.h"

namespace SoMTD {
    class MapLevel : public ijengine::Level, public ijengine::GameEventsListener {
    public:
        MapLevel(const string& actual_map = "", const string& next_map = "", const string& audio_path = "");
        ~MapLevel();
        bool done() const;
        string next() const;
        string audio() const;
        int grid[80][80];
        void load_map_from_file();
        void load_tiles();
        bool on_event(const ijengine::GameEvent& event);
        void load_hud();
        void load_panels();

    protected:
        void draw_help_text(ijengine::Canvas *c);
        void update_self(unsigned now, unsigned last);
        void draw_self(ijengine::Canvas *canvas, unsigned now, unsigned last);

    private:
        std::string m_next;
        std::string m_current;
        std::string m_audio_path;
        bool m_done;
        Player *m_player;
        int m_start;
        std::shared_ptr< ijengine::Texture > m_texture;

        std::pair<int, int> screen_coordinates(int map_x, int map_y, int tw, int th);
    };
}

#endif

