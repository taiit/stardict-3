/* 
 * This file part of StarDict - A international dictionary for GNOME.
 * http://stardict.sourceforge.net
 * Copyright (C) 2006 Evgeniy <dushistov@mail.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <glib.h>

#include "sockets.hpp"

#include "dict_client.hpp"

bool DictClient::connect(const char *host, int port)
{
	int sd = Socket::socket();
	if (sd == -1 || !Socket::connect(sd, host, port)) {
		g_warning("Can not connect to %s: %s\n",
			  host, Socket::getErrorMsg().c_str());
		return false;
	}
	if (!Socket::setNonBlocking(sd)) {
		g_warning("Can not turn on not blocking socket mode: %s\n",
			  Socket::getErrorMsg().c_str());
		return false;
	}

	std::string res;
	bool eof;
	if (!Socket::nbRead(sd, res, &eof)) {
		g_warning("Connection read error %s\n",
			  Socket::getErrorMsg().c_str());
		return false;
	}
	g_message("we get: %s\n", res.c_str());
	return true;
}
