/*
 * BtLineEdit.h is part of Brewtarget, and is Copyright the following
 * authors 2009-2021:
 * - Matt Young <mfsy@yahoo.com>
 * - Mik Firestone <mikfire@gmail.com>
 * - Philip Greggory Lee <rocketman768@gmail.com>
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
#ifndef BTLINEEDIT_H
#define BTLINEEDIT_H

#include <QLineEdit>
#include <QString>
#include <QWidget>

#include "Unit.h"

class BtGenericEdit;
class BtMassEdit;
class BtVolumeEdit;
class BtTemperatureEdit;
class BtTimeEdit;
class BtDensityEdit;
class BtColorEdit;
class BtMixedEdit;
class BtDiastaticPowerEdit;
class BtStringEdit;
class NamedEntity;

/*!
 * \class BtLineEdit
 *
 * \brief This extends QLineEdit such that the Object handles all the unit
 * transformation we do, instead of each dialog. It makes the code much
 * nicer and prevents more cut'n'paste code.
 *
 */
class BtLineEdit : public QLineEdit
{
   Q_OBJECT
   Q_PROPERTY( int     type              READ type              WRITE setType              STORED false)
   Q_PROPERTY( QString configSection     READ configSection     WRITE setConfigSection     STORED false)
   Q_PROPERTY( QString editField         READ editField         WRITE setEditField         STORED false)
   Q_PROPERTY( QString forcedUnit        READ forcedUnit        WRITE setForcedUnit        STORED false)
   Q_PROPERTY( QString forcedScale       READ forcedScale       WRITE setForcedScale       STORED false)

public:

   /*! \brief Initialize the BtLineEdit with the parent and do some things with the type
   * \param parent - QWidget* to the parent object
   * \param lType - the type of label: none, gravity, mass or volume
   * \param maximalDisplayString - an example of the widest string this widget would be expected to need to display
   * \return the initialized widget
   * \todo Not sure if I can get the name of the widget being created.
   *       Not sure how to signal the parent to redisplay
   */

   BtLineEdit(QWidget* parent = nullptr, Unit::UnitType type = Unit::None, QString const & maximalDisplayString = "100.000 L");
   double toSI(Unit::unitDisplay oldUnit = Unit::noUnit, Unit::unitScale oldScale = Unit::noScale, bool force = false);
   // Use this when you want to do something with the returned QString
   QString displayAmount( double amount, int precision = 3);

   // Use one of these when you just want to set the text
   void    setText( NamedEntity* element, int precision=3 );
   void    setText( double amount, int precision = 3);
   void    setText( QString amount, int precision=3 );
   void    setText( QVariant amount, int precision=3 );

   // Too many places still use getDouble, which just hoses me down. We're
   // gonna fix this.
   double  toDouble(bool* ok);

   // By defining the setters/getters, we can remove the need for
   // initializeProperties.
   QString editField() const;
   void setEditField( QString editField );

   QString configSection();
   void setConfigSection( QString configSection );

   int type() const;
   void setType(int type);

   QString forcedUnit() const;
   void setForcedUnit(QString forcedUnit);

   QString forcedScale() const;
   void setForcedScale(QString forcedScale);

public slots:
   void onLineChanged();
   void lineChanged(Unit::unitDisplay oldUnit, Unit::unitScale oldScale);

signals:
   void textModified();

private:
   void calculateDisplaySize(QString const & maximalDisplayString);
   void setDisplaySize(bool recalculate = false);
   int desiredWidthInPixels;

protected:
   QWidget *btParent;
   QString _section, _editField;
   Unit::UnitType _type;
   Unit::unitDisplay _forceUnit;
   Unit::unitScale _forceScale;
   Unit const * _units;

};

class BtGenericEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtGenericEdit(QWidget* parent = nullptr);
};

class BtMassEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtMassEdit(QWidget* parent = nullptr);
};

class BtVolumeEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtVolumeEdit(QWidget* parent = nullptr);
};

class BtTemperatureEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtTemperatureEdit(QWidget* parent = nullptr);
};

class BtTimeEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtTimeEdit(QWidget* parent = nullptr);
};

class BtDensityEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtDensityEdit(QWidget* parent = nullptr);
};

class BtColorEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtColorEdit(QWidget* parent = nullptr);
};

class BtStringEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtStringEdit(QWidget* parent = nullptr);
};

// mixed objects are a pain.
class BtMixedEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtMixedEdit(QWidget* parent = nullptr);

public slots:
   void setIsWeight(bool state);

};

class BtDiastaticPowerEdit : public BtLineEdit
{
   Q_OBJECT

public:
   BtDiastaticPowerEdit(QWidget* parent = nullptr);
};

#endif
