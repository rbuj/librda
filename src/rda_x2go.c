/* -*- Mode: C; c-set-style: linux indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* rda_x2go.c - Remote Desktop Awareness for X2Go Sessions

   Copyright (C) 2018 Mike Gabriel
   All rights reserved.

   The RDA Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The RDA Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Mate Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.
 */

#include <config.h>
#include <glib.h>

#include <rda.h>

gboolean
rda_session_is_x2go (void)
{
	if (remote_technology == REMOTE_TECHNOLOGY_X2GO)
		return TRUE;

	if (g_getenv("X2GO_SESSION"))
	{
		remote_technology = REMOTE_TECHNOLOGY_X2GO;
		return TRUE;
	}

	return FALSE;
}

gboolean
rda_session_suspend_x2go(void)
{
	if (!rda_session_is_x2go())
		return FALSE;

	gint std_in, std_out;
	GError * error = NULL;

	const gchar * argv[1];
	argv[0] = "x2gosuspend-session";

	// FIXME: use g_spawn_sync
	g_spawn_async_with_pipes(NULL, /* pwd */
	                         (gchar **)argv,
	                         NULL, /* env */
	                         G_SPAWN_DO_NOT_REAP_CHILD,
	                         NULL, NULL, /* child setup */
	                         NULL,
	                         &std_in,
	                         &std_out,
	                         NULL, /* stderr */
	                         &error); /* error */

	if (error == NULL)
	{
		return TRUE;
	} else {
		// FIXME: Maybe put some error reporting to a higher API level
		//        here...
		return FALSE;
	}
}

gboolean
rda_session_terminate_x2go(void)
{
	if (!rda_session_is_x2go())
		return FALSE;

	gint std_in, std_out;
	GError * error = NULL;

	const gchar * argv[1];
	argv[0] = "x2goterminate-session";

	// FIXME: use g_spawn_sync
	g_spawn_async_with_pipes(NULL, /* pwd */
	                         (gchar **)argv,
	                         NULL, /* env */
	                         G_SPAWN_DO_NOT_REAP_CHILD,
	                         NULL, NULL, /* child setup */
	                         NULL,
	                         &std_in,
	                         &std_out,
	                         NULL, /* stderr */
	                         &error); /* error */

	if (error == NULL)
	{
		return TRUE;
	} else {
		// FIXME: Maybe put some error reporting to a higher API level
		//        here...
		return FALSE;
	}
}