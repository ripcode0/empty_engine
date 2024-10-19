#pragma once

#define debug_obj(x, xx)

#if defined(_DEBUG)
#define set_name(x, xx) if(x) { x->set_name_t(xx); } 
#else
#define set_name(x, xx) 
#endif