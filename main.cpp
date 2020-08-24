#include <string>

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cxxopts.hpp>
//#include <spdlog>

#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/filesystem.hpp>
#include "util.h"
using namespace std;
int main(int argc, char** argv) {
	
		
	cxxopts::Options options("Preprocessing", "paganinist@gmail.com");
	options.add_options()
	    ("s,source", "Target for conversion", cxxopts::value<std::string>())
	    ("d,destination", "Where the output is stored", cxxopts::value<std::string>())
	    ("f,format", "Output file format", cxxopts::value<std::string>())
	    ("h,help", "Print usage");
	
	auto result = options.parse(argc, argv);

	if(result.count("help")) {
		std::cout << options.help() << std::endl;
		return 0;
	}

	std::string source;
	bool sourceIsFile = false;
	bool sourceIsDirectory = false;

	if(result.count("source")) {
		source = result["source"].as<std::string>();
		sourceIsFile = isFile(source);
		sourceIsDirectory = isDirectory(source);	
	} else {
		return 1;
	}

	std::string format;
	if(result.count("format")) {
		format = result["format"].as<std::string>();
	} else {

	
	}

	std::string destination;
	if(result.count("destination")) {
		destination = result["destination"].as<std::string>();
	} else {

	}

	std::vector<std::string> exts{".ply", ".off"};
	std::vector<std::string> files = getFilesInDir(source, exts, true);
	//for(int i =0; i < files.size(); i++) cout << files[i] <<std::endl;


	for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {
		boost::filesystem::path fpath = boost::filesystem::path(*it);
		boost::filesystem::path fpath_rel_source = boost::filesystem::relative(fpath, source).string();
		boost::filesystem::path export_fpath = boost::filesystem::path(destination) / fpath_rel_source;
		boost::filesystem::create_directories(export_fpath.parent_path());
		cout << *it << std::endl;
			
		Assimp::Importer importer;
		Assimp::Exporter exporter;
		
		const aiScene* scene = importer.ReadFile(fpath.string(), aiProcess_Triangulate);
		//size_t posDot = (*it).find_last_of(".");
		//std::string fname = (*it).substr(0,posDot);
		exporter.Export(scene, format, export_fpath.replace_extension(format).string());	
	}
	return 0;
}
