/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 15;       /* default gap between windows in pixels */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int barheight          = 30;       /* 0 means default height */
static const char *fonts[]          = {
	"Hack:style=Regular:pixelsize=11.5:antialias=true:autohint=true"
};
static const char dmenufont[]       = {
	"Hack:style=Regular:pixelsize=11.5:antialias=true:autohint=true"
};

#define COL_GHOST_WHITE "#f8f8ff"
#define COL_PINK "#ffa8ef"
#define COL_AQUA "#a8efff"
#define COL_BLACK "#000000"

static const char col_inctv_bar[]     = COL_GHOST_WHITE; /* inactive bar bg */
static const char col_inctv_win[]     = COL_PINK; /* inactive window border */
static const char col_inctv_font[]    = COL_BLACK; /* inactive font */
static const char col_actv_font[]     = COL_BLACK; /* active font */
static const char col_actv_bar[]      = COL_GHOST_WHITE; /* active bar bg */
static const char col_actv_win[]      = COL_AQUA; /* active window border */
/* colors specifically for the bar */
static const char col_bar_actv_font[] = COL_PINK; /* specificly for the bar */
static const char col_bar_actv_bar[]  = COL_AQUA; /* specificly for the bar */

static const char *colors[][3]        = {
	/*               fg                  bg                 border   */
	[SchemeNorm] = { col_inctv_font,     col_inctv_bar,     col_inctv_win },
	[SchemeSel]  = { col_actv_font,      col_actv_bar,      col_actv_win  },
	[SchemeBar]  = { col_bar_actv_font,  col_bar_actv_bar,  NULL },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      monoclesmall },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[1] = "0"; /* component of dmenucmd, manipulated in spawn() */
                                                                                     /* col_inctv_bar,        col_inctv_font,        col_actv_bar,    col_actv_font */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_inctv_bar, "-nf", col_inctv_font, "-sb", COL_PINK, "-sf", col_actv_font, NULL };
static const char *termcmd[]  = { "st", "tmux.sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|AltMask,               XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|AltMask,               XK_x,      spawn,          {.v = termcmd } },
	{ MODKEY|AltMask|ControlMask,   XK_x,      spawn,          SHCMD("tmux.sh has 2> /dev/null && st tmux.sh attach") },
	{ MODKEY|AltMask,               XK_c,      spawn,          SHCMD("st tmux.sh new $SHELL -ic lf") },
	{ MODKEY|AltMask|ControlMask,   XK_m,      spawn,          SHCMD("st Music.sh") },
	{ MODKEY|AltMask,               XK_d,      spawn,          SHCMD("firefox.sh p") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_o,      setmfact,       {.f = 1.5} },
	{ MODKEY,                       XK_Return, zoom,           {-1} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|AltMask,               XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -2 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
