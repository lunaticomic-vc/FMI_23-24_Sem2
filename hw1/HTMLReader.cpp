#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#pragma warning(disable:4996)

//comments included to explain algorithm

namespace CONSTANTS
{
    constexpr size_t MAX_ROW_COUNT = 100;
    constexpr size_t MAX_CELLS_PER_ROW = 15;
    constexpr size_t MAX_CHARS_PER_CELL = 50;
    constexpr size_t MAX_CHARS_BEFORE_DECODE = 200;
    constexpr int MAX_CHARS_TAG = 16;
    constexpr int MAX_FILENAME = 100;
}

using namespace CONSTANTS;

char buffer[MAX_CHARS_TAG];
size_t rowNum = 0;
size_t colsNumb = 0;
size_t maxLenghtOfCell = 0;

struct Cell
{
    char cell[MAX_CHARS_PER_CELL] = "";
    bool isFull = 0;
    bool isHeader = 0;
};

struct Row
{
    Cell col[MAX_CELLS_PER_ROW];
};

struct Table
{
    Row row[MAX_ROW_COUNT];
};

enum Tags
{
    tableOp = 1,
    headerOp,
    rowOp,
    cellOp,
    tableCl,
    headerCl,
    rowCl,
    cellCl,
    notTag
};

void charEntReader(char* str)
{
    char* src = str;
    char* dest = str;

    while (*src)
    {
        if (*src == '&' && src[1] == '#')
        {
            int code = 0;
            src += 2;
            while (*src >= '0' && *src <= '9')
            {
                code = code * 10 + (*src - '0');
                src++;
            }
            src--;
            *dest = (char)(code);
        }
        else
        {
            *dest = *src;
        }
        src++;
        dest++;
    }

    *dest = '\0';
}

int sstrcmp(const char* str1, const char* str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        ++str1;
        ++str2;
    }

    if (*str1 == *str2)
    {
        return 0;
    }
    else if (*str1 < *str2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}


void sstrcpy(char* destination, char* source)
{
    if (destination == nullptr || source == nullptr)
    {
        return;
    }

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
}

Tags getTag(std::ifstream& ifs, const char& g)
{
    if (g == '<')
    {
        ifs.getline(buffer, MAX_CHARS_TAG, '>');
        if (sstrcmp(buffer, "/table") == 0)return Tags::tableCl;
        if (sstrcmp(buffer, "table") == 0)return Tags::tableOp;
        if (sstrcmp(buffer, "th") == 0)return Tags::headerOp;
        if (sstrcmp(buffer, "tr") == 0)return Tags::rowOp;
        if (sstrcmp(buffer, "td") == 0)return Tags::cellOp;
        if (sstrcmp(buffer, "/th") == 0)return Tags::headerCl;
        if (sstrcmp(buffer, "/tr") == 0)return Tags::rowCl;
        if (sstrcmp(buffer, "/td") == 0)return Tags::cellCl;
        return Tags::notTag;
    }
    return Tags::notTag;
}

void getCell(std::ifstream& ifs, const size_t& rowNum, const size_t& colNum, Table& table)
{
    int ind = 0, lenOfStr = 0;
    char g = ifs.get();
    bool wordFlag = 0;
    char cellContent[MAX_CHARS_BEFORE_DECODE];

    while (g == ' ' || g == '\n' || g == '\t')
    {
        g = ifs.get(); //cleaning whitespace in beginning
    }

    Tags tag = getTag(ifs, g);

    //If empty content - buffer string is empty
    if (tag == Tags::cellCl || tag == Tags::headerCl)
    {
        cellContent[0] = '\0';
    }
    else
    {
        do
        {
            //Clean all newlines, replace them with a single space
            if (g == '\n')
            {
                cellContent[ind++] = ' ';
                while (g == '\n')
                {
                    g = ifs.get();
                }
            }

            //Update tag
            tag = getTag(ifs, g);

            //Look for last legitimate character to use as array len
            if (g != ' ' && g != '\n' && g != '\t' && tag != Tags::cellCl && tag != Tags::headerCl)
            {
                lenOfStr = ind;
            }

            //Clean all tabs inside array for clarity, replace them with a single space
            if (g != '\t')
            {
                cellContent[ind++] = g;
                g = ifs.get();
            }
            else
            {
                while (g == '\t')
                {
                    g = ifs.get();
                }
                cellContent[ind++] = ' ';
            }

        } while (tag != Tags::cellCl && tag != Tags::headerCl);

        cellContent[++lenOfStr] = '\0';
    }

    charEntReader(cellContent);
    lenOfStr = strlen(cellContent);
    if (table.row[rowNum].col[colNum].isHeader == 1)lenOfStr += 2;
    if (lenOfStr > maxLenghtOfCell)maxLenghtOfCell = lenOfStr;
    sstrcpy(table.row[rowNum].col[colNum].cell, cellContent);
    table.row[rowNum].col[colNum].isFull = 1;
}


void fillRowWithCells(Table& table, std::ifstream& ifs, const size_t& rowNum)
{
    size_t ind = 0;
    char g = ifs.get();

    while (g == ' ' || g == '\n' || g == '\t') g = ifs.get();

    Tags tag = getTag(ifs, g);

    while (tag != Tags::rowCl)
    {
        if (tag == Tags::headerOp)
        {
            table.row[rowNum].col[ind].isHeader = 1;
        }
        getCell(ifs, rowNum, ind++, table);
        g = ifs.get();
        while (g == ' ' || g == '\n' || g == '\t') g = ifs.get();
        tag = getTag(ifs, g);
    }
    if (ind > colsNumb)colsNumb = ind;
}

void readInput(Table& table, const char* fileName)
{
    std::ifstream ifs(fileName);
    char g;
    while (!ifs.eof())
    {
        g = ifs.get();

        while (g == ' ' || g == '\n' || g == '\t')
        {
            g = ifs.get();
        }

        Tags curTag = getTag(ifs, g);

        if (curTag == Tags::rowOp)
        {
            fillRowWithCells(table, ifs, rowNum++);
        }
    }
    ifs.close();
}

Row readRowContent(const char* input, unsigned &cols)
{
    int ind = 0, indBuf = 0, indRow = 0;
    Row row;
    do
    {
        indBuf = 0;
        char buffer[MAX_CHARS_BEFORE_DECODE];
        while (input[ind] != ',' && input[ind] != '\0')
        {
            buffer[indBuf++] = input[ind++];
        }
        buffer[indBuf] = '\0';
        sstrcpy(row.col[indRow++].cell, buffer);

    } while (input[ind] != '\0');
    cols = --indRow;
    return row;
}

void addRow(Table& table, size_t row, Row rowContent, size_t amountOfCols)
{
    rowNum++;
    for (size_t i = rowNum; i >= row; i--)
    {
        for (size_t j = 0; j < colsNumb; j++)
        {
            sstrcpy(table.row[i].col[j].cell, table.row[i - 1].col[j].cell);
            table.row[i].col[j].isFull = table.row[i - 1].col[j].isFull;
            table.row[i].col[j].isHeader = table.row[i - 1].col[j].isHeader;
        }
    }
    for (int i = 0; i < amountOfCols; i++)
    {
        sstrcpy(table.row[row - 1].col[i].cell, rowContent.col[i].cell);
        table.row[row - 1].col[i].isFull = rowContent.col[i].isFull;
        table.row[row - 1].col[i].isHeader = rowContent.col[i].isHeader;
    }
    if (amountOfCols > colsNumb)colsNumb = amountOfCols;
}

void removeRow(Table& table, size_t row)
{
    for (size_t i = row - 1; i < rowNum; i++)
    {
        for (size_t j = 0; j < colsNumb; j++)
        {
            sstrcpy(table.row[i].col[j].cell, table.row[i + 1].col[j].cell);
            table.row[i].col[j].isFull = table.row[i + 1].col[j].isFull;
            table.row[i].col[j].isHeader = table.row[i + 1].col[j].isHeader;
        }
    }
    rowNum--;
}

void editCell(char* newValue, Table& table, size_t row, size_t col)
{
    if (newValue[0] != '\0')
    {
        sstrcpy(table.row[row - 1].col[col - 1].cell, newValue);

        table.row[row - 1].col[col - 1].isFull = 1;
        for (int i = 0; i < col - 1; i++)
        {
            table.row[row - 1].col[i].isFull = 1;
        }
    }
    else
    {
        table.row[row - 1].col[col - 1].isFull = 0;
        int i = 2;
        while (sstrcmp(table.row[row - 1].col[col - i].cell, "") == 0)
        {
            table.row[row - 1].col[col - i].isFull = 0;
            i++;
        }
    }
}

void fillWhiteSpace(int buffer)
{
    for (int i = 0; i < buffer; i++)
    {
        std::cout << " ";
    }
}

void printTable(const Table& table)
{
    int lenghtOfCurrCell, buffer;
    for (size_t i = 0; i < rowNum; i++)
    {
        for (size_t j = 0; j < colsNumb; j++)
        {
            int lenghtOfCurrCell = 0;

            if (table.row[i].col[j].isFull)
            {
                lenghtOfCurrCell = strlen(table.row[i].col[j].cell);

                if (table.row[i].col[j].isHeader)
                {
                    std::cout << "*"; 
                    lenghtOfCurrCell += 2; //For stars
                }
                    
                std::cout << table.row[i].col[j].cell;

            }

            buffer = maxLenghtOfCell - lenghtOfCurrCell;
            fillWhiteSpace(buffer);

            if (table.row[i].col[j].isHeader)
            {
                std::cout << "*";
            }

            std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void writeToFileFormatted(char* fileName, Table& table)
{
    std::ofstream ofs(fileName);

    ofs << "<table>" << std::endl;

    for (size_t i = 0; i < rowNum; i++)
    {
        ofs << "\t<tr>" << std::endl;

        for (size_t j = 0; j < colsNumb; j++)
        {
            if (table.row[i].col[j].isFull)
            {
                if (table.row[i].col[j].isHeader)
                {
                    ofs << "\t\t<th>";
                    ofs << table.row[i].col[j].cell;
                    ofs << "</th>" << std::endl;
                }
                else 
                {
                    ofs << "\t\t<td>";
                    ofs << table.row[i].col[j].cell;
                    ofs << "</td>" << std::endl;
                }
            }
        }
        ofs << "\t</tr>" << std::endl;
    }
    ofs << "</table>" << std::endl;

    ofs.close();
}


bool errorCapture()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        errorMessage();
        return true;
    }
    return false;
}


void errorMessage()
{
    std::cout << "Invalid input. Please provide output according to menu rules." << std::endl;
}

void menuOptions()
{
    std::cout << "For adding a row, enter 1..." << std::endl;
    std::cout << "For removing a row enter 2..." << std::endl;
    std::cout << "To edit a cell enter 3..." << std::endl;
    std::cout << "To print your table enter 4..." << std::endl;
    std::cout << "To exit enter 0..." << std::endl;
}



int main()
{
    Table table;

    std::cout << "Please enter filename" << std::endl;

    char fileName[MAX_FILENAME];

    std::cin >> fileName;

    readInput(table, fileName);

    unsigned step = 1, ind, colsBuff = 0, rowBuff=0;
    char values[MAX_CHARS_BEFORE_DECODE];

    std::cout << "Please enter command:" << std::endl;

    while (step)
    {
        menuOptions();

        std::cin >> step;

        if (errorCapture())
        {
            errorMessage();
            continue;
        }

        switch (step)
        {

            case 1:
            {
                std::cout << "Please enter an index where the new row will be inserted";
                std::cin >> ind;
                std::cout << "Enter the row values, separated by a comma until newline" << std::endl;
                std::cin >> values;
                
                addRow(table, ind, readRowContent(values, colsBuff), colsBuff);
                break;

            }

            case 2:
            {
                std::cout << "Please enter an index where the row will be removed";
                std::cin >> ind;
                removeRow(table, ind);
                break;
            }

            case 3:
            {
                std::cout << "Please enter row";
                std::cin >> rowBuff;
                std::cout << "Please enter column" << std::endl;
                std::cin >> colsBuff;
                std::cout << "Please enter new value of cell" << std::endl;
                std::cin >> values;

                editCell(values, table, rowBuff, colsBuff);
                break;

            }

            case 4:
            {
                printTable(table);
                break;
            }

            default:
            {
                std::cout << "Please enter valid command" << std::endl;
                continue;

            }
        }
    }

    writeToFileFormatted(fileName, table);
    std::cout << "Thank you for using this program! Come again!" << std::endl;
    return 0;
    
}
