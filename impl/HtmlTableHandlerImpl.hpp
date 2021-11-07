#pragma once

/*
template<class ...T>
void HtmlTableHandlerImpl::setHeader(T... anArgs) {
    __cleanNode(_header);
    appendHeader(anArgs...);
}

template<typename ...T>
void HtmlTableHandlerImpl::appendHeader(T... anArgs) {
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    auto &&t = std::forward_as_tuple(anArgs...);
    auto theStream = std::stringstream();

    __handleTuple(theStream, t);

    std::string tmpStr("");
    while (std::getline(theStream, tmpStr)) {
        __createCell(_header, HTH_HEADER_CELL_TAG, tmpStr);
    }
    __fillMaxLength(&_header);
}
//throw std::overflow_error(std::to_string(aRowNumber) + " is too");

template<class ...T>
void HtmlTableHandlerImpl::setRow(size_t aRowNumber, T... anArgs) {
    if ( ! _body.empty()) {
        __cleanNode(*(_body[__getMaxIndex(aRowNumber)]));
    }
    appendRow(aRowNumber, anArgs...);
}

template<class ...T>
void HtmlTableHandlerImpl::appendRow(int aRowNumber, T... anArgs) {
    auto &&t = std::forward_as_tuple(anArgs...);
    auto tmpStr = std::string("");
    auto theStream = std::stringstream();
    int& index = aRowNumber;

    // Don't want to raise error in case out of size rowNumber, but just append to the end
    if ( aRowNumber >= _body.size() ) {
        index = _body.size();
        //Create instance of row
        _body.push_back(new CTML::Node(HTH_ROW_TAG));
    }
    __createRow(*(_body[index]), HTH_CELL_TAG, anArgs...);
}
template <class T1, class T2>
void HtmlTableHandlerImpl::__appendRow(T1& aTag, T2& aRow) {
    _body.push_back(new CTML::Node(HTH_ROW_TAG));
    //_body.end()->
}

template <class T>
void HtmlTableHandlerImpl::__appendRow(T& aRow) {
    appendRow(HTH_ROW_TAG, aRow);
}


template<typename... Args>
void HtmlTableHandlerImpl::__handleTuple(std::stringstream &aStream, const std::tuple<Args...> &t) {
    std::apply([&](const auto &... args) {
        // All objects without implemented "<<" rise compile error
        ((aStream << args << std::endl), ...);
    }, t);
}

template <class T>
void HtmlTableHandlerImpl::__createCell(CTML::Node& aNode, const std::string& aTag,T& aValue) {
    CTML::Node aTh(aTag);
    auto theStream = std::stringstream();

    theStream << aValue;

    aTh.AppendText(theStream.str());
    aNode.AppendChild(aTh);
}

template <class... Args>
void HtmlTableHandlerImpl::__createRow(CTML::Node& aNode, const std::string& aTag, Args... anArgs) {
    auto &&t = std::forward_as_tuple(anArgs...);
    auto tmpStr = std::string("");
    auto theStream = std::stringstream();

    __handleTuple(theStream, t);

    while (std::getline(theStream, tmpStr)) {
        __createCell(aNode, aTag, tmpStr);
    }
    __fillMaxLength(&aNode);
}
*/

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
template <class T>
CTML::Node HtmlTableHandlerImpl::__createCell(const std::string& aTag, T& aValue) {
    CTML::Node theNode(aTag);
    auto theStream = std::stringstream();

    theStream << aValue;

    theNode.AppendText(theStream.str());
    return theNode;
}

template <class T>
void HtmlTableHandlerImpl::__appendCell(CTML::Node& aRow, const std::string& aTag, T& aValue) {
    aRow.AppendChild(std::move(__createCell(aTag, aValue)));
    __fillMaxLength(aRow);
}

template <class... Args>
void HtmlTableHandlerImpl::__appendRow(CTML::Node& aRow, const std::string& aCellTag, Args... anArgs) {
    auto &&t = std::forward_as_tuple(anArgs...);
    auto tmpStr = std::string("");
    auto tmpStream = std::stringstream();

    __handleTuple(tmpStream, t);
    while (std::getline(tmpStream, tmpStr)) {
        __appendCell(aRow, aCellTag, tmpStr);
    }
}

template<class... Args>
void HtmlTableHandlerImpl::__handleTuple(std::stringstream &aStream, const std::tuple<Args...> &t) {
    std::apply([&](const auto &... args) {
        // All objects without implemented "<<" rise compile error
        ((aStream << args << std::endl), ...);
    }, t);
}

template<class ...T>
void HtmlTableHandlerImpl::setHeader(T... anArgs) {
    __cleanNode(_header);
    appendHeader(anArgs...);
}

template<class ...T>
void HtmlTableHandlerImpl::appendHeader(T... anArgs) {
    __appendRow(_header, HTH_HEADER_CELL_TAG, anArgs...);
}

template<class ...T>
void HtmlTableHandlerImpl::setRow(size_t& aRowNumber, T... anArgs) {

    if ( _table.size() < aRowNumber) {
        // _table.push_back(new CTML::Node()) without temp object
        _table.emplace_back(CTML::Node(HTH_ROW_TAG));
        appendRow(_table.size(), anArgs...);
    } else {
        __cleanNode(aRowNumber);
        appendRow(aRowNumber, anArgs...);
    }
}

template<class ...T>
void HtmlTableHandlerImpl::addRow( T... anArgs) {

    // _table.push_back(new CTML::Node()) without temp object
    _table.emplace_back(CTML::Node(HTH_ROW_TAG));
    size_t tmp_size = _table.size() - 2;
    appendRow( tmp_size, anArgs...);

}

template<class ...T>
void HtmlTableHandlerImpl::appendRow(size_t& aRow, T... anArgs) {
    __appendRow(_table[aRow + 1], HTH_CELL_TAG, anArgs...);
}