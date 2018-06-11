#include "backend/sfml/graphics_device.h"


namespace GE {

namespace IO {

TSFMLGraphicsDevice::TSFMLGraphicsDevice(
    sf::RenderTarget* target
) :
    target(target)
{}

const sf::RenderTarget* TSFMLGraphicsDevice::get() const {
    return target;
}
sf::RenderTarget* TSFMLGraphicsDevice::get() {
    return target;
}
const sf::RenderTarget& TSFMLGraphicsDevice::operator*() const {
    return *target;
}
sf::RenderTarget& TSFMLGraphicsDevice::operator*() {
    return *target;
}
const sf::RenderTarget* TSFMLGraphicsDevice::operator->() const {
    return target;
}
sf::RenderTarget* TSFMLGraphicsDevice::operator->() {
    return target;
}

} // namespace IO

} // namespace GE