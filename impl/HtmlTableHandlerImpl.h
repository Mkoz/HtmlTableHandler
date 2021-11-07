
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
    ~HtmlTableHandlerImpl();


    template<class ...T>
    void setHeader(T... anArg);
    template<class ...T>
    void appendHeader(T... anArg);
    template<class ...T>
    void setRow(size_t& aRowNumber, T... anArg);
    template<class ...T>
    void appendRow(size_t& aNode, T... anArg);
    template<class ...T>
    void addRow( T... anArg);
    void removeRow(size_t aRowNum);

public: //inline
    inline CTML::Node& getHeader() { return _table[0];};
    //inline std::vector<CTML::Node>& getBody() { return _body;};
    inline std::pair<unsigned short int, unsigned short int> getSize() {
        return std::pair<size_t, size_t>(this->_table.size(), this->_maxLength);
    };

private:
    // Vector contains rows
    std::vector<CTML::Node> _table;
    CTML::Document _doc;

    size_t _maxLength;

    template <class T>
    CTML::Node __createCell(const std::string& aTag,T& aValue);
    template <typename... Args>
    void __handleTuple(std::stringstream& aStream, const std::tuple<Args...> &t);
    template <class T>
    void __appendCell(CTML::Node& aRow, const std::string& aTag, T& aValue);
    void __fillMaxLength(CTML::Node& aNode);
    void __cleanNode(CTML::Node& aNode);
    void __cleanNode(const size_t& aNum);
    template <class... Args>
    void __appendRow(CTML::Node& aNode, const std::string& aCellTag, Args... anArgs);
    void __removeRow(size_t&& aRowNum);
};

#include <HtmlTableHandlerImpl.hpp>

/*
class HtmlTableHandlerImpl {

public:
    HtmlTableHandlerImpl();
    ~HtmlTableHandlerImpl();

    template<class ...T>void setHeader(T... anArgs);
    void setHeader(std::initializer_list<const char*> anArgs);
    template<typename ...T>void appendHeader(T... anArgs);
    void appendHeader(std::initializer_list<const char*> anArgs);

    template<class ...T>void setRow(size_t aRowNumber, T... anArgs);
    void setRow(size_t aRowNumber, std::initializer_list<const char*> anArgs);

    template<class ...T>void appendRow(int aRowNumber, T... anArgs);
    void appendRow(int aRowNumber, std::initializer_list<const char*> anArgs);
    template<class ...T>void appendToRow(int aRowNumber, T... anArgs);
    void appendToRow(int aRowNumber, std::initializer_list<const char*> anArgs);

    template <typename anArg> void pushSell(anArg);
    template <typename anArg> void pushSell(anArg, unsigned short int a_size_h, unsigned short int a_size_w);
    std::string toString();
    CTML::Document getDoc();

public: //inline
    inline CTML::Node getHeader() { return _header;};
    inline std::vector<CTML::Node*>& getBody() { return _body;};
    inline std::pair<unsigned short int, unsigned short int> getSize() {
        return std::pair<size_t, size_t>(this->_body.size() + 1, this->_maxLength);
    };

private:
    CTML::Node _header;
    std::vector<CTML::Node*> _body;
    CTML::Document _doc;
    unsigned short int _size_h;
    unsigned short int _size_w;
    size_t _maxLength;

    void __cleanNode(CTML::Node& aNode);
    void __cleanNode(size_t& aNum);
    void __fillMaxLength(CTML::Node* aValue);
    size_t __getMaxIndex(size_t& aNum);
    template <class... T>
    void __createRow(CTML::Node& aNode, const std::string& aTag, T... anArgs);
    template <class T>
    void __createCell(CTML::Node& aNode, const std::string& aTag,T& aValue);
    template <typename... Args>
    void __handleTuple(std::stringstream& aStream, const std::tuple<Args...> &t);
    template <class T1, class T2>
    void __appendRow(T1& aTag, T2& aRow);
    template <class T>
    void __appendRow(T& aRow);
};

 */