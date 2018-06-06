#include "richtextarea.h"
#include <algorithm>



BEGIN_GUI

template< class CharT >
static std::pair<size_t, size_t>
_findEarliestOccurrence(
    const std::vector< basic_string<CharT> >& separators,
    const basic_string<CharT>& text,
    const size_t& start
);

template< class CharT >
static std::vector< basic_string<CharT> >
_splitStringBySeparators(
    const basic_string<CharT>& text,
    const std::vector< basic_string<CharT> >& separators
);

template< class CharT >
static size_t _determineLineCharacterCount(
    const basic_string<CharT>& text,
    float maxSize
);



TRichTextArea::TRichTextArea(const TRichTextAreaSource& source,
    const Parent& parent
) :
    parent_type(source, parent),
    lines(),
    separators(source.separators),
    maxSize(source.maxSize),
    lineSpacing(source.lineSpacing)
{}

const TRichTextArea::Separators& TRichTextArea::GetSeparators() const {
    return separators;
}

void TRichTextArea::SetSeparators(const Separators& value) {
    separators = value;
    _update();
}

void TRichTextArea::SetLineSpacing(float value) {
    lineSpacing = value;
}

float TRichTextArea::GetLineSpacing() const {
    return lineSpacing;
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

template< class CharT >
static std::pair<size_t, size_t>
_findEarliestOccurrence(
    const std::vector< basic_string<CharT> >& separators,
    const basic_string<CharT>& text,
    const size_t& start
) {
    size_t min = text.size();
    size_t res = separators.size();
    for (auto it = separators.cbegin(), iend = separators.cend();
        it != iend; ++it)
    {
        const auto& sep = *it;
        const auto pos = text.find(sep.c_str(), start, sep.size());
        if ((pos != text.npos) && (pos < min)) {
            min = pos;
            res = std::distance(separators.cbegin(), it);
        }
    };
    return std::make_pair(res, min);
}

template< class CharT >
static std::vector< basic_string<CharT> >
_splitStringBySeparators(
    const basic_string<CharT>& text,
    const std::vector< basic_string<CharT> >& separators
) {
    std::vector< basic_string<CharT> > result;

    TextString::size_type start = 0;
    while(start != text.size()) {
        const auto occurrence = _findEarliestOccurrence(
            separators, text, start);
        const auto& sepIndex = occurrence.first;

        if (sepIndex < separators.size()) {
            const auto& distance = occurrence.second;
            result.emplace_back(text.substr(start, distance));
            start += distance + separators[sepIndex].size();
        } else {
            result.emplace_back(text.substr(start, text.size() - start));
            break;
        }
    }
    return result;
}

template< class CharT >
static size_t _determineLineCharacterCount(
    const basic_string<CharT>& text,
    float maxSize,
    const TFont& font
) {
    if (font.GetTextWidth(text) < maxSize) {
        return text.size();
    }

    using size = TextString::size_type;

    size lb = 0;
    size ub = text.size();
    while (lb < ub) {
        const size middle = lb + (ub - lb) / 2;

        if (font.GetTextWidth(text.substr(0, middle)) < maxSize) {
            lb = middle + 1;
        } else {
            ub = middle - 1;
        }
    }
    return ub;
}

void TRichTextArea::_splitTextByLines() {
    lines = _splitStringBySeparators(text, separators);

    if (maxSize.x <= 0) { // maximum size is unlimited
        return;
    }

    for(auto it = lines.begin(); it != lines.end(); ++it) {
        const size_t maxChars = _determineLineCharacterCount(
            *it, maxSize.x, font);

        if (maxChars == 0) {
            it = lines.erase(it);
        } else if (maxChars < (*it).size()) {
            it = lines.emplace(it, std::move(String::left(*it, maxChars)));
            ++it;
            it = lines.emplace(it, std::move(String::right(*it, maxChars)));
            ++it;
            it = lines.erase(it);
        } else {
            /* none */
        }
    }
}

void TRichTextArea::_update() {
    _splitTextByLines();
}

void TRichTextArea::Draw(TRenderTarget& target, const TCoordinate& offset) {
    const auto position = GetPosition() + offset;

    auto textSprite = font.CreateText(TEXT(""));
    textSprite.setColor(color);
    for(size_t i = 0; i != lines.size(); ++i) {
        const float lineHeight = font.GetTextHeight(lines[i]) + lineSpacing;
        if ( ( ((0 < maxSize.x) && (maxSize.y < i * lineHeight)) == false) ||
             (maxSize.y == 0)
           )
        {
            textSprite.setString(std::move(lines[i]));
            textSprite.setPosition(position.x, position.y + i * lineHeight);
            target.draw(textSprite);
        }
    }
}


END_GUI
