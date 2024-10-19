#pragma once

namespace emt
{
    class scene
    {
    public:
        scene(){};
        virtual~scene(){};

        virtual void init_frame() = 0;
        virtual void update_frame(float dt) = 0;
        virtual void render_frame() = 0;
        virtual void release_frame() = 0;
    };
    
} // namespace emt
