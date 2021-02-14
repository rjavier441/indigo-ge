// PROJECT:         Indigo
// Author:          R. Javier
// File:            CallbackContainer.hpp
// Created:         2021-01-23
// Last Modified:   2021-01-23
// Details:
//                  Public interface of class CallbackContainer.
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <map>
#include <vector>
#include "../Callback/Callback.hpp"
#include "../CallbackResponse/CallbackResponse.hpp"
using namespace std;

namespace Indigo {
  
  // @namespace       CallbackResponseType
  // @description     A namespace originating in CallbackResponse.hpp,
  //                  this section adds more CallbackResponseTypes
  //                  specially made for the CallbackContainer class.
  namespace CallbackResponseType {
    inline const char* kFireFailed = "CallbackResponseFireFailed";
  }

  // @class           CallbackResponseFireFailed
  // @description     A special type of CallbackResponse indicating that
  //                  an event fire failed (partially or completely).
  class CallbackResponseFireFailed : public CallbackResponse {
    public:
      CallbackResponseFireFailed( string msg = "" ) :
      CallbackResponse( CallbackResponseType::kFireFailed, msg ) {};
  };

  // @class           CallbackContainer
  // @description     A container mapping Callbacks to Events and
  //                  allowing event-driven callback invocation.
  class CallbackContainer {
    private:
      map<sf::Event::EventType, vector<Callback> > cb_map_;
    public:
      CallbackContainer();
      vector<Callback>* getEventCallbacks( sf::Event::EventType et );
      bool on( sf::Event::EventType et, Callback cb );
      bool off( sf::Event::EventType et, string cbName );
      bool purgeEventCallbacks( sf::Event::EventType et );
      bool purgeAllCallbacks();
      vector<CallbackResponse> fireEvent(
        sf::Event::EventType et,
        sf::Event* e = nullptr
      );
  };
}