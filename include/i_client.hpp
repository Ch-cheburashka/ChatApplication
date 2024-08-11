#ifndef INCLUDE_SMART_POINTERS_I_CLIENT_HPP
#define INCLUDE_SMART_POINTERS_I_CLIENT_HPP

constexpr int INVALID_SOCKET = -1;

class i_client {
public:
    virtual ~i_client() = default;
    virtual void connect() = 0;
    virtual void send(const char* message, int len) const = 0;
    [[nodiscard]] virtual const char* receive() const = 0;
    virtual void close() const = 0;
};


#endif //INCLUDE_SMART_POINTERS_I_CLIENT_HPP
