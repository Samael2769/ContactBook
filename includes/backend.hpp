/**
 * @ Author: Samael
 * @ Create Time: 2023-05-22 07:05:01
 * @ Modified by: Samael
 * @ Modified time: 2023-06-01 06:03:40
 * @ Description:
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <sstream>

class Backend
{
    public:
        Backend(std::string confPath);
        ~Backend();
        void loadBdd();
        std::vector<std::vector<std::string>> get(std::string key);
        std::map<std::string, std::vector<std::string>> getAll() { return _bdd;}
        std::vector<std::vector<std::string>> post(std::string key, std::vector<std::string> value);
        std::vector<std::vector<std::string>> patch(std::string key, std::vector<std::string> value);
        int del(std::string key);
        int delitem(std::string key, std::vector<std::string> value);
        void saveBdd();
    protected:
    private:
        std::string _confPath;
        std::map<std::string, std::string> _config;
        std::map<std::string, std::vector<std::string>> _bdd;
};