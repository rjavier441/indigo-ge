// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_ConsoleLogger.cpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  A unit test for the ConsoleLogger class.
// Dependencies:
//                  Catch2 v2.13.3+

// @includes
#include <cstdio>
#include <cstdarg>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <utility>
#include <string>
#include <string.h>
#include <fakeit.hpp> // See https://github.com/eranpeer/FakeIt/issues/197 for a description of how I got fakeit.hpp to compile.
#include "lib/catch2/catch.hpp"
#include "../lib/modules/ConsoleLogger/ConsoleLogger.hpp"
#include "../lib/modules/Util/Util.hpp"
using namespace std;

// @test            ConsoleLogger is a singleton
TEST_CASE( "ConsoleLogger initializes and uses only a single instance", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger* a = &Indigo::ConsoleLogger::getInstance();
  Indigo::ConsoleLogger* b = &Indigo::ConsoleLogger::getInstance();
  Indigo::ConsoleLogger* c = &Indigo::ConsoleLogger::getInstance();

  // Test that successive calls to getInstance() return the same address
  REQUIRE( a == &Indigo::ConsoleLogger::getInstance() );
  REQUIRE( b == &Indigo::ConsoleLogger::getInstance() );
  REQUIRE( c == &Indigo::ConsoleLogger::getInstance() );
}

// @test            log() returns message length
TEST_CASE( "ConsoleLogger::log() returns the correct message length", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();
  string testPrefix[3] = {"[Prefix]","","Only Prefix"};
  string testMessage[3] = {"Test Message","Only Message",""};
  char temp[50];
  int expected[3] = {
    sprintf(temp, "%s%s\n", testPrefix[0].c_str(), testMessage[0].c_str()),
    sprintf(temp, "%s%s\n", testPrefix[1].c_str(), testMessage[1].c_str()),
    sprintf(temp, "%s%s\n", testPrefix[2].c_str(), testMessage[2].c_str())
  };

  // Ensure the lengths match
  REQUIRE( a.log(testMessage[0], testPrefix[0]) == expected[0] );
  REQUIRE( a.log(testMessage[1], testPrefix[1]) == expected[1] );
  REQUIRE( a.log(testMessage[2], testPrefix[2]) == expected[2] );
}

// @test            startRecording() properly throws LogDirNotFound
TEST_CASE(
  "ConsoleLogger::startRecording() should properly throw LogDirNotFound on non-existent directories",
  "[ConsoleLogger]"
) {
  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();

  a.setLogDir("./someNonExistentDir");
  REQUIRE_THROWS_AS(
    a.startRecording(), Indigo::ConsoleLoggerException::LogDirNotFound
  );
}

// @test            generateFileName() creates unique file name
TEST_CASE( "ConsoleLogger::generateFileName() should generate unique file names on successive calls at least 1 second apart", "[ConsoleLogger]" ) {
  
  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();
  string actual[3] = {};
  unordered_set<string> history;

  // Generate filenames seconds apart
  INFO("Generating sample data...");
  for(short i = 0; i < 3; i++) {
    actual[i] = a.generateFileName();
    Indigo::Util::Sleep(1000);
  }

  // Check to make sure successive calls generate different file names
  INFO("Checking filename uniqueness...");
  for(const auto& name : actual) {

    INFO("filename: " + name);
    REQUIRE( strlen(name.c_str()) > 0 );
    REQUIRE( history.find(name) == history.end() );
    history.insert(name);
  }
}

// @test            generateFileName() uses correct log file extension
TEST_CASE( "ConsoleLogger::generateFileName() should generate correct extension and name format", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();
  string test = a.generateFileName();

  // Split name into parts.
  INFO( "Splitting filename into parts" );
  string extension = Indigo::kEmptyString;
  string predicate = Indigo::kEmptyString;
  string datestr = Indigo::kEmptyString;
  string timestr = Indigo::kEmptyString;

  // Split test into extension and predicate
  size_t pos = test.find('.');
  if( pos != string::npos ) {
    extension = test.substr(pos);
  }
  if(
    pos != static_cast<size_t>(0) && extension != Indigo::kEmptyString
  ) {
    predicate = test.substr( 0, test.length() - extension.length() );
  }

  // Split predicate into timestr and datestr
  pos = predicate.find('_');
  if(
    pos != static_cast<size_t>(0) &&
    pos != static_cast<size_t>(predicate.length() - 1)
  ) {
    datestr = predicate.substr(0,pos);
    timestr = predicate.substr(pos + 1);
  }

  // Split datestr into years, months, days
  string years = Indigo::kEmptyString;
  string months = Indigo::kEmptyString;
  string days = Indigo::kEmptyString;
  int i = 0;
  char* token = strtok( const_cast<char*>(datestr.c_str()), "-" );
  while( token != NULL ) {
    switch( i ) {
      case 0:
        years = static_cast<string>(token);
      break;
      case 1:
        months = static_cast<string>(token);
      break;
      case 2:
        days = static_cast<string>(token);
      break;
    }

    token = strtok(NULL,"-");
    i++;
  }

  // Split timestr into hours, mins, sec
  string hours = Indigo::kEmptyString;
  string mins = Indigo::kEmptyString;
  string sec = Indigo::kEmptyString;
  i = 0;
  token = strtok( const_cast<char*>(timestr.c_str()), ":" );
  while( token != NULL ) {
    switch( i ) {
      case 0:
        hours = static_cast<string>(token);
      break;
      case 1:
        mins = static_cast<string>(token);
      break;
      case 2:
        sec = static_cast<string>(token);
      break;
    }

    token = strtok(NULL,":");
    i++;
  }
  
  // Create a test fixture to check these numerical values
  class ConsoleLoggerGfnTestFixture {
    public:
      size_t total_chars_;
      bool is_numeric_;
      int num_val_;
      ConsoleLoggerGfnTestFixture(string s) {

        // Calculate length 
        total_chars_ = s.length();

        // Check if entire string is numeric
        is_numeric_ = total_chars_ < 1 ? false : true;
        for( auto c : s ) {
          if( isdigit( c ) == 0 ) {
            is_numeric_ = false;
          }
        }

        // Provide its numeric equivalent (if possible)
        num_val_ = -1;
        if( is_numeric_ ) {
          num_val_ = stoi(s);
        }
      }
  };

  // Check that the format was not violated (i.e. everything was found)
  INFO( "Checking for proper format" );
  REQUIRE( years != Indigo::kEmptyString );
  REQUIRE( months != Indigo::kEmptyString );
  REQUIRE( days != Indigo::kEmptyString );
  REQUIRE( hours != Indigo::kEmptyString );
  REQUIRE( mins != Indigo::kEmptyString );
  REQUIRE( sec != Indigo::kEmptyString );
  
  // Check that years/months/days and hours/mins/sec are numeric
  INFO( "Checking if years are valid" );
  ConsoleLoggerGfnTestFixture year_fixture(years);
  REQUIRE( year_fixture.is_numeric_ == true );
  REQUIRE( year_fixture.total_chars_ == 4 );
  
  INFO( "Checking if months are valid" );
  ConsoleLoggerGfnTestFixture month_fixture(months);
  REQUIRE( month_fixture.is_numeric_ == true );
  REQUIRE( month_fixture.total_chars_ == 2 );
  REQUIRE( month_fixture.num_val_ > 0);
  REQUIRE( month_fixture.num_val_ < 13 );
  
  INFO( "Checking if days are valid" );
  ConsoleLoggerGfnTestFixture days_fixture(days);
  REQUIRE( days_fixture.is_numeric_ == true );
  REQUIRE( days_fixture.total_chars_ == 2 );
  REQUIRE( days_fixture.num_val_ > 0);
  REQUIRE( days_fixture.num_val_ < 32 );
  
  INFO( "Checking if hours are valid" );
  ConsoleLoggerGfnTestFixture hours_fixture(hours);
  REQUIRE( hours_fixture.is_numeric_ == true );
  REQUIRE( hours_fixture.total_chars_ == 2 );
  REQUIRE( hours_fixture.num_val_ >= 0);
  REQUIRE( hours_fixture.num_val_ < 24 );
  
  INFO( "Checking if mins are valid" );
  ConsoleLoggerGfnTestFixture mins_fixture(mins);
  REQUIRE( mins_fixture.is_numeric_ == true );
  REQUIRE( mins_fixture.total_chars_ == 2 );
  REQUIRE( mins_fixture.num_val_ >= 0);
  REQUIRE( mins_fixture.num_val_ < 60 );
  
  INFO( "Checking if sec is valid" );
  ConsoleLoggerGfnTestFixture sec_fixture(sec);
  REQUIRE( sec_fixture.is_numeric_ == true );
  REQUIRE( sec_fixture.total_chars_ == 2 );
  REQUIRE( sec_fixture.num_val_ >= 0);
  REQUIRE( sec_fixture.num_val_ < 60 );

  // Check that extension is ".log"
  INFO( "Checking if extension is correct" );
  REQUIRE( extension == ".log" );
}

// @test            setRecording() creates file in a specified directory
TEST_CASE( "ConsoleLogger::setRecording() should create a file in the log directory", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();

  // Set log directory to the current directory
  INFO( "Initializing test" );
  string tempPath = filesystem::temp_directory_path();
  a.setLogDir(tempPath);

  // Test creation of file
  INFO( "Testing file creation in temp directory '" + tempPath + "'" );
  string fileUnderTest;
  a.startRecording();
  fileUnderTest = a.getCurrentLogFilePath();
  a.stopRecording();
  REQUIRE( filesystem::exists(fileUnderTest) == true );

  // Ensure residual test file is deleted
  INFO( "Cleaning up" );
  if( filesystem::exists(fileUnderTest) ) {
    REQUIRE( filesystem::remove(fileUnderTest) == true );
  }
  REQUIRE( filesystem::exists(fileUnderTest) == false );
}

// @test            log() writes content to a log file
TEST_CASE( "ConsoleLogger::log() should log to a log file when recording", "[ConsoleLogger]" ) {

  // @SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();

  // Set log directory to the current directory
  INFO( "Initializing test" );
  string tempPath = filesystem::temp_directory_path();
  string expected = "[prefix]Hello world";
  string actual = "";
  a.setLogDir(tempPath);

  // Execute log file writing
  INFO( "Testing message recording" );
  string fileUnderTest;
  a.startRecording();
  fileUnderTest = a.getCurrentLogFilePath();
  a.log( "Hello world", "[prefix]" );
  a.stopRecording();

  // Test message contents
  ifstream file(fileUnderTest);
  REQUIRE( file.is_open() == true );
  if( file.is_open() ) {
    string line;
    while( std::getline(file,line) ) {
      actual += line;
    }
  }
  file.close();
  REQUIRE( file.is_open() == false );

  // Ensure residual test file is deleted
  INFO( "Cleaning up" );
  if( filesystem::exists(fileUnderTest) ) {
    REQUIRE( filesystem::remove(fileUnderTest) == true );
  }
  REQUIRE( filesystem::exists(fileUnderTest) == false );
  
  // Test results
  INFO( "Comparing messages" );
  REQUIRE( strncmp( expected.c_str(), actual.c_str(), 100 ) == 0 );
}