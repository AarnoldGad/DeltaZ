#ifndef RESULTLAYER_HPP
#define RESULTLAYER_HPP

#include "dz/TextRenderer.hpp"
#include "dz/Grid.hpp"
#include "dz/Geometry.hpp"

#include <zgraphics/zgraphics.hpp>

class ResultLayer
{
public:
   void load(Geometry const& geometry, Grid const& grid);

   void render();

   ResultLayer(zg::Window* window);

private:
   void configureRenderers();
   void loadResources();

   void loadResults(Grid const& results);
   void loadGeometry(Geometry const& geometry);

   std::unique_ptr<zg::DefaultRenderer> m_renderer;
   std::unique_ptr<TextRenderer> m_textRenderer;

   zg::Window* m_window;

   zg::Shader* m_shader;
   zg::Shader* m_textShader;
   zg::Font* m_font;

   unsigned int m_elementCount;
   zg::VertexBuffer m_shapeVBO;
   zg::IndexBuffer m_shapeEBO;
   zg::VertexArray m_shapeVAO;

   unsigned int m_gridPoints;
   zg::VertexBuffer m_gridVBO;
   zg::VertexArray m_gridVAO;

   zg::OrthographicCamera m_camera;
};

#endif // RESULTLAYER_HPP

