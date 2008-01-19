/***************************************************************************
 *   Copyright (C) 2005-08 by the Quassel IRC Team                         *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "coreusersettings.h"

CoreUserSettings::CoreUserSettings(UserId uid) : CoreSettings(QString("CoreUser/%1").arg(uid.toInt())), user(uid) {


}

void CoreUserSettings::storeIdentity(const Identity &identity) {
  setLocalValue(QString("Identities/%1").arg(identity.id().toInt()), QVariant::fromValue<Identity>(identity));
}

void CoreUserSettings::removeIdentity(const Identity &identity) {
  removeLocalKey(QString("Identities/%1").arg(identity.id().toInt()));
}

Identity CoreUserSettings::identity(IdentityId id) {
  QVariant v = localValue(QString("Identities/%1").arg(id.toInt()));
  if(qVariantCanConvert<Identity>(v)) {
    return v.value<Identity>();
  }
  return Identity();
}

QList<IdentityId> CoreUserSettings::identityIds() {
  QList<IdentityId> res;
  foreach(QString id, localChildKeys("Identities")) {
    res << id.toInt();
  }
  return res;
}

QVariantMap CoreUserSettings::sessionData() {
  QVariantMap res;
  foreach(QString key, localChildKeys(QString("SessionData"))) {
    res[key] = localValue(QString("SessionData/%1").arg(key));
  }
  return res;
}

void CoreUserSettings::setSessionValue(const QString &key, const QVariant &data) {
  setLocalValue(QString("SessionData/%1").arg(key), data);
}

QVariant CoreUserSettings::sessionValue(const QString &key, const QVariant &def) {
  return localValue(QString("SessionData/%1").arg(key), def);
}

