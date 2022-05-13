inline unsigned int zg::Texture::getHandle() const noexcept
{
   return m_texture;
}

inline glm::ivec2 zg::Texture::getSize() const noexcept
{
   return m_size;
}

inline zg::Texture* ze::ResourceLoader<zg::Texture>::Load(std::filesystem::path const& file)
{
   auto foundFile = ze::ResourceManager<zg::Texture>::FindFile(file);

   if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file), nullptr;

   zg::Texture* texture = new zg::Texture;
   texture->loadFile(foundFile.value());
   return texture;
}

inline zg::Texture* ze::ResourceLoader<zg::Texture>::Load(zg::Image const& image)
{
   zg::Texture* texture = new zg::Texture;
   texture->loadImage(image);
   return texture;
}

inline zg::Texture* ze::ResourceLoader<zg::Texture>::Load(uint8_t const* data, glm::ivec2 size, zg::Image::Format format)
{
   zg::Texture* texture = new zg::Texture;
   texture->loadData(data, size, format);
   return texture;
}

inline void ze::ResourceLoader<zg::Texture>::Reload(zg::Texture* texture, std::filesystem::path const& file)
{
   auto foundFile = ze::ResourceManager<zg::Texture>::FindFile(file);
   if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file);
   texture->loadFile(foundFile.value());
}

inline void ze::ResourceLoader<zg::Texture>::Reload(zg::Texture* texture, zg::Image const& image)
{
   texture->loadImage(image);
}

inline void ze::ResourceLoader<zg::Texture>::Reload(zg::Texture* texture, uint8_t const* data,
                                                    glm::ivec2 size, zg::Image::Format format)
{
   texture->loadData(data, size, format);
}

inline void ze::ResourceLoader<zg::Texture>::Unload(zg::Texture* texture) {}

