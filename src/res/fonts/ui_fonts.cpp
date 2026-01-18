#include "ui_fonts.h"

// generated fonts
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold_16pt_7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold_20pt_7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold_24pt_7b.h"

namespace UIFonts
{
    const lgfx::v1::IFont* Title()
    {
        return &Ubuntu_Bold24pt7b;
    }

    const lgfx::v1::IFont* Body()
    {
        return &Ubuntu_Bold20pt7b;
    }

    const lgfx::v1::IFont* Small()
    {
        return &Ubuntu_Bold16pt7b;
    }
}