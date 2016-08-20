/**
 *	File: mediator.hpp
 *	Author: matthew.james.bird@gmail.com
 *
 *	Functions for the mediator between the Parser and CodeWriter modules of the VM translator.
 *	
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

#include "Parser.hpp"
#include "CodeWriter.hpp"
#include "VMT.hpp"

using namespace std;

#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

/**
 *	isVMFile: Returns whether input is a single .vm file (false if input is a directory of .vm files).
 */
bool isVMFile(const string& input);

/**
 * getVMFiles: Returns a list of all .vm files in path.
 */
vector<string> getVMFiles(string path);

/**
 *  lastPartOfPath: Returns the lowest level directory in a path.
 */
string lastPartOfPath(const string& path);

/**
 *  currentDirectory: Returns the name of the current directory on UNIX
 */
string currentDirectory();

/**
 *	translate: translates source into output.
 *	
 *	Returns whether there are any errors.
 */
bool translate(Parser& parser, CodeWriter& writer);


#endif  /* MEDIATOR_HPP */
