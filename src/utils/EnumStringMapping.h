/*
 * utils/EnumStringMapping.h is part of Brewtarget, and is Copyright the following
 * authors 2021
 * - Matt Young <mfsy@yahoo.com>
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UTILS_ENUMSTRINGMAPPING_H
#define UTILS_ENUMSTRINGMAPPING_H
#pragma once

#include <optional>

#include <QString>
#include <QVector>

/**
 * \brief Associates an enum value with a string representation (eg in the DB or BeerXML or BeerJSON).  Storing a
 *        string is in some cases required by the external serialisation but, even for "internal" storage in the DB,
 *        is more robust than just storing the raw numerical value of the enum.
 */
struct EnumAndItsString {
   QString string;
   int     native;
};

/**
 * \class EnumStringMapping
 *
 *        We don't actually bother creating hashmaps or similar between enum values and string representations
 *        because it's usually going to be a short list that we can search through pretty quickly (probably faster
 *        than calculating the hash of a key!)
 */
class EnumStringMapping : public QVector<EnumAndItsString> {
public:
   // We're not adding data members so we can just use the base class constructors
   using QVector::QVector;

   std::optional<int>     stringToEnum(QString const & stringValue) const;
   std::optional<QString> enumToString(int const       enumValue) const;
};

#endif
