inline zg::Glyph const& zg::Font::getGlyph(uint32_t const charcode) const
{
   return m_glyphs.at(charcode);
}

inline zg::Texture const* zg::Font::getAtlas(uint32_t const plane) const
{
   return m_atlas.at(plane).get();
}

inline zg::Encoding zg::Font::getEncoding() const noexcept
{
   return m_encoding;
}

