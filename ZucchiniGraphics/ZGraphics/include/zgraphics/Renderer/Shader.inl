inline unsigned int zg::Shader::getHandle() const noexcept
{
   return m_program;
}

inline zg::Shader* ze::ResourceLoader<zg::Shader>::Load(std::filesystem::path const& vertex,
                                                        std::filesystem::path const& fragment)
{
   auto vertexFile = ze::ResourceManager<zg::Shader>::FindFile(vertex);
   auto fragmentFile = ze::ResourceManager<zg::Shader>::FindFile(fragment);

   if (!vertexFile)
      ze::Console::Trace("File not found : {}", vertex);
   if (!fragmentFile)
      ze::Console::Trace("File not found : {}", fragment);

   return new zg::Shader(vertexFile.value(), fragmentFile.value());
}

inline void ze::ResourceLoader<zg::Shader>::Reload(zg::Shader* shader, std::filesystem::path const& vertex,
                                                   std::filesystem::path const& fragment)
{
   auto vertexFile = ze::ResourceManager<zg::Shader>::FindFile(vertex);
   auto fragmentFile = ze::ResourceManager<zg::Shader>::FindFile(fragment);

   if (!vertexFile)
      ze::Console::Trace("File not found : {}", vertex);
   if (!fragmentFile)
      ze::Console::Trace("File not found : {}", fragment);

   shader->loadFile(vertexFile.value(), fragmentFile.value());
}

inline void ze::ResourceLoader<zg::Shader>::Unload(zg::Shader* shader) {}

