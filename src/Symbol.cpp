
#include<Symbol.h>
#include<string>

namespace cs222 {
	Symbol::Symbol(const string& name,
                    const int& location,
                    const int& length
					) : name(name),location(locatoin),length(length)
					{}
					
					
	
    const string& Symbol::getName() const{ return name; }
    const int& Symbol::getLocation() const { return location; }
    const int& Symbol::getLength() const{ return length; }
}	
					