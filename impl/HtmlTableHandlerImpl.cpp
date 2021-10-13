#include "HtmlTableHandlerImpl.h"

HtmlTableHandlerImpl::HtmlTableHandlerImpl() : _size_w(0), _size_h(0){
    _doc = CTML::Document();
    _header = CTML::Node(HTH_DEFAULT_TABLE_NAME);
}

HtmlTableHandlerImpl::HtmlTableHandlerImpl(unsigned short int a_size_h, unsigned short int a_size_w) : HtmlTableHandlerImpl() {
    _size_w = a_size_w;
    _size_h = a_size_h;
}

HtmlTableHandlerImpl::~HtmlTableHandlerImpl(){}

/*
// Useless method wonna try variadic templates
template<class ...T>
void HtmlTableHandlerImpl::setHeader(T... anArgs) {
    cleanNode(_header);
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    std::cout<<"Remove me constructor 1"<<std::endl;
    auto&& t = std::forward_as_tuple(anArgs...);
    std::istringstream theStream;
    for(unsigned short int i = 0; i < sizeof...(anArgs); ++i) {
        auto value = std::get<i>(t);
        //static_assert(std::is_same<decltype(value), std::string>::value, "arguments must be std::string");
        theStream << value << std::endl;
    }
    std::string tmpStr("");
    while(std::getline(theStream, tmpStr)){
        std::cout << "DEBUG:: " << tmpStr.c_str() << std::endl;
        _createHeader(tmpStr.c_str());
    }
}*/

void HtmlTableHandlerImpl::setHeader(std::initializer_list<char const*> anArgs) {
    cleanNode(_header);
    for( auto arg : anArgs) {
        _createHeader(arg);
    }
}

void HtmlTableHandlerImpl::setHeader(std::list<char const*> anArgs) {
    cleanNode(_header);
    for( auto arg : anArgs) {
        _createHeader(arg);
    }
}

template<typename ...T>
void HtmlTableHandlerImpl::appendHeader(T&... anArgs) {
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    auto&& t = std::forward_as_tuple(anArgs...);
    for(unsigned short int i = 0; i < sizeof...(anArgs); ++i) {
        auto value = std::get<i>(t);
        _createHeader(value);
    }
}

void HtmlTableHandlerImpl::appendHeader(std::initializer_list<char const*> anArgs) {
    for( auto arg : anArgs) {
        _createHeader(arg);
    }
}

void HtmlTableHandlerImpl::appendHeader(std::list<char const*> anArgs) {
    for( auto arg : anArgs) {
        _createHeader(arg);
    }
}

template<class T>
void HtmlTableHandlerImpl::_createHeader(T aValue) {
    CTML::Node aTh("th");
    aTh.AppendText(aValue);
    _header.AppendChild(aTh);
}

void HtmlTableHandlerImpl::cleanNode(CTML::Node & aNode) {
    auto size = aNode.GetChildren().size();
    for (auto i = 0; i < size; i++) {
        aNode.RemoveChild(i);
    }
}