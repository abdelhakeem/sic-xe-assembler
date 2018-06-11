#include <iomanip>
#include <iostream>
#include <fstream>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>
#include <cs222/Symbol.h>
#include <cs222/Utility.h>
#include <cs222/Validator.h>

size_t processFile(
        const std::string& path,
        std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        std::unordered_map<std::string, cs222::Symbol>& symtab,
        std::unordered_map<
            std::string, std::pair<cs222::Operand::Type, size_t>>& littab);

void writeIntermediateFile(
        const std::string& path,
        const std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        const size_t& START);

void writeSymbolTable(
        const std::string& path,
        const std::unordered_map<std::string, cs222::Symbol>& symtab);

void writeLiteralTable(
        const std::string& path,
        std::unordered_map<
            std::string, std::pair<cs222::Operand::Type, size_t>>& littab);

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cout << "USAGE: pass1 <file>" << std::endl;
            return 0;
        }

        std::vector<std::unique_ptr<cs222::Instruction>> instVec;
        std::unordered_map<std::string, cs222::Symbol> SYMTAB;
        std::unordered_map<
            std::string, std::pair<cs222::Operand::Type, size_t>> LITTAB;
        std::string currentFile;
        size_t START;

        for (size_t i = 1; i < argc; ++i)
        {
            currentFile = argv[i];
            START = processFile(currentFile, instVec, SYMTAB, LITTAB);
            writeIntermediateFile(currentFile + ".listing", instVec, START);
            writeSymbolTable(currentFile + ".symtab", SYMTAB);
            writeLiteralTable(currentFile + ".littab", LITTAB);
        }
    }
    catch(const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}

size_t processFile(
        const std::string& path,
        std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        std::unordered_map<std::string, cs222::Symbol>& symtab,
        std::unordered_map<
            std::string, std::pair<cs222::Operand::Type, size_t>>& littab)
{
    instVec.clear();
    symtab.clear();
    littab.clear();
    std::unordered_map<
        std::string, std::pair<cs222::Operand::Type, size_t>> temp_littab;

    std::ifstream ifs(path);
    if (!ifs)
        throw std::runtime_error(std::string("Cannot open file: ") + path);

    size_t START = 0;
    size_t LOCCTR = 0;
    std::vector<std::string> usedSymbols;
    cs222::Parser parser(ifs);
    cs222::Validator validator;
    std::unique_ptr<cs222::Instruction> inst;

    if (parser.hasNext())
    {
        inst = parser.next();

        while (inst && inst->isCommentLine())
        {
            instVec.push_back(std::move(inst));
            inst = parser.next();
        }

        if (inst)
        {
            cs222::Operand firstOp = inst->getFirstOperand();

            if (
                    cs222::toUpper(inst->getOperation()) == "START" &&
                    firstOp.getType() == cs222::Operand::INT_CONSTANT)
            {
                validator.validate(*inst);
                if (inst->getErrors().empty())
                {
                    LOCCTR = std::stoul(firstOp.getValue(), nullptr, 16);
                    START = LOCCTR;
                    inst->setAddress(LOCCTR);
                }
                instVec.push_back(std::move(inst));
                inst = parser.next();
            }
        }
    }

    while (inst)
    {
        validator.validate(*inst);
        cs222::Operand firstOp = inst->getFirstOperand();
        inst->setAddress(LOCCTR);

        if (
                cs222::toUpper(inst->getOperation()) == cs222::DIR_LTORG ||
                cs222::toUpper(inst->getOperation()) == cs222::DIR_END
                )
        {
            for (auto& it : temp_littab)
            {
                cs222::Operand::Type literalType = it.second.first;
                std::string listingLiteral;
                if (literalType == cs222::Operand::INT_LITERAL)
                {
                    listingLiteral = std::string("W") + it.first;
                }
                else if (literalType == cs222::Operand::CHAR_LITERAL)
                {
                    listingLiteral = std::string("C") + it.first;
                }
                else if (literalType == cs222::Operand::HEX_LITERAL)
                {
                    listingLiteral = std::string("X") + it.first;
                }
                std::unique_ptr<cs222::Instruction> litinst =
                    std::make_unique<cs222::Instruction>(
                        0,
                        "",
                        "*",
                        listingLiteral,
                        cs222::Operand(literalType),
                        cs222::Operand(),
                        "",
                        "",
                        std::bitset<6>());
                litinst->setAddress(LOCCTR);
                it.second.second = LOCCTR;
                littab.insert(it);
                LOCCTR += litinst->getLength();
                instVec.push_back(std::move(litinst));
            }
            temp_littab.clear();
        }
        if (
                firstOp.getType() == cs222::Operand::INT_LITERAL ||
                firstOp.getType() == cs222::Operand::CHAR_LITERAL ||
                firstOp.getType() == cs222::Operand::HEX_LITERAL)
        {
            temp_littab[firstOp.getValue()] =
                std::pair<cs222::Operand::Type, size_t>(
                        firstOp.getType(),
                        0
                        );
        }
        if (!inst->getLabel().empty())
        {
            std::string label = inst->getLabel();
            if (cs222::hashtableContains(symtab, label))
            {
                inst->addError(std::string("Duplicate symbol ") + label);
            }
            else
            {
                cs222::Symbol sym =
                    cs222::Symbol(label, LOCCTR, cs222::Symbol::RELATIVE);
                if (inst->getOperation() == "EQU")
                {
                    if (firstOp.getType() == cs222::Operand::INT_CONSTANT)
                    {
                        sym = cs222::Symbol(
                                label,
                                std::stoi(firstOp.getValue()),
                                cs222::Symbol::ABSOLUTE);
                    }
                    else if (firstOp.getType() == cs222::Operand::SYMBOL)
                    {
                        if (cs222::hashtableContains(
                                    symtab, firstOp.getValue()))
                        {
                            cs222::Symbol tempsym =
                                symtab[firstOp.getValue()];
                            sym = cs222::Symbol(
                                    label,
                                    sym.getValue(),
                                    sym.getType());
                        }
                        else
                        {
                            inst->addError(std::string("Undefined symbol ") +
                                    firstOp.getValue() + ". Are you using a "
                                    "forward reference with EQU?");
                        }
                    }
                    else // cs222::Operand::EXPRESSION
                    {
                        sym = cs222::evaluateExpression(
                                *inst,
                                firstOp.getValue(),
                                symtab);
                    }
                }
                symtab[label] = sym;
            }
        }
        if (inst->getOperation() == "ORG")
        {
            if (firstOp.getType() == cs222::Operand::INT_CONSTANT)
            {
                LOCCTR = std::stoi(firstOp.getValue());
            }
            else if (firstOp.getType() == cs222::Operand::SYMBOL)
            {
                if (cs222::hashtableContains(
                            symtab, firstOp.getValue()))
                {
                    LOCCTR =
                        symtab[firstOp.getValue()].getValue();
                }
                else
                {
                    inst->addError(std::string("Undefined symbol ") +
                            firstOp.getValue() + ". Are you using a "
                            "forward reference with ORG?");
                }
            }
            else // cs222::Operand::EXPRESSION
            {
                LOCCTR = cs222::evaluateExpression(
                        *inst,
                        firstOp.getValue(),
                        symtab).getValue();
            }
        }
        else
        {
            LOCCTR += inst->getLength();
        }

        if (
                !(cs222::toUpper(inst->getOperation()) == cs222::DIR_LTORG) &&
                !(cs222::toUpper(inst->getOperation()) == cs222::DIR_END)
                )
        {
            instVec.push_back(std::move(inst));
        }
        inst = parser.next();
    }

    cs222::Operand firstOp;
    for (std::unique_ptr<cs222::Instruction>& it : instVec)
    {
        firstOp = it->getFirstOperand();
        if (
                firstOp.getType() == cs222::Operand::SYMBOL &&
                !cs222::hashtableContains(symtab, firstOp.getValue()))
        {
            it->addError(std::string("Undefined symbol used: ") +
                    firstOp.getValue());
        }
    }

    ifs.close();
    return START;
}

void writeIntermediateFile(
        const std::string& path,
        const std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        const size_t& START)
{
    std::ofstream ofs(path);
    if (!ofs)
        throw std::runtime_error(std::string("Cannot open file: ") + path);

    std::cout << "Writing intermediate file to " << path << std::endl;
    ofs.setf(std::ios::left);
    ofs << std::setw(8)  << "LINE"
        << std::setw(12) << "ADDRESS"
        << std::setw(12) << "LABEL"
        << std::setw(12) << "MNEMONIC"
        << std::setw(16) << "OPERANDS"
        << '\t' << "COMMENTS" << std::endl << std::endl;

    for (const std::unique_ptr<cs222::Instruction>& it : instVec)
    {
        ofs << std::setw(8) << it->getLineNumber();

        if (it->isCommentLine())
        {
            ofs << std::setw(12) << ' ';
        }
        else
        {
            ofs << std::setw(12) << std::hex << std::uppercase
                << it->getAddress() << std::dec << std::nouppercase
                << std::setw(12) << it->getLabel()
                << std::setw(12) << it->getOperation()
                << std::setw(16) << it->getOperandsToken() << '\t';
        }
        ofs << it->getComment() << std::endl;

        if (!it->getErrors().empty())
        {
            for (const std::string& err : it->getErrors())
            {
                ofs << "*** ERROR *** " << err << " ***" << std::endl;
            }
        }

        if (!it->getWarnings().empty())
        {
            for (const std::string& warning : it->getWarnings())
            {
                ofs << "*** WARNING *** " << warning << " ***" << std::endl;
            }
        }
    }

    ofs << std::endl << "PROGRAM LENGTH: "
        << instVec.back()->getAddress() - START;
    ofs.close();
}

void writeSymbolTable(
        const std::string& path,
        const std::unordered_map<std::string, cs222::Symbol>& symtab)
{
    std::ofstream ofs(path);
    if (!ofs)
        throw std::runtime_error(std::string("Cannot open file: ") + path);

    std::cout << "Writing SYMTAB to " << path << std::endl;
    ofs.setf(std::ios::left);
    ofs << std::setw(12) << "SYMBOL" << "ADDRESS" << std::endl << std::endl;
    for (auto it : symtab)
    {
        ofs << std::setw(12) << std::nouppercase << it.first
            << std::uppercase << std::hex << it.second.getValue() << std::endl;
    }
    ofs.close();
}

void writeLiteralTable(
        const std::string& path,
        std::unordered_map<
            std::string, std::pair<cs222::Operand::Type, size_t>>& littab)
{
    std::ofstream ofs(path);
    if (!ofs)
        throw std::runtime_error(std::string("Cannot open file: ") + path);

    std::cout << "Writing LITTAB to " << path << std::endl;
    ofs.setf(std::ios::left);
    ofs << std::setw(12) << "LITERAL" << "ADDRESS" << std::endl << std::endl;
    for (auto it : littab)
    {
        ofs << std::setw(12) << std::nouppercase << it.first
            << std::uppercase << std::hex << it.second.second << std::endl;
    }
    ofs.close();
}
