#include "dz/Graphics/Legend.hpp"

Legend::Legend()
{
   m_vertices[0].setPosition({ 0.f , 0.f });
   m_vertices[1].setPosition({ 0.1f, 0.f });
   m_vertices[2].setPosition({ 0.1f, 1.f });
   m_vertices[3].setPosition({ 0.f , 1.f });
}

void Legend::setBounds(float const height, float const lower, float const upper)
{
   m_vertices[0].setPosition({ 0.f , 0.f });
   m_vertices[1].setPosition({ height * 0.1f, 0.f });
   m_vertices[2].setPosition({ height * 0.1f, height });
   m_vertices[3].setPosition({ 0.f , height });

   m_vertices[0].setValue(upper);
   m_vertices[1].setValue(upper);
   m_vertices[2].setValue(lower);
   m_vertices[3].setValue(lower);
}
