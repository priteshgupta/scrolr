#ifndef POSTER_H_
#define POSTER_H_

#include <string>

/*
 * A small class whose sole responsibility is to post info to the web
 */
class Poster
{
public:
    Poster(std::string url);
    void send(std::string message);
private:
    std::string m_url;
};

#endif // POSTER_H_
