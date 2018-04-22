
#include<Symbol.h>
#include<string>

namespace cs222 {
	Symbol::Symbol(const string& name,
                    const int& location,
                    const int& length
					) : name(name),location(locatoin),length(length)
					{}
					
					
	
    Symbol::const string& getName() const{ return name; }
    Symbol::const int& getLocation() const { return location; }
    Symbol::const int& getLength() const{ return length; }
}	
					