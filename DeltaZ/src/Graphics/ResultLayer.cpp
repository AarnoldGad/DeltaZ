#include "dz/Graphics/ResultLayer.hpp"

#include "dz/Graphics/NodeVertex.hpp"

ze::EventBus* GetEventBus();

ResultLayer::ResultLayer(zg::Window* window)
   : m_window(window), m_shader(nullptr), m_textShader(nullptr), m_font(nullptr),
     m_grabbed(false), m_camera(ze::degrees(70.f)), m_ortho({ 1.f, 1.f }) {}

void ResultLayer::load(Geometry const& geometry, Grid const& grid)
{
   configureEventsHandler();
   loadResources();
   configureRenderers();
   configureCamera(grid);
   m_geometryShape.setGeometry(geometry);
   m_gridShape.setGrid(grid);
   m_legend.setBounds(m_gridWidth / 2.f, m_geometryShape.getMinValue(), m_geometryShape.getMaxValue());
}

void ResultLayer::render()
{
   glm::ivec2 fbSize = m_window->getFramebufferSize();

   m_shader->use();
   m_shader->setFloat("minValue", m_geometryShape.getMinValue());
   m_shader->setFloat("maxValue", m_geometryShape.getMaxValue());

   m_shader3D->use();
   m_shader3D->setFloat("minValue", m_geometryShape.getMinValue());
   m_shader3D->setFloat("maxValue", m_geometryShape.getMaxValue());

   glDisable(GL_DEPTH_TEST);
   // Render top right: shape outline and grid points
   glViewport(fbSize.x / 2, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
   m_renderer->setViewProjection(&m_ortho);
   m_renderer->submit(&m_gridShape);
   m_renderer->render(m_shader, RenderOptions::InBlack, Primitives::Points);
   m_renderer->submit(&m_geometryShape);
   m_renderer->render(m_shader, RenderOptions::InColor, Primitives::Lines);

   // Render top left: level-rendering
   glViewport(0, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
   m_renderer->submit(&m_gridShape);
   m_renderer->render(m_shader, RenderOptions::InColor, Primitives::Triangles);
   m_renderer->submit(&m_geometryShape);
   m_renderer->render(m_shader, RenderOptions::InBlack, Primitives::Lines);

   // Render bottom right legend
   glViewport(fbSize.x / 2, 0, fbSize.x / 2, fbSize.y / 2);
   m_renderer->submit(&m_legend);
   m_renderer->render(m_shader, RenderOptions::InColor, Primitives::Triangles);
   m_renderer->submit(&m_legend);
   m_renderer->render(m_shader, RenderOptions::InBlack, Primitives::LineStrip);

   m_textRenderer->renderText(*m_textShader, *m_font, std::to_string(m_geometryShape.getMaxValue()), { m_gridWidth * 0.1f, 0.f, 0.f }, 0.002f);
   m_textRenderer->renderText(*m_textShader, *m_font, std::to_string(m_geometryShape.getMinValue()), { m_gridWidth * 0.1f, m_gridWidth / 2.f, 0.f }, 0.002f);

   glEnable(GL_DEPTH_TEST);
   // Render bottom left: 3D perspective
   glViewport(0, 0, fbSize.x / 2, fbSize.y / 2);
   m_renderer->setViewProjection(&m_camera);
   m_renderer->submit(&m_geometryShape, m_3Dtransform.getTransformationMatrix());
   m_renderer->render(m_shader, RenderOptions::InBlack, Primitives::Lines);

   m_renderer->submit(&m_gridShape, m_3Dtransform.getTransformationMatrix());
   m_renderer->render(m_shader3D, RenderOptions::InColor, Primitives::Triangles);
}

void ResultLayer::handleEvent(ze::Event& event)
{
   glm::ivec2 winSize = m_window->getSize();
   bool isIn3DSpace;
   if (zg::Mouse::GetPosition().x > winSize.x / 2
    || zg::Mouse::GetPosition().x < 0
    || zg::Mouse::GetPosition().y < winSize.y / 2
    || zg::Mouse::GetPosition().y > winSize.y)
      isIn3DSpace = false;
   else
      isIn3DSpace = true;

   ze::EventDispatcher dispatcher(event);

   dispatcher.dispatch<zg::MouseButtonEvent>([&] (zg::MouseButtonEvent& event)
         {
            if (event.getAction() == zg::MouseButtonEvent::Action::Pressed
             && event.getButton() == zg::Mouse::Button::Left && isIn3DSpace)
            {
               m_grabbed = true;
               zg::Mouse::SetCursorMode(zg::Mouse::CursorMode::Disabled);
               m_previousMousePos = zg::Mouse::GetPosition();
            }
            if (event.getAction() == zg::MouseButtonEvent::Action::Released
             && event.getButton() == zg::Mouse::Button::Left)
            {
               m_grabbed = false;
               zg::Mouse::SetCursorMode(zg::Mouse::CursorMode::Normal);
            }
         });

   // TODO TPS View
   dispatcher.dispatch<zg::MouseMovedEvent>([&] (zg::MouseMovedEvent& event)
         {
            if (m_grabbed)
            {
               glm::ivec2 offset = m_previousMousePos - event.getPosition();
               if (offset.x)
                  m_3Dtransform.rotate(ze::degrees(3.f), { 0.f, -offset.x, 0.f });
               if (offset.y)
                  m_3Dtransform.rotate(ze::degrees(3.f), { offset.y, 0.f, 0.f });
               m_previousMousePos = event.getPosition();
            }
         });

   dispatcher.dispatch<zg::MouseScrolledEvent>([&] (zg::MouseScrolledEvent& event)
         {
            if (isIn3DSpace)
               m_camera.setFieldOfView(m_camera.getFieldOfView() + (ze::degrees(1.f) * event.getVerticalOffset()));

            if (m_camera.getFieldOfView() < ze::degrees(10.f))
               m_camera.setFieldOfView(ze::degrees(11.f));

            if (m_camera.getFieldOfView() > ze::degrees(120.f))
               m_camera.setFieldOfView(ze::degrees(119.f));
         });

   dispatcher.dispatch<zg::WindowResisedEvent>([&] (zg::WindowResisedEvent& event)
         {
            float aspectRatio = (float) m_window->getSize().x / (float) m_window->getSize().y;
            m_ortho.setSize({ m_gridWidth * aspectRatio, m_gridWidth });
            m_ortho.setCentre(m_gridCenter);

            m_3Dtransform.setScale({ 1.f / m_gridWidth, -1.f / m_gridWidth, 1.f / m_gridWidth });
            m_camera.setAspectRatio(aspectRatio);
         });
}

void ResultLayer::configureCamera(Grid const& results)
{
   m_gridCenter = { (results.getBounds().z + results.getBounds().x) / 2.f,
                    (results.getBounds().w + results.getBounds().y) / 2.f };
   m_gridWidth = (results.getBounds().z - results.getBounds().x < results.getBounds().w - results.getBounds().y) ?
                  results.getBounds().w - results.getBounds().y : results.getBounds().z - results.getBounds().x;

   float aspectRatio = (float) m_window->getSize().x / (float) m_window->getSize().y;
   m_gridWidth += 1.f;
   m_ortho.setSize({ m_gridWidth * aspectRatio, m_gridWidth });

   m_ortho.setCentre(m_gridCenter);

   m_3Dtransform.setScale({ 1.f / m_gridWidth, -1.f / m_gridWidth, 1.f / m_gridWidth });
   m_3Dtransform.setOrigin({ m_gridCenter, 0.f });
   m_camera.setAspectRatio(aspectRatio);
   m_camera.setPosition({ 0.f, 0.f, 1.f });
}

void ResultLayer::configureEventsHandler()
{
   m_window->setEventBus(::GetEventBus());

   static ze::EventSubscriber<ze::Event> subscriber(&ResultLayer::handleEvent, this);
   ::GetEventBus()->addSubscriber(subscriber);
}

void ResultLayer::configureRenderers()
{
   m_renderer = std::make_unique<ResultRenderer>();
   m_textRenderer = std::make_unique<TextRenderer>();

   zg::VertexLayout layout;
   layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
   layout.add(zg::VertexAttribute::Type::Float, "vValue");

   m_renderer->setLayout(layout);
   m_renderer->setViewProjection(&m_ortho);

   zg::VertexLayout layout2;
   layout2.add(zg::VertexAttribute::Type::Vec2, "vPos");
   layout2.add(zg::VertexAttribute::Type::Vec4, "vColor");
   layout2.add(zg::VertexAttribute::Type::Vec2, "vTexCoord");
   
   m_textRenderer->setLayout(layout2);
   m_textRenderer->setViewProjection(&m_ortho);

   glEnable(GL_PROGRAM_POINT_SIZE);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ResultLayer::loadResources()
{
   ze::ResourceManager<zg::Shader>::AddSearchPath("assets/shaders");
   ze::ResourceManager<zg::Font>::AddSearchPath("assets/fonts");

   m_shader = ze::ResourceManager<zg::Shader>::Load("node", "node.vs", "node.fs");
   m_shader3D = ze::ResourceManager<zg::Shader>::Load("node3D", "node3D.vs", "node3D.fs");
   m_textShader = ze::ResourceManager<zg::Shader>::Load("text", "default.vs", "text.fs");
   m_font = ze::ResourceManager<zg::Font>::Load("arial", zg::FontFile("Arial.ttf"), 48);
}

