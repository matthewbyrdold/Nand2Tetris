/**   FileHelpers.h
 *    Various helper functions for managing files for use in the Jack compiler.
 *    matthew.james.bird@gmail.com
 */

#include <fstream>
#include <iostream>
#include <vector>

const std::vector<const std::string> getFiles(const std::string&);

bool isDirectory(const std::string&);

bool isJackFile(const std::string& filename);

std::ifstream openFileToCompile(const std::string&);

std::ofstream openOutputFileFor(const std::string&);
