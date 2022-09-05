/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

/*
 * A Utility class for string operations
 *
 * COPYRIGHT ANSYS. ALL RIGHTS RESERVED.
 *
 * author: Awanish Kumar (copied from cue/Utilities)
 * version: $Revision: 128302 $
 * date: $Date: 2013-12-19 02:03:37 +0530 (Wed, 19 Dec 2013) $
 * $Id: stringutils.h 128302 2012-12-18 20:33:37Z awkumar $
 */
#ifdef __cplusplus


#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

typedef std::list<std::string>              StringList;
typedef std::map<std::string, std::string>  StringMap;
typedef std::pair<std::string, std::string> StringPair;
typedef std::set<std::string>               StringSet;
typedef std::vector<std::string>            StringVector;


namespace StringUtils
{

StringVector stringToVector ( const std::string &p_string, char delim );
StringVector stringToVectorUntrimmed( const std::string &p_string, char p_delim );
StringVector stringToVectorQuoted( const std::string &p_string, char p_delim );
StringVector stringToVectorWithEscape ( const std::string &p_string,
                                        char delim, char p_escape = '\\' );
StringSet stringToSet ( const std::string &p_string, char delim );

StringMap stringToMap ( const std::string &p_string, char delim = '\n' );

std::string vectorToString ( const StringVector &p_vector, char delim );
std::string setToString ( const StringSet &p_set, char delim );

std::string listToString(const StringList, const std::string &p_delim);

std::string vectorToOneLineString( const StringVector &p_vector );

std::size_t stringVectorToStringSet( const StringVector &p_vector,
                                     StringSet &p_set );
std::size_t stringSetToStringVector( const StringSet &p_set,
                                     StringVector &p_vector );
std::size_t stringSetAppend( StringSet &p_set, const StringSet &p_setToAppend );

std::string removeWhitespace(const std::string &p_string);
std::string replaceWhitespace(const std::string &p_string, char p_c = '_');
std::string simplifyWhitespace(const std::string &p_string);

std::string toString (int p_num);
std::string toString (double p_num, const std::string &p_format = "%12g");

std::string replaceSubstring( const std::string &p_s,
                              const std::string &p_substr,
                              const std::string &p_newSubStr );

std::string keepOnlyDigits( const std::string &p_s );

const char **createCharsFromStringVector(const StringVector &p_input,
                                         bool p_addNull = false);



StringVector splitValue( const std::string &p_value, char p_delim = ',' );

StringPair splitString( const std::string &p_str, const char p_token);

StringPair  splitNameValue( const std::string &p_str );

StringMap createNameValueMap ( const StringVector &p_strvec );

std::string simplifyPath(const std::string &p_path);

void removeContinuation(StringVector &p_lines);


void splitPathName(const std::string &p_fullPath,
                   std::string *p_name, std::string *p_path);

std::string pathBaseName(const std::string &p_path);

StringPair  splitObjectTypeAndName (const std::string &p_str);

std::string toTitleCaseWithPunct( const std::string &p_str );

std::string toLowerCase( const std::string &p_str );

std::string toUpperCase( const std::string &p_str );


std::string splitStringToSize( const std::string &p_string,
                               int p_indent,
                               unsigned int p_linelength = 80 );

bool startsWith( const std::string &p_string,
                 const std::string &p_substring );
bool endsWith( const std::string &p_string,
               const std::string &p_substring );
bool removeFromEnd( std::string &p_string,
                    const std::string &p_substring );

std::string::size_type findLastWord( const std::string &p_string );

bool stringToBool( const std::string &p_value );
std::string boolToString( bool p_value );
std::pair<float, bool> valueAsFloat(const std::string &p_value,
                                    std::string &p_num, std::string &p_units);

bool isTrue( const std::string &p_value, bool *p_isValid = 0 );

void addToList( std::string &p_list,
                const std::string &p_itemToAdd );
void removeFromList( std::string &p_list,
                     const std::string &p_itemToRemove );
bool isInList( const std::string &p_list,
               const std::string &p_itemToCheck );

/**
 * Convert string value to value of the given type.
 *
 * @param p_string (in) the string value to be converted. An empty
 *                     input value will fail to convert.
 * @param p_val (out) the converted value in the appropriate 'Type'
 *
 * @return bool. Success or failure.
 */
template <typename Type> bool
toType(const std::string &p_string, Type &p_val);
template <typename Type> bool
toType(const std::string &p_string, Type &p_val)
{
  p_val = 0;
  std::istringstream is(p_string);
  return (is >> p_val) && is.eof();
}

}
#endif
#endif /* _STRINGUTILS_H */
