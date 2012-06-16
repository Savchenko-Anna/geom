#include "visualization/viewer.h"

namespace visualization
{
    struct viewer_adapter : viewer_type
    {
        virtual void print  (printer_type & ) const {};

        virtual void set_window(QWidget * wnd) { wnd_ = wnd; }

        virtual bool on_key         (int)                   { return false; }
        virtual bool on_double_click(point_type const &)    { return false; }
        virtual bool on_move        (point_type const &)    { return false; }
        virtual bool on_press       (point_type const &)    { return false; }
        virtual bool on_release     (point_type const &)    { return false; }

    protected:
        QWidget * get_wnd() const { return wnd_; }

    private:
        QWidget * wnd_;
    };
}
