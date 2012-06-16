#include "stdafx.h"

#include "io/point.h"
#include "io/segment.h"
#include "io/range.h"
#include "io/rectangle.h"

namespace geom {
namespace structures {

    namespace
    {
        std::istream & skip_char(std::istream & in, char ch)
        {
            char c;
            while ((in >> c) && (c != ch));
            return in;
        }
    }

    std::istream & operator >> (std::istream & in, point_type & pt)
    {
        return skip_char(skip_char(skip_char(in, '(') >> pt.x, ',') >> pt.y, ')');
    }

    std::ostream & operator << (std::ostream & out, point_type const & pt)
    {
        out << "(" << pt.x << ", " << pt.y << ")";
        return out;
    }

    std::ostream & operator << (std::ostream & out, vector_type const & v)
    {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }

    std::istream & operator >> (std::istream & in, segment_type & seg)
    {
        return skip_char(skip_char(skip_char(in, '[') >> seg[0], ',') >> seg[1], ']');
    }

    std::ostream & operator << (std::ostream & out, segment_type const & seg)
    {
        out << "[" << seg[0] << ", " << seg[1] << "]";
        return out;
    }

    std::istream & operator >> (std::istream & in, range_type & r)
    {
        return skip_char(skip_char(skip_char(in, '[') >> r.inf, ',') >> r.sup, ']');
    }

    std::ostream & operator << (std::ostream & out, range_type const & r)
    {
        out << "[" << r.inf << ", " << r.sup << "]";
        return out;
    }

    std::istream & operator >> (std::istream & in, rectangle_type & rect)
    {
        return skip_char(skip_char(skip_char(in, '(') >> rect.x, ',') >> rect.y, ')');
    }

    std::ostream & operator << (std::ostream & out, rectangle_type const & rect)
    {
        out << "(" << rect.x << ", " << rect.y << ")";
        return out;
    }

}}
