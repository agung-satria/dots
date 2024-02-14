/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 	= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabCycleKey2 	= 0x31;	/* grave key */
static const unsigned int tabPosY 			= 1;	  /* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	  /* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 200;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 2;        /* snap pixel */
static const unsigned int gappih    = 20;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#770000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3  },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "100x25", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spfm", "-g", "100x25", "-e", "lfub", NULL };
const char *spcmd3[] = { TERMINAL, "-n", "spmus", "-g", "100x25", "-e", "ncmpcpp", NULL };
const char *spcmd4[] = { "galculator", NULL };
const char *spcmd5[] = { "crow", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",        spcmd2},
  {"spmus",       spcmd3},
  {"spcalc",      spcmd4},
  {"spcrow",      spcmd5},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class          instance    title     tags mask    isfloating  monitor */
  { "float-st",	    NULL,			  NULL,		  0,           1,			    -1 },
  { "xdman-Main",   NULL,			  NULL,		  0,           1,			    -1 },
  { "firefox",      NULL,			  NULL,		  1 << 1,	 	   0,			    -1 },
  { "TelegramDesktop",NULL,	    NULL,		  1 << 3,	 	   0,			    -1 },
  { "Gimp",	        NULL,			  NULL,		  1 << 5,      0,			    -1 },
  { "Inkscape",	    NULL,			  NULL,		  1 << 6,      0,			    -1 },
  { "obs",	        NULL,			  NULL,		  1 << 7,      0,			    -1 },
  { TERMCLASS,	    "spterm",		NULL,		  SPTAG(0),	   1,			    -1 },
  { TERMCLASS,	    "spfm",		  NULL,		  SPTAG(1),	   1,			    -1 },
  { TERMCLASS,	    "spmus",		NULL,		  SPTAG(2),	   1,			    -1 },
  { "Galculator",   "galculator",NULL,    SPTAG(3),	   1,			    -1 },
  { "crow-translate","AppRun.wrapped",NULL,SPTAG(4),   1,			    -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include <X11/XF86keysym.h>
#include "movestack.c"
// #include "cycletag.c"
#include "shiftview.c"
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "===",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define XF86MonBrightnessDown 0x1008ff03
#define XF86MonBrightnessUp 0x1008ff02
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,       view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,       toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,       tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,       toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			                  XK_p,		   spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,			                  XK_d,		   spawn,          {.v = (const char*[]){ "rofi", "-show", "run", NULL } } },
	{ MODKEY,			                  XK_r,		   spawn,          {.v = (const char*[]){ "rofi", "-show", "drun", NULL } } },
	{ MODKEY,			                  XK_Return, spawn,          {.v = (const char*[]){ TERMINAL, NULL } } },
	{ MODKEY|ControlMask,			      XK_Return, spawn,          {.v = (const char*[]){ TERMINAL, "-e", "tmux", "attach", NULL } } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_n,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	// { MODKEY,                       XK_o,      cycletag,       {.i = +1 } },
	// { MODKEY,                       XK_i,      cycletag,       {.i = -1 } },
	{ MODKEY,			                  XK_o,		   shiftview,	     { .i = +1 } },
	{ MODKEY,			                  XK_i,		   shiftview,	     { .i = -1 } },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_s,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ControlMask,           XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_semicolon,setlayout,    {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen,{0} },
  { MODKEY,			                  XK_s,		   togglesticky,	 {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY|ControlMask,           XK_j,      defaultgaps,    {0} },
	{ MODKEY|ControlMask,           XK_k,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_l,      incrgaps,       {.i = +4 } },
	{ MODKEY|ControlMask,           XK_h,      incrgaps,       {.i = -4 } },
  { MODKEY|ControlMask,           XK_n,      incrigaps,      {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_n,      incrigaps,      {.i = -4 } },
  { MODKEY|ControlMask,           XK_m,      incrogaps,      {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_m,      incrogaps,      {.i = -4 } },
  { MODKEY|ControlMask,           XK_y,      incrihgaps,     {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_y,      incrihgaps,     {.i = -4 } },
  { MODKEY|ControlMask,           XK_u,      incrivgaps,     {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_u,      incrivgaps,     {.i = -4 } },
  { MODKEY|ControlMask,           XK_i,      incrohgaps,     {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_i,      incrohgaps,     {.i = -4 } },
  { MODKEY|ControlMask,           XK_o,      incrovgaps,     {.i = +4 } },
  { MODKEY|ControlMask|ShiftMask, XK_o,      incrovgaps,     {.i = -4 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY|ShiftMask,            	XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,            			      XK_e,	     togglescratch,  {.ui = 1 } },
	{ MODKEY,            			      XK_m,	     togglescratch,  {.ui = 2 } },
  { MODKEY,                       XK_apostrophe,togglescratch,{.ui = 3 } },
  { MODKEY,                       XK_slash,  togglescratch,  {.ui = 4 } },
	{ Mod1Mask,             		    XK_Tab,    altTabStart,	   {.i = 1} },
	{ Mod1Mask|ShiftMask,           XK_Tab,    altTabStart,	   {.i = 0} },
  { MODKEY|ControlMask,           XK_minus,  setborderpx,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_equal,  setborderpx,    {.i = +1 } },
	{ MODKEY|ControlMask,           XK_0,      setborderpx,    {.i = 0 } },
	{ MODKEY,			        XK_w,		  spawn,     {.v = (const char*[]){ "firefox", NULL } } },
	{ MODKEY|ShiftMask,   XK_w,		  spawn,     {.v = (const char*[]){ "firefox", "--private-window", NULL } } },
	{ MODKEY|ShiftMask,   XK_e,		  spawn,     {.v = (const char*[]){ "thunar", NULL } } },
	{ MODKEY,			        XK_x,		  spawn,     {.v = (const char*[]){ "slock", NULL } } },
	{ MODKEY,			        XK_v,		  spawn,     {.v = (const char*[]){ "clipmenu", NULL } } },
  { MODKEY,             XK_y,     spawn,     SHCMD("gpick -pso --no-newline | xclip -sel c") },
  { 0, XF86XK_AudioMute,          spawn,     SHCMD("changevol mute; pkill -RTMIN+10 dwmblocks") },
  { 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("changevol up; pkill -RTMIN+10 dwmblocks") },
  { 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("changevol down; pkill -RTMIN+10 dwmblocks") },
  { MODKEY,		      XK_F1,        spawn,     SHCMD("changemicvol mute; pkill -RTMIN+12 dwmblocks") },
  { MODKEY,		      XK_F2,        spawn,     SHCMD("changemicvol down; pkill -RTMIN+12 dwmblocks") },
  { MODKEY,		      XK_F3,        spawn,     SHCMD("changemicvol up; pkill -RTMIN+12 dwmblocks") },
  { 0, XF86MonBrightnessUp,       spawn,     SHCMD("light -A 5") },
  { 0, XF86MonBrightnessDown,     spawn,     SHCMD("light -U 5") },
  { MODKEY,			    XK_F11,		    spawn,     SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
  { MODKEY,			    XK_F4,		    spawn,     SHCMD(TERMINAL " -c float-st -e pulsemixer; pkill -RTMIN+10 dwmblocks && pkill -RTMIN+12 dwmblocks") },
  { MODKEY,         XK_F7,		    spawn,     {.v = (const char*[]){ "redshift-tog", NULL } } },
	{ MODKEY,				  XK_Print,	    spawn,     SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
  { MODKEY|Mod1Mask,XK_n,		      spawn,     {.v = (const char*[]){ TERMINAL, "-c", "float-st", "-e", "nmtui", NULL } } },
  { MODKEY|ShiftMask,XK_r,		    spawn,     {.v = (const char*[]){ TERMINAL, "-c", "float-st", "-g", "125x30", "-e", "btop", NULL } } },
  { 0,			        XK_Print,     spawn,     {.v = (const char*[]){ "flameshot", "gui", NULL } } },
	{ ShiftMask,			XK_Print,	    spawn,     {.v = (const char*[]){ "maimpick", NULL } } },
	// { MODKEY,			    XK_grave,	    spawn,     {.v = (const char*[]){ "dmenuunicode", NULL } } },
	{ MODKEY,			    XK_grave,		  spawn,     {.v = (const char*[]){ "rofi", "-show", "emoji", "-theme", "~/.config/rofi/emoji.rasi", NULL } } },
	{ MODKEY,			    XK_g,	        spawn,     {.v = (const char*[]){ "dmenutodo", NULL } } },
  { MODKEY,			    XK_a,	        spawn,     {.v = (const char*[]){ "dunstctl", "history-pop", NULL } } },
  { MODKEY,			    XK_z,	        spawn,     {.v = (const char*[]){ "dunstctl", "close-all", NULL } } },
	// { MODKEY,		      XK_Escape,		spawn,     {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,				  XK_grave,	    spawn,     SHCMD("~/.config/rofi/rofiemoji") },
	{ MODKEY,				  XK_Escape,	  spawn,     SHCMD("~/.config/rofi/rofipowermenu") },
  { MODKEY,			              XK_backslash,		   spawn,  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
  { MODKEY|ShiftMask,	        XK_backslash,		   spawn,  {.v = (const char*[]){ "mpc", "stop", NULL } } },
  { MODKEY,			              XK_bracketleft,	   spawn,  {.v = (const char*[]){ "mpc", "prev", NULL } } },
  { MODKEY,			              XK_bracketright,   spawn,  {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY|ShiftMask,			    XK_bracketleft,		 spawn,  {.v = (const char*[]){ "mpc", "seek", "-5", NULL } } },
	{ MODKEY|ControlMask,		    XK_bracketleft,		 spawn,  {.v = (const char*[]){ "mpc", "seek", "-30", NULL } } },
	{ MODKEY|ShiftMask,			    XK_bracketright,	 spawn,  {.v = (const char*[]){ "mpc", "seek", "+5", NULL } } },
	{ MODKEY|ControlMask,		    XK_bracketright,	 spawn,  {.v = (const char*[]){ "mpc", "seek", "+30", NULL } } },
  { MODKEY|ControlMask|ShiftMask,XK_bracketleft, spawn,  {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_q,      quit,           {1} }, /* restart */
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, /* quit */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
  { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
  { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
  { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
  { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
  { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
