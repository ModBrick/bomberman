#include <string>
#include "Except.hpp"

IndieError::IndieError(std::string const &what) {
  this->wha = what;
}

IndieError::~IndieError() throw() {
}

const char *IndieError::what() const throw() {
  return this->wha.c_str();
}
