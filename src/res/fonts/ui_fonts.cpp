//path src/res/fonts/ui_fonts.cpp
#include "ui_fonts.h"

// generated fonts
#include "res/fonts/Ubuntu/Ubuntu_Regular8pt7b.h"

#include "res/fonts/Ubuntu/Ubuntu_Medium8pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Medium10pt7b.h"

#include "res/fonts/Ubuntu/Ubuntu_Bold6pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold8pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold10pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold12pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold16pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold20pt7b.h"
#include "res/fonts/Ubuntu/Ubuntu_Bold24pt7b.h"

#include "res/fonts/JetBrains_Mono/JetBrainsMono_ExtraBold6pt7b.h"
#include "res/fonts/JetBrains_Mono/JetBrainsMono_ExtraBold10pt7b.h"
#include "res/fonts/JetBrains_Mono/JetBrainsMono_Bold6pt7b.h"

namespace UIFonts
{
    const lgfx::v1::IFont* Ubuntu_Regular_8()  { return &Ubuntu_Regular8pt7b;  }

    const lgfx::v1::IFont* Ubuntu_Medium_8()  { return &Ubuntu_Medium8pt7b;  }
    const lgfx::v1::IFont* Ubuntu_Medium_10()  { return &Ubuntu_Medium10pt7b;  }

    const lgfx::v1::IFont* Ubuntu_Bold_6()  { return &Ubuntu_Bold6pt7b;  }
    const lgfx::v1::IFont* Ubuntu_Bold_8()  { return &Ubuntu_Bold8pt7b;  }
    const lgfx::v1::IFont* Ubuntu_Bold_10() { return &Ubuntu_Bold10pt7b; }
    const lgfx::v1::IFont* Ubuntu_Bold_12() { return &Ubuntu_Bold12pt7b; }
    const lgfx::v1::IFont* Ubuntu_Bold_16() { return &Ubuntu_Bold16pt7b; }
    const lgfx::v1::IFont* Ubuntu_Bold_20() { return &Ubuntu_Bold20pt7b; }   
    const lgfx::v1::IFont* Ubuntu_Bold_24() { return &Ubuntu_Bold24pt7b; }

    const lgfx::v1::IFont* JetBrainsMono_ExtraBold_6()  { return &JetBrainsMono_ExtraBold6pt7b; }
    const lgfx::v1::IFont* JetBrainsMono_ExtraBold_10() { return &JetBrainsMono_ExtraBold10pt7b; }
    const lgfx::v1::IFont* JetBrainsMono_Bold_6()      { return &JetBrainsMono_Bold6pt7b; }

}