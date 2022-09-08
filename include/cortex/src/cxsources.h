/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define LICENSE_C license.c cxcai.c
#define LICENSE_H

#define XDR_C rhoops_xdr.c rcx_xdr.c
#define SHARE_C cxlist.c cxshare.c XDR_C
#define SHARE_H cxmacros.h cxtype.h cxbool.h dll.h cxlist.h

#if HAVE_MOTIF
# define UI_C uixm.c uixm_dialog.c uixm_menu.c uixm_panel.c uixm_panelitems.c \
   uixm_text.c Hyper.c HyperFig.c uixm_help.c Table.c TableLoc.c TableVec.c \
   Rheostat.c cxprofile.c ListTree.c TFolder.c Toolbar.c
# define UI_H uixm.h Hyper.h HyperP.h Table.h TableP.h RheostatP.h Rheostat.h \
   cxprofile.h ListTree.h ListTreeP.h TFolder.h TFolderP.h Toolbar.h ToolbarP.h
#else
# define UI_C
# define UI_H
#endif

#if GRAPHICS
# define GRAPHICS_C cxgraph.c cxg_hdcp.c cxgevent.c cxgcolor.c cxpath_dpy.c \
  cxplane.c cxscene.c cxkeyfrm.c cxg_win.c cxgcontour.c
# define GRAPHICS_CXX cxg_anim.cpp cxgscene.cpp cxg_afr.cpp cxg_asr.cpp \
  cxg_stream.cpp cxg_geom.cpp
# define GRAPHICS_H cxg.h cxscene.h cxg_anim.h cxgscene.h cxg_win.h cxg_afr.h \
    cxg_asr.h cxg_hdcp.h cxg_stream.h cxg_geom.h
#else
# define GRAPHICS_C
# define GRAPHICS_CXX
# define GRAPHICS_H
#endif

#define IMPORT_I /* GLU.imp GL.imp gl.imp   AIX GL GRAPHICS LIBRARIES  */

/* .c and .h files moved to Cortex from Client lib */
#define OLD_CLIENT_C cxpoly.c
#define OLD_CLIENT_H cxpoly.h

#ifdef WORKING_CXX
# define TRACE_H /*cxstacktrace.h*/
# define TRACE_C /*cxstacktrace.cpp*/
# define SERVER_C cxxmain.cpp cxserv.c cxrun.c cxrpcserver.c cxvis.c lcx.c lcxg.c lhoops.c dll.c  cxext_comm.c cxsocket_api.c cxcleanup.c cxxy.c cortexmpc.c \
  UI_C GRAPHICS_C GRAPHICS_CXX LICENSE_C TRACE_C
#else
# define TRACE_H
# define TRACE_C
# define SERVER_C main.c cxserv.c cxrun.c cxrpcserver.c cxvis.c lcx.c lcxg.c lhoops.c dll.c cxext_comm.c cxsocket_api.c cxcleanup.c cxxy.c cortexmpc.c \
  UI_C GRAPHICS_C LICENSE_C TRACE_C
#endif
#define CLIENT_C dll.c cxtree.c cxcf.c cxclient.c cxmptflush.c errsignal.c cxrad.c cxray.c cxrpcclient.c \
  cxsurf.c  cxsrfevl.c cxisosurf.c cxcontour.c cxturbo.c cxndsearch.c TRACE_C OLD_CLIENT_C

#define CXSINGLE_C dll.c cxcf.c cxclient.c cxmptflush.c errsignal.c cxserv.c cxrun.c cxvis.c \
 lcx.c lcxg.c lhoops.c cxlist.c cxsurf.c cxsrfevl.c cxisosurf.c cxcontour.c cxtree.c cortexmpc.c \
 cxturbo.c cxray.c cxrad.c cxshare.c cxndsearch.c OLD_CLIENT_C  cxext_comm.c cxsocket_api.c cxxy.c

#define SINGLE_C CXSINGLE_C UI_C GRAPHICS_C GRAPHICS_CXX LICENSE_C
#define HOST_SINGLE_C CXSINGLE_C cxhost.c cxcleanup.c LICENSE_C

#define XDR_H rcx.h cxconfig.h cxsources.h cxversion.h seem2c.h
#define CLIENT_H dll.h cxtree.h cx.h cxrad.h cxsurf.h cxiface.h cxturbo.h cxcell_table.h cxndsearch.h TRACE_H OLD_CLIENT_H
#define SERVER_H cxserv.h cxext_comm.h cxsocket_api.h cortexmpc.h cxlocalize.h TRACE_H UI_H GRAPHICS_H LICENSE_H SHARE_H

/*parallel*/
#define HOST_F cxhost.c
#define NODE_F cxnodes.c
#define HOST_C dll.c cxtree.c cxcf.c cxclient.c cxmptflush.c errsignal.c cxrpcclient.c cxsurf.c  cxsrfevl.c cxisosurf.c cxcontour.c cxturbo.c cxndsearch.c TRACE_C OLD_CLIENT_C HOST_F
#define NODE_C dll.c cxcf.c cxray.c cxrad.c cxsurf.c cxmptflush.c errsignal.c cxsrfevl.c cxisosurf.c cxcontour.c cxtree.c cxturbo.c cxndsearch.c TRACE_C OLD_CLIENT_C NODE_F

/* inlcude popen.c only for hp platform */
#if _hpux11 || _hpux11_64 || _hpux11_ia64
#define HP_SEEM_C popen.c
#else
#define HP_SEEM_C
#endif

/*seem*/
#define SEEM_C scontin.c schar.c sdump.c cxmptflush.c seval.c sforeign.c sgc.c sgeneric.c sio.c slist.c seem.c sstring.c ssymbol.c svector.c sport.c slogical.c shash.c HP_SEEM_C seem_aas.c
#define SEEM_H lseem.h sprim.h seem.h sdump.h shash.h proto.h seem_aas.h
/*new gui*/
#define GUI_NEW_H cxobject.h cxgui.h
#define GUI_NT_H cx_nt.h cxgui_nt.h cx_nt.rc cx_nt.dlg dibapi.h cxprofile.h cxsplash.h
#define GUI_NEW_C cxobject.cxx cxgui.cxx cxconsole.cxx cxpanel.cxx cxmenu.cxx cxdialog.cxx
#define GUI_NT_C cxpanel_nt.cxx cxpanelitems_nt.cxx cxbitmaps_nt.cxx cxgui_nt.cxx cxconsole_nt.cxx cxmenu_nt.cxx cxdialog_nt.cxx cxsplash.cxx dibutil.c
#ifdef WORKING_CXX
# define SINGLE_NT_C SINGLE_C GUI_NEW_C GUI_NT_C cxprofile.c GRAPHICS_CXX
#else
# define SINGLE_NT_C SINGLE_C GUI_NEW_C GUI_NT_C cxprofile.c
#endif
#define SERVER_NT_C SERVER_C SHARE_C GUI_NEW_C GUI_NT_C cxprofile.c

#if !DEVELOP
#define C_SWITCH_LOW_OPTIMIZE -O0
#define C_SWITCH_MID_OPTIMIZE -O1
#if _lnx86
#define SOURCES_LOW_OPT  cxsurf.o
#define SOURCES_MID_OPT  none.o
#elif _aix51_64
#define SOURCES_MID_OPT  cxisosurf.o
#else
#define SOURCES_LOW_OPT  none.o
#endif
#endif
