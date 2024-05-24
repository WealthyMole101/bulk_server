#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <string>
#include <boost/asio.hpp>

#include "async.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, int bulk_size = 3) : socket_(std::move(socket)), m_bulk_size(bulk_size)
    {
    }

    ~session()
    {
        disconnect(context);
    }

    void start()
    {
        context = connect(m_bulk_size);
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::string str(data_, length);
                    std::vector<std::string> str_array;
                    std::string tmp;
                    std::stringstream str_stream(str);

                    while(std::getline(str_stream, tmp, ' ')) {
                        str_array.push_back(tmp);
                    }

                    for (auto s: str_array) {
                        receive(s.c_str(), s.size(), context);
                    }
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    int m_bulk_size;
    int* context;
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port, int bulk_size = 3) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
        m_bulk_size(bulk_size)
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<session>(std::move(socket), m_bulk_size)->start();
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
    int m_bulk_size;
};

#endif // SERVER_H
