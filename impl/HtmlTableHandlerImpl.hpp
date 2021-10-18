#pragma once

template<typename ...T>
void HtmlTableHandlerImpl::appendRow(int aRowNumber, T... anArgs) {
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    auto &&t = std::forward_as_tuple(anArgs...);
    std::stringstream theStream;

    /*  does not work for gcc 10.2 should be fixed at 11.XX
    handle(theStream, t);
    */
    __handleTuple(theStream, t);
    std::string tmpStr("");
    while (std::getline(theStream, tmpStr)) {
        __createCell(_header, HTH_CELL_TAG, tmpStr);
    }
}

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
    std::stringstream theStream;

    /*  does not work for gcc 10.2 should be fixed at 11.XX
    handle(theStream, t);
    */
    __handleTuple(theStream, t);
    std::string tmpStr("");
    while (std::getline(theStream, tmpStr)) {
        __createCell(_header, HTH_HEADER_CELL_TAG, tmpStr);
    }
}
//throw std::overflow_error(std::to_string(aRowNumber) + " is too");

template<class ...T>
void HtmlTableHandlerImpl::setRow(int aRowNumber, T... anArgs) {
    // Capture args in a tuple
    // perfect forwarding allow to avoid copying
    auto &&t = std::forward_as_tuple(anArgs...);
    std::stringstream theStream;
    auto tmpStr = std::string("");
    int& index = aRowNumber;

    // Don't want to raise error in case out of size rowNumber, but just append to the end
    if ( aRowNumber >= _body.size() ) {
        index = _body.size();
        //Create instance of row
        _body.push_back(new CTML::Node(HTH_ROW_TAG));
    } else {
        __cleanNode(*(_body[index]));
    }

    // Create link to avoid *ptr actions
    auto& theNode = *(_body[index]);

    __handleTuple(theStream, t);

    while (std::getline(theStream, tmpStr)) {
        __createCell(theNode, HTH_CELL_TAG, tmpStr);
    }

    //*(getBody()[index]) = std::move(tmpStr);

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
    std::stringstream tmpStream;
    tmpStream << aValue;
    aTh.AppendText(tmpStream.str());
    aNode.AppendChild(aTh);
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
