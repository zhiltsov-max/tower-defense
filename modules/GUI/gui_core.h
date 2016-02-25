#ifndef GUI_CORE_H
#define GUI_CORE_H

#include "Core\core.h"
#include "Application/debug.h"


#define BEGIN_GUI namespace GUI {
#define END_GUI }


BEGIN_GUI

//### Coordinates ###
using TSize = Point2f;
using TCoordinate = Point2f;

struct TPadding
{
    float left;
    float right;
    float top;
    float bottom;


    constexpr TPadding(float top_ = 0.f, float bottom_ = 0.f, float left_ = 0.f, float right_ = 0.f) :
        left(left_), right(right_), top(top_), bottom(bottom_)
    {}

    bool operator==(const TPadding& other) const {
        return (top == other.top) &&
               (bottom == other.bottom) &&
               (left == other.left) &&
               (right == other.right);
    }

    bool operator!=(const TPadding& other) const {
        return !operator==(other);
    }
};


//### Graphics ###
using TColor = Graphics::ARGB;

struct TColorModifier
{
    double rMod;
    double gMod;
    double bMod;
    double aMod;


    constexpr TColorModifier(
        double r = 1.0,
        double g = 1.0,
        double b = 1.0,
        double alpha = 1.0
    ) :
        rMod(r), gMod(g), bMod(b), aMod(alpha)
    {}


    TColor modify(const TColor& color) const {
        return TColor(
            color.r * rMod,
            color.g * gMod,
            color.b * bMod,
            color.a * aMod
        );
    }

    TColor operator * (const TColor& color) const {
        return modify(color);
    }

    TColorModifier& operator *= (const TColorModifier& other) {
        rMod *= other.rMod;
        gMod *= other.gMod;
        bMod *= other.bMod;
        aMod *= other.aMod;
        return *this;
    }

    TColorModifier operator * (const TColorModifier& other) const {
        return TColorModifier(*this) *= other;
    }

    friend TColor operator * (const TColor& color, const TColorModifier& mod) {
        return mod * color;
    }
};

using TImage = Graphics::TImage;
using TTexture = Graphics::TTexture;
using TSprite = Graphics::TSprite;
using TRect = sf::IntRect;
using TRenderTarget = Graphics::TRenderTarget;

struct TImageSource
{
    string path;
    uint frame;
    uint frameCount;
    TRect boundary;


    TImageSource(
        const string& path_ = string(),
        uint frame_ = 0,
        uint frameCount_ = 0,
        const TRect& boundary_ = TRect()
    ) :
        path(path_),
        frame(frame_),
        frameCount(frameCount_),
        boundary(boundary_)
    {}
};

class TImageContainer
{
public:
    TImageContainer() = default;
    TImageContainer(const TImageSource& source);
    TImageContainer(const TImageContainer& source) = delete;
    TImageContainer& operator=(const TImageContainer& source) = delete;
    TImageContainer(TImageContainer&& source) = default;
    TImageContainer& operator=(TImageContainer&& source) = default;
    ~TImageContainer() = default;

    typedef std::shared_ptr<TImage> Image;
    typedef std::unique_ptr<TTexture> Texture;
    typedef std::unique_ptr<TSprite> DrawingObject;
    Image image;
    Texture texture;
    DrawingObject drawingObject;

    bool operator==(const TImageContainer& other) const;
    bool operator!=(const TImageContainer& other) const;
};

class TRenderObject
{
public:
    TRenderObject(const TSize& size);
    TRenderObject(const TRenderObject& other) = delete;
    TRenderObject(TRenderObject&& other) = default;
    TRenderObject& operator=(const TRenderObject& other) = delete;
    TRenderObject& operator=(TRenderObject&& other) = default;
    ~TRenderObject() = default;

    void resize(const TSize& size);
    void createDrawingObject();

    typedef sf::Sprite DrawingObject;
    const DrawingObject& getDrawingObject() const;
    DrawingObject& getDrawingObject();

    const Graphics::TRenderTarget& getRenderTarget() const;
    Graphics::TRenderTarget& getRenderTarget();
private:
    typedef std::unique_ptr<sf::RenderTexture> RenderTexture;
    RenderTexture renderTexture;

    typedef std::unique_ptr<DrawingObject> DrawingObjectP;
    DrawingObjectP drawingObject;
};


/*### I/O ###
IMPORTANT: Implementation of I/O functions is
specific for each application architecture,
so you shoud check it and adapt for your
concrete needs. Basic (general) implementation
is actually given.
*/
namespace IO {

using MouseKey = ::IO::MouseKey;
using KeyboardKey = ::IO::KeyboardKey;

bool IsMouseMoved();
bool IsCursorInRect(const TCoordinate& p1, const TCoordinate& p2);
bool IsCursorInRect(float x1, float x2, float y1, float y2);
bool IsMouseHit(MouseKey key);
bool IsMouseDown(MouseKey key);
int MouseX();
int MouseY();
TCoordinate MousePos();

::IO::TSFMLGraphicsDevice& GetGraphicsDevice();
void SetGraphicsDevice(::IO::TSFMLGraphicsDevice* value);

} //namespace IO


uint WindowWidth();
uint WindowHeight();


//### Debug ###
namespace Debug {

void throw_(const string& message, const string& where = "GUI");

#define GUI_ASSERT(expr, message) \
    if ((expr) == false) { \
        GUI::Debug::throw_(message, string(__FILE__ ":") + std::to_string(__LINE__)); \
    }

bool& show_frames();

void logMessage(
    const TextString& message,
    const TextString& where = TEXT("GUI"),
    ::LogMessageImportance importance = ::LogMessageImportance::Usual
);

} //Debug


END_GUI

#endif // GUI_CORE_H
