#include "Start.h"
#include "Utility.h"


Start_Screen::~Start_Screen()
{
    Mix_FreeMusic(m_state.bgm);
    Mix_FreeChunk(m_state.jump_sfx);
}

void Start_Screen::initialise()
{
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(0.0f);
    m_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    
    font_texture_id = Utility::load_texture("assets/font : background/font1.png");
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/GSS.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/00.wav");
    
}

void Start_Screen::update(float delta_time) {}


void Start_Screen::render(ShaderProgram *program)
{
    Utility::draw_text(program, font_texture_id, "THE BRAVE", 1.0f, 0.01f, glm::vec3(-4.0f,  1.0f, 0.0f));
    Utility::draw_text(program, font_texture_id, "Press enter to start", 0.4f, 0.0001f, glm::vec3(-4.0f, -1.0f, 0.0f));
}
