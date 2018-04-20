#ifndef CS222_OPERATION_H
#define CS222_OPERATION_H

#include <string>

namespace cs222 {
    using std::string;

    class Operation {
        public:
            enum Format {
                FORMAT_1,
                FORMAT_2,
                FORMAT_3_4,
            };
            Operation(
                    const string& mnemonic,
                    const char& opcode,
                    const Format& format);
            const string& getMnemonic() const;
            const char& getOpcode() const;
            const Format& getFormat() const;
        private:
            string mnemonic;
            char opcode;
            Format format;
    };
}

#endif
