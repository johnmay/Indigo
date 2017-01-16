/****************************************************************************
 * Copyright (C) 2009-2015 EPAM Systems
 * 
 * This file is part of Indigo toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#ifndef __otion_manager_h__
#define __otion_manager_h__

#include "base_cpp/red_black.h"
#include "base_cpp/os_sync_wrapper.h"

#include <sstream>

using namespace indigo;

#define DECL_SET_OPT_HANDLER(suffix, ftype, type, map)               \
   DLLEXPORT void setOptionHandler##suffix (const char* name, ftype func);     \

#define DEF_SET_OPT_HANDLER(suffix, ftype, type, map)                \
   void setOptionHandler##suffix (const char* name, ftype func) {    \
      if (typeMap.find(name))                                        \
         throw Error("Option \"%s\" already defined", name);         \
      typeMap.insert(name, type);                                    \
      map.insert(name, func);                                        \
   }
                                                         

#define DEF_SET_GET_OPT_HANDLER(suffix, fSetType, fGetType, type, mapSet, mapGet)            \
   void setOptionHandler##suffix (const char* name, fSetType setFunc, fGetType getFunc) {    \
      if (typeMap.find(name))                                                                \
         throw Error("Option \"%s\" already defined", name);                                 \
      typeMap.insert(name, type);                                                            \
      mapSet.insert(name, setFunc);                                                          \
      mapGet.insert(name, getFunc);                                                          \
   }

#define CHECK_OPT_DEFINED(name) \
      if (!typeMap.find(name)) \
         throw Error("Property \"%s\" not defined", name)

#define CHECK_OPT_TYPE(name, type) \
      if (typeMap.at(name) != type) \
         throw Error("Property type mismatch", name)

#define SET_BOOL_OPTION(option)                                    \
   [](int enabled) {                                               \
      option = (enabled != 0);                                     \
   },                                                              \
   [](int& enabled) {                                              \
      enabled = (option != 0);                                     \
   }

#define SET_INT_OPTION(option)                                     \
   [](int value) {                                                 \
      option = value;                                              \
   },                                                              \
   [](int& value) {                                                \
      value = option;                                              \
   }

#define SET_FLOAT_OPTION(option)                                   \
   [](float value) {                                               \
      option = value;                                              \
   },                                                              \
   [](float& value) {                                              \
      value = option;                                              \
   }

#define SET_COLOR_OPTION(option)                                   \
   [](float r, float g, float b) {                                 \
      option.set(r, g, b);                                         \
   },                                                              \
   [](float& r, float& g, float& b) {                              \
      r = option.x;                                                \
      g = option.y;                                                \
      b = option.z;                                                \
   }

#define SET_XY_OPTION(optionX, optionY)                            \
   [](int x, int y) {                                              \
      optionX = x;                                                 \
      optionY = y;                                                 \
   },                                                              \
   [](int& x, int& y) {                                            \
      x = optionX;                                                 \
      y = optionY;                                                 \
   }

#define SET_STR_OPTION(option)                                     \
   [](const char* value) {                                         \
      option.readString(value, true);                              \
   },                                                              \
   [](char* value, int len) {                                      \
      copyStrValue(option, value, len);                            \
   }

class OptionManager {
public:
    typedef void (*optf_string_t) (const char*);
    typedef void (*optf_int_t) (int);
    typedef void (*optf_bool_t) (int);
    typedef void (*optf_float_t) (float);
    typedef void (*optf_color_t) (float, float, float);
    typedef void (*optf_xy_t) (int, int);
    typedef void (*optf_void_t) ();

    typedef void (*get_optf_string_t) (char*, int);
    typedef void (*get_optf_int_t) (int&);
    typedef void (*get_optf_bool_t) (int&);
    typedef void (*get_optf_float_t) (float&);
    typedef void (*get_optf_color_t) (float&, float&, float&);
    typedef void (*get_optf_xy_t) (int&, int&);

   OptionManager ();

   DECL_ERROR;
   DEF_SET_GET_OPT_HANDLER(String, optf_string_t, get_optf_string_t, OPTION_STRING, hMapString, hMapGetStr)
   DEF_SET_GET_OPT_HANDLER(Int, optf_int_t, get_optf_int_t, OPTION_INT, hMapInt, hMapGetInt)
   DEF_SET_GET_OPT_HANDLER(Bool, optf_bool_t, get_optf_bool_t, OPTION_BOOL, hMapBool, hMapGetBool)
   DEF_SET_GET_OPT_HANDLER(Float, optf_float_t, get_optf_float_t, OPTION_FLOAT, hMapFloat, hMapGetFloat)
   DEF_SET_GET_OPT_HANDLER(Color, optf_color_t, get_optf_color_t, OPTION_COLOR, hMapColor, hMapGetColor)
   DEF_SET_GET_OPT_HANDLER(XY, optf_xy_t, get_optf_xy_t, OPTION_XY, hMapXY, hMapGetXY)
   DEF_SET_OPT_HANDLER(Void, optf_void_t, OPTION_VOID, hMapVoid)

   bool hasOptionHandler (const char* name);

   void callOptionHandlerInt (const char* name, int value);
   void callOptionHandlerBool (const char* name, int value);
   void callOptionHandlerFloat (const char* name, float value);
   void callOptionHandlerColor (const char* name, float r, float g, float b);
   void callOptionHandlerXY (const char* name, int x, int y);
   void callOptionHandlerVoid(const char* name);
   void callOptionHandler (const char* name, const char* value);

   void GetOptionValueStr (const char* name, char* value, int len);
   void GetOptionValueInt (const char* name, int& value);
   void GetOptionValueBool (const char* name, int& value);
   void GetOptionValueFloat (const char* name, float& value);
   void GetOptionValueColor (const char* name, float& r, float& g, float& b);
   void GetOptionValueXY (const char* name, int& x, int& y);

   int nOptions () const;

   OsLock lock;
protected:
   enum OPTION_TYPE {OPTION_STRING, OPTION_INT, OPTION_BOOL, OPTION_FLOAT, OPTION_COLOR, OPTION_XY, OPTION_VOID};

   int _parseInt (const char *str, int &val);
   int _parseBool (const char *str, int &val);
   int _parseFloat (const char *str, float& val);
   int _parseColor (const char *str, float& r, float& g, float& b);
   int _parseSize (const char *str, int& w, int& h);

   RedBlackStringMap<OPTION_TYPE, false> typeMap;

   RedBlackStringMap<optf_string_t, false> hMapString;
   RedBlackStringMap<optf_int_t, false> hMapInt;
   RedBlackStringMap<optf_bool_t, false> hMapBool;
   RedBlackStringMap<optf_float_t, false> hMapFloat;
   RedBlackStringMap<optf_color_t, false> hMapColor;
   RedBlackStringMap<optf_xy_t, false> hMapXY;
   RedBlackStringMap<optf_void_t, false> hMapVoid;

   RedBlackStringMap<get_optf_string_t, false> hMapGetStr;
   RedBlackStringMap<get_optf_int_t, false> hMapGetInt;
   RedBlackStringMap<get_optf_bool_t, false> hMapGetBool;
   RedBlackStringMap<get_optf_float_t, false> hMapGetFloat;
   RedBlackStringMap<get_optf_color_t, false> hMapGetColor;
   RedBlackStringMap<get_optf_xy_t, false> hMapGetXY;

   template <typename T> 
   void callOptionHandlerT (const char *name, T arg)
   {
      // Convert to string for default string parsing
      std::stringstream ss;
      ss << arg;
      std::string converted = ss.str();
      callOptionHandler(name, converted.c_str());
   }

private:
   OptionManager (const OptionManager&);
};

#endif //__otion_manager_h__
