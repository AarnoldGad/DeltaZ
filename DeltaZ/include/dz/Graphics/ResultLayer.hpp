#ifndef RESULTLAYER_HPP
#define RESULTLAYER_HPP

#include "dz/Graphics/TextRenderer.hpp"
#include "dz/Graphics/ResultRenderer.hpp"
#include "dz/Graphics/GeometryShape.hpp"
#include "dz/Graphics/GridShape.hpp"
#include "dz/Graphics/Legend.hpp"

#include "dz/Solver/Grid.hpp"
#include "dz/Solver/Geometry.hpp"

#include <zgraphics/zgraphics.hpp>

class ResultLayer
{
public:
   void load(Geometry const& geometry, Grid const& grid);

   void render();

   ResultLayer(zg::Window* window);

private:
   void configureEventsHandler();
   void configureRenderers();
   void loadResources();
   void configureCamera(Grid const& grid);

   void handleEvent(ze::Event& event);

   std::unique_ptr<ResultRenderer> m_renderer;
   std::unique_ptr<TextRenderer> m_textRenderer;

   zg::Window* m_window;

   zg::Shader* m_shader;
   zg::Shader* m_shader3D;
   zg::Shader* m_textShader;
   zg::Font* m_font;

   GeometryShape m_geometryShape;
   GridShape m_gridShape;
   Legend m_legend;

   bool m_grabbed;
   glm::ivec2 m_previousMousePos;
   glm::vec2 m_gridCenter;
   float m_gridWidth;

   zg::Transform m_3Dtransform;
   zg::Camera m_camera;
   zg::OrthographicCamera m_ortho;
};

#endif // RESULTLAYER_HPP

