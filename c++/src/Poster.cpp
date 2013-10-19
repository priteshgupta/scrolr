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
    //curlpp::Cleanup myCleanup;

    // standard request object.
    curlpp::Easy myRequest;

    // Set the URL.
    myRequest.setOpt(new curlpp::options::Url(std::string("http://www.wikipedia.com")));

    // Send request and get a result.
    // By default the result goes to standard output.
    // Here I use a shortcut to get it in a string stream ...
    //std::ostringstream os;
    myRequest.perform();
}

using namespace curlpp::options;

void Poster::send2()
{
        try
        {
                // That's all that is needed to do cleanup of used resources (RAII style).
                curlpp::Cleanup myCleanup;

                // Our request to be sent.
                curlpp::Easy myRequest;

                // Set the URL.
                myRequest.setOpt<Url>("http://www.facebook.com");

                // Send request and get a result.
                // By default the result goes to standard output.
                myRequest.perform();
        }

        catch(curlpp::RuntimeError & e)
        {
                std::cout << e.what() << std::endl;
        }

        catch(curlpp::LogicError & e)
        {
                std::cout << e.what() << std::endl;
        }
}
