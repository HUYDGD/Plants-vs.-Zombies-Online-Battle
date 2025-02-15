/**
 * @file config.h
 * @brief Configurations.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @version 1.0
 * @date 2021-07-10
 * @par GitHub
 * https://github.com/czs108
 * @par
 * https://github.com/lgw1995
 */

#pragma once

#include "network/ip_addr.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>


namespace game {

/**
 * @brief Players' roles.
 */
enum class Role { Plant, Zombie };

//! The number of slots.
constexpr std::size_t slot_num{ 9 };


namespace cfg {

//! Slots.
using Slots = std::array<std::int32_t, slot_num>;

/**
 * @brief Player-related configurations.
 */
class Player final {
public:
    //! The default zombie slots.
    static const Slots default_zombies;

    //! The default plant slots.
    static const Slots default_plants;

    //! Get zombie slots.
    const Slots& ZombieSlots() const noexcept;

    //! Get plant slots.
    const Slots& PlantSlots() const noexcept;

private:
    Slots zombies_{ default_zombies };
    Slots plants_{ default_plants };
};

//! Build IPv4 or IPv6.
#ifdef INET6
using IpAddr = net::Ipv6Addr;
#else
using IpAddr = net::Ipv4Addr;
#endif  // INET6

/**
 * @brief Network-related configurations.
 */
class Network final {
public:
    //! The default server IP address.
#ifdef INET6
    static constexpr std::string_view default_server_ip{
        net::Ipv6Addr::loop_back
    };
#else
    static constexpr std::string_view default_server_ip{
        net::Ipv4Addr::loop_back
    };
#endif  // INET6

    //! The default port number.
    static constexpr std::uint16_t default_port{ 10000 };

    Network() noexcept;

    /**
     * @brief Load configurations from an @p .ini file.
     *
     * @param file  A file path.
     */
    Network(std::string_view file) noexcept;

    //! Get the server IP address.
    std::string_view ServerIp() const noexcept;

    //! Get the port number.
    std::uint16_t Port() const noexcept;

private:
    //! The section name of network configurations in the @p .ini file.
    static constexpr std::string_view ini_section{ "Network" };

    //! The key name of the server IP address in the @p .ini file.
    static constexpr std::string_view ip_ini_key{ "ServerIP" };

    //! The key name of the port number in the @p .ini file.
    static constexpr std::string_view port_ini_key{ "Port" };

    std::string server_ip_{ default_server_ip };
    std::uint16_t port_{ default_port };
};

}  // namespace cfg


/**
 * @brief Configurations.
 */
class Config final {
public:
    Config() noexcept;

    /**
     * @brief Load configurations from an @p .ini file.
     *
     * @param file  A file path.
     */
    Config(std::string_view file) noexcept;

    //! Get player-related configurations.
    const cfg::Player& Player() const noexcept;

    //! Get network-related configurations.
    const cfg::Network& Network() const noexcept;

private:
    cfg::Player player_;
    cfg::Network network_;
};

}  // namespace game