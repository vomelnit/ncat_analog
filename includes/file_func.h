#ifndef FILE_FUNC_H
# define FILE_FUNC_H

# include <fstream>
# include <sstream>
# include <string>
# include <iostream>
using namespace std;

//! Print filedata in console file using filepath
/*!
  \param filepath a std::string.
*/
  void printFileByPath(std::string filepath);

  //! Print in console --help text
  /*!
  */
  void printHelpCmd();


#endif
