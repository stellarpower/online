/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 100 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <config.h>
#include <string>
#include <unordered_set>
#include "ConfigUtil.hpp"
#include "Util.hpp"
#include "CommandControl.hpp"

namespace CommandControl
{

bool FreemiumManager::_isFreemiumUser = false;
std::unordered_set<std::string> FreemiumManager::FreemiumDenyList;
std::string FreemiumManager::FreemiumDenyListString;

FreemiumManager::FreemiumManager() {}

void FreemiumManager::generateDenyList()
{
#ifdef ENABLE_FREEMIUM

    FreemiumDenyListString = config::getString("freemium.disabled_commands", "");
    Util::trim(FreemiumDenyListString);
    StringVector commandList = Util::tokenize(FreemiumDenyListString);

    std::string command;
    for (std::size_t i = 0; i < commandList.size(); i++)
    {
        // just an extra check to make sure any whitespace does not sniff in command
        // or else command will not be recognized
        command = Util::trim_whitespace(commandList[i]);
        if(!command.empty())
        {
            FreemiumDenyList.emplace(command);
        }
    }
#endif
}

const std::unordered_set<std::string>& FreemiumManager::getFreemiumDenyList()
{
    if (FreemiumDenyList.empty())
        generateDenyList();

    return FreemiumDenyList;
}

const std::string FreemiumManager::getFreemiumDenyListString()
{
    if (FreemiumDenyListString.empty())
        generateDenyList();

    return FreemiumDenyListString;
}


bool RestrictionManager::_isRestrictedUser = false;
std::unordered_set<std::string> RestrictionManager::RestrictedCommandList;
std::string RestrictionManager::RestrictedCommandListString;

RestrictionManager::RestrictionManager() {}

void RestrictionManager::generateRestrictedCommandList()
{
#ifdef ENABLE_FEATURE_RESTRICTION
    RestrictedCommandListString = config::getString("restricted_commands", "");
    Util::trim(RestrictedCommandListString);
    StringVector commandList = Util::tokenize(RestrictedCommandListString);

    std::string command;
    for (std::size_t i = 0; i < commandList.size(); i++)
    {
        // just an extra check to make sure any whitespace does not sniff in command
        // or else command will not be recognized
        command = Util::trim_whitespace(commandList[i]);
        if(!command.empty())
        {
            RestrictedCommandList.emplace(command);
        }
    }
#endif
}

const std::unordered_set<std::string>& RestrictionManager::getRestrictedCommandList()
{
    if (RestrictedCommandList.empty())
        generateRestrictedCommandList();

    return RestrictedCommandList;
}

const std::string RestrictionManager::getRestrictedCommandListString()
{
    if (RestrictedCommandListString.empty())
        generateRestrictedCommandList();

    return RestrictedCommandListString;
}
} // namespace CommandControl

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
