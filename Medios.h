#ifndef __MEDIOS_H__
#define __MEDIOS_H__

#include "util.h"

struct Info{
    TS  name_ID;
    TD  rating;
    TS  genre;
    struct Date{
        TI day, month, year;
    }release;
};

class Channel{
protected:
    Info detalles;

public:
    Channel ();
    Channel(const Info& fill) : detalles(fill) {} //Constructor por parametro
    virtual ~Channel();

    TD GetRating() const;
    TS GetGenre() const;
    TS GetNameId() const;

    virtual void add_info(istream& entrada);
    virtual void writeBin(ostream& os) const;
    virtual void readBin(istream& is);

    //template <typename U>//para que el template
    friend ostream& operator<<(ostream& os, const Channel& canal);
};

#endif //__MEDIOS_H__