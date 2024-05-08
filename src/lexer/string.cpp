#include "../errors/errors.hpp"
#include "lexer.hpp"

std::shared_ptr<std::string> Lexer::_isString()
{
    if (this->currentChar == "\"")
    {
        if (*this->_peekChar(1) == "\"")
        {
            if (*this->_peekChar(2) == "\"")
            {
                return std::make_shared<std::string>("\"\"\"");
            }
            else
            {
                return std::make_shared<std::string>("\"");
            }
        }
        else
        {
            return std::make_shared<std::string>("\"");
        }
    }
    else if (this->currentChar == "'")
    {
        if (*this->_peekChar(1) == "'")
        {
            if (*this->_peekChar(2) == "'")
            {
                return std::make_shared<std::string>("'''");
            }
            else
            {
                return std::make_shared<std::string>("'");
            }
        }
        else
        {
            return std::make_shared<std::string>("'");
        }
    }
    return std::make_shared<std::string>("");
}

std::shared_ptr<std::string> Lexer::_readString(std::string quote)
{
    std::string str = "";
    std::string literal = quote;
    int stColNo = this->colNo;
    if (quote == "\"\"\"" || quote == "'''")
    {
        this->_readChar();
        this->_readChar();
    }
    while (true)
    {
        this->_readChar();
        if (this->currentChar == "")
        {
            raiseSyntaxError(this->source, "Quotation mark not closed", this->lineNo, stColNo, literal, "UnclosedQuoteError", "Ensure the quotation mark is properly closed at the end of the string literal");
        }
        else if (this->currentChar == "\n" && quote != "\"\"\"" && quote != "'''")
        {
            raiseSyntaxError(this->source, "Unclosed or mismatched quotes in string", this->lineNo, stColNo, literal, "UnclosedQuoteError", "Ensure that the quote marks are properly closed on the same line");
        }
        else if (this->currentChar == "\\")
        {
            this->_readChar();
            if (this->currentChar == "\"")
            {
                str += "\"";
                literal += "\\\"";
            }
            else if (this->currentChar == "'")
            {
                str += "'";
                literal += "\\'";
            }
            else if (this->currentChar == "n")
            {
                str += "\n";
                literal += "\\n";
            }
            else if (this->currentChar == "t")
            {
                str += "\t";
                literal += "\\t";
            }
            else if (this->currentChar == "r")
            {
                str += "\r";
                literal += "\\r";
            }
            else if (this->currentChar == "b")
            {
                str += "\b";
                literal += "\\b";
            }
            else if (this->currentChar == "f")
            {
                str += "\f";
                literal += "\\f";
            }
            else if (this->currentChar == "v")
            {
                str += "\v";
                literal += "\\v";
            }
            else if (this->currentChar == "\\")
            {
                str += "\\";
                literal += "\\\\";
            }
            else
            {
                str += "\\" + this->currentChar;
                literal += "\\" + this->currentChar;
            }
        }
        else if ((this->currentChar == quote))
        {
            this->_readChar();
            break;
        }
        else if (this->currentChar + *this->_peekChar() + *this->_peekChar(2) == quote)
        {
            this->_readChar();
            this->_readChar();
            this->_readChar();
            break;
        }
        else
        {
            str += this->currentChar;
            literal += this->currentChar;
        }
    }
    return std::make_shared<std::string>(str);
}