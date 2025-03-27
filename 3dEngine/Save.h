#pragma once

#include <iostream>
#include <fstream>
#include <string>

//Made for reading, manipulating, and reporting save files to any state
class Save
{
private:
  std::ofstream m_file;

public: 
  //Writes to an already existing file
  bool write(const std::string fileName, const std::string contents);

  //Checks whether a specified file exists or not
  bool exists(const std::string fileName);

  //Creates a file given a specific file name
  bool create(const std::string fileName);

  //Opens and returns a string of existing content in a specified file
  std::string load(const std::string fileName);
};

