#pragma once
#include "../CTML/include/ctml.hpp"
#include <string>
#include <tuple>
#include <HTHConst.h>
#include <list>

class HtmlTableHandlerImpl {

public:
    HtmlTableHandlerImpl();
    HtmlTableHandlerImpl(unsigned short int a_size_h, unsigned short int a_size_w);
    ~HtmlTableHandlerImpl();

    template<typename ...T>void setHeader(T&... anArgs);
    void setHeader(std::initializer_list<const char*> anArgs);
    void setHeader(std::list<const char*> anArgs);

    template<typename ...T>void appendHeader(T&... anArgs);
    void appendHeader(std::initializer_list<const char*> anArgs);
    void appendHeader(std::list<const char*> anArgs);

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
    CTML::Document _doc;
    unsigned short int _size_h;
    unsigned short int _size_w;
    void cleanNode(CTML::Node& aNode);
    template<typename T>
    void _createHeader(T aValue);
    };
