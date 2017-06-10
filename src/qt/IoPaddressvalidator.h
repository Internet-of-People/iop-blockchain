// Copyright (c) 2011-2014 The Bitcoin Core developers 
// Copyright (c) 2017 IoP Ventures LLC

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef IoP_QT_IoPADDRESSVALIDATOR_H
#define IoP_QT_IoPADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class IoPAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit IoPAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** IoP address widget validator, checks for a valid IoP address.
 */
class IoPAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit IoPAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // IoP_QT_IoPADDRESSVALIDATOR_H
