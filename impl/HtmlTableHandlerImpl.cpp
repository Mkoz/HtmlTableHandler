#include "HtmlTableHandlerImpl.h"

HtmlTableHandlerImpl::HtmlTableHandlerImpl() {
    _doc = CTML::Document();
    _header = CTML::Node(HTH_ROW_TAG);
    _body = std::vector<CTML::Node*>();
    _maxLength = 0;
}

HtmlTableHandlerImpl::~HtmlTableHandlerImpl(){
    for ( auto obj : _body ) {
        delete obj;
    }
}

void HtmlTableHandlerImpl::setHeader(std::initializer_list<char const*> anArgs) {
    __cleanNode(_header);
    appendHeader(anArgs);
}

void HtmlTableHandlerImpl::appendHeader(std::initializer_list<char const*> anArgs) {
    for( auto arg : anArgs) {
        __createCell(_header, std::move(std::string("th")),arg);
    }
}

void HtmlTableHandlerImpl::setRow(int aRowNumber, std::initializer_list<char const*> anArgs) {
    __cleanNode(_header);
    appendRow(aRowNumber, anArgs);
}

void HtmlTableHandlerImpl::__cleanNode(CTML::Node& aNode) {
    auto size = aNode.GetChildren().size();
    for (auto i = 0; i < size; i++) {
        aNode.RemoveChild(i);
    }
}

void HtmlTableHandlerImpl::__cleanNode(int& aNum) {
    __cleanNode(*(getBody()[aNum]));
}

void HtmlTableHandlerImpl::__fillMaxLength(CTML::Node* aValue) {
    _maxLength = std::max(aValue->GetChildren().size(), _maxLength);
}
