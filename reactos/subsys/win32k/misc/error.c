/*
 *  ReactOS W32 Subsystem
 *  Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/* $Id: error.c,v 1.7.14.2 2004/11/23 01:57:22 weiden Exp $
 *
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * PURPOSE:          Errors
 * FILE:             subsys/win32k/misc/error.c
 * PROGRAMER:        Casper S. Hornstrup (chorns@users.sourceforge.net)
 * REVISION HISTORY:
 *       06-06-2001  CSH  Created
 */
#include <ddk/ntddk.h>
#include <ddk/ntpoapi.h>
#include <win32k/debug.h>
#include <internal/ps.h>


VOID INTERNAL_CALL
SetLastWin32Error(DWORD Status)
{
  PTEB Teb = PsGetCurrentThread()->Tcb.Teb;

  if (NULL != Teb)
    {
      Teb->LastErrorValue = Status;
    }
}

VOID INTERNAL_CALL
SetLastNtError(NTSTATUS Status)
{
  SetLastWin32Error(RtlNtStatusToDosError(Status));
}

NTSTATUS INTERNAL_CALL
GetLastNtError()
{
  // FIXME - not 100% sure this is correct
  PTEB Teb = PsGetCurrentThread()->Tcb.Teb;

  if ( NULL != Teb )
    {
      return Teb->LastStatusValue;
    }
  return 0;
}

/* EOF */
