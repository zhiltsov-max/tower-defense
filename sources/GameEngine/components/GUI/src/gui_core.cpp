#include "gui_core.h"
#include "Application/application.h"



BEGIN_GUI

TImageContainer::TImageContainer(const TImageSource& source) :
    image(new TImage),
    texture(nullptr),
    drawingObject(nullptr)
{
    if ((source.path.empty() == true) ||
        (image->loadFromFile(source.path) == false))
    {
#if defined(_DEBUG)
        if (source.path.empty() == false) {
            GUI_WARNING(TEXT("Failed to load image '") +
                String::toWide(source.path) + TEXT("'."));
        }
#endif // _DEBUG
        image.reset();
    } else {
        texture.reset(new TTexture);
        texture->loadFromImage(*image);
        TSprite* sprite = new TSprite(*texture);
        drawingObject.reset(sprite);
        sprite->setPosition(source.boundary.left, source.boundary.top);
        if ((source.boundary.width != 0) && (source.boundary.height != 0)) {
            sprite->setTextureRect(source.boundary);
        }
    }
}

bool TImageContainer::operator==(const TImageContainer& other) const {
    return image == other.image;
}

bool TImageContainer::operator!=(const TImageContainer& other) const {
    return !operator==(other);
}



TRenderObject::TRenderObject(const TSize& size) :
    renderTexture(new sf::RenderTexture()),
    drawingObject(new sf::Sprite())
{
    GUI_ASSERT(renderTexture->create(size.x, size.y) == true,
        "Failed to create a RenderTexture.");
    drawingObject->setOrigin(0.f, size.y);
    drawingObject->setScale(1.f, -1.f);
}

void TRenderObject::resize(const TSize& size) {
    auto currentSize = renderTexture->getSize();
    if (currentSize.x != size.x || currentSize.y != size.y) {
        GUI_ASSERT(renderTexture->create(size.x, size.y) == true,
            "Failed to create a RenderTexture.");
        drawingObject->setOrigin(0.f, size.y);
    }
}

void TRenderObject::createDrawingObject() {
    drawingObject->setTexture(renderTexture->getTexture());
}

const TRenderObject::DrawingObject& TRenderObject::getDrawingObject() const {
    return *drawingObject;
}
TRenderObject::DrawingObject& TRenderObject::getDrawingObject() {
    return *drawingObject;
}

const Graphics::TRenderTarget& TRenderObject::getRenderTarget() const {
    return *renderTexture;
}
Graphics::TRenderTarget& TRenderObject::getRenderTarget() {
    return *renderTexture;
}



// Wrappers
bool IO::IsMouseMoved() {
    return app()->getDeviceController().getMouseDevice()->getInfo().xSpeed() ||
           app()->getDeviceController().getMouseDevice()->getInfo().ySpeed();
}

bool IO::IsCursorInRect(const TCoordinate &p1, const TCoordinate &p2) {
    return IsCursorInRect(p1.x, p1.y, p2.x, p2.y);
}

bool IO::IsCursorInRect(float x1, float y1, float x2, float y2) {
    return isPointInRect(MouseX(), MouseY(), x1, y1, x2, y2);
}

bool IO::IsMouseHit(MouseKey key) {
    return app()->getDeviceController().getMouseDevice()->getInfo().isKeyHit(key);
}

bool IO::IsMouseDown(MouseKey key) {
    return app()->getDeviceController().getMouseDevice()->getInfo().isKeyDown(key);
}

int IO::MouseX() {
    return app()->getDeviceController().getMouseDevice()->getInfo().x();
}

int IO::MouseY() {
    return app()->getDeviceController().getMouseDevice()->getInfo().y();
}

TCoordinate IO::MousePos() {
    return TCoordinate(MouseX(), MouseY());
}

static ::IO::TSFMLGraphicsDevice* graphicsDevice = nullptr;
::IO::TSFMLGraphicsDevice& IO::GetGraphicsDevice() {
    return *graphicsDevice;
}

void IO::SetGraphicsDevice(::IO::TSFMLGraphicsDevice* value) {
    graphicsDevice = value;
}



static bool _show_frames = false;
bool& Debug::show_frames() {
    return _show_frames;
}

void Debug::Throw(const string& message, const string& where_) {
    Throw(message, where_);
}

void Debug::logMessage(const TextString& message,
    const TextString& where, ::LogMessageImportance importance)
{
    auto* application = app();
    if (application != nullptr) {
        application->getDebugTools().log(TEXT("@") + where + TEXT(": ") + message, importance);
    } else {
#if defined(UNICODE)
        std::wcerr << TEXT("@") + where + TEXT(": ") + message << std::endl;
#else
        std::cerr << TEXT("@") + where + TEXT(": ") + message << std::endl;
#endif
    }
}

#if defined(UNICODE)
void Debug::logMessage(const string& message,
    const TextString& where, LogMessageImportance importance)
{
    logMessage(String::toWide(message), where, importance);
}
#endif // UNICODE


END_GUI
