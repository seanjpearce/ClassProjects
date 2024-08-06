//Sean Pearce and Anthony Ferraro   CISC210010
#include "Book.hpp"

#include <iostream>
#include <string>
using namespace std;


Book::Book(string t, string auth, int yr, string pub, long long isbn, float rate) { //create the book duh
	title = t;
	author = auth;
	year = yr;
	publisher = pub;
	isbn13 = isbn;
	rating = rate;
	checked_out = false;
}

Book::Book() { //default constructor everything null
	title = "";
	author = "";
	year = 0;
	publisher = "";
	isbn13 = 0;
	rating = 0;
	checked_out = false;
}

float Book::getRating() {
	return rating;
}


void Book::printBook() {
	cout << "---------------------" << endl;
	cout << title << "\nAuthor: " << author << "\t\tYear: " << year << endl;
	cout << "Publisher: " << publisher << "\tISBN-13: " << isbn13 << "\tRating: " << rating << endl;
	cout << "Currently Available: " << (checked_out ? "No" : "Yes") << endl;
}

bool Book::operator<(Book b2) {
    if(author < b2.author) //compare authors
        return true;
    else if(author > b2.author)
        return false;
    else if(title < b2.title) //then compare titles
        return true;
    else
        return false;
}

bool Book::operator>(Book b2) {
    if(author > b2.author) //compare authors
        return true;
    else if(author < b2.author)
        return false;
    else if(title > b2.title) //compare titles
        return true;
    else
        return false;
}

bool Book::operator==(Book b2) {
	if(author == b2.author and title == b2.title) //compare equality of author and title
        return true;
    return false;
}

bool Book::operator!=(Book b2) {
	if(author == b2.author and title == b2.title) //compare equality of author and title
        return false;
    return true;
}

bool Book::operator<=(Book b2) {
	if(*this < b2 or *this == b2) //compare less than or equal to of book
        return true;
    return false;
}

bool Book::operator>=(Book b2) {
	if(*this > b2 or *this == b2) //compare greater than or equal to of book
        return true;
    return false;
}