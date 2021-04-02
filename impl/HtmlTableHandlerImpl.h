#pragma once
#include "../CTML/include/ctml.hpp"
#include <string>
#include <tuple>

class HtmlTableHandlerImpl {

public:
    HtmlTableHandlerImpl();
    HtmlTableHandlerImpl(unsigned short int a_size_h, unsigned short int a_size_w);
    ~HtmlTableHandlerImpl();

    template <class...anArgs> void setHeader(...);
    template <typename anArg> void pushSell(anArg);
    template <typename anArg> void pushSell(anArg, unsigned short int a_size_h, unsigned short int a_size_w);
    std::string toString();
    CTML::Document getDoc();

public: //inline
    inline CTML::Node getHeader() { return _header;};
    inline CTML::Node getBody() { return _body;};
    inline std::tuple <unsigned short int, unsigned short int> getSize() { return std::tuple<unsigned short int, unsigned short int>(this->_size_h, this->_size_w);};
private:
    CTML::Node _header;
    CTML::Node _body;
    unsigned short int _size_h;
    unsigned short int _size_w;
};
