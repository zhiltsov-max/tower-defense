#include "richtextarea.h"
#include <algorithm>

BEGIN_GUI

TRichTextArea::TRichTextArea(const TextString& text, const TCoordinate& position, TWidget* parent) :
    parent_type(text, position, parent),
    lines(),
    separators(),
    maxSize(),
    spacingBetweenLines(DEFAULT_SPACING_BETWEEN_LINES)
{}

const TRichTextArea::Separators& TRichTextArea::GetSeparators() const {
    return separators;
}


void TRichTextArea::SetSpacingBetweenLines(float value) {
    spacingBetweenLines = value;
}

float TRichTextArea::GetSpacingBetweenLines() const {
    return spacingBetweenLines;
}


void TRichTextArea::SetMaxSize(const TSize& value) {
    if (maxSize != value) {
        maxSize = value;
        _update();
    }
}

const TSize& TRichTextArea::GetMaxSize() const {
    return maxSize;
}

float TRichTextArea::GetWidth() const {
    float width = font.GetTextWidth(text);
    if (0 < maxSize.x) {
        width = std::min(width, maxSize.x);
    }
    return width + margin.left + margin.right;
}

float TRichTextArea::GetHeight() const {
    float height = (font.GetTextHeight(text) + spacingBetweenLines) * lines.size();
    if (0 < maxSize.y) {
        height = std::min(height, maxSize.y);
    }
    return height + margin.top + margin.bottom;
}

void TRichTextArea::SetText(const TextString& value) {
    if (text != value) {
        parent_type::SetText(value);
        _update();
    }
}

void TRichTextArea::SetFont(const TFont& value) {
    if (font != value) {
        parent_type::SetFont(value);
        _update();
    }
}

size_t findEarliestOccurrence(const std::vector<TextString>& separators, const TextString& text, size_t start) {
    size_t min = text.size();
    size_t res = separators.size();
    for (auto it = separators.cbegin(), iend = separators.cend(); it != iend; ++it) {
        const auto& sep = *it;
        TextString::size_type pos = text.find(sep.c_str(), start, sep.size());
        if (pos != text.npos) {
            if (pos < min) {
                min = pos;
                res = it - separators.cbegin();
            }
        }
    };
    return res;
}

TRichTextArea::Lines TRichTextArea::_splitStringBySeparators(const TextString& text, const Separators& separators) const {
    Lines res;

    TextString::size_type firstChar = 0;
    size_t sepIndex = separators.size();
    for(TextString::size_type i = 0; i != text.size(); ++i) {
        sepIndex = findEarliestOccurrence(separators, text, i);

        if (sepIndex < separators.size()) {
            size_t delta = i - firstChar;
            if (delta != 0) {
                res.emplace_back(text.substr(firstChar, delta));
            }
            firstChar = i + separators[sepIndex].size();
        }
    }
    if (firstChar == 0) {
        res.emplace_back(text);
    }
    return res;
}

TRichTextArea::Lines TRichTextArea::_splitStringByLength(const TextString& text, size_t length) const {
    Lines res;

    size_t step = std::min(text.size(), length);

    for (size_t pos = 0; pos != text.size(); pos += step) {
        res.emplace_back(text.substr(pos, step));
        step = std::min(text.size() - pos, step);
    }

    return res;
}

void TRichTextArea::_splitTextByLines() {
    lines.clear();

    lines = std::move(_splitStringBySeparators(text, separators));

    if (0 < maxSize.x) {
        size_t maxChars = maxSize.x / font.GetTextWidth(TEXT("W"));

        for(auto it = lines.begin(); it != lines.end(); ++it) {
            if (maxChars < (*it).size()) {
                auto spl = std::move(_splitStringByLength(*it, maxChars));
                lines.insert(it, spl.cbegin(), spl.cend());
                it += spl.size();
            }
        }
    }
}

void TRichTextArea::_update() {
    _splitTextByLines();
}

/*
    Draws this text area at specified coordinate.
*/
void TRichTextArea::Draw(TRenderTarget& target, const TCoordinate& position) {
    float lineHeight = DEFAULT_LINE_HEIGHT;
    if (font.isDefault() == false) {
        lineHeight = font.GetTextHeight(lines[0]) + spacingBetweenLines;
    }

    sf::Text textSprite = std::move(font.createText(TEXT("")));
    textSprite.setColor(color);
    for(size_t i = 0; i != lines.size(); ++i) {
        if ( (((0 < maxSize.x) && (maxSize.y < i * lineHeight)) == false) ||
             (maxSize.y == 0)
           )
        {
            textSprite.setString(lines[i]);
            textSprite.setPosition(position.x, position.y + i * lineHeight);
            target.draw(textSprite);
        }
    }
}

END_GUI
