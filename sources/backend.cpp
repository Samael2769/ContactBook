/**
 * @ Author: Samael
 * @ Create Time: 2023-05-22 07:07:52
 * @ Modified by: Samael
 * @ Modified time: 2023-06-03 02:49:44
 * @ Description:
 */

#include "backend.hpp"

Backend::Backend(std::string confPath) : _confPath(confPath)
{
    loadBdd();
    saveBdd();
}

Backend::~Backend()
{
}

void Backend::loadBdd()
{
    "conf: name path";
    std::ifstream file(_confPath);
    std::string str;
    std::vector<std::string> lines;
    std::map<std::string, std::string> config;

    while (std::getline(file, str))
    {
        lines.push_back(str);
    }
    for (auto &line : lines)
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;
        std::getline(ss, key, ' ');
        std::getline(ss, value, '\n');
        config[key] = value;
    }
    _config = config;
    file.close();
    for (auto &elem : _config)
    {
        std::cout << "Loading " << elem.first << " from (" << elem.second << ")" << std::endl;
        std::ifstream file(elem.second);
        std::string str;
        std::vector<std::string> lines;
        std::map<std::string, std::vector<std::string>> bdd;
        std::string key = elem.first;
        if (!file.is_open())
            throw std::runtime_error("Can't open (" + elem.second+ ")");

        while (std::getline(file, str))
        {
            lines.push_back(str);
        }
        _bdd[key] = lines;
    }
}

std::vector<std::vector<std::string>> Backend::get(std::string key)
{
    std::vector<std::vector<std::string>> values;
    for (auto &pair : _bdd)
    {
        if (pair.first == key)
        {
            values.push_back(pair.second);
            continue;
        }
        for (auto &value : pair.second)
        {
            if (value == key)
            {
                values.push_back(pair.second);
            }
        }
    }
    return values;
}

std::vector<std::vector<std::string>> Backend::post(std::string key, std::vector<std::string> value)
{
    std::vector<std::vector<std::string>> values;
    for (auto &pair : _bdd)
    {
        if (pair.first == key)
        {
            values.push_back(pair.second);
            for (auto &elem : value)
            {
                pair.second.push_back(elem);
            }
            continue;
        }
        for (auto &keyVal : pair.second)
        {
            if (keyVal == key)
            {
                values.push_back(pair.second);
                for (auto &elem : value)
                {
                    pair.second.push_back(elem);
                }
            }
        }
    }
    return values;
}

std::vector<std::vector<std::string>> Backend::patch(std::string key, std::vector<std::string> value)
{
    std::vector<std::vector<std::string>> values;
    for (auto &pair : _bdd)
    {
        if (pair.first == key)
        {
            values.push_back(pair.second);
            pair.second = value;
            continue;
        }
        for (auto &keyVal : pair.second)
        {
            if (keyVal == key)
            {
                values.push_back(pair.second);
                pair.second = value;
            }
        }
    }
    return values;
}

int Backend::del(std::string key)
{
    int ret = 0;
    for (auto &pair : _bdd)
    {
        if (pair.first == key)
        {
            _bdd.erase(pair.first);
            ret = 1;
            continue;
        }
        for (auto &keyVal : pair.second)
        {
            if (keyVal == key)
            {
                _bdd.erase(pair.first);
                ret = 1;
            }
        }
    }
    return ret;
}

int Backend::delitem(std::string key, std::vector<std::string> value)
{
    int ret = 0;
    for (auto &pair : _bdd)
    {
        if (pair.first == key)
        {
            for (auto &elem : value)
            {
                for (auto &keyVal : pair.second)
                {
                    if (keyVal == elem)
                    {
                        pair.second.erase(std::remove(pair.second.begin(), pair.second.end(), elem), pair.second.end());
                        ret = 1;
                    }
                }
            }
            continue;
        }
        for (auto &keyVal : pair.second)
        {
            if (keyVal == key)
            {
                for (auto &elem : value)
                {
                    for (auto &keyVal : pair.second)
                    {
                        if (keyVal == elem)
                        {
                            pair.second.erase(std::remove(pair.second.begin(), pair.second.end(), elem), pair.second.end());
                            ret = 1;
                        }
                    }
                }
            }
        }
    }
    return ret;
}

void Backend::saveBdd()
{
    for (auto &elem : _bdd)
    {
        std::cout << "Saving " << elem.first << " from (" << _config[elem.first] << ")" << std::endl;
        std::ofstream file(_config[elem.first]);
        if (!file.is_open())
            throw std::runtime_error("Can't open (" + _config[elem.first] + ")");
        for (auto &value : elem.second)
        {
            file << value << std::endl;
        }
        file.close();
    }
}