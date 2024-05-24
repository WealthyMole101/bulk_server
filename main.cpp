#include <iostream>
#include <string>
#include <vector>

#include <boost/asio/io_context.hpp>

#include "version.h"
#include "async.h"
#include "server.h"

int version() {
    return PROJECT_VERSION_PATCH;
}

using namespace std;

int main(int argc, char* argv[])
{
    try {
        boost::asio::io_context io_context;
        Server server(io_context, std::atoi(argv[1]), std::atoi(argv[2]));
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

//    auto context = connect(3);
//    vector<string> test = {"CMD1", "CMD2", "{", "CMD3", "CMD4", "}", "{", "CMD5", "CMD6", "{", "CMD7", "CMD8", "}", "CMD9", "}", "{", "CMD10", "CMD11"};

//    for (auto cmd: test) {
//        receive(cmd.c_str(), cmd.size(), context);
//    }

//    disconnect(context);
        return 0;
}
