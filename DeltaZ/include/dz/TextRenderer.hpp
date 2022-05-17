#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <zgraphics/zgraphics.hpp>

#include <glad/glad.h>

class TextRenderer
{
public:
   void setLayout(zg::VertexLayout const& layout);
   void setViewProjection(zg::ViewProjection const* viewProjection) noexcept;

   void renderText(zg::Shader& shader, zg::Font const& font, std::string const& text,
                   glm::vec3 pos, float scale);

   TextRenderer() = default;

private:
   zg::VertexBuffer m_vbo;
   zg::IndexBuffer m_ebo;
   zg::VertexArray m_vao;

   zg::ViewProjection const* m_viewProjection;
};

#endif // TEXTRENDERER_HPP

