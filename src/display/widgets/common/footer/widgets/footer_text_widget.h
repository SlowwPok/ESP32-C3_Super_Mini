// path: src/display/widgets/common/footer/widgets/footer_text_widget.h
#pragma once

class FooterTextWidget
{
public:
    void SetText(const char* text);
    void Draw(int x, int y, int h);

private:
    const char* _text = "";
};