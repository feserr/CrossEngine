/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/io_manager.h"

#include <bx/file.h>
#include <filesystem/path.h>
#include <filesystem/resolver.h>

#include <fstream>
#include <string>
#include <vector>

namespace CrossEngine {
bool IOManager::ReadFileToBuffer(const std::string& file_path,
                                 std::vector<unsigned char>* buffer) {
  std::ifstream file(file_path, std::ios::binary);
  if (file.fail()) {
    perror(file_path.c_str());
    return false;
  }

  // Seek to the end
  file.seekg(0, std::ios::end);

  // Get the file size
  unsigned int fileSize = (unsigned int)file.tellg();
  file.seekg(0, std::ios::beg);

  // Reduce the file size by any header bytes that might be present
  fileSize -= (unsigned int)file.tellg();

  buffer->resize(fileSize);
  file.read(reinterpret_cast<char*>(&buffer[0]), fileSize);
  file.close();

  return true;
}

bool IOManager::ReadFileToBuffer(const std::string& file_path,
                                 std::string* buffer) {
  std::ifstream file(file_path, std::ios::binary);
  if (file.fail()) {
    perror(file_path.c_str());
    return false;
  }

  // Seek to the end
  file.seekg(0, std::ios::end);

  // Get the file size
  unsigned int fileSize = (unsigned int)file.tellg();
  file.seekg(0, std::ios::beg);

  // Reduce the file size by any header bytes that might be present
  fileSize -= (unsigned int)file.tellg();

  buffer->resize(fileSize);
  file.read(reinterpret_cast<char*>(&(buffer[0])), fileSize);
  file.close();

  return true;
}

bool IOManager::GetDirectoryEntries(const char* path,
                                    std::vector<DirEntry>* rv_entries) {
  auto dpath = filesystem::path(path);
  // Must be directory
  if (!dpath.is_directory()) return false;

  for (auto it = filesystem::resolver().begin();
       it != filesystem::resolver().end(); ++it) {
    rv_entries->emplace_back();
    rv_entries->back().path = it->str();
    if (it->is_directory()) {
      rv_entries->back().is_directory = true;
    } else {
      rv_entries->back().is_directory = false;
    }
  }
  return true;
}

bool IOManager::MakeDirectory(const char* path) {
  return bx::make(path);
}
}  // namespace CrossEngine
