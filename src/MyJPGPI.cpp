#include "MyJPGPI.h"
#include "worldfile.h"
#include <wx/stdpaths.h>

extern "C" opencpn_plugin *create_pi(void *ppimgr) { return new MyJPGPI(ppimgr); }
extern "C" void destroy_pi(opencpn_plugin *p)     { delete p; }

MyJPGPI::MyJPGPI(void *ppimgr) : opencpn_plugin_116(ppimgr)
{
    m_api_version = OCPN_API_VERSION_MAJOR;
}

MyJPGPI::~MyJPGPI() {}

int MyJPGPI::Init()
{
    // Exemple : charge un JPG + JGW placé dans le dossier data
    wxString base = StandardPath().GetPluginsDataDir() + wxS("myjpgplugin/");
    wxString imgPath = base + wxS("test.jpg");
    wxString wldPath = base + wxS("test.jgw");

    if(m_image.LoadFile(imgPath))
        LoadWorldFile(wldPath);

    AddCanvasOverlay();
    return 0;
}

bool MyJPGPI::LoadWorldFile(const wxString &path)
{
    return ParseWorldFile(path.ToStdString(), m_ulLon, m_ulLat, m_lrLon, m_lrLat);
}

bool MyJPGPI::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    if(!m_image.IsOk())
        return false;

    int xUL, yUL, xLR, yLR;
    GetCanvasPixFromLL(vp, m_ulLat, m_ulLon, &xUL, &yUL);
    GetCanvasPixFromLL(vp, m_lrLat, m_lrLon, &xLR, &yLR);

    int w = abs(xLR - xUL);
    int h = abs(yLR - yUL);

    wxBitmap bmp(m_image.Scale(w, h));
    dc.DrawBitmap(bmp, std::min(xUL, xLR), std::min(yUL, yLR), true);
    return true;
}
