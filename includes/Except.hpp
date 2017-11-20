#pragma once

#include <stdexcept>

class IndieError : public std::exception {
protected:
    std::string wha;

public:
    IndieError(IndieError const& copy) : wha(std::string(copy.what())){};

    IndieError& operator=(IndieError const&) = delete;

    IndieError(std::string const& what = "Error");

    ~IndieError() throw();

    const char* what() const throw();
};

class AssetError : public IndieError {
public:
    AssetError& operator=(AssetError const&) = delete;

    AssetError(std::string const& what) : IndieError(what){};

    AssetError(AssetError const& copy) : IndieError(std::string(copy.what())){};

    ~AssetError() throw(){};
};

class DeviceError : public IndieError {
public:
    DeviceError& operator=(DeviceError const&) = delete;

    DeviceError(std::string const& what) : IndieError(what){};

    DeviceError(DeviceError const& copy) : IndieError(std::string(copy.what())){};

    ~DeviceError() throw(){};
};

