#include "uGridLayout.h"
#include "uDebugPrinter.h"
#include "uGridObjectFactory.h"

#include <string>

using namespace std;

uGridLayout::uGridLayout(QObject *parent) : QObject(0)
{

}

uGridLayout::uGridLayout(int width, int height) : QObject(0)
{
    mWidth = width;
    mHeight = height;
}

bool uGridLayout::addClass(int i, int j, int width, int height, const QString &name)
{
    uDebugPrinter::printText("adding class: " + name.toStdString() + " index i: " + to_string(i) + " index j: " + to_string(j));
    if (!checkBounds(i,j,width, height)) return false;

    mTable.push_back(uGridObjectFactory::createClass(i ,j ,width ,height ,name));

    return true;
}


bool uGridLayout::removeObject(const QString &name)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            mTable.erase(iter);
            return true;
        }
    }
    return false;
}

bool uGridLayout::removeObject(int x, int y)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x,y)) {
            mTable.erase(iter);
            return true;
        }
    }
    return false;
}

bool uGridLayout::changeObjectName(const QString &name, const QString &newName)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            (*iter)->setName(newName);
            return true;
        }
    }
    return false;
}

bool uGridLayout::moveObject(const QString &name, int newX, int newY)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            if(checkBounds((*iter)->getX() + newX, (*iter)->getY() + newY, (*iter)->getWidth(), (*iter)->getHeight())){
                (*iter)->setY((*iter)->getY() + newY);
                (*iter)->setX((*iter)->getX() + newX);
                return true;
            }
        }
    }

    return false;
}

bool uGridLayout::createAggregation(const QString &aggregationName, const QString &name)
{

    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++)
    {
        if((*iter)->equals(aggregationName, name, uAggregation))
            return false;
    }

    mArrows.push_back(new uGridArrow(aggregationName, name, uAggregation));
    return true;
}

bool uGridLayout::createInheritance(const QString &name, const QString &parent)
{
    for(TGridArrowConstIter iter=mArrows.begin(); iter != mArrows.end(); iter++)
    {
        if((*iter)->equals(name, parent, uInheritance))
            return false;
    }

    mArrows.push_back(new uGridArrow(name, parent, uInheritance));
    return true;
}

int uGridLayout::getAggregationIndex(const QString &name, const QString &reference) const
{
    for(unsigned int i = 0; i < mArrows.size(); i++)
    {
        if(mArrows[i]->equals(name, reference, uAggregation))
            return i;
    }

    return -1;
}

int uGridLayout::getInheritanceIndex(const QString &name, const QString &reference) const
{
    for(unsigned int i = 0; i < mArrows.size(); i++)
    {
        if(mArrows[i]->equals(name, reference, uInheritance))
            return i;
    }

    return -1;
}

void uGridLayout::addSegmentToArrow(int arrowIndex, int mX, int mY, int mWidth, int mHeight) const
{
    mArrows[arrowIndex]->addSegment(uGridObjectFactory::createSegment(mX, mY, mWidth, mHeight));
}


QString uGridLayout::getString(int x, int y) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x, y)) {
            return (*iter)->getName();
        }
    }
    return "";
}

int uGridLayout::getWidth() const
{
    return mWidth;
}

int uGridLayout::getHeight() const
{
    return mHeight;
}

int uGridLayout::getArrowsSize() const
{
    return mArrows.size();
}

int uGridLayout::getArrowSize(int index) const
{
    return mArrows[index]->getSize();
}

bool uGridLayout::setWidth(int width)
{
    if (width < 0) return false;
    mWidth = width;
    //uDebugPrinter::printText("Set grid width: " + to_string(width));
    return true;
}

bool uGridLayout::setHeight(int height)
{
    if (height < 0) return false;
    mHeight = height;
    //uDebugPrinter::printText("Set grid height: " + to_string(height));
    return true;
}

bool uGridLayout::setPrinted(const QString &name)
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            (*iter)->setPrinted(true);
            return true;
        }
    }
    return false;
}

int uGridLayout::getX(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getX();
        }
    }
    return -1;
}

int uGridLayout::getY(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter)->getY();
        }
    }
    return -1;
}

int uGridLayout::getSegmentX(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getX();
}

int uGridLayout::getSegmentY(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getY();
}

int uGridLayout::getSegmentWidth(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getWidth();
}

int uGridLayout::getSegmentHeight(int arrowIndex, int segIndex) const
{
    return mArrows[arrowIndex]->getSegment(segIndex)->getHeight();
}

bool uGridLayout::isEmpty(int x, int y) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->selected(x, y)) {
            return false;
        }
    }
    return true;
}

bool uGridLayout::contains(const QString &name) const
{
    for(TGridClassConstIter iter=mTable.begin(); iter != mTable.end(); iter++) {
        if ((*iter)->getName() == name) {
            return true;
        }
    }
    return false;
}

bool uGridLayout::checkBounds(int i, int j, int width, int height) const
{
    return (i + width <mWidth && j + height <mHeight && i>=0 && j >= 0);
}

bool uGridLayout::checkBounds(int i, int j) const
{
    return (i <mWidth && j <mHeight && i>=0 && j >= 0);
}


