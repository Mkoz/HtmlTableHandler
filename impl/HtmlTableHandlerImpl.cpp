#include "HtmlTableHandlerImpl.h"

HtmlTableHandlerImpl::HtmlTableHandlerImpl() : _size_w(0), _size_h(0){
    _doc = CTML::Document();
    _header = CTML::Node(HTH_ROW_TAG);
    _body = std::vector<CTML::Node>();
}

HtmlTableHandlerImpl::HtmlTableHandlerImpl(unsigned short int a_size_h, unsigned short int a_size_w) : HtmlTableHandlerImpl() {
    _size_w = a_size_w;
    _size_h = a_size_h;
}

HtmlTableHandlerImpl::~HtmlTableHandlerImpl(){}

void HtmlTableHandlerImpl::setHeader(std::initializer_list<char const*> anArgs) {
    __cleanNode(_header);
    appendHeader(anArgs);
}

void HtmlTableHandlerImpl::appendHeader(std::initializer_list<char const*> anArgs) {
    for( auto arg : anArgs) {
        __createRow(std::move(std::string("th")),arg);
    }
}

void HtmlTableHandlerImpl::__cleanNode(CTML::Node & aNode) {
    auto size = aNode.GetChildren().size();
    for (auto i = 0; i < size; i++) {
        aNode.RemoveChild(i);
    }
}

void HtmlTableHandlerImpl::__cleanNode(int& aNum) {
    __cleanNode(getBody()[aNum]);
}