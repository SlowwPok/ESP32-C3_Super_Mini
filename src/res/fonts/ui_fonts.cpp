//path src/res/fonts/ui_fonts.cpp
#include "ui_fonts.h"

// generated fonts
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold8pt7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold10pt7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold12pt7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold16pt7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold20pt7b.h"
#include "res/fonts/Ubuntu_Bold/Ubuntu_Bold24pt7b.h"

namespace UIFonts
{
    const lgfx::v1::IFont* Title_16pt7b()
    {
        return &Ubuntu_Bold16pt7b;
    }

    const lgfx::v1::IFont* Title_20pt7b()
    {
        return &Ubuntu_Bold20pt7b;
    }

    const lgfx::v1::IFont* Title_24pt7b()
    {
        return &Ubuntu_Bold24pt7b;
    }

    const lgfx::v1::IFont* Body_10pt7b()
    {
        return &Ubuntu_Bold10pt7b;
    }

    const lgfx::v1::IFont* Body_12pt7b()
    {
        return &Ubuntu_Bold12pt7b;
    }

    const lgfx::v1::IFont* Small_8pt7b()
    {
        return &Ubuntu_Bold8pt7b;
    }
}