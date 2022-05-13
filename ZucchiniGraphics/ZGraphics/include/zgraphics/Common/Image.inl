inline uint8_t const* zg::Image::getData() const noexcept
{
   return m_data;
}

inline zg::Image::Format zg::Image::getFormat() const noexcept
{
   return m_format;
}

inline glm::ivec2 zg::Image::getSize() const noexcept
{
   return m_size;
}

inline zg::Image::operator bool() const noexcept
{
   return isLoaded();
}

inline bool zg::Image::isLoaded() const noexcept
{
   return m_data;
}

inline zg::Image* ze::ResourceLoader<zg::Image>::Load(std::filesystem::path const& file, zg::Image::Format format)
{
   auto foundFile = ze::ResourceManager<zg::Image>::FindFile(file);

   if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file), nullptr;
   
   return new zg::Image(foundFile.value(), format);
}

inline void ze::ResourceLoader<zg::Image>::Reload(zg::Image* image, std::filesystem::path const& file,
                                                        zg::Image::Format format)
{
   auto foundFile = ze::ResourceManager<zg::Image>::FindFile(file);
   
   if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file);

   image->loadFile(foundFile.value(), format);
}

inline void ze::ResourceLoader<zg::Image>::Unload(zg::Image* image)
{
   image->unload();
}

