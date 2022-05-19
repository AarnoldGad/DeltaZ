#include "dz/ResultLayer.hpp"

#include "dz/NodeVertex.hpp"

ResultLayer::ResultLayer(zg::Window* window)
   : m_window(window), m_shader(nullptr), m_textShader(nullptr), m_font(nullptr),
     m_camera({ 1.f, 1.f }) {}

void ResultLayer::load(Geometry const& geometry, Grid const& grid)
{
   loadResources();
   configureRenderers();
   loadGeometry(geometry);
   loadResults(grid);
}

void ResultLayer::render()
{
   m_shader->use();
   m_shader->setMatrix4("view", m_camera.getViewMatrix());
   m_shader->setMatrix4("projection", m_camera.getProjectionMatrix());

   m_shapeVAO.bind();

   glDrawElements(GL_LINE_STRIP, m_elementCount, GL_UNSIGNED_INT, 0);

   m_gridVAO.bind();
   glDrawArrays(GL_POINTS, 0, m_gridPoints);
}

void ResultLayer::loadGeometry(Geometry const& geometry)
{
   m_shapeVAO.bind();

   m_shapeVBO.resize(geometry.getNodes().size() * sizeof(NodeVertex));
   m_shapeEBO.resize((geometry.getNodes().size() + 1) * sizeof(unsigned int));

   m_elementCount = geometry.getNodes().size() + 1;
   {
      unsigned int* buffer = m_shapeEBO.map<unsigned int>();

      for (int element = 0; element < geometry.getNodes().size(); ++element)
         buffer[element] = element;
      buffer[geometry.getNodes().size()] = 0;

      m_shapeEBO.unmap();
   }

   {
      int i = 0;
      float* buffer = m_shapeVBO.map<float>();
      for (auto const& node : geometry.getNodes())
      {
         buffer[i * 3 + 0] = node.getPosition().x;
         buffer[i * 3 + 1] = node.getPosition().y;
         buffer[i * 3 + 2] = node.getValue();
         ++i;
      }
      m_shapeVBO.unmap();
   }
}

void ResultLayer::loadResults(Grid const& results)
{
   glm::vec2 center = { (results.getBounds().z + results.getBounds().x) / 2.f,
                        (results.getBounds().w + results.getBounds().y) / 2.f };
   float largest = (results.getBounds().z - results.getBounds().x < results.getBounds().w - results.getBounds().y) ?
                   results.getBounds().w - results.getBounds().y : results.getBounds().z - results.getBounds().x;
   float aspectRatio = (float) m_window->getSize().x / (float) m_window->getSize().y;
   largest += 1.f;
   m_camera.setSize({ largest * aspectRatio, largest });

   m_camera.setCentre(center);

   m_gridVAO.bind();

   m_gridVBO.resize(results.getNodes().size() * sizeof(NodeVertex));

   m_gridPoints = results.getNodes().size();
   {
      int i = 0;
      float* buffer = m_gridVBO.map<float>();
      for (auto const& node : results.getNodes())
      {
         buffer[i * 3 + 0] = node.second.getPosition().x;
         buffer[i * 3 + 1] = node.second.getPosition().y;
         buffer[i * 3 + 2] = node.second.getValue();
         ++i;
      }
      m_gridVBO.unmap();
   }
}

void ResultLayer::configureRenderers()
{
   m_renderer = std::make_unique<zg::DefaultRenderer>();
   m_textRenderer = std::make_unique<TextRenderer>();

   zg::VertexLayout layout;
   layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
   layout.add(zg::VertexAttribute::Type::Float, "vValue");

   m_shapeVBO.bind();
   m_shapeVAO.setLayout(layout);

   m_gridVBO.bind();
   m_gridVAO.setLayout(layout);

   glEnable(GL_PROGRAM_POINT_SIZE);

   zg::VertexLayout layout2;
   layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
   layout.add(zg::VertexAttribute::Type::Vec4, "vColor");
   layout.add(zg::VertexAttribute::Type::Vec2, "vTexCoord");
   
   m_textRenderer->setLayout(layout2);
   m_textRenderer->setViewProjection(&m_camera);

   m_renderer->setLayout(layout2);
   m_renderer->setViewProjection(&m_camera);
}

void ResultLayer::loadResources()
{
   ze::ResourceManager<zg::Shader>::AddSearchPath("assets/shaders");
   ze::ResourceManager<zg::Font>::AddSearchPath("assets/fonts");

   m_shader = ze::ResourceManager<zg::Shader>::Load("node", "node.vs", "node.fs");
   m_textShader = ze::ResourceManager<zg::Shader>::Load("text", "default.vs", "text.fs");
   m_font = ze::ResourceManager<zg::Font>::Load("arial", zg::FontFile("Arial.ttf"), 48);
}

