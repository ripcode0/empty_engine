#pragma once

#include "scene/scene.h"
#include "core/typedef.h"

namespace emt
{
    class triangle_scene : public scene
    {
    public:
        triangle_scene() = default;

        void init_frame() override;
        void update_frame(float dt) override;
        void render_frame() override;
        void release_frame() override;

        ibuffer* m_vbo{};
        ibuffer* m_ibo{};
        input_layout* m_input_layout{};
        shader* m_vs;
        shader* m_ps;

    };    
} // namespace emt

