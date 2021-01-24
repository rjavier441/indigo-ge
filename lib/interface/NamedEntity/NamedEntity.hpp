// PROJECT:         Indigo
// Author:          R. Javier
// File:            NamedEntity.hpp
// Created:         2021-01-23
// Last Modified:   2021-01-23
// Details:
//                  Defines an interface for named items.
// Dependencies:
//                  n/a

// @includes
#include <string>
using namespace std;

namespace Indigo {

  // @class           NamedEntity
  // @description     Pure interface class for items that are named.
  class NamedEntity {
    public:
      virtual string getName() = 0;
  };
}