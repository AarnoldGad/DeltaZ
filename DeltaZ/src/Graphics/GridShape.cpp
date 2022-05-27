#include "dz/Graphics/GridShape.hpp"

void GridShape::setGrid(Grid const& grid)
{
   std::map<std::tuple<int, int>, int> nodeIndex;
   size_t i = 0;
   for (auto& element : grid.getNodes())
   {
      Node const& node = element.second;
      m_vertices.push_back(NodeVertex(node.getPosition(), node.getValue()));
      nodeIndex.emplace(element.first, i);
      ++i;
   }

   for (auto& element : grid.getNodes())
   {
      Node const& node = element.second;

      // Alright, here goes
      int x = std::get<0>(element.first);
      int y = std::get<1>(element.first);

      std::tuple<int, int> here      = std::make_tuple(x, y);
      std::tuple<int, int> right     = std::make_tuple(x + 1, y);
      std::tuple<int, int> left      = std::make_tuple(x - 1, y);
      std::tuple<int, int> up        = std::make_tuple(x, y + 1);
      std::tuple<int, int> down      = std::make_tuple(x, y - 1);
      std::tuple<int, int> rightUp   = std::make_tuple(x + 1, y + 1);
      std::tuple<int, int> leftUp    = std::make_tuple(x - 1, y + 1);
      std::tuple<int, int> rightDown = std::make_tuple(x + 1, y - 1);
      std::tuple<int, int> leftDown  = std::make_tuple(x - 1, y - 1);

      Node::Neighbours const& neighbours = node.getNeighbours();
      if (neighbours.right && neighbours.rightUp)
      {
         // Consider that if there is neighbourood, there is corresponding entry in
         // nodeIndex: i.e use .at()
         m_elements.push_back(nodeIndex.at(here));
         m_elements.push_back(nodeIndex.at(right));
         m_elements.push_back(nodeIndex.at(rightUp));
      }

      if (neighbours.up && neighbours.rightUp)
      {
         m_elements.push_back(nodeIndex.at(here));
         m_elements.push_back(nodeIndex.at(rightUp));
         m_elements.push_back(nodeIndex.at(up));
      }

      if (!neighbours.rightUp && neighbours.up && neighbours.right)
      {
         m_elements.push_back(nodeIndex.at(here));
         m_elements.push_back(nodeIndex.at(right));
         m_elements.push_back(nodeIndex.at(up));
      }

      if (!neighbours.down && neighbours.right && neighbours.rightDown)
      {
         m_elements.push_back(nodeIndex.at(here));
         m_elements.push_back(nodeIndex.at(rightDown));
         m_elements.push_back(nodeIndex.at(right));
      }

      // Special cases
      if (!neighbours.up && !neighbours.right && neighbours.rightUp)
      {
         if (neighbours.rightUp->getNeighbours().right)
         {
            std::tuple<int, int> rightUpThenRight = std::make_tuple(x + 2, y + 1);

            m_elements.push_back(nodeIndex.at(here));
            m_elements.push_back(nodeIndex.at(rightUpThenRight));
            m_elements.push_back(nodeIndex.at(rightUp));
         }

         if (neighbours.rightUp->getNeighbours().up)
         {
            std::tuple<int, int> rightUpThenUp = std::make_tuple(x + 1, y + 2);

            m_elements.push_back(nodeIndex.at(here));
            m_elements.push_back(nodeIndex.at(rightUp));
            m_elements.push_back(nodeIndex.at(rightUpThenUp));
         }
      }

      if (!neighbours.up && neighbours.right && !neighbours.rightUp)
      {
         if (neighbours.right->getNeighbours().rightUp)
         {
            std::tuple<int, int> rightThenRightUp = std::make_tuple(x + 2, y + 1);

            m_elements.push_back(nodeIndex.at(here));
            m_elements.push_back(nodeIndex.at(right));
            m_elements.push_back(nodeIndex.at(rightThenRightUp));
         }
      }

      if (neighbours.up && !neighbours.right && !neighbours.rightUp)
      {
         if (neighbours.up->getNeighbours().rightUp)
         {
            std::tuple<int, int> upThenRightUp = std::make_tuple(x + 1, y + 2);

            m_elements.push_back(nodeIndex.at(here));
            m_elements.push_back(nodeIndex.at(upThenRightUp));
            m_elements.push_back(nodeIndex.at(up));
         }
      }
   }
}
