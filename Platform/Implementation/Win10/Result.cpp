#include <Platform/ErrorHandling.hpp>

#include <Platform/StdLib.hpp>

const bool Result::HasErrors() const {
    return errorCount_ != 0;
}

const bool Result::IsOkay() const {
    return errorCount_ == 0;
}

const char* Result::Errors() const {
    return finalError_;
}

void Result::AppendError(const char* newError) {
    strncat_s(finalError_, newError, MAX_STRING_LENGTH - 1);
    strncat_s(finalError_, "\n", 1);
    ++errorCount_;
}
