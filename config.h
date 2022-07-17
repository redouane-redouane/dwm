/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 8;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[]  = { "brave", NULL };
static const char *filemgr[]  = { "nemo", NULL };
static const char *screenlock[]  = { "i3lock", "-i", "./white_lion_cub-1366x768.png" };
static const char *shutdown[]  = { "sh", "-c", "scripts/shutdown.sh" };
static const char *reboot[]  = { "sh", "-c", "scripts/reboot.sh" };

static Key keys[] = {
	/* modifier                     key    function        argument */
	{ MODKEY,                       33,    spawn,          {.v = dmenucmd } },      // p
	{ MODKEY,                       36,    spawn,          {.v = termcmd } },       // Return
	{ MODKEY,                       52,    spawn,          {.v = browser } },       // w
	{ MODKEY,                       57,    spawn,          {.v = filemgr } },       // n
	{ MODKEY,                       56,    togglebar,      {0} },                   // b
	{ MODKEY,                       44,    focusstack,     {.i = +1 } },            // j
	{ MODKEY,                       45,    focusstack,     {.i = -1 } },            // k
	{ MODKEY,                       113,   focusstack,     {.i = +1 } },            // Left
	{ MODKEY,                       114,   focusstack,     {.i = -1 } },            // Right
	{ MODKEY,                       31,    incnmaster,     {.i = +1 } },            // i
	{ MODKEY,                       40,    incnmaster,     {.i = -1 } },            // d
	{ MODKEY,                       43,    setmfact,       {.f = -0.05} },          // h
	{ MODKEY,                       46,    setmfact,       {.f = +0.05} },          // l
	{ MODKEY|ShiftMask,             36,    zoom,           {0} },                   // Return
	{ MODKEY,                       23,    view,           {0} },                   // Tab
    { MODKEY|ShiftMask,             44,    aspectresize,   {.i = +24} },            // j
    { MODKEY|ShiftMask,             45,    aspectresize,   {.i = -24} },            // k
    { MODKEY|ShiftMask,             113,   aspectresize,   {.i = +24} },            // Left
    { MODKEY|ShiftMask,             114,   aspectresize,   {.i = -24} },            // Right
	{ MODKEY,                       54,    killclient,     {0} },                   // c
	{ MODKEY,                       28,    setlayout,      {.v = &layouts[0]} },    // t
	{ MODKEY,                       41,    setlayout,      {.v = &layouts[1]} },    // f
	{ MODKEY,                       47,    setlayout,      {.v = &layouts[2]} },    // m
    { MODKEY|ControlMask,           59,    cyclelayout,    {.i = -1 } },            // comma
    { MODKEY|ControlMask,           60,    cyclelayout,    {.i = +1 } },            // period
	{ MODKEY,                       65,    setlayout,      {0} },                   // space
	{ MODKEY|ShiftMask,             65,    togglefloating, {0} },                   // space
	{ MODKEY,                       19,    view,           {.ui = ~0 } },           // 0
	{ MODKEY|ShiftMask,             19,    tag,            {.ui = ~0 } },           // 0
	{ MODKEY,                       59,    focusmon,       {.i = -1 } },            // comma
	{ MODKEY,                       60,    focusmon,       {.i = +1 } },            // period
	{ MODKEY|ShiftMask,             59,    tagmon,         {.i = -1 } },            // comma
	{ MODKEY|ShiftMask,             60,    tagmon,         {.i = +1 } },            // period
	TAGKEYS(                        87,                    0)                       // 1
	TAGKEYS(                        88,                    1)                       // 2
	TAGKEYS(                        89,                    2)                       // 3
	TAGKEYS(                        83,                    3)                       // 4
	TAGKEYS(                        84,                    4)                       // 5
	TAGKEYS(                        85,                    5)                       // 6
	TAGKEYS(                        79,                    6)                       // 7
	TAGKEYS(                        80,                    7)                       // 8
	TAGKEYS(                        81,                    8)                       // 9
	{ MODKEY|ShiftMask,             38,    quit,           {0} },                   // q
	{ MODKEY|ControlMask|ShiftMask, 38,    quit,           {1} },                   // q

    { MODKEY,                       53,    spawn,          {.v = screenlock} },     // x

    { MODKEY|ShiftMask,             39,    spawn,          {.v = reboot} },         // s
    { MODKEY,                       39,    spawn,          {.v = shutdown} },       // s
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

