#pragma once
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <iostream>

/*
    Check if given string path is of a file
*/
bool isFile(std::string filePath)
{
    try {
        boost::filesystem::path pathObj(filePath); 
        if (boost::filesystem::exists(pathObj) && boost::filesystem::is_regular_file(pathObj))
            return true;
    }
    catch (boost::filesystem::filesystem_error & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
}

/*
Check if given string path is of a Directory
*/
bool isDirectory(std::string filePath)
{
    try { 
        boost::filesystem::path pathObj(filePath); 
        if (boost::filesystem::exists(pathObj) && boost::filesystem::is_directory(pathObj))
            return true;
    }
    catch (boost::filesystem::filesystem_error & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
}

/**
 * @note If extension is empty string ("") then all files are returned
 * @param Path root directory
 * @param extension String or vector of strings to filter - empty string returns all files - default: ""
 * @param recursive Set true to scan directories recursively - default false
 * @return Vector of strings with full paths
 */

std::vector<std::string> getFilesInDir(const std::string &path, const std::string &extension="", const bool &recursive=false){
    std::vector<std::string> files;
    boost::filesystem::path dir(path);
    if(boost::filesystem::exists(path) && boost::filesystem::is_directory(path)){

        if(recursive){
            boost::filesystem::recursive_directory_iterator it(path);
            boost::filesystem::recursive_directory_iterator endit;
            while (it != endit) {
                if(boost::filesystem::is_regular_file(*it) && (extension=="")?true:it->path().extension() == extension) {
			// Returns full path
                    	files.push_back(it->path().string());
		    	//files.push_back(boost::filesystem::relative(it->path().string(), path).string());

                }
                ++it;
            }
        }
        else {
            boost::filesystem::directory_iterator it(path);
            boost::filesystem::directory_iterator endit;
            while (it != endit) {
                if(boost::filesystem::is_regular_file(*it) && (extension=="")?true:it->path().extension() == extension) {
                    files.push_back(it->path().string());
                }
                ++it;
            }
        }
    }
    return files;
}

std::vector<std::string> getFilesInDir(const std::string &path, const std::vector<std::string> &extension, const bool &recursive=false){
    if(extension.size() <=0) return getFilesInDir(path, "", recursive);
    std::vector<std::string> outArray;
    for (const std::string &ext: extension){
        std::vector<std::string> files = getFilesInDir(path, ext, recursive);
        outArray.insert(outArray.end(), files.begin(), files.end());
    }
    return outArray;
}
