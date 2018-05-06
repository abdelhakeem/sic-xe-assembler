#include <iomanip>
#include <iostream>
#include <fstream>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>
#include <cs222/Utility.h>
#include <cs222/Validator.h>

size_t processFile(
        const std::string& path,
        std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        std::unordered_map<std::string, int>& symtab);

void writeIntermediateFile(
        const std::string& path,
        const std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        const size_t& START);

void writeSymbolTable(
        const std::string& path,
        const std::unordered_map<std::string, int>& symtab);

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
        std::unordered_map<std::string, int> SYMTAB;
        std::string currentFile;
        size_t START;

        for (size_t i = 1; i < argc; ++i)
        {
            currentFile = argv[i];
            START = processFile(currentFile, instVec, SYMTAB);
            writeIntermediateFile(currentFile + ".listing", instVec, START);
            writeSymbolTable(currentFile + ".symtab", SYMTAB);
        }
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}

size_t processFile(
        const std::string& path,
        std::vector<std::unique_ptr<cs222::Instruction>>& instVec,
        std::unordered_map<std::string, int>& symtab)
{
    instVec.clear();
    symtab.clear();

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
            validator.validate(*inst);
            cs222::Operand firstOp = inst->getFirstOperand();
            if (
                    cs222::toUpper(inst->getOperation()) == "START" &&
                    inst->getErrors().empty())
            {
                LOCCTR = std::stoul(firstOp.getValue(), nullptr, 16);
                START = LOCCTR;
                inst->setAddress(LOCCTR);
            }
            else
            {
                inst->setAddress(LOCCTR);
                std::string op = inst->getOperation();
                if (op[0] == '+')
                    op = op.substr(1);

                if (cs222::isOperation(op))
                {
                    cs222::Instruction::Format fmt =
                        cs222::OpTable.find(op)->second.getValidFormat();
                    if (fmt == cs222::Instruction::FORMAT_3_4)
                    {
                        fmt = cs222::Instruction::FORMAT_3;
                        if (inst->isSet(cs222::Instruction::FLAG_EXTENDED))
                        {
                            fmt = cs222::Instruction::FORMAT_4;
                        }
                    }

                    LOCCTR += cs222::Instruction::Length.find(fmt)->second;
                }
                else
                {
                    if (op == cs222::DIR_WORD)
                    {
                        LOCCTR += 3;
                    }
                    else if (op == cs222::DIR_RESW)
                    {
                        LOCCTR += 3 * std::stoul(firstOp.getValue());
                    }
                    else if (op == cs222::DIR_RESB)
                    {
                        LOCCTR += std::stoul(firstOp.getValue());
                    }
                    else if (op == cs222::DIR_BYTE)
                    {
                        size_t length = firstOp.getValue().length();
                        if (firstOp.getType() == cs222::Operand::HEX_CONSTANT)
                        {
                            length /= 2;
                        }
                        LOCCTR += length;
                    }
                }

                if (firstOp.getType() == cs222::Operand::SYMBOL)
                {
                    usedSymbols.push_back(firstOp.getValue());
                }
            }

            instVec.push_back(std::move(inst));
        }
    }

    while (parser.hasNext())
    {
        inst = parser.next();
        validator.validate(*inst);
        cs222::Operand firstOp = inst->getFirstOperand();
        inst->setAddress(LOCCTR);

        if (!inst->getLabel().empty())
        {
            std::string label = inst->getLabel();
            if (symtab.find(label) != symtab.end())
            {
                inst->addError(std::string("Duplicate symbol ") + label);
            }
            else
            {
                symtab[label] = LOCCTR;
            }
        }

        std::string op = inst->getOperation();
        if (op[0] == '+')
            op = op.substr(1);

        if (cs222::isOperation(op))
        {
            cs222::Instruction::Format fmt =
                cs222::OpTable.find(op)->second.getValidFormat();
            if (fmt == cs222::Instruction::FORMAT_3_4)
            {
                fmt = cs222::Instruction::FORMAT_3;
                if (inst->isSet(cs222::Instruction::FLAG_EXTENDED))
                {
                    fmt = cs222::Instruction::FORMAT_4;
                }
            }

            LOCCTR += cs222::Instruction::Length.find(fmt)->second;
        }
        else
        {
            if (op == cs222::DIR_WORD)
            {
                LOCCTR += 3;
            }
            else if (op == cs222::DIR_RESW)
            {
                LOCCTR += 3 * std::stoul(firstOp.getValue());
            }
            else if (op == cs222::DIR_RESB)
            {
                LOCCTR += std::stoul(firstOp.getValue());
            }
            else if (op == cs222::DIR_BYTE)
            {
                size_t length = firstOp.getValue().length();
                if (firstOp.getType() == cs222::Operand::HEX_CONSTANT)
                {
                    length /= 2;
                }
                LOCCTR += length;
            }
        }

        instVec.push_back(std::move(inst));
    }

    cs222::Operand firstOp;
    for (std::unique_ptr<cs222::Instruction>& it : instVec)
    {
        firstOp = it->getFirstOperand();
        if (
                firstOp.getType() == cs222::Operand::SYMBOL &&
                symtab.find(firstOp.getValue()) == symtab.end())
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
        const std::unordered_map<std::string, int>& symtab)
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
            << std::uppercase << std::hex << it.second << std::endl;
    }
    ofs.close();
}
