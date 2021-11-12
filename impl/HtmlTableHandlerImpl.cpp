#include "HtmlTableHandlerImpl.h"

HtmlTableHandlerImpl::HtmlTableHandlerImpl() {
    _doc = CTML::Document();
    _table = std::vector<CTML::Node>();
    // Create header
    // _table.push_back(CTML::Node(HTH_ROW_TAG)) without temp object
    _table.emplace_back(CTML::Node(HTH_ROW_TAG));
    _maxLength = 0;
}

HtmlTableHandlerImpl::~HtmlTableHandlerImpl() {}

void HtmlTableHandlerImpl::removeRow(size_t aRowNum) {
    __removeRow(aRowNum + 1);
}

void HtmlTableHandlerImpl::__removeRow(size_t&& aRowNum) {
    if ( _table.size() > aRowNum ) {
        _table.erase(_table.begin() + aRowNum);
        __findMaxLength();
    } else {
        PRINT_ERROR << "The table has only " << _table.size() - 1 << " rows, but requested to remove " << aRowNum << std::endl;
        //exit(2);
    }
}

void HtmlTableHandlerImpl::__fillMaxLength(CTML::Node& aNode) {
    _maxLength = std::max(aNode.GetChildren().size(), _maxLength);
}

void HtmlTableHandlerImpl::__findMaxLength() {
    _maxLength = 0;
    for (auto iter = _table.begin(); iter != _table.end(); iter++) {
        if ( iter->GetChildren().size() > _maxLength ) {
            _maxLength = iter->GetChildren().size();
        }
    }
}

void HtmlTableHandlerImpl::__cleanNode(CTML::Node& aNode) {
    auto&& size = aNode.GetChildren().size();

    for (auto i = 0; i < size; i++) {
        aNode.RemoveChild(i);
    }
}
void HtmlTableHandlerImpl::__cleanNode(const size_t& aNum) {
    __cleanNode(_table[aNum]);
}
/*
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
        __createCell(_header, std::move(std::string("th")), arg);
    }
}

void HtmlTableHandlerImpl::setRow(size_t aRowNumber, std::initializer_list<char const*> anArgs) {
    if ( ! _body.empty()) {
        __cleanNode(*(_body[__getMaxIndex(aRowNumber)]));
    }
    appendRow(__getMaxIndex(aRowNumber), anArgs);
}

void HtmlTableHandlerImpl::appendRow(int aRowNumber, std::initializer_list<const char*> anArgs) {
    for( auto arg : anArgs) {
        __appendRow(HTH_CELL_TAG, arg);
    }
}


void HtmlTableHandlerImpl::__cleanNode(CTML::Node& aNode) {
    auto size = aNode.GetChildren().size();

    for (auto i = 0; i < size; i++) {
        aNode.RemoveChild(i);
    }
}

void HtmlTableHandlerImpl::__cleanNode(size_t& aNum) {
    __cleanNode(*(getBody()[aNum]));
}

void HtmlTableHandlerImpl::__fillMaxLength(CTML::Node* aValue) {
    PRINT << "GetChildren().size(): " << aValue->GetChildren().size() << std::endl;
    PRINT << "_maxLength: " << _maxLength << std::endl;
    _maxLength = std::max(aValue->GetChildren().size(), _maxLength);
}

size_t HtmlTableHandlerImpl::__getMaxIndex(size_t& aNum) {
    if (_body.empty()) {
        return 0;
    } else {
        return std::min(aNum, _body.size() - 1);
    }
}
*/