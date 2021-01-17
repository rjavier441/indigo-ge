// PROJECT:         Indigo
// Author:          R. Javier
// File:            CallbackResponse.hpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  Defines a message packet class standardizing the way
//                  callbacks respond when called.
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>

namespace Indigo {

  // @namespace       CallbackResponseType
  // @description     A namespace defining string representations of
  //                  the different callback response types.
  namespace CallbackResponseType {
    inline const char* kSuccess = "CallbackResponseSuccess";
    inline const char* kUncaughtException = "CallbackResponseUncaughtExecption";
  }

  // @class           CallbackResponse
  // @description     A standardized response packet for instances of
  //                  class Callback.
  class CallbackResponse {
    private:
      std::string name;
      std::string message;
    public:
      CallbackResponse( std::string n, std::string m = "" );
      std::string getName();
      std::string getMessage();
  };

  // @class           CallbackResponseSuccess
  // @description     A special type of CallbackResponse solely for
  //                  success messages.
  class CallbackResponseSuccess : public CallbackResponse {
    public:
      CallbackResponseSuccess( std::string msg = "" ) :
      CallbackResponse( CallbackResponseType::kSuccess, msg ) {}
  };

  // @class           CallbackResponseUncaughtException
  // @description     A special type of CallbackResponse solely for
  //                  success messages.
  class CallbackResponseUncaughtException : public CallbackResponse {
    public:
      CallbackResponseUncaughtException( std::string msg = "" ) :
      CallbackResponse(
        CallbackResponseType::kUncaughtException, msg
      ) {}
  };
}