#include "Poster.h"

#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

Poster::Poster(std::string url = "http://pritesh.info/test_kent.php?test=") : m_url(url)
{}

void Poster::send(std::string message)
{
    // RAII cleanup
    curlpp::Cleanup myCleanup;

    // standard request object.
    curlpp::Easy myRequest;

    // Set the URL.
    myRequest.setOpt(new curlpp::options::Url(std::string(m_url + message)));

    // Send request and get a result.
    // By default the result goes to standard output.
    // Here I use a shortcut to get it in a string stream ...
    myRequest.perform();
}
