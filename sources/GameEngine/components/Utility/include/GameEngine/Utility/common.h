#ifndef GAME_ENGINE_COMMON_UTILITY_H
#define GAME_ENGINE_COMMON_UTILITY_H

/*
 * Macros for marking a variable as unused.
 * Enables to selectively suppress intentionally unused variables.
 * Note: in C++14 code attribute [[maybe_unused]] might be used for that.
 *
 * Usage example:
 *
 * int x;
 * UNUSED(x);
 *
 *
 * Usage example:
 *
 * struct RaiiHolder {
 *   int handle;
 *
 *   RaiiHolder(int);
 *   ~RaiiHolder();
 * };
 * extern int osHandle;
 * RaiiHolder handleHolder(osHandle);
 * UNUSED(handleHolder);
 */
#define UNUSED(var) static_cast<void>(var);

/*
 * Macros for GameEngine namespace declaration.
 *
 * Usage:
 *
 * BEGIN_NAMESPACE
 * // code in namespace
 * END_NAMESPACE
 *
 */
#define GE_BEGIN_ENGINE_NAMESPACE namespace GE {
#define GE_END_ENGINE_NAMESPACE } // namespace GE

#endif // GAME_ENGINE_COMMON_UTILITY_H