#pragma once

static const std::string HTH_TABLE_TAG = "table";
static const std::string HTH_ROW_TAG = "tr";
static const std::string HTH_HEADER_CELL_TAG = "th";
static const std::string HTH_CELL_TAG = "td";

#define PRINT std::cout << __FILE__ << ":" << __LINE__ << "->[" << __FUNCTION__ << "]::"
#define PRINT_ERROR std::cout << "ERROR###"<< __FILE__ << ":" << __LINE__ << "->[" << __FUNCTION__ << "]::"

#define _header _table[0]
#define _body _table[1]