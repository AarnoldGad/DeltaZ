#ifndef RESULTRENDERER_HPP
#define RESULTRENDERER_HPP

#include <bitset>
#include <zgraphics/zgraphics.hpp>

enum class Primitives
{
   Points, Lines, LineStrip, Triangles, TriangleStrip, TriangleFan
};

// TODO Figure out a way to make type sage flag enums (bitset ?)
enum RenderOptions : uint32_t
{
   InBlack = FLAG(0),
   InColor = FLAG(1)
};

class ResultRenderer
{
public:
   void setLayout(zg::VertexLayout const& layout);
   void setViewProjection(zg::ViewProjection const* viewProjection) noexcept;

   void submit(zg::Mesh const* mesh, glm::mat4 transform = glm::mat4(1.f));
   void render(zg::Shader* shader, RenderOptions options, Primitives primitive = Primitives::Triangles);

   ResultRenderer() = default;

private:
   zg::VertexArray m_vao;
   zg::VertexBuffer m_vbo;
   zg::IndexBuffer m_ebo;

   zg::ViewProjection const* m_viewProjection;
   std::map<zg::Mesh const*, glm::mat4> m_objects;
};

#endif // RESULTRENDERER_HPP

