#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 18
#define LEVEL_HEIGHT 8

unsigned int LEVELA_DATA[] =
{
   24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 2, 2,
   24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 2, 2,
   24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 3,
   24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,24,24,24,24,
   24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   24, 0, 0, 0, 0, 0, 0, 0,26,31,26,29,26,27,29,32,33,31,
   24,26,27,28,29,26,29,27,26, 3, 2, 7, 3, 2, 3, 2, 7, 2,
    3, 2, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 3, 2,
};

LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/world/Overworld Tiles Pack/Tileset_1.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 11, 8);
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/sprites/player sprites/FETH Right.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[3] { 60, 61, 62 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 44, 45, 46, 47 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 10;
    m_state.player->m_animation_rows   = 8;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.6f);
    
    // Jumping
    m_state.player->m_jumping_power = 5.0f;
    
    // existing
    GLuint enemy_texture_id = Utility::load_texture("assets/sprites/enemy sprites/Knight-Sheet-W.png");
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(RUNNER);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    m_state.enemies[0].scale(glm::vec3(1.5f, 1.5f, 0.0f));
    m_state.enemies[0].set_position(glm::vec3(10.0f, 0.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(2.0f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.enemies[0].set_height(0.6f);
    m_state.enemies[0].set_width(0.4f);
    
    // walking animation set
    m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT] = new int[8] { 10, 11, 12, 13, 14, 15, 16, 17 };
    m_state.enemies[0].m_walking[m_state.enemies[0].LEFT]  = new int[8] { 30, 31, 32, 33, 34, 35, 36, 37 };
    
    // enemies start looking left
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].LEFT];
    m_state.enemies[0].m_animation_frames = 8;
    m_state.enemies[0].m_animation_index  = 0;
    m_state.enemies[0].m_animation_time   = 0.0f;
    m_state.enemies[0].m_animation_cols   = 10;
    m_state.enemies[0].m_animation_rows   = 24;
    
    // jumping
    m_state.enemies[0].m_jumping_power = 1.0f;
    
    // music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/concept_1.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/00.wav");
}

void LevelA::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, 0, 0, m_state.map);
    }
    
    if (m_state.player->get_position().x > 13.0f) m_state.next_scene_id = 1;
}


void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].render(program);
    }
}
