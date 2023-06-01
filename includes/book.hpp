/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** book
*/

#ifndef BOOK_HPP_
#define BOOK_HPP_

#include "backend.hpp"
#include "frontend.hpp"

class book {
    public:
        book();
        ~book();
    protected:
    private:
        Backend _backend;
        Frontend _frontend;
};

#endif /* !BOOK_HPP_ */
