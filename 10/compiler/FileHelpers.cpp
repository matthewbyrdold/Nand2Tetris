/**   FileHelpers.cpp
 *    Various helper functions for managing files for use in the Jack compiler.
 *    matthew.james.bird@gmail.com
 */

#include <FileHelpers.h>

#include <iostream>
#include <sys/stat.h> // for stat (checking if file is dir)
#include <dirent.h> // for getting files in a directory on UNIX

using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

const vector<const string> getFiles(const string& path)
{
    vector<const string> files;
    if (!isDirectory(path))
    {
        if (isJackFile(path))
        {
            files.push_back(path);
        }
        else
        {
            cerr << path << " is not a Jack file" << endl;
        }
    }
    else
    {
        DIR* dir;
        dirent* pdir;
        dir = opendir(path.c_str());

        while ((pdir = readdir(dir))) 
        {
            string fileName = pdir->d_name;
            if (isJackFile(fileName))
            {
                string fullPath = path + "/" + fileName;
                files.push_back(fullPath);
            }
        }
    }
    return files;
}

bool isDirectory(const string& path)
{
    struct stat s;
    if(stat(path.c_str(), &s) == 0)
    {
        if(s.st_mode & S_IFDIR)
        {
            return true;
        }
        else if(s.st_mode & S_IFREG)
        {
            return false;
        }
        else
        {
            cerr << "isDirectory(): weird path type" << path << endl;
            return false;
        }
    }
    else
    {
        cerr << "isDirectory(): cannot read type of " << path << endl;
        return false;
    }
}

bool isJackFile(const string& filename)
{
    if (filename.size() < 5)
    {
        return false; // must be > ".jack"
    }
    return (filename.substr(filename.size() - 5, filename.size() - 1) == ".jack")
            | (filename.substr(filename.size() - 5, filename.size() - 1) == ".Jack");
}

ofstream openOutputFileFor(const string& fileToCompile)
{
    ofstream output;
    string outputFilename = fileToCompile.substr(0, (fileToCompile.length() - 5))
                          + ".xml";
    output.open(outputFilename.c_str());
    return output;
}

ifstream openFileToCompile(const string& fileToCompile)
{
    ifstream file;
    file.open(fileToCompile.c_str());
    return file;
}

