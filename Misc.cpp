#include "Main.h"
#include "offsets.h"
#include "Antiaim.h"
#include "Autowall.h"
#include "BackTrack.h"
#include "Visuals.h"
Globals* g_Globals = new Globals();
DEBUG* g_DEBUG = new DEBUG();
Utils* g_Utils = new Utils();
ImGuiRendering* g_ImRender = new ImGuiRendering();
CVars* g_Vars = new CVars();
antiaim* G_Antiaim = new antiaim();
CAutowall* G_Autowall = new CAutowall();
LagCompensation* LagComp = new LagCompensation();
ESP* Visuals = new ESP();