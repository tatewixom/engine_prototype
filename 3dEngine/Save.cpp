#include "Save.h"

bool Save::write(const std::string fileName, const std::string contents)
{
  if (exists(fileName))
  {
    m_file.open(fileName);
    if (m_file.is_open())
    {
      m_file << contents << '\n';
      m_file.close();
      return true;
    }
    else
    {
      std::cerr << "ERROR::SAVE.CPP::WRITE::FILE_FAILED_TO_OPEN\n";
      return false;
    }
  }
  else
  {
    std::cerr << "ERROR::SAVE.CPP::WRITE::FILE_DOES_NOT_EXIST\n";
    return false;
  }
  return false;
}

bool Save::exists(const std::string fileName)
{
  std::ifstream file(fileName);
  return file.good();
}

bool Save::create(const std::string fileName)
{
  if (exists(fileName))
  {
    std::cerr << "ERROR::SAVE.CPP::CREATE::FILE_ALREADY_EXISTS\n";
    return false;
  }
  else
  {
    std::ofstream file(fileName);
    if (file)
    {
      file.close();
      return true;
    }
    else
    {
      std::cerr << "ERROR::SAVE.CPP::CREATE::FAILURE_IN_CREATING_OR_OPENING_FILE\n";
      return false;
    }
  }
  return false;
}

std::string Save::load(const std::string fileName)
{
  return fileName;
}