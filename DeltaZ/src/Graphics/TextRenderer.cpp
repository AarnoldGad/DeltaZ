#include "dz/Graphics/TextRenderer.hpp"

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

   for (auto it = text.begin(); it != text.end(); ++it)
   {
      uint32_t charcode = 0;
      std::bitset<8> byteChar(*it);
      std::bitset<8> twoBytesFilter(0b11100000);
      std::bitset<8> twoBytesSign(0b11000000);
      // Convert 2-bytes utf8 to unicode codepoints
      // TODO Rework this monstrosity
      if ((byteChar & twoBytesFilter) == twoBytesSign)
      {
         // TODO Should check for out of bounds, etc, its messy
         std::bitset<8> byte1Filter(0b00011111);
         std::bitset<8> byte2Filter(0b00111111);
         std::bitset<8> byte1 = (byteChar & byte1Filter);
         byteChar = *(++it);
         std::bitset<8> byte2 = (byteChar & byte2Filter);
         charcode = (byte1.to_ullong() << 6) | byte2.to_ullong();
      }
      else
         charcode = byteChar.to_ullong();

      zg::Glyph const& glyph = font.getGlyph(charcode);
      
      glm::vec2 charPos = pen;
      glm::vec2 charSize = scale * static_cast<glm::vec2>(glyph.getSize());
      charPos.x += static_cast<float>(glyph.getBearing().x) * scale;
      charPos.y += static_cast<float>(glyph.getSize().y - glyph.getBearing().y) * scale;

      float vertices[] = 
      {
         charPos.x             , charPos.y - charSize.y, 0.f, 0.f, 0.f, 1.f, glyph.getRect().x                    , glyph.getRect().y,
         charPos.x             , charPos.y             , 0.f, 0.f, 0.f, 1.f, glyph.getRect().x                    , glyph.getRect().y + glyph.getRect().w,
         charPos.x + charSize.x, charPos.y             , 0.f, 0.f, 0.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y + glyph.getRect().w,

         charPos.x             , charPos.y - charSize.y, 0.f, 0.f, 0.f, 1.f, glyph.getRect().x                    , glyph.getRect().y,
         charPos.x + charSize.x, charPos.y             , 0.f, 0.f, 0.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y + glyph.getRect().w,
         charPos.x + charSize.x, charPos.y - charSize.y, 0.f, 0.f, 0.f, 1.f, glyph.getRect().x + glyph.getRect().z, glyph.getRect().y
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

