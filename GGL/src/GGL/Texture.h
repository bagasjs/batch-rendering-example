#pragma once

#include <string>
namespace GGL
{
    unsigned int LoadTexture(const std::string& path);
    void BindTexture(unsigned int texId, unsigned int slot = 0);
}