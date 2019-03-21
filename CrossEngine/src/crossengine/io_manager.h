/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_IOMANAGER_H_
#define CROSSENGINE_IOMANAGER_H_

#include <string>
#include <vector>

namespace CrossEngine {
/**
 * @brief
 */
struct DirEntry {
  std::string path;
  bool isDirectory;
};

/**
 * @brief Class to manage io operations.
 */
class IOManager {
 public:
  /**
   * @brief Reads the file into the vector of buffers.
   *
   * @param[in] file_path The path of the file.
   * @param[out] buffer The buffer.
   * @return true If succeessed to read the file to the buffer.
   * @return false If failed to read the file to the buffer.
   */
  static bool ReadFileToBuffer(const std::string& file_path,
                               std::vector<unsigned char>* buffer);

  /**
   * @brief Reads the file into a buffer.
   *
   * @param[in] file_path The path of the file.
   * @param[out] buffer The buffer.
   * @return true If succeessed to read the file to the buffer.
   * @return false If failed to read the file to the buffer.
   */
  static bool ReadFileToBuffer(const std::string& file_path,
                               std::string* buffer);

  /**
   * @brief Gets all directory entries in the directory specified by path and
   * stores in rv_entries.
   *
   * @param[in] path The path
   * @param[out] rv_entries The entries.
   * @return true If it could get the directory entries.
   * @return false If the path is not a directory.
   */
  static bool GetDirectoryEntries(const char* path,
                                  std::vector<DirEntry>* rv_entries);

  /**
   * @brief Create a directory.
   *
   * @param[in] path The path.
   * @return true If it could create the directory.
   * @return false If failed.
   */
  static bool MakeDirectory(const char* path);
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_IOMANAGER_H_
