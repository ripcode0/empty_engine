#pragma once

#include "core/typedef.h"

namespace emt
{
    struct texture_buffer
    {
        uint tex{};
        uint64 tex_addr{};

        void create();
        
    };
    

} // namespace emt
