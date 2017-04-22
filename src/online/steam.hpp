//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2017 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_STEAM_HPP
#define HEADER_STEAM_HPP

#ifdef WIN32
#  include <windows.h>
#endif

#include <string>
#include <vector>

/** This class provides a simple interface to the SteamWorks API. Due to 
 *  our current license, the SteamWorks lib can not be linked with STK.
 *  So this wrapper class actually starts a seprate process (ssm, see
 *  https://github.com/hiker/steam-synchron-manager) and communicats
 *  with the SSM using pipes.
 */
class Steam
{
private:
    /** True if a connection to steam was made successfully. */
    bool m_steam_available;

    /** Steam user name. Only defined if m_steam_available. */
    std::string m_user_name;

    /** Unique steam id. */
    std::string m_steam_id;

#ifdef WIN32
    // Various handles for the window pipes
    HANDLE m_child_stdin_read;
    HANDLE m_child_stdin_write;
    HANDLE m_child_stdout_read;
    HANDLE m_child_stdout_write;

    bool createChildProcess();
#endif

    std::string decodeString(const std::string &s);
    std::string sendCommand(const std::string &command);
    std::string getLine();
public:
     Steam();
    ~Steam();
    const std::string& getUserName();
    const std::string& getSteamID();
    int saveAvatarAs(const std::string &filename);
    std::vector<std::string> getFriends();
    // ------------------------------------------------------------------------
    /** Returns true if the connection to the Steam API was successful, i.e.
     *  connection to steam worked, and SteamWorks API could be initialised. */
    bool isSteamAvailable() const { return m_steam_available;  }
};   // class Steam

#endif // HEADER_STEAM_HPP
