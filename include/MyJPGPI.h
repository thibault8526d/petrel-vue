#ifndef _MYJPGPI_H_
#define _MYJPGPI_H_

#include <wx/wx.h>
#include <ocpn_plugin.h>

class MyJPGPI : public opencpn_plugin_116
{
public:
    MyJPGPI(void *ppimgr);
    ~MyJPGPI() override;

    int Init() override;
    bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp) override;

private:
    wxImage m_image;         // image chargée
    double  m_ulLat, m_ulLon;// coin haut‑gauche
    double  m_lrLat, m_lrLon;// coin bas‑droit
    bool    LoadWorldFile(const wxString &path);
};

#endif // _MYJPGPI_H_
