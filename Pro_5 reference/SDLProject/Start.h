#include "Scene.h"

class Start_Screen : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    GLuint font_texture_id;
    
    // ————— CONSTRUCTOR ————— //
    ~Start_Screen();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
