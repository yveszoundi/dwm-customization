/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:style=Regular:size=11" };
static const char dmenufont[]       = "-*-terminus-bold-r-*-*-11-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#282c34";
static const char normbgcolor[]     = "#282c34";
static const char normfgcolor[]     = "#c8ccd4";
static const char selbordercolor[]  = "#be5046";
static const char selbgcolor[]      = "#be5046";
static const char selfgcolor[]      = "#c8ccd4";

static const char *colors[][3]      = {
	/*               fg           bg               border         */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor    },
	[SchemeSel]  = { selfgcolor, selbgcolor     , selbordercolor },
};


/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    { "Firefox",  NULL,       NULL,       1 << 1,       False,        -1 },                             
	/* { "Chromium", NULL,       NULL,       1 << 1,       1,        -1 }, */
	/* { "Firefox",  NULL,       NULL,       0,            1,        -1 }, */
	 /* { "Vlc",      NULL,       NULL,       0,            1,        -1 } */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define PREFIX_MODKEY ControlMask
#define PREFIX_KEYSYM XK_t

#define TAGKEYS(KEY,TAG) \
	{ None,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask,                KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ShiftMask,                  KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ControlMask | ShiftMask,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]         = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, \
				  "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]          = { "st", NULL };
static const char *rclip_copycmd[]    = { "clipboard-cli-copy", NULL };
static const char *rclip_pastecmd[]   = { "clipboard-cli-paste", NULL };
static const char *zoomcmd[]          = { "boomer", NULL };
static const char *lockcmd[]          = { "slock", NULL };
static const char *volmutecmd[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[]         = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldncmd[]         = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *print_screen_cmd[] = { "/bin/bash", "-c", "img=$HOME/Pictures/`date +%Y_%m_%d_%H_%M_%S`.png; import $img; cat $img | xclip -selection clipboard -t image/png", NULL};

/* Multimedia keys - check keys values using 'xev' */
#define XF86AudioMute			0x1008ff12
#define XF86AudioLowerVolume	0x1008ff11
#define XF86AudioRaiseVolume	0x1008ff13

static Key keys[] = {
	/* modifier      key                     function        argument */
    { 0,		     XF86AudioMute,          spawn,          {.v = volmutecmd } },
	{ 0,	         XF86AudioRaiseVolume,   spawn,          {.v = volupcmd } },
    { 0,             XF86AudioLowerVolume,   spawn,          {.v = voldncmd } },
	{ None,          XK_Return,              spawn,          {.v = dmenucmd } },
	{ None,          XK_c,                   spawn,          {.v = termcmd } },
	{ ShiftMask,     XK_c,                   spawn,          {.v = rclip_copycmd } },
	{ ShiftMask,     XK_v,                   spawn,          {.v = rclip_pastecmd } },    
	{ None,          XK_b,                   togglebar,      {0} },
	{ None,          XK_n,                   focusstack,     {.i = +1 } },
	{ None,          XK_p,                   focusstack,     {.i = -1 } },
	{ None,          XK_bracketright,        incnmaster,     {.i = +1 } },
	{ None,          XK_bracketleft,         incnmaster,     {.i = -1 } },
	{ ShiftMask,     XK_bracketleft,         setmfact,       {.f = -0.05} },
	{ ShiftMask,     XK_bracketright,        setmfact,       {.f = +0.05} },
	{ None,          XK_grave,               zoom,           {0} },
	{ None,          XK_v,                   view,           {0} },
	{ None,          XK_k,                   killclient,     {0} },
 	{ None,          XK_l,                   spawn,          {.v = lockcmd } },
 	{ None,          XK_z,                   spawn,          {.v = zoomcmd } },
  { 0,             XK_Print,               spawn,          {.v = print_screen_cmd } },
	{ None,          XK_t,                   setlayout,      {.v = &layouts[0]} },
	{ None,          XK_f,                   setlayout,      {.v = &layouts[1]} },
	{ None,          XK_m,                   setlayout,      {.v = &layouts[2]} },
	{ None,          XK_space,               setlayout,      {0} },
	{ ShiftMask,     XK_space,               togglefloating, {0} },
	{ None,          XK_0,                   view,           {.ui = ~0 } },
	{ ShiftMask,     XK_0,                   tag,            {.ui = ~0 } },
	{ None,          XK_j,                   focusmon,       {.i = -1 } },
	{ None,          XK_period,              tagmon,         {.i = -1 } },
	{ None,          XK_q,                   quit,           {0} },
	TAGKEYS(         XK_1,                   0)
	TAGKEYS(         XK_2,                   1)
	TAGKEYS(         XK_3,                   2)
	TAGKEYS(         XK_4,                   3)
	TAGKEYS(         XK_5,                   4)
	TAGKEYS(         XK_6,                   5)
	TAGKEYS(         XK_7,                   6)
	TAGKEYS(         XK_8,                   7)
	TAGKEYS(         XK_9,                   8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         ControlMask,    Button1,        movemouse,      {0} },
	{ ClkClientWin,         ControlMask,    Button2,        togglefloating, {0} },
	{ ClkClientWin,         ControlMask,    Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            ControlMask,    Button1,        tag,            {0} },
	{ ClkTagBar,            ControlMask,    Button3,        toggletag,      {0} },
};

