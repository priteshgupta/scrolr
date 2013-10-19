#include "Poster.h"

#include <string>
#include <iostream>
#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

void Poster::send()
{
    // RAII cleanup
    curlpp::Cleanup myCleanup;

    // standard request object.
    curlpp::Easy myRequest;

    // Set the URL.
    myRequest.setOpt(new curlpp::options::Url(std::string("http://pritesh.info/test_kent.php?test=Mack_was_here")));

    // Send request and get a result.
    // By default the result goes to standard output.
    // Here I use a shortcut to get it in a string stream ...
    myRequest.perform();
}
