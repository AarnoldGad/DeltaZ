#ifndef ZE_TYPES_HPP
#define ZE_TYPES_HPP

#include <fmt/format.h>
#include <filesystem>

typedef struct
{
   char const* file;
   unsigned int line;
   char const* function;
} SourceLocation;

enum class Status
{
   Error = 0,
   OK
};

enum class Priority : uint8_t
{
   VeryLow  = 1 << 0,
   Low      = 1 << 1,
   Normal   = 1 << 2,
   High     = 1 << 3,
   VeryHigh = 1 << 4
};

template <>
struct fmt::formatter<std::filesystem::path>
{
   constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
   {
      auto it = ctx.begin(), end = ctx.end();
      if (it != end && *it != '}') throw format_error("invalid format");
      return it;
   }

   template<typename FormatContext>
   auto format(std::filesystem::path const& path, FormatContext& ctx) -> decltype(ctx.out())
   {
      return format_to(ctx.out(), "{}", path.string());
   }
};

#endif // ZE_TYPES_HPP

