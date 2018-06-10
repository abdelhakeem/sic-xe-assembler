#ifndef CS222_SYMBOL_H
#define CS222_SYMBOL_H

#include <string>

namespace cs222 {
    using std::string;

    class Symbol {
        public:
            Symbol(
                    const string& name,
                    const int& location,
                    const int& length);
            const string& getName() const;
            const int& getLocation() const;
            const int& getLength() const;
        private:
            string name;
            int location;
            int length;
    };
}

#endif
