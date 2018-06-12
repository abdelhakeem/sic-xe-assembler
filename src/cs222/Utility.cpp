#include <algorithm>
#include <regex>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>
#include <cs222/Utility.h>

namespace cs222 {
    std::string toUpper(const std::string& str)
    {
        std::string upper(str);
        std::transform(str.begin(), str.end(), upper.begin(), toupper);
        return upper;
    }

    template<class Key, class T>
    bool hashtableContains(
            const std::unordered_map<Key, T>& table, const Key& key)
    {
        return table.find(key) != table.end();
    }

    template bool hashtableContains<std::string, int>(
            const std::unordered_map<std::string, int>& table,
            const std::string& key);
    template bool hashtableContains<std::string, Operation>(
            const std::unordered_map<std::string, Operation>& table,
            const std::string& key);

    bool isOperation(const std::string& str)
    {
        return hashtableContains(OpTable, toUpper(str));
    }

    bool isDirective(const std::string& str)
    {
        return arrayContains(DIRECTIVES, toUpper(str));
    }

    bool isRegister(const std::string& str)
    {
        return hashtableContains(REGISTERS, toUpper(str));
    }

    char getOpcode(const std::string& op)
    {
        std::string opp = op;
        if (opp[0] == '+')
        {
            opp = op.substr(1);
        }
        if (isOperation(opp))
        {
            return OpTable.find(toUpper(opp))->second.getOpcode();
        }

        return -1;
    }

    Symbol evaluateExpression(
            Instruction& inst,
            const std::string& expr,
            const std::unordered_map<std::string, Symbol>& symtab)
    {
        std::smatch match;
        std::regex_search(expr, match, Parser::op_regex);
        size_t opPos = match.position();
        std::string firstTerm = expr.substr(0, opPos);
        std::string secondTerm = expr.substr(opPos+1);

        int firstTermValue, secondTermValue;
        if (std::regex_match(firstTerm, Parser::label_regex))
        {
            if (!hashtableContains(symtab, firstTerm))
            {
                inst.addError(std::string("Undefined symbol: ") +
                        firstTerm);
                return Symbol("", 0, Symbol::ABSOLUTE);
            }
            firstTermValue = symtab.find(firstTerm)->second.getValue();
        }
        else
        {
            firstTermValue = std::stoi(firstTerm);
        }
        if (std::regex_match(secondTerm, Parser::label_regex))
        {
            if (!hashtableContains(symtab, secondTerm))
            {
                inst.addError(std::string("Undefined symbol: ") +
                        secondTerm);
                return Symbol("", 0, Symbol::ABSOLUTE);
            }
            secondTermValue = symtab.find(secondTerm)->second.getValue();
        }
        else
        {
            secondTermValue = std::stoi(secondTerm);
        }

        int resultValue = firstTermValue + secondTermValue;
        return Symbol(inst.getLabel(), resultValue, Symbol::ABSOLUTE);
    }
}
