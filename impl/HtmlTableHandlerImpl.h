#pragma once
#include "../CTML/include/ctml.hpp"
#include <string>
#include <tuple>
#include <sstream>
#include <iostream>

#include <HTHConst.h>

class HtmlTableHandlerImpl {

public:
    HtmlTableHandlerImpl();
    HtmlTableHandlerImpl(unsigned short int a_size_h, unsigned short int a_size_w);
    ~HtmlTableHandlerImpl();

    template<class ...T>void setHeader(T... anArgs);
    void setHeader(std::initializer_list<const char*> anArgs);
    template<typename ...T>void appendHeader(T... anArgs);
    void appendHeader(std::initializer_list<const char*> anArgs);

    template<class ...T>void setRow(T... anArgs);
    void setRow(std::initializer_list<const char*> anArgs);
    template<typename ...T>void appendRow(T... anArgs);
    void appendRow(std::initializer_list<const char*> anArgs);

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
    void __cleanNode(CTML::Node& aNode);
    template<typename T>
    void __createRow(std::string&& aTag,T aValue);
    template <typename... Args>
    void __handleTuple(std::stringstream& aStream, const std::tuple<Args...> &t);
};


template<class ...T>
void HtmlTableHandlerImpl::setHeader(T... anArgs) {
    __cleanNode(_header);
    appendHeader(anArgs...);
}

template<typename ...T>
void HtmlTableHandlerImpl::appendHeader(T... anArgs) {
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    auto&& t = std::forward_as_tuple(anArgs...);
    std::stringstream theStream;

    /*  does not work for gcc 10.2 should be fixed at 11.XX
    handle(theStream, t);
     */
    __handleTuple(theStream, t);
    std::string tmpStr("");
    while(std::getline(theStream, tmpStr)){
        __createRow(std::move(std::string("th")), tmpStr.c_str());
    }
}


template <typename... Args>
void HtmlTableHandlerImpl::__handleTuple(std::stringstream& aStream, const std::tuple<Args...> &t) {
    std::apply([&](const auto &... args) {
        // All objects without implemented "<<" rise compile error
        ((aStream << args << std::endl), ...);
    }, t);
}

/*  does not work for gcc 10.2 should be fixed at 11.XX
template <size_t Size, typename... Args>
struct tupleHelper  {
    static void handle( std::stringstream& aStream, const std::tuple<Args...> &t) {
        aStream << std::get<Size>(t) << std::endl;
        tupleHelper<Size + 1, Args...>::handle(t);
    }
};

template <typename... Args>
struct tupleHelper<sizeof...(Args), Args...> {
    static void handle(const std::tuple<Args...> &) {}
};

template <typename... Args>
void handle(const std::tuple<Args...> &t) {
    tupleHelper<0, Args...>::handle(t);
}
*/

