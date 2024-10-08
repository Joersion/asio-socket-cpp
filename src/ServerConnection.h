#pragma once

#include <map>

#include "Session.h"

class ServerConnection : public Connection {
public:
    ServerConnection(int port, int timeout = 0);
    ~ServerConnection() = default;
    ServerConnection(const ServerConnection& other) = delete;
    ServerConnection& operator=(const ServerConnection& other) = delete;

public:
    void start();
    void send(const std::string& ip, const std::string& msg);
    // 重写关闭方法，防止子类继续重写
    virtual void doClose(const std::string& ip, int port, const std::string& error) override final;

private:
    void accept();
    void acceptHandle(std::shared_ptr<Session> session, const boost::system::error_code& error);
    void addSession(std::shared_ptr<Session> session);
    void delSession(const std::string& ip);

private:
    boost::asio::io_context& ioContext_;
    // boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::map<std::string, std::shared_ptr<Session>> sessions_;
    std::mutex mutex_;
    int timeout_;
};
