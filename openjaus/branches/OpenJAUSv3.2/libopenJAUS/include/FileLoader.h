/**
 * @file FileLoader.h
 * @brief Contains the FileLoader class
 * @class FileLoader
 * @brief Loads the config files
 * @author Jeffrey Kunkle
 * @date 04-26-2006
 *
 * Modifications:
 *	Date/Author
 *	Description
 *
 * @par 04-26-2006 Jeff Kunkle
 * - Initial Creation
 *
 */
#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <math.h>

using std::string;
using std::vector;
using std::ios;
using std::ifstream;

struct Config_Data_t
{
	string label;
	vector< string > tok;
};

struct Config_File_Data_t
{
	string configheader;
	vector< Config_Data_t > data;
};

class FileLoader
{
private:
	vector< Config_File_Data_t > configFileData;
	int findHeader( string hdr );
	int findLabel( int hdrIndex, string label );
        
public:
	/**
	 * @brief Constructs the File Loader
	 */
	FileLoader( );
	FileLoader( string filename );

	/**
	 * @brief Deconstructs the File Loader
	 */
	~FileLoader( );

	/**
	 * @brief Loads the configuration file
	 *
	 * @param[in] filename is the name of the configuration file with extension
	 * @return success
	 */
	bool load_cfg( string filename );

	/**
	 * @brief Reads a string from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return The string being searched for or "" if not found
	 */
	string GetConfigDataString( string header, string label );

	/**
	 * @brief Reads an int from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return The int being searched for, -1 if not found, or 0 if a string or char
	 */
	int GetConfigDataInt( string header, string label );

	/**
	 * @brief Reads a float from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return The float being searched for, -1 if not found, or 0 if a string or char
	 */
	float GetConfigDataFloat( string header, string label );

	/**
	 * @brief Reads a double from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return The double being searched for, -1 if not found, or 0 if a string or char
	 */
	double GetConfigDataDouble( string header, string label );

	/**
	 * @brief Reads a vector from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return A pointer to the vector being searched for or NULL if nothing found
	 */
	vector< string >* GetConfigDataVector( string header, string label );
	
	/**
	 * @brief Reads a boolean from the config file
	 *
	 * @param[in] header The data grouping. In the config file, this is enclosed in "[]"
	 * @param[in] label The label of the data being searched for. In the config file, this ends with ":"
	 *
	 * @return true if "true" (compared case insensitve) is found, false otherwise
	 */
	bool GetConfigDataBool( string header, string label );
};
#endif
