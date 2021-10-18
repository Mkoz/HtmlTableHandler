
#include "../CTML/include/ctml.hpp"
#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

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

    template<class ...T>void setRow(int aRowNumber, T... anArgs);
    void setRow(int aRowNumber, std::initializer_list<const char*> anArgs);
    template<typename ...T>void appendRow(int aRowNumber, T... anArgs);
    void appendRow(int aRowNumber, std::initializer_list<const char*> anArgs);
    template<typename ...T>void appendToRow(int aRowNumber, T... anArgs);
    void appendToRow(int aRowNumber, std::initializer_list<const char*> anArgs);

    template <typename anArg> void pushSell(anArg);
    template <typename anArg> void pushSell(anArg, unsigned short int a_size_h, unsigned short int a_size_w);
    std::string toString();
    CTML::Document getDoc();

public: //inline
    inline CTML::Node getHeader() { return _header;};
    inline std::vector<CTML::Node*>& getBody() { return _body;};
    inline std::tuple <unsigned short int, unsigned short int> getSize() { return std::tuple<unsigned short int, unsigned short int>(this->_size_h, this->_size_w);};
private:
    CTML::Node _header;
    std::vector<CTML::Node*> _body;
    CTML::Document _doc;
    unsigned short int _size_h;
    unsigned short int _size_w;
    void __cleanNode(CTML::Node& aNode);
    void __cleanNode(int& aNum);

    template <class T>
    void __createCell(CTML::Node& aNode, const std::string& aTag,T& aValue);
    template <typename... Args>
    void __handleTuple(std::stringstream& aStream, const std::tuple<Args...> &t);
};

#include <HtmlTableHandlerImpl.hpp>