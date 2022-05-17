#include "dz/TextRenderer.hpp"

void TextRenderer::setLayout(zg::VertexLayout const& layout)
{
   m_vbo.bind();
   m_vao.setLayout(layout);
}

void TextRenderer::setViewProjection(zg::ViewProjection const* viewProjection) noexcept
{
   m_viewProjection = viewProjection;
}

void TextRenderer::renderText(zg::Shader& shader, zg::Font const& font,
                              std::string const& text, glm::vec3 const pos, float const scale)
{
   shader.use();

   glm::mat4 model = glm::translate(glm::mat4(1.f), pos);
   shader.setMatrix4("model", model);
   shader.setMatrix4("view", m_viewProjection->getViewMatrix());
   shader.setMatrix4("projection", m_viewProjection->getProjectionMatrix());

   glActiveTexture(GL_TEXTURE0);
   m_vao.bind();
   
   glm::vec2 pen = { 0.f, 0.f };

   for (auto ch = text.begin(); ch != text.end(); ++ch)
   {
      uint32_t charcode = (uint32_t) *ch;
      // Convert utf8 to unicode codepoints
//      if (*ch & 0b11000000)
      zg::Glyph const& glyph = font.getGlyph(charcode);
      
      glm::vec2 charPos = pen;
      glm::vec2 charSize = scale * static_cast<glm::vec2>(glyph.getSize());
      charPos.x += static_cast<float>(glyph.getBearing().x) * scale;
      charPos.y += static_cast<float>(glyph.getBearing().y - glyph.getSize().y) * scale;

      float vertices[] = 
      {
         charPos.x             , charPos.y - charSize.y, 1.f, 1.f, 1.f, 1.f, glyph.getRect().x                    , glyph.getRect().y,
         charPos.x             , charPos.y             , 1.f, 1.f, 1.f, 1.f, glyph.getRect().x                    , glyph.getRect().y + glyph.getRect().w,
         charPos.x + charSize.x, charPos.y             , 1.f, 1.f, 1.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y + glyph.getRect().w,

         charPos.x             , charPos.y - charSize.y, 1.f, 1.f, 1.f, 1.f, glyph.getRect().x                    , glyph.getRect().y,
         charPos.x + charSize.x, charPos.y             , 1.f, 1.f, 1.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y + glyph.getRect().w,
         charPos.x + charSize.x, charPos.y - charSize.y, 1.f, 1.f, 1.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y
      };

      glyph.getTexture()->bind();

      m_vbo.bind();
      m_vbo.setData(6 * 8 * sizeof(float), vertices);
      m_vbo.unbind();

      glDrawArrays(GL_TRIANGLES, 0, 6);

      pen.x += static_cast<float>(glyph.getAdvance() >> 6) * scale;
   }

   shader.setInteger("atlas", 0);
}

