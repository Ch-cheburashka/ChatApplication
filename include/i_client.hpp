#ifndef CHATAPPLICATION_I_CLIENT_HPP
#define CHATAPPLICATION_I_CLIENT_HPP

constexpr int INVALID_SOCKET = -1;

class i_client {
public:
    virtual ~i_client() = default;
    virtual void connect() = 0;
    virtual void send(int, const char* message, int len) const = 0;
    [[nodiscard]] virtual const char* receive(int) const = 0;
    virtual void close() const = 0;
};


#endif //CHATAPPLICATION_I_CLIENT_HPP
