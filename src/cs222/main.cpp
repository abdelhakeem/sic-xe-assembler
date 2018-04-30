#include <iomanip>
#include <iostream>
#include <fstream>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>
#include <cs222/Utility.h>
#include <cs222/Validator.h>

void processFile(const std::string& path);

int main(int argc, char* argv[])
{
    //try
    {
        if (argc < 2)
        {
            std::cout << "USAGE: pass1 <file>" << std::endl;
            return 0;
        }

        for (size_t i = 1; i < argc; ++i)
        {
            processFile(argv[i]);
        }
    }
    //catch(const std::exception& ex)
    {
     //   std::cout << ex.what() << std::endl;
    }

    return 0;
}

void processFile(const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        throw std::runtime_error(std::string("Cannot open file ") + path);
    }

    std::string output = path + ".listing";
    std::string symoutput = path + ".symtab";
    std::ofstream ofs(output);
    std::ofstream symofs(symoutput);
    if (!ofs)
    {
        throw std::runtime_error(std::string("Cannot open file ") + output);
    }
    if (!symofs)
    {
        throw std::runtime_error(std::string("Cannot open file ") + symoutput);
    }

    std::cout << "Writing intermediate file to " << output << std::endl;
    ofs.setf(std::ios::left);
    ofs << std::setw(8) << "LINE"
        << std::setw(12) << "ADDRESS"
        << std::setw(12) << "LABEL"
        << std::setw(12) << "MNEMONIC"
        << std::setw(16) << "OPERANDS"
        << '\t' << "COMMENTS" << std::endl << std::endl;

    size_t START = 0;
    size_t LOCCTR = 0;
    std::unordered_map<std::string, int> SYMTAB;
    cs222::Parser parser(ifs);
    cs222::Validator validator;

    std::shared_ptr<cs222::Instruction> inst;
    if (parser.hasNext())
    {
        inst = parser.next();
        if (inst == nullptr)
        {
            ofs.close();
            symofs.close();
            ifs.close();
            return;
        }

        while (inst->isCommentLine() && parser.hasNext())
        {
            inst = parser.next();
        }

        validator.validate(*inst);

        if (
                cs222::toUpper(inst->getOperation()) == "START" &&
                inst->getErrors().empty())
        {
            LOCCTR = std::stoul(
                    inst->getFirstOperand().getValue(),
                    nullptr,
                    16);
            START = LOCCTR;
        }

        ofs << std::setw(8) << inst->getLineNumber()
            << std::setw(12) << std::hex << LOCCTR
            << std::setw(12) << inst->getLabel()
            << std::setw(12) << inst->getOperation()
            << std::setw(16) << inst->getOperandsToken()
            << '\t' << inst->getComment() << std::endl;

        if (!inst->getErrors().empty())
        {
            for (const std::string& err : inst->getErrors())
            {
                ofs << "****" << err << "****" << std::endl;
            }
        }
    }
    bool firstAfterStart = true;
    while (parser.hasNext())
    {
        inst = parser.next();
        if (inst == nullptr)
        {
            ofs.close();
            ifs.close();
            return;
        }
        validator.validate(*inst);
        if (!inst->getLabel().empty())
        {
            std::string label = inst->getLabel();
            if (SYMTAB.find(label) != SYMTAB.end())
            {
                inst->addError(std::string("Duplicate symbol ") + label);
            }
            else
            {
                SYMTAB[label] = LOCCTR;
            }
        }
        std::string op = inst->getOperation();
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
            if (!firstAfterStart)
            {
                LOCCTR += cs222::Instruction::Length.find(fmt)->second;
            }
            else
            {
                firstAfterStart = false;
            }
        }
        else
        {
            if (op == "WORD")
            {
                LOCCTR += 3;
            }
            else if (op == "RESW")
            {
                LOCCTR += 3 * std::stoul(inst->getFirstOperand().getValue());
            }
            else if (op == "RESB")
            {
                LOCCTR += std::stoul(inst->getFirstOperand().getValue());
            }
            else if (op == "BYTE")
            {
                LOCCTR += inst->getFirstOperand().getValue().length();
            }
        }

        ofs << std::setw(8) << inst->getLineNumber()
            << std::setw(12) << std::hex << LOCCTR
            << std::setw(12) << inst->getLabel()
            << std::setw(12) << inst->getOperation()
            << std::setw(16) << inst->getOperandsToken()
            << '\t' << inst->getComment() << std::endl;

        if (!inst->getErrors().empty())
        {
            for (const std::string& err : inst->getErrors())
            {
                ofs << "****" << err << "****" << std::endl;
            }
        }
    }
    ofs << std::endl << "PROGRAM LENGTH: " << LOCCTR - START << std::endl;

    std::cout << "Writing SYMTAB to " << symoutput << std::endl;
    symofs.setf(std::ios::left);
    symofs << std::setw(12) << "SYMBOL" << "ADDRESS" << std::endl << std::endl;
    for (auto it : SYMTAB)
    {
        symofs << std::setw(12) << it.first << it.second << std::endl;
    }

    ofs.close();
    symofs.close();
    ifs.close();
}
