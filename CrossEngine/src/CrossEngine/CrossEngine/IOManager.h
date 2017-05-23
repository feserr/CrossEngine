/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _IOMANAGER_H_
#define _IOMANAGER_H_

#include <string>
#include <vector>

namespace CrossEngine {
struct DirEntry {
    std::string path;
    bool isDirectory;
};

class IOManager {
 public:
    static bool ReadFileToBuffer(std::string filePath,
        std::vector<unsigned char>& buffer);
    static bool ReadFileToBuffer(std::string filePath,
        std::string& buffer);

    // Gets all directory entries in the directory specified by path and stores
    // in rvEntries.
    // Returns false if path is not a directory.
    static bool GetDirectoryEntries(const char* path,
        std::vector<DirEntry>* rvEntries);
    static bool MakeDirectory(const char* path);
};
}  // namespace CrossEngine

#endif  // _IOMANAGER_H_
