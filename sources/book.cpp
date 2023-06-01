/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** book
*/

#include "book.hpp"

book::book(): _backend("../bdd/bdd.conf")
{
    _frontend.setBackend(&_backend);
    _frontend.run();
}

book::~book()
{
    
}