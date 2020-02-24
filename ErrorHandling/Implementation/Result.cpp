#include <ErrorHandling/Result.hpp>

const bool Result::HasErrors() const {
    return !errors_.empty();
}

const bool Result::IsOkay() const {
    return errors_.empty();
}

const std::string Result::Errors() const {
    std::string returnValue = "";
    ErrorList::const_iterator errorFinder = errors_.begin();
    ErrorList::const_iterator errorEnd = errors_.end();
    while (errorFinder != errorEnd) {
        returnValue.append(*errorFinder);
        returnValue.append("\n");

        // Loop incrementer.
        ++errorFinder;
    }
    return returnValue;
}

void Result::AppendError(const char* newError) {
    errors_.emplace_back(std::string(newError));
}
