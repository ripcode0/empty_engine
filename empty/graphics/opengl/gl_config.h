#pragma once

#include "wglad/wglad.h"
#include "core/typedef.h"

#define gl_is_bound(name, obj)          \
    glGetIntegerv(name, (obj))          \
    if(*(obj))                          \
    {                                   \
       bou \
    }                                   \

namespace emt
{
   namespace gl_transform
   {
      inline int get_topology(const topology& topology){
         switch (topology)
         {
         case topology::points: return GL_POINTS;
         case topology::lines: return GL_LINES;
         case topology::line_strip: return GL_LINE_STRIP;
         case topology::triangles: return GL_TRIANGLES;
         case topology::triangle_strip: return GL_TRIANGLE_STRIP;
         default:
            return -1;
         }
      };

      inline constexpr std::pair<uint, GLenum> get_gl_format(const emt::format& format)
      {
         switch (format)
         {
         case format::rgba8_sint:   return { 4, GL_BYTE};
         case format::rgba8_uint:  return { 4, GL_UNSIGNED_BYTE};
         case format::rgba16_float: return { 4, GL_HALF_FLOAT};
         case format::rgba16_uint: return {4, GL_UNSIGNED_SHORT};
         case format::rgb32_float: return {3, GL_FLOAT};
         case format::rgb32_sint: return {3, GL_INT};
         case format::rgb32_uint: return {3, GL_UNSIGNED_INT};
         case format::rgba32_float: return { 4, GL_FLOAT};
         case format::rgba32_uint: return { 4, GL_UNSIGNED_INT};
         case format::rgba32_sint: return { 4, GL_INT};
         default:
            assert(0 && "failed to convertion type");
            break;
         }
         return {0, 0};
      }
   } // namespace gl_transform
   
} // namespace emt


