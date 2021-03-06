/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "Addon.h"

namespace ADDON
{

class CPluginSource : public CAddon
{
public:

  enum Content { UNKNOWN, AUDIO, IMAGE, EXECUTABLE, VIDEO, GAME };

  static std::unique_ptr<CPluginSource> FromExtension(CAddonInfo addonInfo, const cp_extension_t* ext);

  explicit CPluginSource(CAddonInfo addonInfo);
  CPluginSource(CAddonInfo addonInfo, const std::string& provides);

  TYPE FullType() const override;
  bool IsType(TYPE type) const override;
  bool Provides(const Content& content) const
  {
    return content == UNKNOWN ? false : m_providedContent.count(content) > 0;
  }

  bool ProvidesSeveral() const
  {
    return m_providedContent.size() > 1;
  }

  static Content Translate(const std::string &content);
private:
  /*! \brief Set the provided content for this plugin
   If no valid content types are passed in, we set the EXECUTABLE type
   \param content a space-separated list of content types
   */
  void SetProvides(const std::string &content);
  std::set<Content> m_providedContent;
};

} /*namespace ADDON*/
